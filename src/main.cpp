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
  std::string f_ = "[]p-><>q";

  Formula * f = parse(f0);
  Formula * g = parse(f_);
  std::cout << f->to_string() << std::endl;
  std::cout << g->to_string() << std::endl;
  Formula * h = uniformly_substitution(f,g,"p");
  delete f;
  delete g;
  std::cout << h->to_string() << std::endl;
}
