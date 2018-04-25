#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include <string>
#include <vector>
#include <map>
#include "formula.hpp"

/*
BNF
<command> ::= <quit> | <comment>
            | <axiom> <formula>
            | <mp> <indicatar> <indicator>
            | <us> <indicator> (<indicatar> | <formula>) <varname>
            | <g> <indicator>
            | <name> <indicator> <theorem_name>
<indicator> ::= "#" (<number> | <theorem_name> | "^")
<number> = +[0-9]
<axiom> ::= "Axiom"
<mp> ::= "MP"
<us> ::= "US"
<g> ::= "G"
<quit> ::= "Q"
<comment> ::= "//" <string>
<name> ::= "Name"
<theorem_name> ::= <varname>
*/

namespace pml {
  typedef std::vector<Fmlp> Thms;
  typedef std::map<std::string, Fmlp> ThmDict;

  bool command_parser(const std::string & str, std::size_t & p, Thms & theorems, ThmDict & thm_dict);
  Fmlp indicator(const std::string & str, std::size_t & p, Thms & theorems, ThmDict & thm_dict);
  std::string theorem_name(const std::string & str, std::size_t & p);
  int number(const std::string & str, std::size_t & p);
  bool is_number(char c);
};

#endif
