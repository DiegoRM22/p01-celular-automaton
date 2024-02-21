
#include <iostream>

#include "lattice.h"

Lattice::Lattice(int size, std::string border, std::vector<Cell> cells) {
  // El constructor del retículo crea las células en memoria dinámica.
  size_ = size;
  border_ = border;
  // Usar memoria dinámica para crear las células.
  for (int i = 0; i < cells.size(); i++) {
    Cell* cell = new Cell(State(cells[i].getState().getValue(), cells[i].getState().getSymbol()), i);
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

Cell Lattice::getCell(int position) const {
  return *cells_[position];
}

void Lattice::setCell(Cell cell, int position) {
  *cells_[position] = cell;
}

Lattice::~Lattice() {
  for (int i = 0; i < cells_.size(); i++) {
    delete cells_[i];
  }
}

int Lattice::getSize() const {
  return cells_.size();
}

std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getSize(); i++) {
    os << lattice.getCell(i);
  }
  return os;
}

void Lattice::nextGeneration() {
  for (int cell = 0; cell < size_; cell++) {
    std::cout << "celda " << cell << std::endl;
    cells_[cell]->nextState(*this);
  }
  std::cout << *this << std::endl;
  for (int cell = 0; cell < size_; cell++) {
    cells_[cell]->updateState();
  }
  std::cout << *this << std::endl;
}