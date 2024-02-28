


#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <iostream>

#include "../cell/cell.h"
#include "../tools/position.h"

class Lattice {
 public:
  //Lattice(int size, std::string border, std::vector<Cell> cells, const int openBorderValue);
  Lattice(int size, std::string border, const std::string& fileName, const int openBorderValue = 0);
  Lattice(const int rows, const int cols, const std::string border);
  // Lattice(const Lattice& lattice);  // NOLINT(runtime/references
  ~Lattice();
  Cell getCell(Position position) const;
  std::string getBorder() const { return border_;}
  void setCell(Cell cell, Position position);
  //int getSize() const;
  int getRowSize() const { return cells_.size(); }
  int getColumnSize() const { return cells_[0].size(); }
  void resizeCells(int rowSize, int columnSize) { cells_.resize(rowSize, std::vector<Cell*>(columnSize)); }
  void resizeBorder();
  void resizingCells();
  void addBorders(int borders[4]);

  size_t population() const;
  // int getOpenBorderValue() const { return openBorderValue_; }
  // std::vector<Cell*> getCells() const { return cells_; }

  Cell& operator[](const Position& position) const;

  
  void nextGeneration();

  void addFirstCell(const Cell& cell);
 private:
  std::string border_;
  int openBorderValue_;
  int size_ = 0;
  std::vector<std::vector<Cell*>> cells_;
};

std::ostream& operator<<(std::ostream& os, const Lattice& lattice);


#endif  // LATTICE_H