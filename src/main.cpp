#include <iostream>
#include <string>
#include <vector>

#include "formula.hpp"
#include "propositional_logic.hpp"
#include "parser.hpp"
#include "rule.hpp"

using namespace pml;

int main() {
  std::string modal_fml = "[](p->q)->([]p->[]q)";
  std::string f0 = "(p->q->r)->(p->q)->(p->r)";
  std::string f1 = "(( ~p\\/(p/\\q) )->(p->q)) /\\ ((p->q)->( ~p\\/(p/\\q) ))";
  std::string f2 = "( ~p\\/(p/\\q) ) -> (p->q)";
  std::string f_g_ = "p->q";
  std::string f_ = "p";

  Formula * f_g = parse(f_g_);
  Formula * f = parse(f_);
  Formula * g = modus_ponens(f, f_g);
  std::cout << g->to_string() << std::endl;
}
