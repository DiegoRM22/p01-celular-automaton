
#include <iostream>

#include "cell.h"
#include "lattice.h"

void Cell::nextState(const Lattice& lattice) {
  // C (G+1)=(C (G)+R (G)+C (G) *R (G)+L (G) *C (G) *R (G))%2
  std::cout << "Posicion de la celda: " << position_ << std::endl;
  // Implementar con bucle for un array de vecinos [left, center, right]
  if (lattice.getBorder() == "periodic") {
    std::cout << "periodic" << std::endl;
  } else if (lattice.getBorder() == "fixed") {
    std::cout << "fixed" << std::endl;
  } else if (lattice.getBorder() == "free") {
    std::cout << "free" << std::endl;
  }
  State left = lattice.getCell(position_ - 1).getState();
  std::cout << "funciona despues" << std::endl;
  State right = lattice.getCell(position_ + 1).getState();
  State center = state_;

  int value = (left.getValue() + right.getValue() + left.getValue() * center.getValue() +
              center.getValue() * right.getValue()) % 2;
  char symbol = value == 0 ? ' ' : '*';
  std::cout << "celda " << position_ << " value " << value << " symbol " << symbol << std::endl;
  nextState_.setValue(value);
  nextState_.setSymbol(symbol);
}



void Cell::updateState() {
  state_.setValue(nextState_.getValue());
  state_.setSymbol(nextState_.getSymbol());
}