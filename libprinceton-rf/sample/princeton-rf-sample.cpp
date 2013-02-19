
// octopus program squeleton

#include "octopus/event/looper.h"

using namespace octopus;

int main(void)
{
    Looper::instance.run();
    return 0;
}
