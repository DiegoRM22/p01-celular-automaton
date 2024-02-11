
#include <iostream>

#include "cell.h"

void Cell::nextState(const Lattice& lattice) {
  // C (G+1)=(C (G)+R (G)+C (G) *R (G)+L (G) *C (G) *R (G))%2
  State left = lattice.getCell(position_ - 1).getState();
  State right = lattice.getCell(position_ + 1).getState();
  State center = state_;
  int value = (left.getValue() + right.getValue() + left.getValue() * center.getValue() +
              center.getValue() * right.getValue()) % 2;
  char symbol = value == 0 ? ' ' : '*';
  nextState_.setValue(value);
  nextState_.setSymbol(symbol);
}

void Cell::updateState() {
  state_.setValue(nextState_.getValue());
  state_.setSymbol(nextState_.getSymbol());
}