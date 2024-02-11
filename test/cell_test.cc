

#include <gtest/gtest.h>
#include "../src/cell.h"
#include "../src/lattice.h"

TEST(CellTest, Constructor) {
  Lattice lattice = Lattice(10, "periodic");
  
  Cell cell(State::kEmpty, 0);
  EXPECT_EQ(cell.getState(), State::kEmpty);
  EXPECT_EQ(cell.getPosition(), 0);
}