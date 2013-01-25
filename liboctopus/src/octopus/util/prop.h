/*
 * Copyright 2012 Cedric Priscal
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

#ifndef PROP_H_
#define PROP_H_

namespace octopus {
namespace util {

/**
 * Node
 */
class Node {
public:
	Node(const char* name, const char* description = 0) :
			mName(name), mDescription(description) {
	}
	virtual ~Node() {
	}
protected:
	const char* mName;
	const char* mDescription;
};



/**
 * Folder
 */
class Folder: public Node, Set<Folder> {
public:
	Folder(Folder* parent, const char* name, const char* description = 0) :
			Node(name, description), Set<Folder>(), mParent(parent), mFirstSubFolder(0), mFirstFile(0) {
		if (mParent) {
			mParent->registerSubFolder(this);
		}
	}
	virtual ~Folder() {
		if (mParent) {
			mParent->unregisterSubFolder(this);
		}
	}
	void registerSubFolder(Folder* folder) {
		if (!mFirstSubFolder) {
			mFirstSubFolder = folder;
		} else {
			mFirstSubFolder->append(folder);
		}
	}
	void unregisterSubFolder(Folder* folder) {
		if (mFirstSubFolder == folder) {
			mFirstSubFolder = mFirstSubFolder->mNext;
		}
	}
	void registerFile(File* file) {
		if (!mFirstFile) {
			mFirstFile = file;
		} else {
			mFirstFile->append(file);
		}
	}
	void unregisterFile(File* file) {
		if (mFirstFile == file) {
			mFirstFile = mFirstFile->mNext;
		}
	}
protected:
	Folder *mParent;
	Folder *mFirstSubFolder;
	File *mFirstFile;
};

/**
 * File
 */
class File: public Node, public Set<File> {
public:
	File(Folder* parent, const char* name, const char* description = 0) :
			Node(name, description), mParent(parent) {
		if (parent) {
			parent->registerFile(this);
		}
	}
	virtual ~File() {
		if (mParent) {
			mParent->unregisterFile(this);
		}
	}
protected:
	Folder* mParent;
};

template<typename T>
class TFile: File {
public:
	TFile(T value, Folder* parent, const char* name, const char* description = 0) :
			File(parent, name, description), mValue(value) {
	}
	virtual ~TFile() {
	}
	inline T operator =(T value) {
		mValue = value;
		return value;
	}
	inline operator T() {
		return mValue;
	}
private:
	T mValue;
};

} /* util */
} /* octopus */

#endif /* PROP_H_ */
