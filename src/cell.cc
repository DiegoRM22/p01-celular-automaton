
#include <iostream>

#include "cell.h"
#include "lattice.h"

void Cell::nextState(const Lattice& lattice) {
  // C (G+1)=(C (G)+R (G)+C (G) *R (G)+L (G) *C (G) *R (G))%2
  //std::cout << "Posicion de la celda: " << position_ << std::endl;
  // Implementar con bucle for un array de vecinos [left, center, right]
  int leftPosition = position_ - 1;
  int rightPosition = position_ + 1;
  if (lattice.getBorder() == "periodic") { 
    if (position_ == 0) {
      leftPosition = lattice.getSize() - 1;
    }
    if (position_ == lattice.getSize() - 1) {
      rightPosition = 0;
    }
  } else if (lattice.getBorder() == "fixed") {
  } else if (lattice.getBorder() == "free") {
  }
  State left = lattice.getCell(leftPosition).getState();
  State right = lattice.getCell(rightPosition).getState();
  State center = state_;

  int value = (center.getValue() + right.getValue() + center.getValue() * right.getValue() +
              left.getValue() * right.getValue() * center.getValue()) % 2;
  char symbol = (value == 0) ? '_' : 'X';
  //std::cout << "celda " << position_ << " value " << value << " symbol " << symbol << std::endl;
  nextState_.setValue(value);
  nextState_.setSymbol(symbol);
}



void Cell::updateState() {
  state_.setValue(nextState_.getValue());
  state_.setSymbol(nextState_.getSymbol());
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.getState().getSymbol();
  return os;
}