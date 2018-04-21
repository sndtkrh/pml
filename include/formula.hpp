#ifndef FORMULA
#define FORMULA
#include <string>
#include <vector>

namespace pml {
  // the basic modal language
  enum struct operators {
    NonOperator,
    Top, Bottom, // nullary
    Not, Diamond, Box, // unary
    Imply, And, Or // binary
  };

  struct Formula {
    operators op;

    virtual std::string to_string() const = 0;
    virtual std::vector<Formula *> get_subformulas() const = 0;
  };

  struct Var : Formula {
    std::string varname;

    Var(std::string varname);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  struct Not : Formula {
    Formula * subformula;

    Not(Formula * subformula);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  struct Imply : Formula {
    Formula * lhs, * rhs;

    Imply(Formula * lhs, Formula * rhs);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  struct And : Formula {
    Formula * lhs, * rhs;

    And(Formula * lhs, Formula * rhs);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  struct Or : Formula {
    Formula * lhs, * rhs;

    Or(Formula * lhs, Formula * rhs);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };
}

#endif
