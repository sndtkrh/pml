#include <iostream>
#include <string>
#include <vector>

#include "pml.hpp"
using namespace pml;

void interactive_mode();
int main() {
  std::cout << "PML -- A Proof Assistant for Modal Logic" << std::endl;
  std::cout << "Axioms are :" << std::endl;
  for(const auto & axiom : AxiomK) {
    std::cout << axiom->to_string() << std::endl;
  }
  interactive_mode();
}

void interactive_mode() {
  std::vector<Formula *> theorems;
  std::string command;
  std::cout << ">> " << std::flush;
  while(std::getline(std::cin, command)){
    std::size_t p = 0;
    if( command_parser(command, p, theorems) ){
      std::size_t i = theorems.size() - 1;
      std::cout << "#" << i << "  |- " << theorems[i]->to_string() << std::endl;
    } else {
      std::cout << "Failed." << std::endl;
    }
    std::cout << ">> " << std::flush;
  }
  std::cout << std::endl;
}
