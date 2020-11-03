#pragma once
#include "IMethod.h"


class BlockMethod : IMethod
{
protected:
	vector<vector<SLAE>> slaes;

	BlockMethod(SLAE slae)
	{
		this->slae = slae;
	}

	virtual void Solution() { cout << "Solution was failed"; };

	virtual void ReportSolution() { cout << "Report was failed"; };

	virtual vector<real> MatVecMult() = 0;

	virtual real Inconspicuous() = 0;

	virtual inline real Iteration() = 0;

	virtual void ReportSolution() = 0;
};