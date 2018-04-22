#include "parser.hpp"
#include <cassert>
#include <iostream>

namespace pml {
  Formula * parse(const std::string & str) {
    std::size_t p = 0;
    Formula * fml = formula(str, p);
    assert( end(str, p) );
    return fml;
  }

  Formula * formula(const std::string & str, std::size_t & p) {
    // std::cout << "formula " << p << std::endl;
    skip_spaces(str, p);
    Formula * fml = subformula(str, p);
    skip_spaces(str, p);
    if( end(str, p) ) return fml;
    if( match(to_string(operators::Imply), str, p) ) {
      fml = new BinOp<operators::Imply>(fml, formula(str, p));
    } else if( match(to_string(operators::Or), str, p) ) {
      fml = new BinOp<operators::Or>(fml, formula(str, p));
    } else if( match(to_string(operators::And), str, p) ) {
      fml = new BinOp<operators::And>(fml, formula(str, p));
    }
    return fml;
  }

  Formula * subformula(const std::string & str, std::size_t & p) {
    // std::cout << "subformula " << p << std::endl;
    skip_spaces(str, p);
    Formula * fml = nullptr;
    if( match("(", str, p) ) {
      fml = formula(str, p);
      skip_spaces(str, p);
      bool endp = match(")", str, p);
      assert( endp );
    } else if( match(to_string(operators::Not), str, p) ) {
      fml = new UnOp<operators::Not>( subformula(str, p) );
    } else if( match(to_string(operators::Box), str, p) ){
      fml = new UnOp<operators::Box>( subformula(str, p) );
    } else if( match(to_string(operators::Diamond), str, p) ){
      fml = new UnOp<operators::Diamond>( subformula(str, p) );
    } else {
      fml = var(str, p);
    }
    skip_spaces(str, p);
    return fml;
  }

  Formula * var(const std::string & str, std::size_t & p) {
    // std::cout << "var " << p << std::endl;
    skip_spaces(str, p);
    std::string varname = "";
    for(; p < str.size() && is_lowercase(str[p]); p++) {
      varname += str[p];
    }
    skip_spaces(str, p);
    return (varname == "") ? nullptr : new Var(varname);
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
