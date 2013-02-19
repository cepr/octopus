/*
 * Copyright 2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SET_H_
#define SET_H_

namespace octopus {

/**
 * @brief List
 *
 * This template class represents a list of items. Each item is linked with its previous and next items. Unlike
 * the std::list class from STL library, when an item is added to the list, it is not copied, it is just linked.
 * This behavior has the following impacts: each item can only be present only one time in a list, and can be
 * present in only one list.
 *
 * The class T should contain two attributes <code>T* prev</code> and <code>T* next</code>.
 */
template<class T>
class List {

public:
	/**
     * @brief List iterator.
	 */
	class Iterator {
	public:
		/**
         * @brief Default constructor.
         *
         * @param ptr  Pointer to the instance of T that the Iterator will point to.
		 */
		Iterator(T* ptr = 0) : ptr(ptr) {
		}

		/**
         * @brief Indirection operator.
		 *
         * @return
         *  This operator returns the item value pointed by this iterator.
		 */
		T* operator *() {
			return ptr;
		}

		/**
         * @brief Copy constructor.
         *
         * @param[in] that  Iterator to copy.
		 */
		Iterator(const Iterator & that) : ptr(that.ptr) {
		}

		/**
		 * Prefix increment
		 *
		 * This operator update the iterator to point to the next item in the list.
         *
         * @return
         *  This operator returns the incremented iterator.
		 */
		Iterator & operator ++() {
			if (ptr) {
                ptr = static_cast<T*>(ptr->next);
			}
			return *this;
		}

		bool operator ==(const Iterator & that) const {
			return (that.ptr == ptr);
		}

		bool operator !=(const Iterator & that) const {
			return (that.ptr != ptr);
		}

		/**
         * @brief Get iterator validity
		 *
		 * \return This function returns whether it points to an item or not.
		 */
		bool is_valid() const {
			return (ptr != 0);
		}

	private:
		friend class List;
		T* ptr;
	};

	/**
     * @brief Constructor
	 *
	 * This constructor creates an empty list.
	 */
	List() {
	}

	/**
     * @brief Insert an item in the list.
	 *
     * @param[in,out] item  Item to insert.
     * @param[in,out] at    Position where the item should be inserted.
	 *
	 * This function inserts a new item just before \a at. If \a at is not specified,
	 * the item is appended at the end of the list.
	 *
	 * If the item is already in the list, nothing happens, you have to remove it first.
	 *
     * @return
     *  This method returns @a item.
     *
     * @warning
     *  This function is not safe from interrupts.
	 */
	T* insert(T* item, T* at = 0) {
		if ( item && !item->prev && !item->next ) {
			if (at) {
				// not the last element
				item->prev = at->prev;
				at->prev = item;
			} else {
				// last element
				item->prev = last.ptr;
				last.ptr = item;
			}
			item->next = at;
			if (item->prev) {
				// not the first element
				item->prev->next = item;
			} else {
				// first element
				first.ptr = item;
			}
		}
		return item;
	}

    /**
     * @brief Insert another list
     *
     * @param[in,out] list  List to insert.
     * @param[in,out] at    Position where the list should be inserted.
     *
     * This function inserts the items of another list into that list, just before @a at if specified or at
     * the end otherwise.
     *
     * The list @a list will be empty after this call.
     */
    void insert(List<T>* list, T* at = 0) {
        if ( list && list->first.is_valid() ) {
            // First we extract the first and last elements from list
            T* a = list->first.ptr;
            T* b = list->last.ptr;
            list->first.ptr = 0;
            list->last.ptr = 0;

            // Then we insert them in that list
            if (at) {
                // not the last element
                a->prev = at->prev;
                at->prev = b;
            } else {
                // last element
                a->prev = last.ptr;
                last.ptr = b;
            }
            b->next = at;
            if (a->prev) {
                // not the first element
                a->prev->next = a;
            } else {
                // first element
                first.ptr = a;
            }
        }
    }

	/**
     * @brief Remove an item
	 *
     * @param[in,out] item   Item to remove.
	 *
	 * \return This function returns \a item.
	 *
     * @warning This function is not safe from interrupts.
	 */
	T* remove(T* item) {
		if (item) {
			if (item->prev) {
				item->prev->next = item->next;
			} else {
                first.ptr = static_cast<T*>(item->next);
            }
			if (item->next) {
				item->next->prev = item->prev;
			} else {
                last.ptr = static_cast<T*>(item->prev);
			}
			item->prev = 0;
			item->next = 0;
		}
		return item;
	}

    /**
     * @brief Remove all items
     *
     * @warning This function is not safe from interrupts.
     */
    void clear() {
        while(!isEmpty()) {
            remove(front());
        }
    }

	/**
     * @brief Get the first item of the list
	 *
	 * \return This function returns a reference to the first item of the list, or 0 if the list if empty.
	 */
	T* front() {
		return first.ptr;
	}

	/**
     * @brief Get the last item of the list
	 *
	 * \return This function returns a reference to the first item of the list, or 0 if the list if empty.
	 */
	T* back() {
		return last.ptr;
	}

	/**
     * @brief Iterator pointing to the first item of the list
	 *
	 * \return This function returns an iterator pointing to the first element of the list.
	 */
	const Iterator & begin() const {
		return first;
	}

    /**
     * @brief Tels whether the list is empty or not.
     *
     * @return @a true if list is empyt, @a false otherwise.
     */
    bool isEmpty() {
        return (first == 0);
    }

protected:
	Iterator first;
	Iterator last;

private:
	// No copy constructor
	List(const List<T> & from);
};

} /* octopus */

#endif /* SET_H_ */
