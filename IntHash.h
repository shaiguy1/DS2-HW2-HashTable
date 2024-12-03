#pragma once
#include "HashTable.h"
using namespace std;

template <class T>
class IntHash : public HashTable<int, T>
{
private:
	int h1(int k) const override
	{
		return (k % this->size);
	}
	int h2(int k) const override
	{
		return (1 + (k % (this->size - 1)));
	}

public:
	IntHash(int m = 10) : HashTable<int, T>(m) {}
};

// the main i used to test
//  #include "IntHash.h"
//  #include <iostream>
//  using namespace std;

// int main()
// {
//     IntHash<int> hashTable(7);
//     hashTable.insert(1, 10);
//     hashTable.insert(2, 20);
//     hashTable.insert(3, 30);

//     try
//     {
//         cout << "Value for key 2: " << hashTable.search(2) << endl;
//     }
//     catch (const runtime_error &e)
//     {
//         cout << e.what() << endl;
//     }

//     hashTable.print();
//     return 0;
// }
// this works
