#pragma once
#include "IMethod.h"


class NotBlockMethod : IMethod
{
protected:
	SLAE slae;

	NotBlockMethod(SLAE slae)
	{
		this->slae = slae;
	}

	virtual int Solution(real w) { cout << "Solution was failed"; return 0; };

	virtual void ReportSolution(ofstream* fout) { cout << "Report was failed"; };

	virtual real FindMinW() { return 0; };

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
};