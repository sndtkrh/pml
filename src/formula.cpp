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
      {operators::Equiv, "<->"},
      {operators::And, "/\\"},
      {operators::Or, "\\/"},
    };
    return M.at(op);
  }

  std::vector<Fmlp> Formula::get_subformulas() const {
    return subformulas;
  }

  Var::Var(std::string varname) : varname(varname) {
    op = operators::NonOperator;
  }
  std::string Var::to_string() const {
    return varname;
  }

  template <operators Op>
  NullOp<Op>::NullOp() {
    op = Op;
  }
  template <operators Op>
  std::string NullOp<Op>::to_string() const {
    return pml::to_string(op);
  }
  template class NullOp<operators::Top>;
  template class NullOp<operators::Bottom>;

  template <operators Op>
  UnOp<Op>::UnOp(Fmlp subformula) : subformula(subformula) {
    op = Op;
    subformulas = {subformula};
  }
  template <operators Op>
  std::string UnOp<Op>::to_string() const {
    return pml::to_string(op) + subformula->to_string();
  }
  template class UnOp<operators::Not>;
  template class UnOp<operators::Box>;
  template class UnOp<operators::Diamond>;

  template <operators Op>
  BinOp<Op>::BinOp(Fmlp lhs, Fmlp rhs) : lhs(lhs), rhs(rhs) {
    op = Op;
    subformulas = {lhs, rhs};
  }
  template <operators Op>
  std::string BinOp<Op>::to_string() const {
    return "(" + lhs->to_string() + pml::to_string(op) + rhs->to_string() + ")";
  }
  template class BinOp<operators::Imply>;
  template class BinOp<operators::Equiv>;
  template class BinOp<operators::And>;
  template class BinOp<operators::Or>;


  template <operators Op>
  Fmlp make_binop(Fmlp lhs, Fmlp rhs) {
    Fmlp ret;
    if( lhs && rhs ) ret = std::make_shared<BinOp<Op>>(lhs, rhs);
    return ret;
  }
  template Fmlp make_binop<operators::Imply>(Fmlp lhs, Fmlp rhs);
  template Fmlp make_binop<operators::Equiv>(Fmlp lhs, Fmlp rhs);
  template Fmlp make_binop<operators::And>(Fmlp lhs, Fmlp rhs);
  template Fmlp make_binop<operators::Or>(Fmlp lhs, Fmlp rhs);

  template <operators Op>
  Fmlp make_unop(Fmlp f) {
    Fmlp ret;
    if( f ) ret = std::make_shared<UnOp<Op>>(f);
    return ret;
  }
  template Fmlp make_unop<operators::Not>(Fmlp f);
  template Fmlp make_unop<operators::Box>(Fmlp f);
  template Fmlp make_unop<operators::Diamond>(Fmlp f);

  bool same(const Fmlp f, const Fmlp g) {
    bool ret = true;
    if( f->op == g->op ) {
      if( f->op == operators::NonOperator ) {
        ret = f->to_string() == g->to_string();
      } else {
        std::vector<Fmlp> fsub = f->get_subformulas();
        std::vector<Fmlp> gsub = g->get_subformulas();
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

  Fmlp copy(const Fmlp f) {
    Fmlp ret;
    switch(f->op){
      case(operators::NonOperator) :
        ret = std::make_shared<Var>(f->to_string());
        break;
      case(operators::Top) :
        ret = std::make_shared<NullOp<operators::Top>>();
        break;
      case(operators::Bottom) :
        ret = std::make_shared<NullOp<operators::Bottom>>();
        break;
      case(operators::Not) :
        ret = std::make_shared<UnOp<operators::Not>>(copy(f->get_subformulas()[0]));
        break;
      case(operators::Box) :
        ret = std::make_shared<UnOp<operators::Box>>(copy(f->get_subformulas()[0]));
        break;
      case(operators::Diamond) :
        ret = std::make_shared<UnOp<operators::Diamond>>(copy(f->get_subformulas()[0]));
        break;
      case(operators::Imply) :
        {
          Fmlp lhs = copy(f->get_subformulas()[0]);
          Fmlp rhs = copy(f->get_subformulas()[1]);
          ret = std::make_shared<BinOp<operators::Imply>>(lhs, rhs);
        }
        break;
      case(operators::Equiv) :
        {
          Fmlp lhs = copy(f->get_subformulas()[0]);
          Fmlp rhs = copy(f->get_subformulas()[1]);
          ret = std::make_shared<BinOp<operators::Equiv>>(lhs, rhs);
        }
        break;
      case(operators::And) :
        {
          Fmlp lhs = copy(f->get_subformulas()[0]);
          Fmlp rhs = copy(f->get_subformulas()[1]);
          ret = std::make_shared<BinOp<operators::And>>(lhs, rhs);
        }
        break;
      case(operators::Or) :
        {
          Fmlp lhs = copy(f->get_subformulas()[0]);
          Fmlp rhs = copy(f->get_subformulas()[1]);
          ret = std::make_shared<BinOp<operators::Or>>(lhs, rhs);
        }
        break;
    }
    return ret;
  }
}
