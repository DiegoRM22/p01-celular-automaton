
#include <iostream>

#include "cell.h"
#include "../lattice/lattice.h"

/**
 * @brief Calculates the next state of the cell.
 * @param lattice Lattice to get the neighbors.
*/
void Cell::nextState(const Lattice& lattice) {
  int aliveNeighbors = 0;
  // Frontera reflectora.Si sale del limite, se refleja.
  aliveNeighbors = aliveNeighborsReflective(lattice);
  std::cout << "Alive neighbors: " << aliveNeighbors << std::endl;
  // 23/3 rule
  if (state_.getSymbol() == 'X') {
    if (aliveNeighbors < 2 || aliveNeighbors > 3) {
      nextState_ = State(0, ' ');
    } else {
      nextState_ = State(1, 'X');
    }
  } else {
    if (aliveNeighbors == 3) {
      nextState_ = State(1, 'X');
    } else {
      nextState_ = State(0, ' ');
    }
  }
  // for (int i = -1; i < 2; i++) {
  //   for (int j = -1; j < 2; j++) {
  //     int auxI = position_.getXCoordinate() + i;
  //     int auxJ = position_.getYCoordinate() + j;
  //     if (auxI < 0) { 
  //       auxI = (lattice.getRowSize() + i);
  //     } else if (auxI >= lattice.getRowSize()) {
  //       auxI = (auxI - lattice.getRowSize());
  //     }
  //     if (auxJ < 0) { 
  //       auxJ = (lattice.getColumnSize() + j);
  //     } else if (auxJ >= lattice.getColumnSize()) {
  //       auxJ = (auxJ - lattice.getColumnSize());
  //     }
  //     std::cout << "Position: " << auxI << " " << auxJ << std::endl;
  //   }
  // }
}

/**
 * @brief Calculates the number of alive neighbors of the cell with reflective border.
 * @param lattice Lattice to get the neighbors.
 * @return int.
*/
int Cell::aliveNeighborsReflective(const Lattice& lattice) {
  int aliveNeighbors = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      int auxI = position_.getXCoordinate() + i;
      int auxJ = position_.getYCoordinate() + j;
      if (auxI < 0 || auxI >= lattice.getRowSize()) { 
        auxI = position_.getXCoordinate();
      }
      if (auxJ < 0 || auxJ >= lattice.getColumnSize()) { 
        auxJ = position_.getYCoordinate();
      }
      Position auxPosition(auxI, auxJ);
      if (lattice[auxPosition].getState().getSymbol() == 'X') {
        aliveNeighbors++;
      }
    }
  }
  return aliveNeighbors;
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