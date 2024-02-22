


#ifndef CELULAR_AUTOMATON_H
#define CELULAR_AUTOMATON_H

#include "lattice.h"

class CelularAutomaton {
 public:
  CelularAutomaton(const Lattice& lattice) : lattice_(lattice) {}
  Lattice getLattice() const { return lattice_; }
  void transition();
 private:
  Lattice lattice_;

};

#endif // CELULAR_AUTOMATON_H