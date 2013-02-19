
Octopus Control Panel

Requirements
============

- Operating systems
 - Linux
 - Android
- Communication interfaces
 - Serial port
 - TCP socket
 - stdio
- Gauges
 - toggle button
 - slider
  - horizontal/vertical
  - text field with value
 - 2D scrolling graph
- Layout
 - Tree view
 - Show/hide controls
 - Save & Load layout
- Misc
 - Pause & Fast Reverse even when not recording (ring buffer)
 - Record & Playback
 - Periodic refresh
- Controllers
 - Joystick
 - Mouse
 - Touchscreen, including dual finger
 - Keyboard

Architecture
============

- SFML
 - thread
 - joystick
 - mouse
 - keyboard
 - tcp
 - opengl context
 - network

- libcairomm + glitz + librsvg
 - 2D drawing

