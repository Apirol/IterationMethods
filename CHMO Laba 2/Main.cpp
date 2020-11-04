#include "SLAE.h"
#include "JacobiMethod.h"
#include "SeidelMethod.h"


int main()
{
	SLAE slae;
	InputSLAEHandler input{ "I", "A", "Info", "B" };
	slae.Init(input);

	JakobiMethod Jacobi{ slae };
	OutputSolution out{ "Jacoby" };

	out.ReportSolution(Jacobi);
	
	//Jacobi.Solution();

	/*SeidelMethod Seidel{ slae };
	Seidel.Solution();*/

	return 0;
}