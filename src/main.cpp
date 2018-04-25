#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "pml.hpp"
using namespace pml;

void interactive_mode(std::vector<Fmlp> & theorems);
void filechecking(const std::string & filename, std::vector<Fmlp> & theorems);
int main(int argc, char *argv[]) {
  std::vector<Fmlp> theorems;
  if( argc == 1 ) {
    interactive_mode(theorems);
  } else if( argc == 2 ) {
    filechecking(argv[1], theorems);
  } else {
    std::cout << "Usage :" << std::endl;
    std::cout << "    pml              [interactive mode]" << std::endl;
    std::cout << "    pml <filename>   [cheking proof of the <filename>]" << std::endl;
  }
}

void interactive_mode(std::vector<Fmlp> & theorems) {
  std::cout << "PML -- A Proof Assistant for Modal Logic" << std::endl;
  std::cout << "Axioms are :" << std::endl;
  for(const auto & axiom : AxiomK) {
    std::cout << axiom->to_string() << std::endl;
  }

  std::string command;
  std::cout << ">> " << std::flush;
  while(std::getline(std::cin, command)){
    std::size_t p = 0;
    std::size_t j = theorems.size();
    if( command_parser(command, p, theorems) ){
      std::size_t i = theorems.size();
      if( j < i ) {
        std::cout << "#" << i - 1 << "  |- " << theorems[i - 1]->to_string() << std::endl;
      }
    } else {
      std::cout << "Failed." << std::endl;
    }
    std::cout << ">> " << std::flush;
  }
  std::cout << std::endl;
}

void filechecking(const std::string & filename, std::vector<Fmlp> & theorems) {
  std::ifstream fin;
  fin.open(filename, std::ios::in);
  if( !fin ){
    std::cout << "Error : cannot open the file " << filename << "." << std::endl;
    exit(1);
  }
  bool failed = false;
  std::string source;
  int line = 1;
  while(std::getline(fin, source)) {
    std::size_t p = 0;
    std::size_t j = theorems.size();
    if( command_parser(source, p, theorems) ){
      std::size_t i = theorems.size();
      if( j < i ) {
        std::cout << "#" << i - 1 << "  |- " << theorems[i - 1]->to_string() << std::endl;
      }
    } else {
      std::cout << "Failed at line " << line << std::endl;
      failed = true;
      break;
    }
    line++;
  }
  if( failed ) {
    std::cout << "\x1b[32mERROR\x1b[39m" << std::endl;
  } else {
    std::cout << "\x1b[32mOK\x1b[39m" << std::endl;
  }
}
