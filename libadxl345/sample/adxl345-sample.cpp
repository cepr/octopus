
// adxl345 sample

#include "octopus/looper.h"

using namespace octopus;

int main(void)
{
    Looper::instance.run(&Gpio::B5);
    return 0;
}
