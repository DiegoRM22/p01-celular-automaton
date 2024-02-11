


#pragma once


#include <vector>
#include <iostream>

#include "cell.h"

class Lattice {
 public:
  Lattice::Lattice(int size, std::string border, std::vector<Cell> cells);
  Lattice(int size, std::string border);
  ~Lattice();
  Cell getCell(int position) const;
  void setCell(Cell cell, int position);
  int getSize() const;
  void nextGeneration();
 private:
  int size_ = 0;
  std::vector<Cell*> cells_;
};

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getSize(); i++) {
    os << lattice.getCell(i).getState().getSymbol();
  }
  return os;
}