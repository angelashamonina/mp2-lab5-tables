#include <iostream>
#include "polinom.h"
#include "tree.h"
#include "hash.h"
#include "unsorted.h"

int main()
{
	try {
		string s;
		RBTree<string, Polinom> tree;
		Hash<Polinom>* hash = new Hash<Polinom>;
		Table <Polinom> table;
		double c;
		int k, k1 = 1,k2;
		cout << "Enter count of polinoms" << endl;
		cin >> k;
		for (int i = 0; i < k; i++)
		{
			cout << "Enter name for polinom" << endl;
			cin >> s;
			while (hash->search(s)!=NULL) {
				cout << "A polinom with this name is already exist " << endl;
				cout << "Enter name for polinom" << endl;
				cin >> s;
			}
			Polinom A;
			A.SetPolinom();
			cout << endl << s << ": " << A << endl << endl;
			tree.insert(s, A);
			cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
			hash->insertNode(s, A);
			cout << "Inserting in hash table: " << hash->count_i<<" operations" << endl;
			table.insert(s, A);
			cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
		}
		while(k1)
		{
			cout << "Choose the actions to perform " << endl;
			cout << "1. Delete polinom" << endl;
			cout << "2. Search polinom" << endl;
			cout << "3. Actions with 2 polinoms" << endl;
			cout << "0.Exit" << endl << endl;
			cin >> k;
			switch (k)
			{
			case 1:
			{
				cout << "Enter a name of polinom" << endl;
				cin >> s;
				tree.remove(s);
				cout << "Deleting from tree : " << tree.count_d << " operations" << endl;
				hash->deleteNode(s);
				cout << "Deleting from the hash table: " << hash->count_d << " operations" << endl;
				table.del(s);
				cout << "Deleting from unsorted table: " << table.count_d << " operations" << endl;
				cout << endl;
				break;
			}
			case 2:
			{
				cout << "Enter a name of polinom" << endl;
				cin >> s;
				tree.search(s);
				cout << endl;
				cout << "Searching from tree: " << tree.count_s << " operations" << endl;
				hash->search(s);
				cout << "Searching from the hash table: " << hash->count_s << " operations" << endl;
			    table.search(s);
				cout << "Searching from unsorted table: " << table.count_s << " operations" << endl;
				cout << endl << s << ": " << table.search(s) << endl << endl;
				cout << endl;
				break;
			}
			case 3:
			{   Polinom  B, C, sum, dif, mul;
				cout << "Enter a name of polinom" << endl;
				cin >> s;
				B = table.search(s);
				cout << endl << s << ": " << B << endl << endl;
				cout << "If you want to perform the operations witn new polinom enter 1, with table polinom enter 0" << endl;
				cin >> k;
				if (k) {
					C.SetPolinom();
					cout << endl << C << endl << endl;
				}
				else {
					cout << "Enter a name of polinom" << endl;
					cin >> s;
					C = table.search(s);
					cout << endl << s << ": " << C << endl << endl;
				}
				cout << endl;
				cout << "Choose the actions to perform with polinoms" << endl;
				cout << "1) Sum" << endl;
				cout << "2) Dif" << endl;
				cout << "3) * const" << endl;
				cout << "4)  Mul" << endl;
				cin >> k;
				cout << "If you want to insert the new polinom in table enter 1, else 0" << endl;
				cin >> k2;
				switch (k)
				{
				case 1:
				{
					sum = C + B;
					cout << " Sum: " << sum << endl << endl;
					if (k2) {
						cout << "Enter a name of sum polinom" << endl;
						cin >> s;
						while (hash->search(s) != NULL) {
							cout << "A polinom with this name is already exist " << endl;
							cout << "Enter a name of sum polinom" << endl;
							cin >> s;
						}
						tree.insert(s,sum);
						cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
						hash->insertNode(s, sum);
						cout << "Inserting in hash table: " << hash->count_i << " operations" << endl;
						table.insert(s, sum);
						cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
					}

				break;
				}
				case 2:
				{dif = C - B;
				cout << " Dif: " << dif << endl << endl;
				if (k2) {
					cout << "Enter a name of dif polinom" << endl;
					cin >> s;
					while (hash->search(s) != NULL) {
						cout << "A polinom with this name is already exist " << endl;
						cout << "Enter a name of dif polinom" << endl;
						cin >> s;
					}
					tree.insert(s, dif);
					cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
					hash->insertNode(s, dif);
					cout << "Inserting in hash table: " << hash->count_i << " operations" << endl;
					table.insert(s, dif);
					cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
				}
				break;
				}
				case 3:
				{
					cout << "Const:";
					cin >> c;
					mul = B * c;
					cout << B << " * const: " << mul << endl << endl;
					if (k2) {
						cout << "Enter a name of 1 polinom*const" << endl;
						cin >> s;
						while (hash->search(s) != NULL) {
							cout << "A polynomial with this name is already exist " << endl;
							cout << "Enter a name of 1 polinom" << endl;
							cin >> s;
						}
						tree.insert(s, mul);
						cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
						hash->insertNode(s, mul);
						cout << "Inserting in hash table: " << hash->count_i << " operations" << endl;
						table.insert(s, mul);
						cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
					}
					mul = C * c;
					cout << C << " * const: " << mul << endl << endl;
					if (k2) {
						cout << "Enter a name of 2 polinom*const" << endl;
						cin >> s;
						while (hash->search(s) != NULL) {
							cout << "A polinom with this name is already exist " << endl;
							cout << "Enter a name of 2 polinom" << endl;
							cin >> s;
						}
						tree.insert(s, mul);
						cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
						hash->insertNode(s, mul);
						cout << "Inserting in hash table: " << hash->count_i << " operations" << endl;
						table.insert(s, mul);
						cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
					}
					break;
				}
				case 4:
				{
					mul = C * B;

				cout << "Mul: " << mul << endl;
				if (k2) {
					cout << "Enter a name of mul polinom" << endl;
					cin >> s;
					while (hash->search(s) != NULL) {
						cout << "A polinom with this name is already exist " << endl;
						cout << "Enter a name of mul polinom" << endl;
						cin >> s;
					}
					tree.insert(s, mul);
					cout << "Inserting in tree: " << tree.count_i << " operations" << endl;
					hash->insertNode(s, mul);
					cout << "Inserting in hash table: " << hash->count_i << " operations" << endl;
					table.insert(s, mul);
					cout << "Inserting in unsorted table: " << 1 << " operation" << endl;
				}
				break;

				}
				default:
					cout << "Wrong choice";
					cout << "1) Sum" << endl;
					cout << "2) Dif" << endl;
					cout << "3) * const" << endl;
					cout << "4)  Mul" << endl;
					cin >> k;
					break;
				}
			}
			default:
				k1 = 0;
				break;
			}
		}
			cout << endl;
			

	}
	catch (const char* error)
	{
		cout << error << endl;
	}
	cout << endl;
	return 0;

}
