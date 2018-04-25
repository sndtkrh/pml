#include "rule.hpp"

namespace pml {
  Fmlp modus_ponens(const Fmlp f, const Fmlp f_imply_g) {
    Fmlp ret;
    if ( (f_imply_g->op == operators::Imply) && same(f, f_imply_g->get_subformulas()[0]) ){
      ret = f_imply_g->get_subformulas()[1];
    }
    return ret;
  }

  Fmlp uniformly_substitution(const Fmlp f, const Fmlp g, const std::string & p) {
    Fmlp ret;
    switch(f->op) {
      case(operators::NonOperator) :
        if( f->to_string() == p ) {
          ret = copy(g);
        } else {
          ret = copy(f);
        }
        break;
      case(operators::Top) :
        ret = std::make_shared<NullOp<operators::Top>>();
        break;
      case(operators::Bottom) :
        ret = std::make_shared<NullOp<operators::Top>>();
        break;
      case(operators::Not) :
        ret = std::make_shared<UnOp<operators::Not>>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Box) :
        ret = std::make_shared<UnOp<operators::Box>>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Diamond) :
        ret = std::make_shared<UnOp<operators::Diamond>>( uniformly_substitution(f->get_subformulas()[0], g, p) );
        break;
      case(operators::Imply) :
        {
          Fmlp lhs = f->get_subformulas()[0];
          Fmlp rhs = f->get_subformulas()[1];
          ret = std::make_shared<BinOp<operators::Imply>>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
      case(operators::Equiv) :
        {
          Fmlp lhs = f->get_subformulas()[0];
          Fmlp rhs = f->get_subformulas()[1];
          ret = std::make_shared<BinOp<operators::Equiv>>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
      case(operators::And) :
        {
          Fmlp lhs = f->get_subformulas()[0];
          Fmlp rhs = f->get_subformulas()[1];
          ret = std::make_shared<BinOp<operators::And>>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
      case(operators::Or) :
        {
          Fmlp lhs = f->get_subformulas()[0];
          Fmlp rhs = f->get_subformulas()[1];
          ret = std::make_shared<BinOp<operators::Or>>(
            uniformly_substitution(lhs, g, p),
            uniformly_substitution(rhs, g, p)
          );
        }
        break;
    }
    return ret;
  }

  Fmlp generalization(const Fmlp f) {
    return std::make_shared<UnOp<operators::Box>>( f );
  }
}
