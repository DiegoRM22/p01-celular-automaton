
#include <iostream>

#include "cell.h"
#include "lattice.h"

/**
 * @brief Calculates the next state of the cell.
 * @param lattice Lattice to get the neighbors.
*/
void Cell::nextState(const Lattice& lattice) {
  const int kNeighborsDistance = 4;
  int leftPosition = position_ - kNeighborsDistance;
  int rightPosition = position_ + kNeighborsDistance;
  State left;
  State right;
  if (lattice.getBorder() == "periodic") { 
    if (position_ < kNeighborsDistance) {
      leftPosition = lattice.getSize() - kNeighborsDistance + position_;
    }
    if (position_ >= lattice.getSize() - kNeighborsDistance) {
      rightPosition = position_ - lattice.getSize() + kNeighborsDistance;
    }
    left = lattice.getCell(leftPosition).getState();
    right = lattice.getCell(rightPosition).getState();
  } else if (lattice.getBorder() == "open") {
    char symbol = (lattice.getOpenBorderValue() == 0) ? '_' : 'X';
    leftPosition = (position_ - kNeighborsDistance < 0) ? 0 : position_ - kNeighborsDistance;
    rightPosition = (position_ + kNeighborsDistance >= lattice.getSize()) ? lattice.getSize() - 1 : position_ + kNeighborsDistance;
    if (position_ <= 0) {
      left = State(lattice.getOpenBorderValue(), symbol);
      right = lattice.getCell(rightPosition).getState();
    } else if (position_ == lattice.getSize() - 1) {
      right = State(lattice.getOpenBorderValue(), symbol);
      left = lattice.getCell(leftPosition).getState();
    } else {
      left = lattice.getCell(leftPosition).getState();
      right = lattice.getCell(rightPosition).getState();
    }
  } else if (lattice.getBorder() == "free") {
  }
  State center = state_;

  int value = (center.getValue() + right.getValue() + center.getValue() * right.getValue() +
              left.getValue() * right.getValue() * center.getValue()) % 2;
  char symbol = (value == 0) ? '_' : 'X';
  nextState_.setValue(value);
  nextState_.setSymbol(symbol);
}


/**
 * @brief Updates the state of the cell.
*/
void Cell::updateState() {
  this->setState(nextState_);
}

/**
 * @brief Overloads the << operator to print the cell.
 * @param os Output stream.
 * @param cell Cell to print.
 * @return Output stream.
*/
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.getState().getSymbol();
  return os;
}