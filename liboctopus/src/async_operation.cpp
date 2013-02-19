
#include "octopus/async_operation.h"
#include "octopus/looper.h"

namespace octopus {

void AsyncOperation::post()
{
    if (looper) {
        Lock l;
        looper->insert(this);
    } else {
        onFinished();
    }
}

} /* namespace octopus */
