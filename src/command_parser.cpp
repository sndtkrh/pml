#include "command_parser.hpp"
#include "parser.hpp"
#include "axiom.hpp"
#include "rule.hpp"
#include "propositional_logic.hpp"

namespace pml {
  bool command_parser(const std::string & str, std::size_t & p, Thms & theorems, ThmDict & thm_dict) {
    bool ret = false;
    skip_spaces(str, p);
    if( match("//", str, p) ) {
      ret = true;
    } else if( match("Q", str, p) ) {
      skip_spaces(str, p);
      if( end(str, p) ) exit(0);
    } else if( match("Axiom", str, p) ) {
      Fmlp fml = formula(str, p);
      skip_spaces(str, p);
      if( end(str,p) && fml ) {
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
        }
      }
    } else if( match("MP", str, p) ) {
      Fmlp f = indicator(str, p, theorems, thm_dict);
      Fmlp f_g = indicator(str, p, theorems, thm_dict);
      if( f && f_g && end(str, p) ) {
        Fmlp g = modus_ponens(f, f_g);
        if( g ) {
          ret = true;
          theorems.push_back(g);
        }
      }
    } else if( match("US", str, p) ) {
      Fmlp f = indicator(str, p, theorems, thm_dict);
      if( f ) {
        Fmlp g = indicator(str, p, theorems, thm_dict);
        if( !g ) {
          g = formula(str, p);
        }
        if( g ) {
          std::string name = varname(str, p);
          if( end(str, p) && name.size() > 0 ) {
            ret = true;
            theorems.push_back(uniformly_substitution(f, g, name));
          }
        }
      }
    } else if( match("G", str, p) ) {
      Fmlp f = indicator(str, p, theorems, thm_dict);
      if( f && end(str, p) ){
        ret = true;
        Fmlp g = generalization(f);
        theorems.push_back(g);
      }
    } else if( match("Name", str, p) ) {
      ret = true;
      Fmlp f = indicator(str, p, theorems, thm_dict);
      skip_spaces(str, p);
      std::string name = theorem_name(str, p);
      skip_spaces(str, p);
      if( end(str, p) && f && thm_dict.find(name) == thm_dict.end() ) {
        thm_dict[name] = f;
      }
    }
    return ret;
  }

  Fmlp indicator(const std::string & str, std::size_t & p, Thms & theorems, ThmDict & thm_dict) {
    skip_spaces(str, p);
    Fmlp ret;
    if( match("#", str, p) ) {
      if( is_number(str[p]) ) {
        int idx = number(str, p);
        if( 0 <= idx && static_cast<std::size_t>(idx) < theorems.size() ) {
          ret = theorems[idx];
        }
      } else if( match("^", str, p) ) {
        if( theorems.size() > 0 ) {
          ret = theorems[theorems.size() - 1];
        }
      } else {
        std::string thm_name = theorem_name(str, p);
        if( thm_dict.find(thm_name) != thm_dict.end() ) {
          ret = thm_dict[thm_name];
        }
      }
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

  std::string theorem_name(const std::string & str, std::size_t & p) {
    return varname(str, p);
  }

  bool is_number(char c) {
    return '0' <= c && c <= '9';
  }
}
