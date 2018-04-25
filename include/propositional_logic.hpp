#ifndef PROPOSITIONAL
#define PROPOSITIONAL
#include <string>
#include <vector>
#include <set>
#include <map>
#include "formula.hpp"

namespace pml {
  bool is_propositional_formula(const Fmlp fml);
  std::set<std::string> get_variables(const Fmlp fml);
  bool eval(const Fmlp fml, const std::map<std::string, bool> & valuation);
  bool is_tautology(const Fmlp fml);
};

#endif
