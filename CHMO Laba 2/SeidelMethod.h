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

		/*vector<real> sos(12, 1);

		Inconspicuous(sos);*/

		int k = 0;
		while (k < slae.maxiter && err > slae.eps)
		{
			//vector <real> xk1(slae.sizeMatrix, 0);

			for (int i = 0; i < slae.sizeMatrix; i++)
				xk[i] = Iteration(xk[i], w, xk, xk, i);

			//xk = xk1;
			err = Inconspicuous(xk);
			k++;
		}

		slae.X = xk;
		return k;
	}
};