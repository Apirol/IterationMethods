#pragma once
#include "OutputSolution.h"
#include "Vector.h"
#include "SLAE.h"

class IMethod
{
public:

	virtual inline real Iteration(real xki, real w, vector<real> vecAl, vector<real> vecDiAu, real i) = 0;

	virtual vector<real> MatVecMult(vector<real> vec) = 0;

	virtual real Inconspicuous(vector<real> vec) = 0;

};