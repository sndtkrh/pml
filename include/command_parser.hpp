#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include <string>
#include <vector>
#include "formula.hpp"

/*
BNF
<command> ::= <axiom> <formula>
            | <mp> <indicatar> <indicator>
            | <us> <indicator> (<indicatar> | <formula>) <var>
            | <g> <indicator>
<indicator> ::= "#" <number>
<number> = +[0-9]
<axiom> ::= "Axiom"
<mp> ::= "MP"
<us> ::= "US"
<g> ::= "G"
*/

namespace pml {
  bool command_parser(const std::string & str, std::size_t & p, std::vector<Formula *> & theorems);
  // int indicator(const std::string & str, std::size_t & p);
  // int number(const std::string & str, std::size_t & p);
};

#endif
