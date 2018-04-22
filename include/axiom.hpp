#ifndef AXIOM
#define AXIOM
#include "formula.hpp"
#include <set>

namespace pml {
  extern const Formula * Dual;
  extern const Formula * K;
  extern const std::set<const Formula *> AxiomK;
}

#endif
