#include "axiom.hpp"
#include "parser.hpp"

namespace pml {
  const Fmlp DualB = parse("<>p <-> ~[]~p");
  const Fmlp DualD = parse("[]p <-> ~<>~p");
  const Fmlp K = parse("[](p->q) -> ([]p->[]q)");
  const std::vector<Fmlp> AxiomK = {DualB, DualD, K};
}
