#pragma once
#include "HashTable.h"
#include <string>
using namespace std;

template <class T>
class StringHash : public HashTable<string, T>
{
private:
	int h1(string name) const override
	{
		int length = name.length();
		if (length <= 0)
		{
			throw runtime_error("Key is empty - failed StringHash::h1");
		}
		if (length > 8)
		{
			throw runtime_error("Key is too long - failed StringHash::h1");
		}
		// cout << name << endl;
		unsigned long long int hash = 0;
		unsigned long long int temp = 0;
		for (int i = 0; i < length; ++i)
		{
			temp = (unsigned long long int)name[i] * ((unsigned long long int)pow(256, i));
			hash += temp % (this->size);
			// cout << (int)name[i] << "*256^" << i << "+";
		}
		return (hash % (this->size));
	}


	int h2(string name) const override
	{
		return 1;
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
