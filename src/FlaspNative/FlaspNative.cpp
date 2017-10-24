// FlaspNative.cpp : Defines the exported functions for the DLL application.
//

#include "FlaspNative.h"


DllExport(Clasp::Asp::LogicProgram*) fNewProgram()
{
	return new Clasp::Asp::LogicProgram();
}

DllExport(void) fFreeProgram(Clasp::Asp::LogicProgram* program)
{
	delete program;
}

DllExport(Clasp::Asp::Atom_t) fNewAtom(Clasp::Asp::LogicProgram* program)
{
	return program->newAtom();
}

void test()
{
	Clasp::Asp::LogicProgram lp;
	Potassco::RuleBuilder rb;

	// Among other things, SharedContext maintains a Solver object
	// which hosts the data and functions for CDNL answer set solving.
	// See shared_context.h for details.
	Clasp::SharedContext ctx;

	// startProgram must be called once before we can add atoms/rules
	lp.startProgram(ctx);
}
