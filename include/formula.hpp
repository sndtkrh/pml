#ifndef FORMULA
#define FORMULA
#include <string>
#include <vector>
#include <memory>

namespace pml {
  // the basic modal language
  enum struct operators {
    NonOperator,
    Top, Bottom, // nullary
    Not, Diamond, Box, // unary
    Imply, Equiv, And, Or // binary
  };
  const char * to_string(operators op);

  class Formula;
  typedef std::shared_ptr<Formula> Fmlp;

  class Formula {
  public:
    operators op;

    virtual std::string to_string() const = 0;
    std::vector<Fmlp> get_subformulas() const;
  protected:
    std::vector<Fmlp> subformulas;
  };
  bool same(const Fmlp f, const Fmlp g);
  Fmlp copy(const Fmlp f);

  class Var : public Formula {
  public:
    std::string varname;
    Var(std::string varname);
    std::string to_string() const;
  };

  template <operators Op>
  class NullOp : public Formula {
  public:
    NullOp();
    std::string to_string() const;
  };

  template <operators Op>
  class UnOp : public Formula {
  public:
    UnOp(Fmlp subformula);
    std::string to_string() const;
  private:
    Fmlp subformula;
  };
  template <operators Op>
  Fmlp make_unop(Fmlp f);

  template <operators Op>
  class BinOp : public Formula {
  public:
    BinOp(Fmlp lhs, Fmlp rhs);
    std::string to_string() const;
  private:
    Fmlp lhs, rhs;
  };
  template <operators Op>
  Fmlp make_binop(Fmlp lhs, Fmlp rhs);

}

#endif
