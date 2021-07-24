#include "hpglrun.h"



typedef struct RunContext
{
	// A System Unit (SU) or plotter unit is 1/40 mm represented as 1px on screen
	// User units (UU) are runtime user defined units, defined with IP and SC commands

	int selectedPen; // Which pen is selected
	int posX; // in SU
	int posY; // in SU
	int penUp; // bool
	int userXOffset; // in system units (where UU(X) = 0 is in SU)
	int userYOffset; // in system units (where UU(Y) = 0 is in SU)
	float userXScale; //how many SUs is 1 UU(X), >1;
	float userYScale; //how many SUs is 1 UU(Y), >1;
	int stdchar;
	int altchar;
	int stdselected; // bool
	char bufferedLabel[256];
} RunContext;



/* static int execInstr(HPGLInstruction instr, RunContext* ctx) {
	switch (instr.cmd)
	{
		
	}
	return 0;
} */