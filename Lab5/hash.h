#include <iostream>
#include <string>

template<class DataType >
struct  hashRow
{
public:
	string key;
	bool state; // if state = false element is deleted
	DataType data;
	

	hashRow() {
		 state = true;
	}
	hashRow(const DataType& data_, string s) : data(data_), state(true),key(s) {};

	bool operator ==(hashRow r)
	{
		if ((data == r.data) && (key == r.key))
			return true;
		else false;
	}
	
};
template<class T>
class  Hash
{
	hashRow<T>** arr;
	hashRow<T>* del;
	int capacity;
	int size;
	
public:
	int count_s;
	int count_i;
	int count_d;
	Hash()
	{
		capacity = 255;
		size = 0;
		arr = new hashRow<T>*[capacity];
		for (int i = 0; i < capacity; i++) { arr[i] = NULL; }
		count_s = 0;
		count_d = 0;
		count_i = 0;
		
	}
	bool isEmpty()
	{
		return size == 0;
	}
	int hashFunc1(string s)
	{

		int sum = 0;
		for (int i = 0; i < s.length(); i++)
		{
			sum = sum + (unsigned int)s[i];
		}
		return (sum % 255);
	}
	int hashFunc2(string s)
	{
		int sum = 0;
		for (int i = 0; i < s.length(); i++)
		{
			sum = sum + (unsigned int)s[i];
		}
		return (sum % 253 + 1);
	}
	void insertNode(string key, T value)

	{
		count_i = 0;
		hashRow<T>* temp = new hashRow<T>(value,key);
		int index1 = hashFunc1(key);
		if(arr[index1] != NULL )
		{
			int index2 = hashFunc2(key);
			int i = 1;
			while (1)
			{

				int newIndex = (index1 + i * index2) %255;
				count_i++;
				if (arr[newIndex] == NULL|| arr[newIndex]->state==false)

				{
					if (!(arr[newIndex]->state)) { size++; };
					arr[newIndex] = temp;
					break;

				}

				i++;
			}
		}
		else

		{
			
			arr[index1] = temp;
			
		}
		count_i++;
	}
	hashRow<T>*search(string key) {
		count_s=0;
		int h1 = hashFunc1(key); 
		int h2 = hashFunc2(key);
		int i = 0;
		while (arr[h1] != NULL && i < capacity)

		{
			count_s++;
			if (arr[h1]->key == key && (arr[h1]->state==true))
			{
				return arr[h1];
			}

			h1 = (h1 + h2) % capacity;
			++i;

		}
		count_s++;
		return NULL;
	}
	int deleteNode(string key) {
		int h1 = hashFunc1(key);
		int h2 = hashFunc2(key);
		int i = 0;
		count_d=0;
		while (arr[h1] != NULL && i < capacity)

		{
			count_d++;
			if (arr[h1]->key == key)
			{
				hashRow<T>* temp = arr[h1];
				arr[h1]->state = false;
				size--;
				return 0;
			}

			h1 = (h1 + h2) % capacity;
			++i;

		}
		count_d++;
		return 0;
	}
};
