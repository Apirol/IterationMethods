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
	int diagAmount;
	vector<vector<real>> A;
	vector<int> I;
	vector<real> B;
	vector<real> x;

	SLAE() 
	{
		A.resize(n);
		I.resize(n);
		B.resize(n);
		x.resize(n);
	}

	void Init(InputSLAEHandler input)
	{
		pair<int, int> sizes = input.InputSize();
		sizeMatrix = sizes.first;
		diagAmount = sizes.second;

		A = input.InputMatrix(sizeMatrix, diagAmount);
		B = input.InputVectorB(sizeMatrix);
		I = input.InputVectorI(diagAmount);
	}


	void JakobiSolution()
	{
		vector <real> approximationX (n, 0);
		int err = 1;
		int eps = 0.001;
		int MaxIter = 10000;
		real w = 0.1;

		for (int k = 0; k < MaxIter && err > eps; k++)
		{
			vector <real> xK(n, 0);
			for (int i = 0; i < sizeMatrix; i++)
			{
				real sum = Sum(approximationX, A[i]);
				sum = (w / A[i][I[diagAmount / 2]])* (B[i] - sum);
				xK[i] = approximationX[i] + sum;
			}
			approximationX = xK;
			err = Inconspicuous(approximationX);
		}
	}


	inline real norm(vector <real> vector)
	{
		int size = vector.size();
		real answer = 0;

		for (int i = 0; i < size; i++)
			answer += vector[i] * vector[i];

		return sqrt(answer);
	}


	inline real Inconspicuous(vector <real> approximationX)
	{
		return norm(B - Mult(approximationX)) / norm(B);
	}


	vector<real> Mult(vector <real> currentX)
	{
		vector <real> answer(sizeMatrix);

		for (int i = 0; i < sizeMatrix; i++)
		{
			for (int j = 0; j < diagAmount; j++)
				answer[i] += A[i][j] * currentX[I[j]];
		}

		return answer;
	}

	real Sum(vector <real> currentX, int i)
	{
		real answer = 0;
		
		int j0 = abs(I[i]);
		int j1 = j0 + sizeMatrix;

		for (int j = abs(I[i] - 1); j < diagAmount; j++)
			answer += A[i][j] * currentX[I[j]];

		
		return answer;
	}
};