#pragma once


#include <clasp/config.h>
#include <clasp/logic_program.h>    // for defining logic programs
#include <clasp/unfounded_check.h>  // unfounded set checkers
#include <clasp/model_enumerators.h>// for enumerating answer sets
#include <clasp/solve_algorithms.h> // for enumerating answer sets

#ifdef __APPLE__
#define DllExport(t) extern "C" t
#elif __GNUC__
#define DllExport(t) extern "C" t
#else
#include "stdafx.h"
#include <stdio.h>
#define DllExport(t) extern "C"  __declspec( dllexport ) t __cdecl
#endif


DllExport(Clasp::Asp::LogicProgram*) fNewProgram();
DllExport(Clasp::Asp::Atom_t) fNewAtom(Clasp::Asp::LogicProgram* program);

