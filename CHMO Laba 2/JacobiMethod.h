#pragma once
#include "IterationMethod.h"
#include <iomanip>

class JakobiMethod : public IterationMethod
{
private:
	real currentW;
	int iterationCount;
public:
	JakobiMethod(SLAE slae) : IterationMethod(slae) { };

	int Solution(real w) override
	{
		vector<real> xk(slae.sizeMatrix, 0);
		real err = 1;

		int k = 0;
		while (k < slae.maxiter && err > slae.eps)
		{
			vector <real> xk1(slae.sizeMatrix, 0);

			for (int i = 0; i < slae.sizeMatrix; i++)
				xk1[i] = Iteration(xk[i], w, xk, xk, i);

			xk = xk1;
			err = Inconspicuous(xk);
			k++;
		}

		slae.X = xk;
		iterationCount = k;
	}
};