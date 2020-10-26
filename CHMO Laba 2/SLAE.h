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
		int err = 0;
		int eps = 0.001;
		int MaxIter = 10000;
		real w = 0;

		for (int k = 0; k < MaxIter && err > eps; k++)
		{
			for (int i = 0; i < MaxIter && err > eps; i++)
			{

			}
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

	vector <real> sum(int jMax)
	{

	}
};