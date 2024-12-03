#pragma once
#include <iostream>
#include <stdexcept>
#include "PrimeUtil.h" // for the prime-->getNextPrime method

using namespace std;

// enum to track the status of the table
enum tableStatus // SG
{
	TABLE_NOT_FULL,
	TABLE_FULL
};

enum state
{
	EMPTY,
	FULL,
	DELETED
};

template <class K, class T>
class HashTable
{
protected:
	class Item
	{
	public:
		T data;		// The value
		K key;		// The key
		state flag; // Describes the state of the cell

		Item() // default constructor for the empty default Item class
		{
			key = K();	  // initialize the key to the default value of the key type
			data = T();	  // initialize the data to the default value of the data type
			flag = EMPTY; // set the flag to empty
		}

		Item(K k, T d) // constructor for the non-default Item class
		{
			key = k;
			data = d;
			flag = FULL;
		}
	};

	int size;			// The size of the table
	Item *table;		// The table, specifically a pointer to an array of Items
	tableStatus status; // SG tableStatus to hold the status of the table (full or not full) SG

	// methods to track the "fullness" status of the table
	virtual void setTableStatus(tableStatus state) { this->status = state; }; // SG set the table status
	virtual tableStatus getTableStatus() const { return status; };			  // SG get the table status

	// pure virtual hash functions
	virtual int h1(K k) const = 0;
	virtual int h2(K k) const = 0;

	bool prime(int m) const
	{
		// cout << "IF YOU SEE THIS MESSAGE IT MEANS THAT PRIME FUNCTION IS BROKEN" << endl
		//	 << "change the method in getNextPrime to use PrimeUtil.h's method\n";
		for (int i = 2; i < (int)sqrt(m); i++)
			if (m % i == 0)
				return false;
		return true;
	}
	// can't change PrimeUtil.h, so i'm expanding on it here
	int getNextPrime(int m) const;

public:
	HashTable(int m = 10);
	~HashTable();

	// double hash function
	int hash(K k, int i) const;

	// declaration of the functions insert, search and remove
	bool insert(K key, T data);
	T search(K key) const;
	bool remove(K key);

	void print() const;
};

// implement getNextPrime
template <class K, class T>
int HashTable<K, T>::getNextPrime(int m) const
{
	// if m is less than 1, return 1
	if (m < 1)
	{
		return 1;
	}
	// so long as m is not prime
	// while (!PrimeUtil::prime(m))
	while (!prime(m))
	{
		++m;
	}
	return m;
}

template <class K, class T>
HashTable<K, T>::HashTable(int m)
{
	// if the size is less than 1, throw an error and be sad
	if (m < 1)
	{
		throw runtime_error("Invalid size for table - failed constructor");
	}
	size = getNextPrime(m);
	table = new Item[size];
	if (table == nullptr)
	{
		throw runtime_error("Memory allocation failed - failed constructor");
	}
	// now have a dynamic array with correct size
	for (int i = 0; i < size; ++i)
	{
		// set all flags within the array (table, whatever) to empty
		table[i].flag = EMPTY;
	}
	// set the table status to TABLE_NOT_FULL to indicate that the table is not full
	status = (tableStatus)TABLE_NOT_FULL;
}

template <class K, class T>
HashTable<K, T>::~HashTable()
{
	delete[] table;
}

// double hash function
template <class K, class T>
int HashTable<K, T>::hash(K key, int i) const
{
	// the 'i' comes from amount of collisions
	if (i < 0)
	{
		throw runtime_error("Invalid step value - failed hash");
	}

	return (h1(key) + i * h2(key)) % (this->size);
}

template <class K, class T>
bool HashTable<K, T>::insert(K key, T data)
{
	// prevent attempting to insert into a full table
	if (getTableStatus() == TABLE_FULL)
	{
		throw runtime_error("Table is full - failed insert");
	}

	int collisions = 0, index = 0; // initialize collisions and index to 0 to avoid garbage values

	do
	{
		index = hash(key, collisions);
		if (index > size)
		{
			// avoid accessing out of bounds
			throw runtime_error("Index out of bounds - failed insert");
		}
		// we can only inssert if the cell is marked as empty or if the cell is marked as deleted
		if (table[index].flag == EMPTY || table[index].flag == DELETED)
		{
			// we found a valid slot for insertion
			// make a new 'item' with the given key and data,
			// assign that index that new item's data
			table[index] = Item(key, data);
			table[index].flag = FULL;
			// successfully inserted
			// cout << "inserted key: " << key << " at index: " << index << endl; // Debug print for successful insertion
			return true;
		}
		// what happens we find a slot that has the same key as the key we're trying to insert?
		// update the data
		// are we sure we want to update the data?
		else if (table[index].key == key)
		{
			table[index].data = data;
			// successfully updated
			// cout << "updated the key: " << key << " at index: " << index << endl; // Debug print for successful update
			return true;
		}
		++collisions;
	} while (collisions < size);
	// cout << "failed to insert key: " << key << " with " << collisions << " collisions" << endl; // Debug print for failed insertion
	// if we have as many collisions as we do size, then we will start looping

	setTableStatus((tableStatus)TABLE_FULL);
	return false;
	// failed the insertion, do nothing, be sad, get wrecked, drink cement
}

template <class K, class T>
T HashTable<K, T>::search(K key) const
{
	int collisions = 0, index = 0; // initialize collisions and index to 0 to avoid garbage values

	do
	{
		index = hash(key, collisions);
		// if we come accross a cell that has not been touched, aka empty, then we end our search since it can't be past here
		if (table[index].flag == EMPTY)
		{
			// yeet
			throw runtime_error("Key does not exist in table - failed search");
		}
		// if there's something in that cell and it has the right key (garbage value are lame)
		else if (table[index].flag == FULL && table[index].key == key)
		{
			return table[index].data;
		}
		++collisions;
	} while (collisions < size);
	// more yeet
	throw runtime_error("Key does not exist in table - failed search");
}

template <class K, class T>
bool HashTable<K, T>::remove(K key)
{
	int collisions = 0, index = 0; // initialize collisions and index to 0 to avoid garbage values

	do
	{
		// this method uses the same type of searching as search method
		index = hash(key, collisions);
		if (table[index].flag == EMPTY)
		{
			// search landed on empty, nothing beyond, leave
			return false;
		}
		else if (table[index].flag == FULL && table[index].key == key)
		{
			// found a thing that matched the thing wooooo
			table[index].flag = DELETED;
			if (getTableStatus() == TABLE_FULL)
			{
				// if the table was formerly full- tis not anymore
				setTableStatus((tableStatus)TABLE_NOT_FULL);
			}
			return true;
		}
		++collisions;
	} while (collisions < size);

	return false;
}

template <class K, class T>
void HashTable<K, T>::print() const
{
	for (int i = 0; i < size; ++i)
	{
		if (table[i].flag == FULL)
		{
			cout << i << ":\t" << table[i].key << '\n';
		}
		if (table[i].flag == DELETED)
		{
			cout << i << ":\t" << "DELETED" << '\n';
		}
	}
}
