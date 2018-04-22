#include "parser.hpp"
#include <cassert>
#include <iostream>

namespace pml {
  Formula * parse(const std::string & str) {
    std::size_t p = 0;
    Formula * fml = formula(str, p);
    return end(str,p) ? fml : nullptr;
  }

  Formula * formula(const std::string & str, std::size_t & p) {
    skip_spaces(str, p);
    Formula * fml = subformula(str, p);
    skip_spaces(str, p);
    if( end(str, p) ) return fml;
    if( match(to_string(operators::Imply), str, p) ) {
      fml = make_binop<operators::Imply>(fml, formula(str, p));
    } else if( match(to_string(operators::Equiv), str, p) ) {
      fml = make_binop<operators::Equiv>(fml, formula(str, p));
    } else if( match(to_string(operators::Or), str, p) ) {
      fml = make_binop<operators::Or>(fml, formula(str, p));
    } else if( match(to_string(operators::And), str, p) ) {
      fml = make_binop<operators::And>(fml, formula(str, p));
    }
    return fml;
  }

  Formula * subformula(const std::string & str, std::size_t & p) {
    skip_spaces(str, p);
    Formula * fml = nullptr;
    if( match("(", str, p) ) {
      fml = formula(str, p);
      skip_spaces(str, p);
      bool endp = match(")", str, p);
      if( !endp ) fml = nullptr;
    } else if( match(to_string(operators::Not), str, p) ) {
      fml = make_unop<operators::Not>( subformula(str, p) );
    } else if( match(to_string(operators::Box), str, p) ){
      fml = make_unop<operators::Box>( subformula(str, p) );
    } else if( match(to_string(operators::Diamond), str, p) ){
      fml = make_unop<operators::Diamond>( subformula(str, p) );
    } else if ( match(to_string(operators::Top), str, p) ){
      fml = new NullOp<operators::Top>();
    } else if ( match(to_string(operators::Bottom), str, p) ){
      fml = new NullOp<operators::Bottom>();
    } else {
      fml = var(str, p);
    }
    skip_spaces(str, p);
    return fml;
  }

  Formula * var(const std::string & str, std::size_t & p) {
    std::string name = varname(str, p);
    return (name == "") ? nullptr : new Var(name);
  }
  std::string varname(const std::string & str, std::size_t & p) {
    skip_spaces(str, p);
    std::string varname = "";
    for(; p < str.size() && is_lowercase(str[p]); p++) {
      varname += str[p];
    }
    skip_spaces(str, p);
    return varname;
  }

  void skip_spaces(const std::string & str, std::size_t & p) {
    for(; p < str.size() && str[p] == ' '; p++) { ; }
  }

  bool end(const std::string & str, const std::size_t p) {
    return p >= str.size();
  }

  bool match(const std::string & pattern, const std::string & str, std::size_t &p) {
    if( end(str, p + pattern.size() - 1) ) return false;
    bool f = true;
    for(std::size_t i = 0; i < pattern.size(); i++) {
      f = f && (pattern[i] == str[p + i]);
    }
    if(f) p = p + pattern.size();
    return f;
  }

  bool is_lowercase(char c) {
    return 'a' <= c && c <= 'z';
  }
}
