#include "SLAE.h"
#include "JacobiMethod.h"
#include "SeidelMethod.h"

using namespace std;

int main()
{
	SLAE slae;
	InputSLAEHandler input{ "I", "A", "Info", "B" };
	slae.Init(input);

	//JakobiMethod Jacobi{ slae };
	//Jacobi.ReportSolution("JacobyReport");

	SeidelMethod Seidel{ slae };
	Seidel.ReportSolution("SeidelSolution");

	return 0;
}