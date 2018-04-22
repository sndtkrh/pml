#include "command_parser.hpp"
#include "parser.hpp"
#include "axiom.hpp"
#include "propositional_logic.hpp"

namespace pml {
  bool command_parser(const std::string & str, std::size_t & p, std::vector<Formula *> & theorems) {
    bool ret = false;
    skip_spaces(str, p);
    if( match("Axiom", str, p) ) {
      Formula * fml = formula(str, p);
      skip_spaces(str, p);
      if( end(str,p) && fml != nullptr ) {
        if( is_propositional_formula(fml) && is_tautology(fml) ) {
          ret = true;
        } else {
          for(const auto & axiom : AxiomK) {
            if( same(fml, axiom) ) {
              ret = true;
              break;
            }
          }
        }
        if( ret )
          theorems.push_back(fml);
      }
    } else if( match("MP", str, p) ) {
    } else if( match("US", str, p) ) {
    } else if( match("G", str, p) ) {
    }
    return ret;
  }
}
