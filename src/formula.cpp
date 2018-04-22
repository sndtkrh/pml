#include "formula.hpp"

namespace pml {
  const char * to_string(const operators & op) {
    switch(op){
      case(operators::NonOperator) :
        return "";
      case(operators::Top) :
        return "T";
      case(operators::Bottom) :
        return "F";
      case(operators::Not) :
        return "~";
      case(operators::Box) :
        return "[]";
      case(operators::Diamond) :
        return "<>";
      case(operators::Imply) :
        return "->";
      case(operators::And) :
        return "/\\";
      case(operators::Or) :
        return "\\/";
    }
    return "";
  }

  Var::Var(std::string varname) : varname(varname) {
    op = operators::NonOperator;
  }
  std::string Var::to_string() const {
    return varname;
  }
  std::vector<Formula *> Var::get_subformulas() const {
    return {};
  }

  Not::Not(Formula * subformula) : subformula(subformula) {
    op = operators::Not;
  }
  std::string Not::to_string() const {
    return "~" + subformula->to_string();
  }
  std::vector<Formula *> Not::get_subformulas() const {
    return {subformula};
  }

  template <operators Op>
  BinOp<Op>::BinOp(Formula * lhs, Formula * rhs) : lhs(lhs), rhs(rhs) {
    op = Op;
  }
  template <operators Op>
  std::string BinOp<Op>::to_string() const {
    return "(" + lhs->to_string() + pml::to_string(op) + rhs->to_string() + ")";
  }
  template <operators Op>
  std::vector<Formula *> BinOp<Op>::get_subformulas() const {
    return {lhs, rhs};
  }

  template class BinOp<operators::Imply>;
  template class BinOp<operators::And>;
  template class BinOp<operators::Or>;
}
