#include "command_parser.hpp"
#include "parser.hpp"
#include "axiom.hpp"
#include "rule.hpp"
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
        if( ret ) {
          theorems.push_back(fml);
        } else {
          delete fml;
        }
      }
    } else if( match("MP", str, p) ) {
      int idx0 = indicator(str, p);
      int idx1 = indicator(str, p);
      if( 0 <= idx0 && static_cast<std::size_t>(idx0) < theorems.size()
        && 0 <= idx1 && static_cast<std::size_t>(idx1) < theorems.size() ) {
        Formula * f = theorems[idx0];
        Formula * f_g = theorems[idx1];
        if( end(str, p) ) {
          Formula * g = modus_ponens(f, f_g);
          if( g != nullptr ) {
            ret = true;
            theorems.push_back(g);
          }
        }
      }
    } else if( match("US", str, p) ) {
    } else if( match("G", str, p) ) {
    }
    return ret;
  }

  int indicator(const std::string & str, std::size_t & p) {
    skip_spaces(str, p);
    int ret = -1;
    if( match("#", str, p) ) {
      ret = number(str, p);
    }
    skip_spaces(str, p);
    return ret;
  }

  int number(const std::string & str, std::size_t & p) {
    skip_spaces(str, p);
    int ret = 0;
    for(; is_number(str[p]); p++) {
      ret *= 10;
      ret += str[p] - '0';
    }
    skip_spaces(str, p);
    return ret;
  }

  bool is_number(char c) {
    return '0' <= c && c <= '9';
  }
}
