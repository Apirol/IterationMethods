#pragma once
#include <iostream>
#include <vector>


vector<real> operator -(const vector<real>& a, const vector<real>& b)
{
	if (a.size() != b.size())
		throw("a.size() != b.size()");
	vector<real> c(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		c[i] = a[i] - b[i];
	return c;
}