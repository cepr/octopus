
// Blink sample

#include "octopus/looper.h"
#include "octopus/blink.h"

using namespace octopus;

Blink blink(&Looper::instance);

int main(void)
{
    blink.enable();
    Looper::instance.run();
    return 0;
}
