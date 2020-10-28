#include "SLAE.h"


int main()
{
	SLAE slae;
	InputSLAEHandler input{ "I", "A", "Info", "B" };

	slae.Init(input);
	//slae.JakobiSolution(); 
	slae.SeidelSolution();
	return 0;
}