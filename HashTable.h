#pragma once
#include <iostream>
#include <stdexcept>
#include "PrimeUtil.h" // for the prime-->getNextPrime method

using namespace std;

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
		T data;					 // The value
		K key;					 // The key
		state flag;				 // Describes the state of the cell
		Item() { flag = EMPTY; } // Initialization
		Item(K k, T d)
		{
			data = d;
			key = k;
			flag = FULL;
		}
	};

	int size;
	Item *table;

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
	size = getNextPrime(m);
	table = new Item[size];
	// now have a dynamic array with correct size
	for (int i = 0; i < size; ++i)
	{
		// set all flags within the array (table, whatever) to empty
		table[i].flag = EMPTY;
	}
}

template <class K, class T>
HashTable<K, T>::~HashTable()
{
	delete[] table;
}

// double hash function
template <class K, class T>
int HashTable<K, T>::hash(K k, int i) const
{
	return ((h1(k) + (i * h2(k))) % size);
}

template <class K, class T>
bool HashTable<K, T>::insert(K key, T data)
{
	int collisions = 0;
	int index;
	do
	{
		index = hash(key, collisions);
		// we can only inssert if the cell is marked as empty or if the cell is marked as deleted
		// cout << "DEBUGGING LINE: Attempting to insert key: " << key << " at index: " << index << " with collision count: " << collisions << endl;
		if (table[index].flag == EMPTY || table[index].flag == DELETED)
		{
			// we found a valid slot for insertion
			// make a new 'item' with the given key and data,
			// assign that index that new item's data
			table[index] = Item(key, data);
			table[index].flag = FULL;
			// successfully inserted
			return true;
		}
		// what happens we find a slot that has the same key as the key we're trying to insert?
		// update the data
		else if (table[index].key == key)
		{
			table[index].data = data;
			// successfully updated
			return true;
		}
		++collisions;
	} while (collisions < size);
	// if we have as many collisions as we do size, then we will start looping
	return false;
	// failed the insertion, do nothing, be sad, get wrecked, drink water
}

template <class K, class T>
T HashTable<K, T>::search(K key) const
{
	int collisions = 0;
	int index;
	do
	{
		index = hash(key, collisions);
		// if we come accross a cell that has not been touched, aka empty, then we end our search since it can't be past here
		if (table[index].flag == EMPTY)
		{
			// yeet
			throw runtime_error("Key does not exist in table");
		}
		// if there's something in that cell and it has the right key (garbage value are lame)
		else if (table[index].flag == FULL && table[index].key == key)
		{
			return table[index].data;
		}
		++collisions;
	} while (collisions < size);
	// more yeet
	throw runtime_error("Key does not exist in table");
}

template <class K, class T>
bool HashTable<K, T>::remove(K key)
{
	int collisions = 0;
	int index;
	do
	{
		// this method uses the same type of searching as search method
		index = hash(key, collisions);
		if (table[index].flag == EMPTY)
		{
			// search, landed on empty, nothing beyond, leave
			return false;
		}
		else if (table[index].flag == FULL && table[index].key == key)
		{
			// found a thing that matched the thing wooooo
			table[index].flag = DELETED;
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
		else if (table[i].flag == DELETED)
		{
			cout << i << ":\t" << "DELETED" << '\n';
		}
		else // for debugging
		{
			// cout << ""DEBUGGING LINE: " << i << ":\tEMPTY\n";
		}
	}
}