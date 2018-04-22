#include "axiom.hpp"
#include "parser.hpp"

namespace pml {
  const Formula * Dual = parse("<>p <-> ~[]~p");
  const Formula * K = parse("[](p->q) -> ([]p->[]q)");
}
