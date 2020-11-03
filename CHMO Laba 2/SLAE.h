#pragma once
#include "InputSLAEHandler.h"
#include "OutputSolution.h"
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

	// Инициализация матрицы 
	void Init(InputSLAEHandler input)
	{
		// Ввод размерностей, максимального числа итераций и точности решения
		input.InputInfo(&sizeMatrix, &nonZeroLen1, &nonZeroLen2, &maxiter, &eps);

		Al.resize(sizeMatrix);
		Au.resize(sizeMatrix);
		di.resize(sizeMatrix);
		X.resize(sizeMatrix);

		// Ввод матрицы
		input.InputMatrix(sizeMatrix, &Al, &Au, &di);

		// Ввод вектора правой части
		B = input.InputVectorB(sizeMatrix);

		// Расчет массива I со сдвигами диагоналей
		InitI();

		// Расчет нормы вектора правой части
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

	// Расчет нормы вектора
	inline real Norm(vector<real> vec)
	{
		int size = vec.size();
		real answer = 0;

		for (int i = 0; i < size; i++)
			answer += vec[i] * vec[i];

		return sqrt(answer);
	}
};