#include <iostream>
#include <string>
#include <vector>

#include "pml.hpp"
using namespace pml;

int main() {
  std::string modal_fml = "[](p->q)->([]p->[]q)";
  std::string f0 = "(p->q->r)->(p->q)->(p->r)";
  std::string f1 = "(( ~p\\/(p/\\q) )->(p->q)) /\\ ((p->q)->( ~p\\/(p/\\q) ))";
  std::string f2 = "( ~p\\/(p/\\q) ) -> (p->q)";
  std::string f_g_ = "(p->q)->q";
  std::string f_ = "p->q";

  Formula * f = parse(f_);
  std::cout << f->to_string() << std::endl;
  Formula * Gf = generalization(f);
  std::cout << Gf->to_string() << std::endl;
  delete f;
}
