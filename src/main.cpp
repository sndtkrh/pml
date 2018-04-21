#include <iostream>
#include <string>
#include <vector>

#include "formula.hpp"
#include "propositional_logic.hpp"
#include "parser.hpp"

using namespace pml;

int main() {
  std::string modal_fml = "[](p->q)->([]p->[]q)";
  std::string f0 = "(p->q->r)->(p->q)->(p->r)";
  std::string f1 = "((~p\\/(p/\\q))->(p->q))/\\((p->q)->(~p\\/(p/\\q)))";
  std::string f2 = "p/\\q";
  std::string f3 = "~p";

  Formula * fml = parse(f1);
  auto taut = [](Formula * fml) {
    if( is_tautology(fml) ){
      return "tautology";
    }
    return "not tautology";
  };
  std::cout << fml->to_string() << " is " << taut(fml) << std::endl;
}
