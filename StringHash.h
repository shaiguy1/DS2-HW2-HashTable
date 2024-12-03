#pragma once
#include "HashTable.h"
#include <string>
using namespace std;

template <class T>
class StringHash : public HashTable<string, T>
{
private:
	int h1(string k) const override
	{
		if (k.length() <= 0)
		{
			throw runtime_error("Key is empty - failed StringHash::h1");
		}
		unsigned long long int hash = 0;
		for (int i = 0; i < k.length(); ++i)
		{
			hash = (hash * 256 + k[i]) % this->size;
		}
		/*
  		Should it not be?:
  SG  		for (int i = 1; i <= k.length(); i++) {
			power = (unsigned long long)pow(256, (i - 1)) % this->size;
			sum += (k[i - 1] * power) % this->size;
   		??????????????????????? idk bro
		 */
		return hash;
	}
	int h2(string k) const override
	{
		int length = k.length();
		if (length <= 0)
		{
			throw runtime_error("Key is empty - failed StringHash::h2");
		}
		if (length > 8)
		{
			throw runtime_error("Key is too long - failed StringHash::h2");
		}
		unsigned long long int hash = 0;
		for (int i = 0; i < length; ++i)
		{
			hash = (hash * 256 + k[i]) % (this->size - 1);
		}
		return 1 + (hash % (this->size - 1));
	}

public:
	StringHash(int m = 10) : HashTable<string, T>(m) {}
};

// main used for testing
//  #include "StringHash.h"
//  #include <iostream>
//  #include <string>
//  using namespace std;

// int main()
// {
//     StringHash<int> hashTable(7);
//     hashTable.insert("name1", 10);
//     hashTable.insert("name2", 20);
//     hashTable.insert("name3", 30);

//     try
//     {
//         cout << "Value for key 'Name1': " << hashTable.search("Name1") << endl;
//     }
//     catch (const runtime_error &e)
//     {
//         cout << e.what() << endl;
//     }

//     hashTable.print();
//     return 0;
// }
// this works too
