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
	vector<vector<real>> Al;
	vector<vector<real>> Au;
	vector<real> di;
	vector<int> I;
	vector<real> B;
	vector<real> x;

	SLAE() 
	{
		Al.resize(n);
		Au.resize(n);
		di.resize(n);
		I.resize(7);
		B.resize(n);
		x.resize(n);
	}

	void Init(InputSLAEHandler input)
	{
		vector<int> sizes = input.InputSize();
		sizeMatrix = sizes[0];
		nonZeroLen1 = sizes[1];
		nonZeroLen2 = sizes[2];

		Al.resize(sizeMatrix);
		Au.resize(sizeMatrix);
		di.resize(sizeMatrix);

		input.InputMatrix(sizeMatrix, &Al, &Au, &di);
		B = input.InputVectorB(sizeMatrix);
		InitI();
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

	void JakobiSolution()
	{
		vector<real> approximationX (7, 0);
		int err = 1;
		int eps = 0.001;
		int MaxIter = 10000;
		real w = 0.1;

		for (size_t i = 0; i < 7; i++)
			approximationX[i] = i + 1;

		vector<real> vec(7);

		for (size_t i = 0; i < 7; i++)
		{
			vec[i] = Sum(approximationX, i);
		}

		int sdf = 0;

		/*for (int k = 0; k < MaxIter && err > eps; k++)
		{
			vector <real> xK(n, 0);
			for (int i = 0; i < sizeMatrix; i++)
			{
				real sum = Sum(approximationX, i);
				sum = (w / A[i][I[diagAmount / 2]])* (B[i] - sum);
				xK[i] = approximationX[i] + sum;
			}
			approximationX = xK;
			err = Inconspicuous(approximationX);
		}*/
	}

	inline real norm(vector <real> vector)
	{
		int size = vector.size();
		real answer = 0;

		for (int i = 0; i < size; i++)
			answer += vector[i] * vector[i];

		return sqrt(answer);
	}


	/*inline real Inconspicuous(vector <real> approximationX)
	{
		return norm(B - Mult(approximationX)) / norm(B);
	}*/


	/*vector<real> Mult(vector <real> currentX)
	{
		vector <real> answer(sizeMatrix);

		for (int i = 0; i < sizeMatrix; i++)
		{
			for (int j = 0; j < diagAmount; j++)
				answer[i] += A[i][j] * currentX[I[j]];
		}

		return answer;
	}*/

	real Sum(vector<real> X, int i)
	{
		real answer = di[i] * X[i];

		for (size_t j = 0; j < 3; j++)
		{
			int tl = i + I[j];

			if (tl >= 0)
				answer += Al[i][j] * X[tl];

			int tu = i + I[j + 4];

			if (tu < 7)
				answer += Au[i][j] * X[tu];
		}

		return answer;
	}
};