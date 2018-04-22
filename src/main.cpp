#include <iostream>
#include <string>
#include <vector>

#include "pml.hpp"
using namespace pml;

int main() {
  std::string modal_fml = "[](p->q)->([]p->[]q)";
  std::string f5 = "T->T";
  std::string f0 = "(p->q->r)->(p->q)->(p->r)";
  std::string f1 = "(( ~p\\/(p/\\q) )->(p->q)) /\\ ((p->q)->( ~p\\/(p/\\q) ))";
  std::string f2 = "( ~p\\/(p/\\q) ) -> (p->q)";
  std::string f_g_ = "(p->q)->q";
  std::string f_ = "[]p-><>q";

  std::cout << K->to_string() << std::endl;
  std::cout << Dual->to_string() << std::endl;
}
