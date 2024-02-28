
#ifndef POSITION_H
#define POSITION_H

/**
 * Class to represent a position in the grid
*/
class Position {
  public:
    Position() : xCoordinate_(0), yCoordinate_(0) {}
    Position(int x, int y) : xCoordinate_(x), yCoordinate_(y) {}
    int getXCoordinate() const { return xCoordinate_; }
    int getYCoordinate() const { return yCoordinate_; }
    void setXCoordinate(int x) { xCoordinate_ = x; }
    void setYCoordinate(int y) { yCoordinate_ = y; }

  private:
    int xCoordinate_;
    int yCoordinate_;
};

#endif  // POSITION_H