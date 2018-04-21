#ifndef PARSER
#define PARSER

#include "formula.hpp"
#include <string>

/*
BNF
<formula>
  ::= <subformula> *( "->" <subformula> | "\/" <subformula> | "/\" <subformula> )
<subformula>
  ::= "T" | "F" | <var>
    | "(" <formula> ")"
    | "~" <subformula> | "[]" <subformula> | "[]" <subformula>

<var> ::= +[a-z]
*/

namespace pml {
  Formula * parse(const std::string & str);

  Formula * formula(const std::string & str, std::size_t & p);
  Formula * subformula(const std::string & str, std::size_t & p);
  Formula * var(const std::string & str, std::size_t & p);
  void skip_spaces(const std::string & str, std::size_t &p);
  bool end(const std::string & str, const std::size_t p);
  bool match(const std::string & pattern, const std::string & str, std::size_t &p);
  bool is_lowercase(char c);
}
#endif
