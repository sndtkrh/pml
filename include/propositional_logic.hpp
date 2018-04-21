#ifndef PROPOSITIONAL
#define PROPOSITIONAL
#include <string>
#include <vector>
#include <set>
#include <map>
#include "formula.hpp"

namespace pml {
  bool is_propositional_formula(const Formula * fml);
  std::set<std::string> get_variables(const Formula * fml);
  bool eval(const Formula * fml, const std::map<std::string, bool> & valuation);
  bool is_tautology(const Formula * fml);
};

#endif
