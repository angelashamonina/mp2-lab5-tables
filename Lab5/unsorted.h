#pragma once
#include <string>
template<class DataType >
struct  Row
{
public:
	string key;
	DataType data;
	bool empty;
	
	Row() {
		empty=true;
	}
	Row( string s,const DataType& data_) : data(data_), key(s) {};

	bool operator ==(Row r)
	{
		if ((data == r.data) && (key == r.key))
			return true;
		else false;
	}
	bool GetEmpty()
	{
		return empty;
	}
};
template<class T>
class  Table
{
protected:
	Row<T> mas[255];
	int count;
public:
	int count_s;
	int count_i;
	int count_d;
Table()
	{
		count = 0;
		count_s = 0;
		count_d = 0;
		count_i = 0;
	}
void insert(string key, T value)
{
	Row<T> r( key, value);
	if (count + 1 > 255)
	{
		throw "Unsorted table is full";
	}
	mas[count] = r;
	mas[count].empty = false;
	count++;
	
}
T search(string key) {
	count_s = 0;
	
	for (int i = 0; i < count; i++)
	{
		count_s++;
		if (mas[i].key == key&& mas[i].empty != true)
			return mas[i].data;
	}
	cout << "Searching from unsorted table: " << count_s+1 << " operations" << endl;
	throw "Not found";
}
void del(string s)
{
	if (count==0)
		throw "table is empty";
	count_d = 0;
	Row<T> r(s,search(s) );
	count_d += count_s;
	for (int i = 0; i < 255; i++)
	{
		count_d++;
		if (mas[i].key == r.key)
		{
			mas[i].empty = true;
			count--;
			break;
		}
	}
}
~Table()
{
	
	
}
int getCount()
{
	return count;
}
};