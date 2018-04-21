#include <iostream>
#include <string>
#include <vector>

#include "formula.hpp"
#include "propositional_logic.hpp"
using namespace pml;

int main() {
  std::string fml = "[](p->q)->([]p->[]q)";
  Var p("p");
  Var q("q");
  Not np(&p);
  Imply q_imply_np(&q, &np);
  Imply p_imply_p(&np, &np);

  auto taut = [](Formula * fml) {
    if( is_tautology(fml) ){
      return "tautology";
    }
    return "not tautology";
  };
  std::cout << q_imply_np.to_string() << " is " << taut(&q_imply_np) << std::endl;
  std::cout << p_imply_p.to_string() << " is " << taut(&p_imply_p) << std::endl;
}
