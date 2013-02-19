
# libcomm #

## Presentation ##

`libcomm` handles the communication part of Octopus. This library provides different
levels of services to communicate with a target: you can either simply use an Usart
interface to read and write raw data to/from the device serial port, or use a complete
control and telemetry framework.

## Asynchronous, non-blocking API ##

Like all drivers in Octopus, the serial port driver interface is interrupt driven. It
means that it never stays blocked in a function waiting for a buffer to flush or some
data to arrive on a serial port. Instead you have to provide a listener in order to be
notified when new data is available, and any writing to the port is asynchronous, which
mean that when you ask for the serial port driver to send data, the function returns
before the data to be actually sent.

## Control and telemetry framework ##

The Octopus control and telemetry framework provides a simple and convenient way to
remotely control your target and monitor the state of your target by using the
provided computer software.

### Protocol ###

The protocol of the Octopus control and telemetry framework is explained hereafter:

#### Packets ####

The target and the computer are sending each other messages. Each message is contained
in a packet. The format of a packet is the following:

    ╭──────────┬────────┬──────────┬───────────────────────╮
    │ offset   │ length │ value    │ description           │
    ├──────────┼────────┼──────────┼───────────────────────┤
    │ 0        │ 1      │ '$'      │ Packet start          │
    │ 1        │ 2      │ <size>   │ Message size          │
    │ 3        │ <size> │ <data>   │ Message data          │
    │ 3+<size> │ 1      │ <chksum> │ Message checksum      │
    ╰──────────┴────────┴──────────┴───────────────────────╯

*   Packet start

    Every packet starts with the ASCII character '$'.

*   Message size

    Size of the message, in little-endian. The maximum size of a message is 65535. The
    special value 0xFFFF is reserved for future use.

*   Message data

    Actual content of the message.

*   Message checksum

    The message checksum is computed by adding every single byte of the message data,
    and by keeping only the lower byte of the result.

#### Messages ####

The format of a message depends on its type. The message type is always determined by
its first byte. To simplify debug, this byte is usually taken from the ASCII table.

The list of commands are:

    ╭────────────┬───────┬─────────────────────────────────╮
    │ name       │ value │ description                     │
    ├────────────┼───────┼─────────────────────────────────┤
    │ CMD_ID     │ '?'   │ Request target ID               │
    │ CMD_READ   │ 'R'   │ Read target memory              │
    │ CMD_WRITE  │ 'W'   │ Write target memory             │
    │ CMD_REBOOT │ 'B'   │ Reboot the target               │
    ╰────────────┴───────┴─────────────────────────────────╯

In the following tables, the value `<bus_size>` refers to the address bus size of the
target. For Atmel AVR devices, `<bus_size> == 2`.

1.  `CMD_ID`

    `CMD_ID` can be used to request the ID of a target. The ID of a target is a
    constant associated with a specific firmware. It can be a string with the firmware
    name along with its version or compilation timestamp, or a hash. A target ID
    should be different between each firmware so that the computer can load the
    correct firmware symbols.

        ╭──────────┬────────┬──────────┬───────────────────────╮
        │ offset   │ length │ value    │ description           │
        ├──────────┼────────┼──────────┼───────────────────────┤
        │ 0        │ 1      │ '?'      │ CMD_ID                │
        ╰──────────┴────────┴──────────┴───────────────────────╯

    The target should reply with its target ID.

        ╭──────────┬────────┬─────────────┬───────────────────────╮
        │ offset   │ length │ value       │ description           │
        ├──────────┼────────┼─────────────┼───────────────────────┤
        │ 0        │ 1      │ '?'         │ CMD_ID                │
        │ 1        │ -      │ <target ID> │ Target ID             │
        ╰──────────┴────────┴─────────────┴───────────────────────╯

2.  `CMD_READ`

    `CMD_READ` can be used to read part of the target memory, from a single variable
    to a complete memory dump. The memory part to read is specified by an offset and
    a size. In order to determine the offset and the size of a specific variable, the
    computer software uses the firmware symbol files corresponding to the current
    target ID (see command `CMD_ID`).

        ╭──────────────┬────────────┬──────────┬───────────────────────────────────╮
        │ offset       │ length     │ value    │ description                       │
        ├──────────────┼────────────┼──────────┼───────────────────────────────────┤
        │ 0            │ 1          │ 'R'      │ CMD_READ                          │
        │ 1            │ <bus_size> │ <offset> │ Pointer to the first byte to read │
        │ 1+<bus_size> │ <bus_size> │ <size>   │ Number of bytes to read           │
        ╰──────────────┴────────────┴──────────┴───────────────────────────────────╯

    The target should reply with:

        ╭──────────────┬────────────┬──────────┬───────────────────────────────────╮
        │ offset       │ length     │ value    │ description                       │
        ├──────────────┼────────────┼──────────┼───────────────────────────────────┤
        │ 0            │ 1          │ 'R'      │ CMD_READ                          │
        │ 1            │ <bus_size> │ <offset> │ Pointer to the first read byte    │
        │ 1+<bus_size> │ -          │ <data>   │ Read data                         │
        ╰──────────────┴────────────┴──────────┴───────────────────────────────────╯

    Please note that a target may send that message to report spontaneously the value
    of a variable to the computer. This is why the computer software should check that
    the `<offset>` value which is present in the reply corresponds to the one in the
    command.

3.  `CMD_WRITE`

    `CMD_WRITE` is used to modify part of the target memory.

        ╭──────────┬────────┬──────────┬────────────────────────────────────╮
        │ offset   │ length │ value    │ description                        │
        ├──────────┼────────┼──────────┼────────────────────────────────────┤
        │ 0        │ 1      │ 'W'      │ CMD_WRITE                          │
        │ 1        │ X (*)  │ <offset> │ Pointer to the first byte to write │
        │ 1+X      │ -      │ <data>   │ Number of bytes to write           │
        ╰──────────┴────────┴──────────┴────────────────────────────────────╯

    (*) The size of `<offset>` and `<size>` is equal to the size of the target memory
    address bus, which corresponds to `sizeof(int)`. For Atmel ATMEGA328P, this is
    2 bytes.

        ╭──────────┬────────┬──────────┬───────────────────────────────────╮
        │ offset   │ length │ value    │ description                       │
        ├──────────┼────────┼──────────┼───────────────────────────────────┤
        │ 0        │ 1      │ 'W'      │ CMD_WRITE                         │
        ╰──────────┴────────┴──────────┴───────────────────────────────────╯

    The write reply is a simple aknowledge.

4.  `CMD_REBOOT`

    `CMD_REBOOT` will reset a target device. The target will execute its boot loader,
    allowing you to upgrade the firmware.

        ╭──────────┬────────┬──────────┬───────────────────────────────────╮
        │ offset   │ length │ value    │ description                       │
        ├──────────┼────────┼──────────┼───────────────────────────────────┤
        │ 0        │ 1      │ 'B'      │ CMD_REBOOT                        │
        ╰──────────┴────────┴──────────┴───────────────────────────────────╯

    This command does not return any reply.
