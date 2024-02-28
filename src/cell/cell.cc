
#include <iostream>

#include "cell.h"
#include "../lattice/lattice.h"

/**
 * @brief Calculates the next state of the cell.
 * @param lattice Lattice to get the neighbors.
*/
void Cell::nextState(const Lattice& lattice) {
  int aliveNeighbors = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int auxI = position_.getXCoordinate() + i;
      int auxJ = position_.getYCoordinate() + j;
      if (auxI < 0) { 
        auxI = (lattice.getRowSize() + i);
      } else if (auxI >= lattice.getRowSize()) {
        auxI = (auxI - lattice.getRowSize());
      }
      if (auxJ < 0) { 
        auxJ = (lattice.getColumnSize() + j);
      } else if (auxJ >= lattice.getColumnSize()) {
        auxJ = (auxJ - lattice.getColumnSize());
      }
      std::cout << "Position: " << auxI << " " << auxJ << std::endl;
    }
  }
}
    


/**
 * @brief Updates the state of the cell.
*/
// void Cell::updateState() {
//   this->setState(nextState_);
// }

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