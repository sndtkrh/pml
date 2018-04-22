#include "axiom.hpp"
#include "parser.hpp"

namespace pml {
  const Formula * DualB = parse("<>p <-> ~[]~p");
  const Formula * DualD = parse("[]p <-> ~<>~p");
  const Formula * K = parse("[](p->q) -> ([]p->[]q)");
  const std::set<const Formula *> AxiomK = {DualB, DualD, K};
}
