#include "rule.hpp"

namespace pml {
  Formula * modus_ponens(const Formula * f, const Formula * f_imply_g) {
    if ( (f_imply_g->op == operators::Imply) && same(f, f_imply_g->get_subformulas()[0]) ){
      return copy( f_imply_g->get_subformulas()[1] );
    }
    return nullptr;
  }

  Formula * uniformly_substitution(const Formula * f, const Formula * g, const std::string & p) {
    Formula * ret = nullptr;
    switch(f->op) {
      case(operators::NonOperator) :
        if( f->to_string() == p ) {
          ret = copy(g);
        } else {
          ret = copy(f);
        }
        break;
      case(operators::Top) :
      case(operators::Bottom) :
        break;
      case(operators::Not) :
        ret = new UnOp<operators::Not>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Box) :
        ret = new UnOp<operators::Box>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Diamond) :
        ret = new UnOp<operators::Diamond>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Imply) :
        {
          Formula * lhs = f->get_subformulas()[0];
          Formula * rhs = f->get_subformulas()[1];
          ret = new BinOp<operators::Imply>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
      case(operators::And) :
        {
          Formula * lhs = f->get_subformulas()[0];
          Formula * rhs = f->get_subformulas()[1];
          ret = new BinOp<operators::And>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
      case(operators::Or) :
        {
          Formula * lhs = f->get_subformulas()[0];
          Formula * rhs = f->get_subformulas()[1];
          ret = new BinOp<operators::Or>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
    }
    return ret;
  }

  Formula * generalization(const Formula * f) {
    return new UnOp<operators::Box>( copy(f) );
  }
}
