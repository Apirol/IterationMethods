#pragma once
#include "InputSLAEHandler.h"
#include "OutputSLAEHandler.h"
#include "Vector.h"
#include "NotBlockMethod.h"

class SeidelMethod : public NotBlockMethod
{
public:
	SeidelMethod(SLAE slae) : NotBlockMethod(slae) { };


	void Solution()
	{
		vector<real> xk(slae.sizeMatrix, 0);
		real err = 1;
		real w = 1;

		for (int k = 0; k < slae.maxiter && err > slae.eps; k++)
		{
			vector <real> xk1(slae.sizeMatrix, 0);

			for (int i = 0; i < slae.sizeMatrix; i++)
				xk1[i] = Iteration(xk[i], w, xk1, xk, i);

			xk = xk1;
			err = Inconspicuous(xk);
		}

		slae.X = xk;
	}
};