#include "SLAE.h"


int main()
{
	SLAE slae;
	InputSLAEHandler input{ "I", "A", "Size", "B" };

	slae.Init(input);
	slae.JakobiSolution();
	return 0;
}