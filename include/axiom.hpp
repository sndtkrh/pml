#ifndef AXIOM
#define AXIOM
#include "formula.hpp"
#include <set>

namespace pml {
  extern const Formula * DualB;
  extern const Formula * DualD;
  extern const Formula * K;
  extern const std::set<const Formula *> AxiomK;
}

#endif
