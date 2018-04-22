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
  const char * to_string(const operators & op);

  class Formula {
  public:
    operators op;

    virtual std::string to_string() const = 0;
    virtual std::vector<Formula *> get_subformulas() const = 0;
  };
  bool same(const Formula * f, const Formula * g);
  Formula * copy(const Formula * f);

  class Var : public Formula {
  public:
    std::string varname;

    Var(std::string varname);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  class Not : public Formula {
  public:
    Formula * subformula;

    Not(Formula * subformula);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };


  template <operators Op>
  class BinOp : public Formula {
  public:
    Formula * lhs, * rhs;
    BinOp(Formula * lhs, Formula * rhs);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

}

#endif
