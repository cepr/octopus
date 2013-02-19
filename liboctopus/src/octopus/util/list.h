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
namespace util {

/**
 * \brief List
 *
 * This template class represents a list of items. Each item is linked with its previous and next items. Unlike
 * the std::list class from STL library, when an item is added to the list, it is not copied, it is just linked.
 * This behavior has the following impacts: each item can only be present only one time in a list, and can be
 * present in only one list.
 */
template<class T>
class List {

public:
	/**
	 * \brief Item of the list.
	 */
	class Item {
	public:

		/**
		 * \brief Constructor
		 *
		 * The item value is constructed with its default constructor.
		 */
		Item(): value(), prev(0), next(0) {
		}

		/**
		 * \brief Constructor
		 *
		 * \param[in] value  Item value.
		 *
		 * The item value is copied from the given parameter.
		 */
		Item(const T & value): value(value), prev(0), next(0) {
		}

		/**
		 * Item value
		 */
		T value;

	private:
		friend class List;
		Item* prev;
		Item* next;
	};

	/**
	 * \brief List iterator
	 */
	class Iterator {
	public:
		/**
		 * \brief Default constructor
		 */
		Iterator(Item* item = 0) : item(item) {
		}

		/**
		 * \brief Indirection operator
		 *
		 * This operator returns the item value pointed by this iterator.
		 */
		T* operator *() {
			if (item) {
				return &item->value;
			} else {
				return 0;
			}
		}

		/**
		 * Copy constructor
		 */
		Iterator(const Iterator & that) : item(that.item) {
		}

		/**
		 * Prefix increment
		 *
		 * This operator update the iterator to point to the next item in the list.
		 */
		Iterator & operator ++() {
			if (item) {
				item = item->next;
			}
			return *this;
		}

		bool operator ==(const Iterator & that) const {
			return (that.item == item);
		}

		bool operator !=(const Iterator & that) const {
			return (that.item != item);
		}

		/**
		 * \brief Get iterator validity
		 *
		 * \return This function returns whether it points to an item or not.
		 */
		bool is_valid() const {
			return (item != 0);
		}

	private:
		friend class List;
		Item* item;
	};

	/**
	 * \brief Constructor
	 *
	 * This constructor creates an empty list.
	 */
	List() {
	}

	/**
	 * \brief Insert an item
	 *
	 * \param[in,out] item  Item to insert.
	 * \param[in,out] at    Position where the item should be inserted.
	 *
	 * This function inserts a new item just before \a at. If \a at is not specified,
	 * the item is appended at the end of the list.
	 *
	 * If the item is already in the list, nothing happens, you have to remove it first.
	 *
	 * \warning This function is not safe from interrupts.
	 */
	Item* insert(Item* item, Item* at = 0) {
		if ( item && !item->prev && !item->next ) {
			if (at) {
				// not the last element
				item->prev = at->prev;
				at->prev = item;
			} else {
				// last element
				item->prev = last.item;
				last.item = item;
			}
			item->next = at;
			if (item->prev) {
				// not the first element
				item->prev->next = item;
			} else {
				// first element
				first.item = item;
			}
		}
		return item;
	}

	/**
	 * \brief Remove an item
	 *
	 * \param[in,out] item   Item to remove.
	 *
	 * \return This function returns \a item.
	 *
	 * \warning This function is not safe from interrupts.
	 */
	Item* remove(Item* item) {
		if (item) {
			if (item->prev) {
				item->prev->next = item->next;
			} else {
				first.item = item->next;
			}
			if (item->next) {
				item->next->prev = item->prev;
			} else {
				last.item = item->prev;
			}
			item->prev = 0;
			item->next = 0;
		}
		return item;
	}

	/**
	 * \brief Get the first item of the list
	 *
	 * \return This function returns a reference to the first item of the list, or 0 if the list if empty.
	 */
	Item* front() {
		return first.item;
	}

	/**
	 * \brief Get the last item of the list
	 *
	 * \return This function returns a reference to the first item of the list, or 0 if the list if empty.
	 */
	Item* back() {
		return last.item;
	}

	/**
	 * \brief Iterator pointing to the first item of the list
	 *
	 * \return This function returns an iterator pointing to the first element of the list.
	 */
	const Iterator & begin() const {
		return first;
	}

protected:
	Iterator first;
	Iterator last;

private:
	// No copy constructor
	List(const List & from);
};

} /* util */
} /* octopus */

#endif /* SET_H_ */
