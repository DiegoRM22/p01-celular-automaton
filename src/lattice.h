


#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <iostream>

#include "cell.h"

class Lattice {
 public:
  Lattice(int size, std::string border, std::vector<Cell> cells, const int openBorderValue);
  Lattice(int size, std::string border, const std::string& fileName, const int openBorderValue = 0);
  ~Lattice();
  Cell getCell(int position) const;
  std::string getBorder() const { return border_;}
  void setCell(Cell cell, int position);
  int getSize() const;
  void nextGeneration();
  int getOpenBorderValue() const { return openBorderValue_; }

  void addFirstCell(const Cell& cell);
 private:
  std::string border_;
  int openBorderValue_;
  int size_ = 0;
  std::vector<Cell*> cells_;
};

std::ostream& operator<<(std::ostream& os, const Lattice& lattice);

#endif  // LATTICE_H