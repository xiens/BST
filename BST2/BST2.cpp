// BST2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include<iostream>
#include"conio.h"

using namespace std;

int main()
{
	Tree<int>bst;

	bst.insert(5);
	cout << bst << endl << endl;
	bst.insert(3);
	cout << bst << endl << endl;
	bst.insert(2);
	cout << bst << endl << endl;
	bst.insert(7);
	cout << bst << endl << endl;
	bst.insert(0);
	cout << bst << endl << endl;
	
	bst.insert(2);
	bst.insert(4);
	cout << bst << endl << endl;
	
	bst.erase(3);
	cout << bst << endl << endl;
	
	

	cout << bst << endl << endl;

	cout << "max in this tree is: " << bst.max() << endl;



	Tree<char>bst2;

	bst2.insert('f');
	cout << bst2 << endl << endl;
	bst2.insert('d');
	cout << bst2 << endl << endl;
	bst2.insert('a');
	cout << bst2 << endl << endl;
	bst2.insert('c');
	cout << bst2 << endl << endl;
	bst2.insert('e');
	cout << bst2 << endl << endl;

	cout << "min in this tree is: " << bst2.min() << endl;
	_getch();
	return 0;
}

