#ifndef RULE
#define RULE

#include "formula.hpp"

namespace pml {
  // f,f->g |-> g
  Formula * modus_ponens(Formula * f, Formula * f_imply_g);

  // f,g |-> f[g/p]
  // Formula * uniformly_substirution(Formula * f, Formula * g, const std::string * p);

  // f |-> []f
  Formula * generalization(Formula * f);
}

#endif
