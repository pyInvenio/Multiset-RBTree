// Multiset.cpp : Defines the entry point for the application.
//
#pragma once

#include "Multiset.h"

using namespace std;

int main()
{
	
	Multiset<int> set;

	set.add(10);
	set.add(20);
	set.add(15);
	set.add(12);
	set.add(21);
	set.add(32);
	set.add(50);
	set.add(100);

	// Add duplicated data
	set.add(5);
	set.add(5);
	set.add(5);
	cout << "Original multiset:" << endl;
	set.print();
	
	Multiset<int> copied = set;
	cout << "Copied multiset:" << endl;
	copied.print();
	copied.remove(5);
	cout << "Copied multiset with duplicates removed:" << endl;
	copied.print();
	cout << "Original multiset:" << endl;
	set.print();
	Multiset<int> moved = std::move(set);
	cout << "Moved multiset:" << endl;
	moved.print();
	cout << "Original multiset:" << endl;
	set.print();
	moved.remove(5);
	cout << "Moved multiset with duplicates removed:" << endl;
	moved.print();


	rbiterator<int> b = copied.begin();
	cout << "Begin iterator value:" << endl;
	cout << *b << endl;
	rbiterator<int> e = copied.begin();
	for (int i = 0; i < 4; i++)
		e++;
	cout << "Iterator value four later:" << endl;
	cout << *e << endl;
	copied.erase(b, e);
	cout << "Set with range removed:" << endl;
	copied.print();

	cout << "Set iterated forward:" << endl;
	for (rbiterator<int> i = copied.begin(); i <= copied.end(); i++)
		cout << i.value() << endl;
	cout << "Set iterated backward:" << endl;
	for (rbiterator<int> i = copied.end(); i >= copied.begin(); i--)
		cout << i.value() << endl;
	cout << endl;
	rbiterator<int> c = copied.findIter(50);
	cout << "Found iterator:" << endl;
	if(c)
		cout << c.value() << endl;
	return 0;
}
