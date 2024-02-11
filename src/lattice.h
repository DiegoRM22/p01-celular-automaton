


#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <iostream>

#include "cell.h"

class Lattice {
 public:
  Lattice(int size, std::string border, std::vector<Cell> cells);
  Lattice(int size, std::string border);
  ~Lattice();
  Cell getCell(int position) const;
  std::string getBorder() const { return border_;}
  void setCell(Cell cell, int position);
  int getSize() const;
  void nextGeneration();
 private:
  std::string border_;
  int size_ = 0;
  std::vector<Cell*> cells_;
};

std::ostream& operator<<(std::ostream& os, const Lattice& lattice);

#endif  // LATTICE_H