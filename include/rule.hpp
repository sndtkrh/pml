#ifndef RULE
#define RULE

#include "formula.hpp"

namespace pml {
  // f,f->g |-> g
  Fmlp modus_ponens(const Fmlp f, const Fmlp f_imply_g);

  // f,g |-> f[g/p]
  Fmlp uniformly_substitution(const Fmlp f, const Fmlp g, const std::string & p);

  // f |-> []f
  Fmlp generalization(const Fmlp f);
}

#endif
