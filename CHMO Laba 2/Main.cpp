#include "SLAE.h"


int main()
{
	SLAE slae;
	InputSLAEHandler input{ "I", "A", "Size", "B" };

	slae.Init(input);
	return 0;
}