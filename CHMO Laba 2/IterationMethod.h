#pragma once
#include "Method.h"
#include <iomanip>

class IterationMethod: Method
{
public:

	SLAE slae;

	IterationMethod(SLAE slae)
	{
		this->slae = slae;
	}


	inline real Iteration(real xki, real w, vector<real> vecAl, vector<real> vecDiAu, real i)
	{
		return xki + w * (slae.B[i] - Sum(vecAl, vecDiAu, i)) / slae.di[i];
	}

	inline real Inconspicuous(vector<real> vec)
	{
		return slae.Norm(slae.B - MatVecMult(vec)) / slae.normB;
	}


	// Умножение матрицы на вектор
	vector<real> MatVecMult(vector<real> vec)
	{
		vector<real> answer(slae.sizeMatrix);

		for (int i = 0; i < slae.sizeMatrix; i++)
			answer[i] = Sum(vec, i);

		return answer;
	}


	real Sum(vector<real> vec, int i)
	{
		return Sum(vec, vec, i);
	}


	// Умножение i-той строки нижнего треугольника матрицы на вектор vecAl,
	// плюс умножение i-той строки верхнего треугольника матрицы на вектор vecDiAu
	real Sum(vector<real> vecAl, vector<real> vecDiAu, int i)
	{
		return SumAl(vecAl, i) + SumDiAu(vecDiAu, i);
	}


	// Умножение i-той строки нижнего треугольника матрицы на вектор vec
	real SumAl(vector<real> vec, int i)
	{
		real answer = 0;

		for (size_t j = 0; j < 3; j++)
		{
			int tl = i + slae.I[j];

			if (tl >= 0)
				answer += slae.Al[i][j] * vec[tl];
		}
		return answer;
	}


	// Умножение i-той строки верхнего треугольника матрицы на вектор vecDiAu
	real SumDiAu(vector<real> vec, int i)
	{
		real answer = slae.di[i] * vec[i];

		for (size_t j = 0; j < 3; j++)
		{
			int tu = i + slae.I[j + 4];

			if (tu < slae.sizeMatrix)
				answer += slae.Au[i][j] * vec[tu];
		}

		return answer;
	}

	real FindMinW()
	{
		int mink = INT32_MAX;
		real w = 0;

		while (true)
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

	void ReportSolution(string fileName)
	{
		ofstream fout;
		fout.open(fileName + ".txt");
		real wMax = FindMinW();
		real w = 0;

		while (w + 0.1 < wMax)
		{
			ReportForCurrentW(&fout, w);
			w += 0.1;
		}

		while (w < wMax)
		{
			ReportForCurrentW(&fout, w);
			w += 0.01;
		}
	}

	void ReportForCurrentW(ofstream* fout, real w)
	{
		int k = Solution(w);
		vector<real> x_prec(slae.sizeMatrix);

		for (int i = 0; i < slae.sizeMatrix; i++)
			x_prec[i] = i + 1;

		*fout << "w:\tx:\tx* - x:\tvA:\tk:" << endl;

		for (int i = 0; i < slae.sizeMatrix; i++)
		{
			if (i == 0)
				*fout << setprecision(2) << fixed << w << "\t";
			else
				*fout << " \t";

			*fout << setprecision(10) << scientific;

			*fout << slae.X[i] << "\t" << x_prec[i] - slae.X[i] << "\t";

			if (i == 0)
				*fout << slae.Norm(slae.X - x_prec) / slae.Norm(x_prec) / Inconspicuous(slae.X) << "\t" << k;
			else
				*fout << " \t \t";

			*fout << endl;
		}

		*fout << endl;
	}


	virtual int Solution(real w) { return 0; };
};