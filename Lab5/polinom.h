#include "iostream"
#include <vector>
#include <stdio.h>
#include "cmath"
using namespace std;
template <class T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node() : next(nullptr), prev(nullptr) {}
	~Node() {
	};
};
template <class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
public:
	List() : head(nullptr), tail(nullptr) {}
	~List()
	{

	}
	Node<T>* get_head() const
	{
		return head;
	}
	Node<T>* get_tail() const
	{
		return tail;
	}
	void Insert(T tdata)
	{
		Node <T>* tmp1 = new Node<T>;
		tmp1->data = tdata;

		if (IsEmpty())
		{
			head = tmp1;
		}
		else
		{
			Node<T>* tmp2 = nullptr;
			Node<T>* tmp3 = head;

			if (tdata > head->data)
			{
				head->prev = tmp1;
				tmp1->next = head;
				head = tmp1;
			}
			else
			{
				while ((tmp3->data > tdata) && (tmp3->next != nullptr))
				{
					tmp3 = tmp3->next;
				}
				if (tmp3->next != nullptr)
				{
					tmp2 = tmp3->prev;
					tmp1->next = tmp2->next;
					tmp2->next->prev = tmp1;
					tmp2->next = tmp1;
					tmp1->prev = tmp2;
				}
				else
				{
					tmp3->next = tmp1;
					tmp1->prev = tmp3;
				}
			}
		}

	}
	void clean()
	{
		while (head != nullptr)
		{
			tail = head->next;
			delete head;
			head = tail;
		}

		head = nullptr;

	}
	bool IsEmpty()
	{
		if (head == nullptr && tail == nullptr)
		{
			return(true);
		}
		else
		{
			return(false);
		}

	}
	void Merge(Node<T>* p1, Node<T>* p2)
	{
		p1->data = p1->data + p2->data;
		p1->next = p2->next;
		if (p2->next != nullptr)
		{
			p2->next->prev = p1;
		}
		delete p2;
	}
	void Delete(Node<T>* elem)
	{
		Node<T>* tmp;
		if (elem == head)
		{
			head = elem->next;
		}
		if (elem == tail)
		{
			tail = elem->prev;
		}
		if (elem->prev != nullptr)
		{
			tmp = elem->prev;
			tmp->next = elem->next;
		}
		if (elem->next != nullptr)
		{
			tmp = elem->next;
			tmp->prev = elem->prev;
		}
		delete elem;
	}
	bool operator== (const List<T>& l) const
	{
		Node<T>* tmp1 = head;
		Node<T>* tmp2 = l.head;

		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->data != tmp2->data)
			{
				return(false);
			}

			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}

		if (tmp1 == nullptr && tmp2 == nullptr)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}

};
class Monom
{
public:

	double cf;
	int deg;

	Monom()
	{
		cf = 0.0;
		deg = 0;
	}
	Monom(double tcf, int tdeg)
	{
		if (tdeg < 0 || tdeg >= 1000)
		{
			throw "You have wrong degree";
		}

		cf = tcf;
		deg = tdeg;
	}
	Monom operator+(const Monom& m);
	Monom operator*(const Monom& m);
	Monom& operator=(const Monom& m);
	bool operator==(const Monom& m) const;
	bool operator<(const Monom& m)const;
	bool operator>(const Monom& m)const;
	bool operator!= (const Monom& m)const;

};
class Polinom : public List<Monom>
{
public:
	List<Monom> polinom;
	Polinom()
	{

	}
	void simplification();
	void SetPolinom();
	Polinom& operator=(List<Monom>& p);
	Polinom& operator+(const Polinom& p);
	Polinom& operator-(Polinom& p);
	Polinom& operator*(double _const);
	Polinom  operator*(Polinom& p);
	friend ostream& operator<<(ostream& os, const Polinom& p)
	{
		List<Monom> poli = p.polinom;
		Node<Monom>* tmp = poli.get_head();

		if (poli.IsEmpty())
		{
			os << 0;
		}
		else
		{
			while (tmp != nullptr)
			{
				if (tmp != poli.get_head())
				{
					if (tmp->data.cf > 0)
					{
						os << " +";
					}
				}
				if (tmp->data.deg == 0)
				{
					os << tmp->data.cf;
				}
				if (tmp->data.cf != 1 && tmp->data.deg != 0)
				{
					os << tmp->data.cf << " *";
				}
				if (tmp->data.deg / 100 != 0)
				{
					os << "x^" << tmp->data.deg / 100;
				}
				if (tmp->data.deg % 100 / 10 != 0)
				{
					os << " y^" << tmp->data.deg % 100 / 10;
				}
				if (tmp->data.deg % 10)
				{
					os << " z^" << tmp->data.deg % 10;
				}

				tmp = tmp->next;
			}
		}

		return os;
	}

};

