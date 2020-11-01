#pragma once
#include "OutputSolution.h"
#include "Vector.h"
#include "SLAE.h"

class IMethod
{
public:

	virtual vector<real> MatVecMult() = 0;

	virtual real Inconspicuous() = 0;

	virtual inline real Iteration() = 0;

	virtual void ReportSolution() = 0;
};