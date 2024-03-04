
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
  // Vecino 1 (dos arriba, dos izquierda)
  int knumberOfNeighbors = 11;
  // Array de posiviones de tamño knumberOfNeighbors
  Position neighbors[knumberOfNeighbors];
  neighbors[0] = Position(position_.getXCoordinate() - 2, position_.getYCoordinate() - 2);
  neighbors[1] = Position(position_.getXCoordinate(), position_.getYCoordinate() - 2);
  neighbors[2] = Position(position_.getXCoordinate() + 2, position_.getYCoordinate() - 2);
  neighbors[3] = Position(position_.getXCoordinate() + 3, position_.getYCoordinate() - 1);
  neighbors[4] = Position(position_.getXCoordinate(), position_.getYCoordinate() + 2);
  neighbors[5] = Position(position_.getXCoordinate() + 3, position_.getYCoordinate() - 1);
  neighbors[6] = Position(position_.getXCoordinate() + 2, position_.getYCoordinate() + 2);
  neighbors[7] = Position(position_.getXCoordinate(), position_.getYCoordinate() + 2);
  neighbors[8] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate() + 2);
  neighbors[9] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate() + 1);
  neighbors[10] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate());
  // Si se sale del limite, se refleja.
  for (int i = 0; i < knumberOfNeighbors; i++) {
    if (neighbors[i].getXCoordinate() < 0 || neighbors[i].getXCoordinate() >= lattice.getRowSize()) {
      neighbors[i].setXCoordinate(position_.getXCoordinate());
    }
    if (neighbors[i].getYCoordinate() < 0 || neighbors[i].getYCoordinate() >= lattice.getColumnSize()) {
      neighbors[i].setYCoordinate(position_.getYCoordinate());
    }
    if (lattice[neighbors[i]].getState().getSymbol() == 'X') {
      aliveNeighbors++;
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
  // Vecino 1 (dos arriba, dos izquierda)
  int knumberOfNeighbors = 11;
  // Array de posiviones de tamño knumberOfNeighbors
  Position neighbors[knumberOfNeighbors];
  neighbors[0] = Position(position_.getXCoordinate() - 2, position_.getYCoordinate() - 2);
  neighbors[1] = Position(position_.getXCoordinate(), position_.getYCoordinate() - 2);
  neighbors[2] = Position(position_.getXCoordinate() + 2, position_.getYCoordinate() - 2);
  neighbors[3] = Position(position_.getXCoordinate() + 3, position_.getYCoordinate() - 1);
  neighbors[4] = Position(position_.getXCoordinate(), position_.getYCoordinate() + 2);
  neighbors[5] = Position(position_.getXCoordinate() + 3, position_.getYCoordinate() - 1);
  neighbors[6] = Position(position_.getXCoordinate() + 2, position_.getYCoordinate() + 2);
  neighbors[7] = Position(position_.getXCoordinate(), position_.getYCoordinate() + 2);
  neighbors[8] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate() + 2);
  neighbors[9] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate() + 1);
  neighbors[10] = Position(position_.getXCoordinate() - 1, position_.getYCoordinate());
  // Si se sale del limite es un vecino muerto.
  for (int i = 0; i < knumberOfNeighbors; i++) {
    if (neighbors[i].getXCoordinate() < 0 || neighbors[i].getXCoordinate() >= lattice.getRowSize()) {
      continue;
    }
    if (neighbors[i].getYCoordinate() < 0 || neighbors[i].getYCoordinate() >= lattice.getColumnSize()) {
      continue;
    }
    if (lattice[neighbors[i]].getState().getSymbol() == 'X') {
      aliveNeighbors++;
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