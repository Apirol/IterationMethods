#pragma once
#include "InputSLAEHandler.h"
#include "OutputSLAEHandler.h"

typedef double real;
const int n = 100;

using namespace std;

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


	void YakobiSolution()
	{
		vector <real> initialX (n, 0);

			
	}


	inline real norm(vector <real> vector)
	{

	}


	inline real Inconspicuous()
	{
		return norm(B)
	}


	vector<real> Mult(vector <real> currentX)
	{
		vector <real> answer(sizeMatrix);

		for(int i = 0; i < sizeMatrix; i++)
			answer[i] += 
	}
};