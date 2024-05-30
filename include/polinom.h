#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

struct Monom
{
	int coef;
	int degree;
	Monom* pNext;

	Monom(int cf, int deg):coef(cf),degree(deg), pNext(nullptr) {}
};

class Iterator
{
private:
	Monom* cur;
public:
	Iterator(Monom*cur=nullptr): cur(cur) {}
	Monom& operator*()
	{
		return *cur;
	}
	Iterator& operator++()
	{
		if (cur)
			cur = cur->pNext;
		return *this;
	}
	bool operator!=(const Iterator& p)
	{
		return cur != p.cur;
	}

};

class Polinom
{
private:
	Monom* pFirst;
public:
	Polinom() : pFirst(nullptr) {};
	Polinom(string pol);
	~Polinom()
	{
		pFirst = nullptr;
	}

	void addMonom(int cf, int deg);
	Polinom operator+(const Polinom& pol) const;
	Polinom operator-(const Polinom& pol) const;
	Polinom operator*(const Polinom& pol) const;
	Polinom operator*(double c) const;

	double value_pol(double x1, double y1, double z1) const;

	bool operator==(const Polinom& pol) const;

	Iterator begin();
	Iterator end();

	void Print();
};