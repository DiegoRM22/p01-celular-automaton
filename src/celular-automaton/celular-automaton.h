


#ifndef CELULAR_AUTOMATON_H
#define CELULAR_AUTOMATON_H

#include "../lattice/lattice.h"

class CelularAutomaton {
 public:
  CelularAutomaton(const Lattice& lattice) : lattice_(lattice) {}
  Lattice getLattice() const { return lattice_; }
  void transition();
  void printMenu();
  void executeOption(char option, bool& showOnlyPopulation);
  void saveToFile();
 private:
  Lattice lattice_;

};

#endif // CELULAR_AUTOMATON_H