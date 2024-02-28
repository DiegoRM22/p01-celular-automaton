

#ifndef CELL_H
#define CELL_H

#include "../tools/state.h"
#include "../tools/position.h"

class Lattice;
class Cell {
 public:
  Cell() : state_(State()), position_() {}
  Cell(State state, Position position) : state_(state), position_(position) {}
  State getState() const { return state_; }
  Position getPosition() const { return position_; }
  void setState(State state) { state_ = state; }
  void setPosition(Position position) { position_ = position; }
  void nextState(const Lattice& lattice);
  int aliveNeighborsReflective(const Lattice& lattice);
  // void updateState();

 private:
  State state_;
  Position position_;
  State nextState_;
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

#endif  // CELL_H