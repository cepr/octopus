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

#include <gtest/gtest.h>

#include "octopus/util/list.h"
using octopus::util::List;

TEST(List, Empty) {
	// Create an empty list
	List<int> list;

	// Check that the list is empty
	EXPECT_EQ(0, list.front());
	EXPECT_EQ(0, list.back());
	EXPECT_FALSE(list.begin().is_valid());

	// Insert an item in the list
	List<int>::Item item;
	EXPECT_EQ(&item, list.insert(&item));

	// Check that the list contains the element
	EXPECT_EQ(&item, list.front());
	EXPECT_EQ(&item, list.back());
	List<int>::Iterator it(list.begin());
	EXPECT_TRUE(it.is_valid());
	++it;
	EXPECT_FALSE(it.is_valid());

	// Remove the item from the list
	EXPECT_EQ(&item, list.remove(&item));

	// Check that list is empty again
	EXPECT_EQ(0, list.front());
	EXPECT_EQ(0, list.back());
	EXPECT_FALSE(list.begin().is_valid());
}

TEST(List, InsertAndRemove) {
	// Create an empty list
	List<int> list;

	// Insert two items
	List<int>::Item item1(1);
	List<int>::Item item3(3);
	list.insert(&item1);
	list.insert(&item3);

	// Insert a third one in the middle
	List<int>::Item item2(2);
	list.insert(&item2, &item3);

	// Check result
	List<int>::Iterator it(list.begin());
	ASSERT_TRUE(it.is_valid());
	EXPECT_EQ(1, **it);
	++it;
	ASSERT_TRUE(it.is_valid());
	EXPECT_EQ(2, **it);
	++it;
	ASSERT_TRUE(it.is_valid());
	EXPECT_EQ(3, **it);
	++it;
	ASSERT_FALSE(it.is_valid());

	// Remove the second one
	list.remove(&item2);

	// Check result
	it = list.begin();
	ASSERT_TRUE(it.is_valid());
	EXPECT_EQ(1, **it);
	++it;
	ASSERT_TRUE(it.is_valid());
	EXPECT_EQ(3, **it);
	++it;
	ASSERT_FALSE(it.is_valid());
}

TEST(List, Iterator) {
	// Dereference invalid iterator
	List<int>::Iterator it;
	EXPECT_FALSE(it.is_valid());
	EXPECT_EQ(0, *it);
}
