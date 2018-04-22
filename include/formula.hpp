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
    Imply, Equiv, And, Or // binary
  };
  const char * to_string(operators op);

  class Formula {
  public:
    operators op;
    virtual ~Formula();
    virtual std::string to_string() const = 0;
    virtual std::vector<Formula *> get_subformulas() const = 0;
  protected:
    std::vector<Formula *> subformulas;
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

  template <operators Op>
  class NullOp : public Formula {
  public:
    NullOp();
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  };

  template <operators Op>
  class UnOp : public Formula {
  public:
    UnOp(Formula * subformula);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  private:
    Formula * subformula;
  };

  template <operators Op>
  class BinOp : public Formula {
  public:
    BinOp(Formula * lhs, Formula * rhs);
    std::string to_string() const;
    std::vector<Formula *> get_subformulas() const;
  private:
    Formula * lhs, * rhs;
  };

}

#endif
