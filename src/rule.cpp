#include "rule.hpp"

namespace pml {
  Formula * modus_ponens(Formula * f, Formula * f_imply_g) {
    if ( (f_imply_g->op == operators::Imply) && same(f, f_imply_g->get_subformulas()[0]) ){
      return copy( f_imply_g->get_subformulas()[1] );
    }
    return nullptr;
  }

  Formula * generalization(Formula * f) {
    return new UnOp<operators::Box>( copy(f) );
  }
}
