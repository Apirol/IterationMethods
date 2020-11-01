#pragma once
#include "IMethod.h"


class BlockMethod : IMethod
{
public:
	SLAE slae;

	BlockMethod(SLAE slae)
	{
		this->slae = slae;
	}


	virtual vector<real> MatVecMult() = 0;

	virtual real Inconspicuous() = 0;

	virtual inline real Iteration() = 0;

	virtual void ReportSolution() = 0;
};