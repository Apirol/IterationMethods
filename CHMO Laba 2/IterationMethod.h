#pragma once
#include "Method.h"


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

	virtual void Solution(real w) = 0;
};