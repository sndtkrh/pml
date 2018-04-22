#ifndef RULE
#define RULE

#include "formula.hpp"

namespace pml {
  // f,f->g |-> g
  Formula * modus_ponens(const Formula * f, const Formula * f_imply_g);

  // f,g |-> f[g/p]
  Formula * uniformly_substitution(const Formula * f, const Formula * g, const std::string & p);

  // f |-> []f
  Formula * generalization(const Formula * f);
}

#endif
