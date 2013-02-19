#ifndef ASYNC_OPERATION_H
#define ASYNC_OPERATION_H

#include "octopus/lock.h"

namespace octopus {

class Looper;

/**
 * @brief The AsyncOperation class
 *
 * This class is the base class for all asynchronous operations.
 */
class AsyncOperation
{
public:

    /**
     * @brief Operation status.
     */
    typedef enum {
        /**
         * @brief This asynchronous operation is idle.
         *
         * This status means that the operation has not been programmed yet, or that
         * the operation has finished. While in this state, you can fully access this
         * instance without taking any Lock. You can use this instance for a new
         * operation.
         */
        STATUS_IDLE,

        /**
         * @brief This asynchronous operation is pending.
         *
         * An operation has been programmed using this instance, but is still in a
         * waiting queue. While in this state, you may still modify this instance
         * attributes (e.g. the data for a write operation) or abort the operation.
         * Please keep in mind that asynchronous operation may be executed in interrupt
         * context, so you should protect your code against concurrency using the class
         * Lock.
         */
        STATUS_PENDING,

        /**
         * @brief This asynchronous operation is currently realized.
         *
         * You shall not access the operation attributes while in this state.
         */
        STATUS_RUNNING
    } Status;

    /**
     * @brief Constructor.
     *
     * @param[in] looper
     *      Looper which should handle the call to onFinished(), or zero if you want
     *      onFinished() to be called directly. Using a Looper is recommended if
     *      onFinished() has to perform a long treatment.
     */
    AsyncOperation(Looper* looper = 0) :
        status(STATUS_IDLE),
        looper(looper),
        prev(0),
        next(0)
    {
    }

    /**
     * @brief Posts this operation to the application looper
     *
     * This method appends the event to the event queue if it is not already pending.
     * The event queue looper will call the method #onFinished() in application context.
     */
    void post();

    /**
     * @brief Callback for finished operation.
     */
    virtual void onFinished() = 0;

    // Current operation status
    Status status;

    // Looper which should call onFinished(), or zero if onFinished() should be called directly in post()
    Looper* looper;

    // For List<AsyncOperation>
    AsyncOperation* prev;
    AsyncOperation* next;
};

} /* namespace octopus */

#endif // ASYNC_OPERATION_H
