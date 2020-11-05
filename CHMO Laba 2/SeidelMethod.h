#pragma once
#include "IterationMethod.h"

class SeidelMethod : public IterationMethod
{
public:
	SeidelMethod(SLAE slae) : IterationMethod(slae) { };

	int Solution(real w) override
	{
		vector<real> xk(slae.sizeMatrix, 0);
		real err = 1;

		int k = 0;
		while (k < slae.maxiter && err > slae.eps)
		{
			for (int i = 0; i < slae.sizeMatrix; i++)
				xk[i] = Iteration(xk[i], w, xk, xk, i);

			err = Inconspicuous(xk);
			k++;
		}

		slae.X = xk;
		return k;
	}
};