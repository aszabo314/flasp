// FlaspNative.cpp : Defines the exported functions for the DLL application.
//

#include "FlaspNative.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace Potassco;

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

	auto a = lp.newAtom();
	auto b = lp.newAtom();

	lp.addRule(rb.start().addHead(a).addGoal(Potassco::neg(b)));
	lp.addRule(rb.start().addHead(b).addGoal(Potassco::neg(a)));

	lp.addOutput("a", a);
	lp.addOutput("b", b);


	// exist(a).
	// exist(b).
	// related(A,B) :- exist(A), exist(B).


	vector<Atom_t> atoms;
	atoms.push_back(a);
	atoms.push_back(b);
	auto span = Potassco::toSpan(atoms);
	
	lp.addRule(rb.start().addHead(!a));
	//lp.addRule(rb.start().addHead(b));

	lp.endProgram();

	Clasp::ModelEnumerator enumerator;
	enumerator.init(ctx);

	ctx.endInit();

	Clasp::BasicSolve solve(*ctx.master());
	enumerator.start(solve.solver());

	while (solve.solve() == Clasp::value_true) {
		if (enumerator.commitModel(solve.solver()))
		{
			auto model = enumerator.lastModel();

			for (Clasp::OutputTable::fact_iterator it = ctx.output.fact_begin(), end = ctx.output.fact_end(); it != end; ++it) {
				std::cout << "FACT:" << *it << " ";
			}

			std::cout << std::endl;
			for (Clasp::OutputTable::pred_iterator it = ctx.output.pred_begin(), end = ctx.output.pred_end(); it != end; ++it) {
				if (model.isTrue(it->cond)) {
					std::cout << "PRED: " << it->name << " ";
				}
				else
				{
					std::cout << "PRED: NOT " << it->name << " ";
				}
			}

			std::cout << std::endl;
			for (Clasp::OutputTable::range_iterator it = ctx.output.vars_begin(), end = ctx.output.vars_end(); it != end; ++it) {
				std::cout << (model.isTrue(Clasp::posLit(*it)) ? int(*it) : -int(*it)) << " ";
			}

			std::cout << std::endl;




		}
		enumerator.update(solve.solver());
	}

	std::cout << "finished" << std::endl;
}

DllExport(void) testEverything()
{
	test();
}