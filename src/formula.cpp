#include "formula.hpp"

namespace pml {
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

  Imply::Imply(Formula * lhs, Formula * rhs) : lhs(lhs), rhs(rhs) {
    op = operators::Imply;
  }
  std::string Imply::to_string() const {
    return "(" + lhs->to_string() + "->" + rhs->to_string() + ")";
  }
  std::vector<Formula *> Imply::get_subformulas() const {
    return {lhs, rhs};
  }

  And::And(Formula * lhs, Formula * rhs) : lhs(lhs), rhs(rhs) {
    op = operators::Imply;
  }
  std::string And::to_string() const {
    return "(" + lhs->to_string() + "/\\" + rhs->to_string() + ")";
  }
  std::vector<Formula *> And::get_subformulas() const {
    return {lhs, rhs};
  }

  Or::Or(Formula * lhs, Formula * rhs) : lhs(lhs), rhs(rhs) {
    op = operators::Imply;
  }
  std::string Or::to_string() const {
    return "(" + lhs->to_string() + "\\/" + rhs->to_string() + ")";
  }
  std::vector<Formula *> Or::get_subformulas() const {
    return {lhs, rhs};
  }
}
