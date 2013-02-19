#ifndef POOL_H
#define POOL_H

#include "list.h"
#include "lock.h"

namespace octopus {

/**
 * @brief This template defines a pool of elements.
 *
 * The template Pool defines a pool of @a size elements of type @a T.
 * A pool is a list of free elements that can be allocated and
 * released. You can see this template as a replacement for new and
 * delete.
 */
template <class T, int size>
class Pool: private List<T>
{
public:
    // Constructor
    Pool() {
        for (int i = 0; i < size; i++) {
            List<T>::insert(&array[i]);
        }
    }

    /**
     * @brief Gets a free element
     *
     * @return An uninitialized element
     */
    T* get() {
        Lock l;
        T* ret = List<T>::front();
        List<T>::remove(ret);
        return ret;
    }

    /**
     * @brief Releases an element by putting it back in the pool
     *
     * @param desc An element previously allocated with @ref get().
     */
    void release(T* desc) {
        Lock l;
        int index = desc - array;
        if ( (index >= 0) && (index < size) ) {
            List<T>::insert(desc);
        }
    }

private:
    T array[size];
};

} /* namespace octopus */

#endif // POOL_H
