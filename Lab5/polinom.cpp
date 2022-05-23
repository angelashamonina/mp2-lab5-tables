#include "polinom.h"
#include "tree.h"
#include "hash.h"
#include "unsorted.h"
#include "cmath"
Monom Monom::operator+(const Monom& m)
{
	if (deg == m.deg)
	{
		Monom res(cf + m.cf, deg);
		return res;
	}
	else
	{
		throw "You degrees aren't equal";
	}
}
Monom Monom::operator*(const Monom& m)
{
	Monom res;
	int x, y, z;
	res.cf = cf * m.cf;
	res.deg = deg + m.deg;
	x = deg / 100 + m.deg / 100;
	y = deg % 100 / 10 + m.deg % 100 / 10;
	z = deg % 10 + m.deg % 10;
	if ((x > 9) || (y > 9) || (z > 9))
	{
		throw "A * B:You have wrong degree in polinom";
	}
	return res;
}
Monom& Monom::operator=(const Monom& m)
{
	cf = m.cf;
	deg = m.deg;

	return *this;
}
bool Monom:: operator==(const Monom& m) const
{
	if (deg == m.deg)
	{
		return (true);
	}
	else
	{
		return(false);
	}

}
bool Monom::operator<(const Monom& m)const
{
	return(deg < m.deg);
}
bool Monom:: operator>(const  Monom& m)const
{
	return (deg > m.deg);
}
bool Monom:: operator!= (const Monom& m)const
{
	if (cf != m.cf || deg != m.deg)
	{
		return (true);
	}
	else
	{
		return(false);
	}
}


void Polinom::simplification()
{
	Node<Monom>* tmp1 = polinom.get_head();
	Node<Monom>* tmp2;
	while (tmp1 != nullptr)
	{
		if (abs(tmp1->data.cf) < 1e-10)
		{
			tmp2 = tmp1->next;
			Delete(tmp1);
			tmp1 = tmp2;
		}
		else
		{
			if (tmp1->next != nullptr && (tmp1->next->data.deg == tmp1->data.deg))
			{
				tmp1->data.cf += tmp1->next->data.cf;
				Delete(tmp1->next);
			}
			else
			{
				tmp1 = tmp1->next;
			}
		}

	}

}
void Polinom::SetPolinom()
{
	int count;
	int tdeg;
	double tcf;
	Monom m;
	cout << endl << "Enter monoms count: ";
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		cout << "Enter monom coefficient: ";
		cin >> tcf;
		cout << "Enter monom degree : ";
		cin >> tdeg;
		while ((tdeg > 999) || (tdeg < 0))
		{
			cout << "Your degree is error(>999 or <0). Try again: " << endl;
			cin >> tdeg;
		}
		if (tcf != 0)
		{
			Monom m1(tcf, tdeg);
			m = m1;
			polinom.Insert(m);
		}
	}

	simplification();
}
Polinom& Polinom::operator=(List<Monom>& p)
{
	List<Monom>::operator=(p);
	return(*this);
}
Polinom& Polinom::operator+(const Polinom& p)
{
	Polinom res;
	Node<Monom>* tmp1 = polinom.get_head();
	Node<Monom>* tmp2 = p.polinom.get_head();
	Monom tmp_m;

	while ((tmp1 != nullptr) && (tmp2 != nullptr))
	{
		if (tmp1->data > tmp2->data)
		{
			res.polinom.Insert(tmp1->data);
			tmp1 = tmp1->next;
		}
		else
		{
			if (tmp1->data == tmp2->data)
			{
				tmp_m = tmp2->data + tmp1->data;
				if (tmp_m.cf != 0)
				{
					res.polinom.Insert(tmp2->data + tmp1->data);
				}

				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
			else
			{
				res.polinom.Insert(tmp2->data);

				tmp2 = tmp2->next;
			}
		}
	}

	if ((tmp1 == nullptr) && (tmp2 != nullptr))
	{
		while (tmp2 != nullptr)
		{
			res.polinom.Insert(tmp2->data);
			tmp2 = tmp2->next;
		}
	}

	if ((tmp1 != nullptr) && (tmp2 == nullptr))
	{
		while (tmp1 != nullptr)
		{
			res.polinom.Insert(tmp1->data);
			tmp1 = tmp1->next;
		}
	}

	return res;
}
Polinom& Polinom::operator*(double _const)
{
	Polinom res;
	Node<Monom>* tmp = polinom.get_head();
	Monom m;

	if (_const != 0)
	{
		while (tmp != nullptr)
		{
			m = tmp->data;
			m.cf *= _const;
			res.polinom.Insert(m);
			tmp = tmp->next;
		}
	}
	else
	{
		Monom m1(0, 0);
		m = m1;
		res.polinom.Insert(m);
	}
	return res;
}
Polinom& Polinom::operator-(Polinom& p)
{
	Polinom tmp;
	Polinom res;
	tmp = (p * (-1));
	res = *this + tmp;
	return res;
}
Polinom Polinom::operator *(Polinom& p)
{
	Polinom res;
	Node<Monom>* tmp1 = polinom.get_head();
	Node<Monom>* tmp2;
	Monom tmp_m;

	while (tmp1 != nullptr)
	{
		tmp_m = tmp1->data;
		tmp2 = p.polinom.get_head();

		while (tmp2 != nullptr)
		{
			tmp_m = tmp_m * tmp2->data;
			res.polinom.Insert(tmp_m);
			tmp2 = tmp2->next;
			tmp_m = tmp1->data;
		}

		tmp1 = tmp1->next;
	}
	res.simplification();
	return res;
}
