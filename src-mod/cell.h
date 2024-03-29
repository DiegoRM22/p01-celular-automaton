

#ifndef CELL_H
#define CELL_H

#include "state.h"

class Lattice;
class Cell {
 public:
  Cell() : state_(State()), position_(0) {}
  Cell(State state, int position) : state_(state), position_(position) {}
  State getState() const { return state_; }
  int getPosition() const { return position_; }
  void setState(State state) { state_ = state; }
  void setPosition(int position) { position_ = position; }
  void nextState(const Lattice& lattice);
  void updateState();

 private:
  State state_;
  int position_;
  State nextState_;
};

std::ostream& operator<<(std::ostream& os, const Cell& cell);

#endif  // CELL_H