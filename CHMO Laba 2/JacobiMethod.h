#pragma once
#include "NotBlockMethod.h"
#include <iomanip>

class JakobiMethod : public NotBlockMethod
{
public:
	JakobiMethod(SLAE slae) : NotBlockMethod(slae) { };

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
		return k;
	}

	real FindMinW() override
	{
		int mink = INT32_MAX;
		real w = 0;

		while(true)
		{
			int k = Solution(w);

			if (k <= mink)
				mink = k;
			else
				break;

			w += 0.01;
		}
		return w;
	};

	void ReportSolution(ofstream* fout) override
	{
		real wMax = FindMinW();
		real w = 0;

		while(w + 0.1 < wMax)
		{
			pridumayName(fout, w);
			w += 0.1;
		}

		while (w < wMax)
		{
			pridumayName(fout, w);
			w += 0.01;
		}
	};

	void pridumayName(ofstream* fout, real w)
	{
		int k = Solution(w);
		vector<real> x_prec(slae.sizeMatrix);

		for (int i = 0; i < slae.sizeMatrix; i++)
			x_prec[i] = i + 1;
		
		*fout << setprecision(2) << fixed;

		*fout << "w = " << w << endl;
		*fout << "x: " << endl;

		*fout << setprecision(10) << scientific;

		for (int i = 0; i < slae.sizeMatrix; i++)
			*fout << slae.X[i] << endl;

		*fout << "x* - x: " << endl;
		for (int i = 0; i < slae.sizeMatrix; i++)
			*fout << x_prec[i] - slae.X[i] << endl;

		*fout << "vA = " << slae.Norm(slae.X - x_prec) / slae.Norm(x_prec) / Inconspicuous(slae.X) << endl;
		*fout << "k = " << k << endl << endl;
	}
};