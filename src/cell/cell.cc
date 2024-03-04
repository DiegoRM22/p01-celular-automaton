
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
  if (lattice.getBorder() == "reflective") {
    aliveNeighbors = aliveNeighborsReflective(lattice);
  } else if (lattice.getBorder() == "noborder") {
    aliveNeighbors = aliveNeighborsNoBorder(lattice);
  }  
  // 23/3 rule
  // Una célula en estado «viva» con 2 ó 3 células vecinas en estado «viva» continúa
  //en estado «viva» en la siguiente generación. En otro caso pasa al estado «muerta».
  if (lattice.getCell(position_).getState().getValue() == 1) {
    if (aliveNeighbors == 2 || aliveNeighbors == 3) {
      nextState_ = State(1, 'X');
    } else {
      nextState_ = State(0, '_');
    }
  } else {
    if (aliveNeighbors == 3) {
      nextState_ = State(1, 'X');
    } else {
      nextState_ = State(0, '_');
    }
  }
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
 * @brief Calculates the number of alive neighbors of the cell with no border.
 * @param lattice Lattice to get the neighbors.
 * @return int.
*/
int Cell::aliveNeighborsNoBorder(const Lattice& lattice) {
  int aliveNeighbors = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int neighborI = position_.getXCoordinate() + i;
      int neighborJ = position_.getYCoordinate() + j;
      if (position_.getXCoordinate() == neighborI && position_.getYCoordinate() == neighborJ) {
        continue;
      }
      if (neighborI < 0 || neighborI >= lattice.getRowSize() || neighborJ < 0 || neighborJ >= lattice.getColumnSize()) {
        continue;
      }
      if (lattice[Position(neighborI, neighborJ)].getState().getSymbol() == 'X') {
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