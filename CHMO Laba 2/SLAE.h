#pragma once
#include "InputSLAEHandler.h"
#include "OutputSLAEHandler.h"
#include "Vector.h"

typedef double real;
const int n = 100;

class SLAE
{
public:
	int sizeMatrix;
	int nonZeroLen1, nonZeroLen2;
	int maxiter;
	real eps;

	vector<vector<real>> Al;
	vector<vector<real>> Au;
	vector<real> di;
	vector<int> I;
	vector<real> B;
	vector<real> X;

	real normB;

	SLAE() 
	{
		Al.resize(n);
		Au.resize(n);
		di.resize(n);
		I.resize(7);
		B.resize(n);
		X.resize(n);
	}

	void Init(InputSLAEHandler input)
	{
		input.InputInfo(&sizeMatrix, &nonZeroLen1, &nonZeroLen2, &maxiter, &eps);

		Al.resize(sizeMatrix);
		Au.resize(sizeMatrix);
		di.resize(sizeMatrix);
		X.resize(sizeMatrix);

		input.InputMatrix(sizeMatrix, &Al, &Au, &di);
		B = input.InputVectorB(sizeMatrix);
		InitI();
		normB = Norm(B);
	}

	void InitI()
	{
		I[0] = -3 - nonZeroLen1 - nonZeroLen2;
		I[1] = -1 - nonZeroLen1 - nonZeroLen2;
		I[2] = -1;

		I[3] = 0;

		I[4] = -I[2];
		I[5] = -I[1];
		I[6] = -I[0];
	}

	inline real Iteration(real xki, real w, vector<real> vecAl, vector<real> vecDiAu, real i)
	{
		return xki + w * (B[i] - Sum(vecAl, vecDiAu, i)) / di[i];
	}

	void JakobiSolution()
	{
		vector<real> xk (sizeMatrix, 0);
		real err = 1;
		real w = 1;

		for (int k = 0; k < maxiter && err > eps; k++)
		{
			vector <real> xk1(sizeMatrix, 0);

			for (int i = 0; i < sizeMatrix; i++)
				xk1[i] = Iteration(xk[i], w, xk, xk, i);

			xk = xk1;
			err = Inconspicuous(xk);
		}

		X = xk;
	}

	void SeidelSolution()
	{
		vector<real> xk(sizeMatrix, 0);
		real err = 1;
		real w = 1;

		for (int k = 0; k < maxiter && err > eps; k++)
		{
			vector <real> xk1(sizeMatrix, 0);

			for (int i = 0; i < sizeMatrix; i++)
				xk1[i] = Iteration(xk[i], w, xk1, xk, i);

			xk = xk1;
			err = Inconspicuous(xk);
		}

		X = xk;
	}

	real Sum(vector<real> vecAl, vector<real> vecDiAu, int i)
	{
		return SumAl(vecAl, i) + SumDiAu(vecDiAu, i);
	}

	real Sum(vector<real> vec, int i)
	{
		return Sum(vec, vec, i);
	}

	real SumAl(vector<real> vec, int i)
	{
		real answer = 0;

		for (size_t j = 0; j < 3; j++)
		{
			int tl = i + I[j];

			if (tl >= 0)
				answer += Al[i][j] * vec[tl];
		}

		return answer;
	}

	real SumDiAu(vector<real> vec, int i)
	{
		real answer = di[i] * vec[i];

		for (size_t j = 0; j < 3; j++)
		{
			int tu = i + I[j + 4];

			if (tu < sizeMatrix)
				answer += Au[i][j] * vec[tu];
		}

		return answer;
	}

	vector<real> MatVecMult(vector<real> vec)
	{
		vector<real> answer(sizeMatrix);

		for (int i = 0; i < sizeMatrix; i++)
			answer[i] = Sum(vec, i);

		return answer;
	}

	inline real Norm(vector<real> vec)
	{
		int size = vec.size();
		real answer = 0;

		for (int i = 0; i < size; i++)
			answer += vec[i] * vec[i];

		return sqrt(answer);
	}

	inline real Inconspicuous(vector<real> vec)
	{
		return Norm(B - MatVecMult(vec)) / normB;
	}

	
};