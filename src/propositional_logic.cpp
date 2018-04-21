#include "propositional_logic.hpp"
#include <cassert>
#include <algorithm>
#include <iterator>

namespace pml {
  bool is_propositional_formula(const Formula * fml){
    switch(fml->op){
      case operators::NonOperator :
      case operators::Top :
      case operators::Bottom :
        return true;
      case operators::Not :
        return is_propositional_formula(fml->get_subformulas()[0]);
      case operators::Diamond :
      case operators::Box :
        return false;
      case operators::Imply :
      case operators::And :
      case operators::Or :
        auto fmls = fml->get_subformulas();
        return is_propositional_formula(fmls[0])
          && is_propositional_formula(fmls[1]);
    }
    return false;
  }

  std::set<std::string> get_variables(const Formula * fml) {
    switch(fml->op){
      case operators::NonOperator :
        return {fml->to_string()};
      case operators::Top :
      case operators::Bottom :
        return {};
      case operators::Not :
      case operators::Diamond :
      case operators::Box :
        return get_variables(fml->get_subformulas()[0]);
      case operators::Imply :
      case operators::And :
      case operators::Or :
        auto fmls = fml->get_subformulas();
        std::set<std::string> s0 = get_variables(fmls[0]);
        std::set<std::string> s1 = get_variables(fmls[1]);
        std::set<std::string> t;
        std::set_union( std::begin(s0), std::end(s0),
          std::begin(s1), std::end(s1),
          std::inserter(t, std::end(t)) );
        return t;
    }
    return {};
  }

  bool eval(const Formula * fml, std::map<std::string, bool> & valuation){
    assert(is_propositional_formula(fml));
    switch(fml->op){
      case operators::NonOperator :
        return valuation[fml->to_string()];
      case operators::Top :
        return true;
      case operators::Bottom :
        return false;
      case operators::Not :
        return !eval(fml->get_subformulas()[0], valuation);
      case operators::Imply :
        {
          auto fmls = fml->get_subformulas();
          bool v = eval(fmls[0], valuation);
          return (!v) || (v && eval(fmls[1], valuation));
        }
      case operators::And :
        {
          auto fmls = fml->get_subformulas();
          return eval(fmls[0], valuation) && eval(fmls[0], valuation);
        }
      case operators::Or :
        {
          auto fmls = fml->get_subformulas();
          return eval(fmls[0], valuation) || eval(fmls[1], valuation);
        }
      default :
        return false;
    }
  }

  bool is_tautology(const Formula * fml) {
    std::set<std::string> phi = get_variables(fml);
    std::map<std::string, bool> valuation;
    std::vector<std::string> index;
    for(const auto & p : phi) {
      valuation[p] = false;
      index.push_back(p);
    }
    bool ans = eval(fml, valuation);
    for(std::size_t i = 0; i < (static_cast<std::size_t>(1) << phi.size()); i++) {
      for(std::size_t j = 0; j < phi.size(); j++) {
        if(valuation[index[j]]) {
          valuation[index[j]] = false;
        } else {
          valuation[index[j]] = true;
          break;
        }
      }
      ans = ans && eval(fml, valuation);
      if( !ans ) break;
    }
    return ans;
  }
}
