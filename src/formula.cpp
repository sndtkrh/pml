#include "formula.hpp"
#include <map>
namespace pml {
  const char * to_string(operators op) {
    const std::map<operators, const char *> M = {
      {operators::NonOperator, ""},
      {operators::Top, "T"},
      {operators::Bottom, "F"},
      {operators::Not, "~"},
      {operators::Box, "[]"},
      {operators::Diamond, "<>"},
      {operators::Imply, "->"},
      {operators::And, "/\\"},
      {operators::Or, "\\/"},
    };
    return M.at(op);
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

  bool same(const Formula * f, const Formula * g) {
    bool ret = true;
    if( f->op == g->op ) {
      if( f->op == operators::NonOperator ) {
        ret = f->to_string() == g->to_string();
      } else {
        std::vector<Formula *> fsub = f->get_subformulas();
        std::vector<Formula *> gsub = g->get_subformulas();
        if( fsub.size() == gsub.size() ) {
          for(std::size_t i = 0; i < fsub.size(); i++) {
            ret = ret && same(fsub[i], gsub[i]);
          }
        } else {
          ret = false;
        }
      }
    } else {
      ret = false;
    }
    return ret;
  }

  Formula * copy(const Formula * f) {
    Formula * ret = nullptr;
    switch(f->op){
      case(operators::NonOperator) :
        ret = new Var(f->to_string());
        break;
      case(operators::Top) :
        break;
      case(operators::Bottom) :
        break;
      case(operators::Not) :
        ret = new Not(f->get_subformulas()[0]);
        break;
      case(operators::Box) :
        break;
      case(operators::Diamond) :
        break;
      case(operators::Imply) :
        {
          Formula * lhs = copy(f->get_subformulas()[0]);
          Formula * rhs = copy(f->get_subformulas()[1]);
          ret = new BinOp<operators::Imply>(lhs, rhs);
        }
        break;
      case(operators::And) :
        {
          Formula * lhs = copy(f->get_subformulas()[0]);
          Formula * rhs = copy(f->get_subformulas()[1]);
          ret = new BinOp<operators::And>(lhs, rhs);
        }
        break;
      case(operators::Or) :
        {
          Formula * lhs = copy(f->get_subformulas()[0]);
          Formula * rhs = copy(f->get_subformulas()[1]);
          ret = new BinOp<operators::Or>(lhs, rhs);
        }
        break;
    }
    return ret;
  }
}
