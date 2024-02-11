
#include <iostream>

#include "lattice.h"

Lattice::Lattice(int size, std::string border, std::vector<Cell> cells) {
  // El constructor del retículo crea las células en memoria dinámica.
  size_ = size;
  // Usar memoria dinámica para crear las células.
  for (int i = 0; i < cells.size(); i++) {
    Cell* cell = new Cell(State(), i);
    cells_.push_back(cell);
  }
}

Lattice::Lattice(int size, std::string border) {
  size_ = size;
  // Usar memoria dinámica para crear las células.
  for (int i = 0; i < size; i++) {
    if (i == size / 2 + 1) {
      Cell* cell = new Cell(State(1, 'X'), i);
      cells_.push_back(cell);
    } else {
      Cell* cell = new Cell(State(), i);
      cells_.push_back(cell);
    }
  }
}