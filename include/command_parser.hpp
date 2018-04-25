#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include <string>
#include <vector>
#include "formula.hpp"

/*
BNF
<command> ::= <quit> | <comment>
            | <axiom> <formula>
            | <mp> <indicatar> <indicator>
            | <us> <indicator> (<indicatar> | <formula>) <varname>
            | <g> <indicator>
<indicator> ::= "#" <number>
<number> = +[0-9]
<axiom> ::= "Axiom"
<mp> ::= "MP"
<us> ::= "US"
<g> ::= "G"
<quit> ::= "Q"
<comment> ::= "//" <string>
*/

namespace pml {
  bool command_parser(const std::string & str, std::size_t & p, std::vector<Fmlp> & theorems);
  int indicator(const std::string & str, std::size_t & p);
  int number(const std::string & str, std::size_t & p);
  bool is_number(char c);
};

#endif
