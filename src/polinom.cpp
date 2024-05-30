#include "polinom.h"
#include <stdlib.h>


void Polinom::addMonom(int cf, int deg)
{
	Monom* newMonom = new Monom(cf, deg);

	if ((pFirst == nullptr) || (deg > pFirst->degree))
	{
		newMonom->pNext = pFirst;
		pFirst = newMonom;
	}
	else
	{
		Monom* tmp = pFirst;
		Monom* prev = nullptr;
		while ((tmp != nullptr) && (tmp->degree) > deg)
		{
			prev = tmp;
			tmp = tmp->pNext;
		}
		if ((tmp != nullptr) && (tmp->degree == deg))
		{
			tmp->coef += cf;
			if (tmp->coef == 0)
				if (prev == nullptr) 
					pFirst = tmp->pNext;
				else 
					prev->pNext = tmp->pNext;
		}
		else
		{
			newMonom->pNext = tmp;
			if (prev == nullptr) pFirst = newMonom;
			else prev->pNext = newMonom;
		}
	}
}

Polinom::Polinom(string pol)
{
	pFirst = nullptr;
	if (pol == "0") return;
	int coef = 0; 
	int sign = 1;
	int pos = 0;
	string deg = "000";
	string num = "";

	for (int i = 0; i <= pol.length(); i++)
	{
		if ((i == pol.length()) || (pol[i] == '-') || (pol[i] == '+'))
		{
			if (!num.empty())
			{
				coef = stoi(num) * sign;
				addMonom(coef, stoi(deg));
				num = ""; deg = "000";
			}
			if ((i < pol.length()) && (pol[i] == '-'))
				sign = -1;
			else
				sign = 1;
		}
		else if (((int(pol[i]) - int('0')) >= 0) && ((int(pol[i]) - int('0')) < 10))
			num += pol[i];
		else if ((pol[i] == 'x') || (pol[i] == 'y') || (pol[i] == 'z'))
		{
			if ((num.empty()) && ((i == 0) || (pol[i - 1] != '^')))
				num = "1";
			if (pol[i] == 'x') pos = 0;
			else if (pol[i] == 'y') pos = 1;
			else if (pol[i] == 'z') pos = 2;
			i++;

			if ((i < pol.length()) && (pol[i] == '^'))
			{
				i++;
				string exp = "";
				while ((i < pol.length()) && (((int(pol[i]) - int('0')) >= 0) && ((int(pol[i]) - int('0')) < 10)))
					exp += pol[i++];
				i--;
				if (exp.empty()) 
					deg[pos] = '1';
				else 
					deg[pos] = exp[0];
			}
			else
			{
				deg[pos] = '1';
				i--;
			}
		}
	}
}

Iterator Polinom::begin()
{
	return Iterator(pFirst);
}

Iterator Polinom::end()
{
	return Iterator(nullptr);
}

void Polinom::Print()
{
	if (pFirst == nullptr)
	{
		cout << "0";
		return;
	}

	for (auto i = begin(); i != end(); ++i)
	{
		Monom mon = *i;

		if ((i != begin()) && (mon.coef > 0)) 
			cout << "+";
		if ((mon.coef == 1) && (mon.degree == 0)) 
			cout << mon.coef;
		if (mon.coef != 1) 
			cout << mon.coef;

		int deg_x = mon.degree / 100;
		int deg_y = (mon.degree / 10) % 10;
		int deg_z = mon.degree % 10;

		if (deg_x > 0)
			if (deg_x == 1) cout << "x";
			else cout << "x^" << deg_x;

		if (deg_y > 0)
			if (deg_y == 1) cout << "y";
			else cout << "y^" << deg_y;

		if (deg_z > 0)
			if (deg_z == 1) cout << "z";
			else cout << "z^" << deg_z;
	}
}

Polinom Polinom::operator+(const Polinom& pol) const
{
	Polinom res;
	Monom* mon1 = this->pFirst;
	Monom* mon2 = pol.pFirst;
	while ((mon1 != nullptr) || (mon2 != nullptr))
	{
		if (mon1 == nullptr) 
		{
			res.addMonom(mon2->coef, mon2->degree);
			mon2 = mon2->pNext;
		}
		else if (mon2 == nullptr) 
		{
			res.addMonom(mon1->coef, mon1->degree);
			mon1 = mon1->pNext;
		}
		else if (mon1->degree == mon2->degree) 
		{
			int newCoef = mon1->coef + mon2->coef;
			if (newCoef != 0)
				res.addMonom(newCoef, mon1->degree);
			mon1 = mon1->pNext;
			mon2 = mon2->pNext;
		}
		else if (mon1->degree > mon2->degree) 
		{
			res.addMonom(mon1->coef, mon1->degree);
			mon1 = mon1->pNext;
		}
		else 
		{
			res.addMonom(mon2->coef, mon2->degree);
			mon2 = mon2->pNext;
		}
	}
	return res;
}

Polinom Polinom::operator*(const Polinom& pol) const
{
	Polinom res;
	for (Monom* mon1 = pFirst; mon1 != nullptr; mon1 = mon1->pNext)
		for (Monom* mon2 = pol.pFirst; mon2 != nullptr; mon2 = mon2->pNext)
			res.addMonom((mon1->coef) * (mon2->coef), (mon1->degree) + (mon2->degree));
	return res;
}

Polinom Polinom::operator*(double c) const
{
	Polinom res;
	if (c == 0) 
		return res;

	for (Monom* mon = pFirst; mon != nullptr; mon = mon->pNext) 
		res.addMonom((mon->coef) * c, mon->degree);

	return res;
}

Polinom Polinom::operator-(const Polinom& pol) const
{
	return (*this + pol*(-1));
}

double Polinom::value_pol(double x1, double y1, double z1) const
{
	double res=0;
	for (Monom* mon = pFirst; mon != nullptr; mon = mon->pNext)
	{
		int deg_x = (mon->degree) / 100;
		int deg_y = ((mon->degree) / 10) % 10;
		int deg_z = (mon->degree) % 10;
		res += (mon->coef) * pow(x1, deg_x) * pow(y1, deg_y) * pow(z1, deg_z);

	}
	return res;
}

bool Polinom::operator==(const Polinom& pol) const
{
	Monom* mon1 = this->pFirst;
	Monom* mon2 = pol.pFirst;

	while ((mon1 != nullptr) && (mon2 != nullptr))
	{
		if (((mon1->coef) != (mon2->coef)) || ((mon1->degree) != (mon2->degree))) 
			return false;
		mon1 = mon1->pNext;
		mon2 = mon2->pNext;
	}

	if ((mon1 == nullptr) && (mon2 == nullptr))
		return true;
	else return false;
}