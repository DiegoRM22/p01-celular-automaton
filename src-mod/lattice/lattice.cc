
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "lattice.h"

/**
 * @brief Constructor of the lattice.
 * @param size Size of the lattice.
 * @param border Border of the lattice.
 * @param cells Vector of cells.
 * @param openBorderValue Value of the open border.
 * @return Lattice.
 *
*/
// Lattice::Lattice(int size, std::string border, std::vector<Cell> cells, const int openBorderValue) {
//   // El constructor del retículo crea las células en memoria dinámica.
//   size_ = size;
//   border_ = border;
//   openBorderValue_ = openBorderValue;
//   // Usar memoria dinámica para crear las células.
//   for (int i = 0; i < cells.size(); i++) {
//     Cell* cell = new Cell(State(cells[i].getState().getValue(), cells[i].getState().getSymbol()), i);
//     cells_.push_back(cell);
//   }
// }

/**
 * @brief Copy constructor of the lattice.
 * @param lattice Lattice to copy.
 * @return Lattice.
 *
*/
// Lattice::Lattice(const Lattice& lattice) {
//   size_ = lattice.getSize();
//   border_ = lattice.getBorder();
//   openBorderValue_ = lattice.getOpenBorderValue();
//   for (int i = 0; i < lattice.getCells().size(); i++) {
//     Cell* cell = new Cell(State(lattice.getCell(i).getState().getValue(), lattice.getCell(i).getState().getSymbol()), i);
//     cells_.push_back(cell);
//   }
// }

/**
 * @brief Constructor of the lattice.
 * @param size Size of the lattice.
 * @param border Border of the lattice.
 * @param fileName Name of the file to read the initial state of the lattice.
 * @param openBorderValue Value of the open border.
 * @return Lattice.
 *
*/
Lattice::Lattice(int size, std::string border, const std::string& fileName, const int openBorderValue) {
  size_ = size;
  border_ = border;
  openBorderValue_ = openBorderValue;
  std::ifstream file(fileName);
  std::string line;
  getline(file, line);
  int rows = line[0] - '0';
  int columns = line[2] - '0';
  cells_.resize(rows, std::vector<Cell*>(columns));
  for (int i = 0; i < rows; i++) {
    getline(file, line);
    // Eliminar espacios en blanco.
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    if (line != "") {
      for (int j = 0; j < columns; j++) {
        if (line[j] == '0') {
          cells_[i][j] = new Cell(State(0, '_'), Position(i, j));
        } else {
          cells_[i][j] = new Cell(State(1, 'X'), Position(i, j));
        }
      }
    }
  }
  file.close();
}

/**
 * @brief Constructor of the lattice.
 * @param rows Number of rows of the lattice.
 * @param cols Number of columns of the lattice.
 * @param border Border of the lattice.
 * @return Lattice.
 *
*/
Lattice::Lattice(const int rows, const int cols, const std::string border) {
  border_ = border;
  openBorderValue_ = 0;
  cells_.resize(rows, std::vector<Cell*>(cols));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cells_[i][j] = new Cell(State(0, '_'), Position(i, j));
    }
  }
  // Ask the user which cells are alive.
  while(true) {
    std::cout << "Enter the position of the alive cells. Enter -1 to finish. \n";
    int row, col;
    std::cout << "Row: ";
    std::cin >> row;
    if (row == -1) {
      break;
    }
    std::cout << "Column: ";
    std::cin >> col;
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
      std::cout << "Invalid position. \n";
      continue;
    }
    cells_[row][col] = new Cell(State(1, 'X'), Position(row, col));
  }
}

/**
 * @brief Get the cell in the position.
 * @param position Position of the cell.
 * @return Cell.
 *
*/
Cell Lattice::getCell(Position position) const {
  return *cells_[position.getXCoordinate()][position.getYCoordinate()];
}

/**
 * @brief Set the cell in the position.
 * @param cell Cell to set.
 * @param position Position of the cell.
*/
void Lattice::setCell(Cell cell, Position position) {
  *cells_[position.getXCoordinate()][position.getYCoordinate()] = cell;
}

/**
 * @brief Get the population of the lattice.
 * @return size_t.
 *
*/
size_t Lattice::population() const {
  size_t population = 0;
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      if (cells_[i][j]->getState().getValue() == 1) {
        population++;
      }
    }
  }
  return population;
}

/**
 * @brief Destructor of the lattice.
*/
Lattice::~Lattice() {
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      delete cells_[i][j];
    }
  }
}

/**
 * @brief Get the size of the lattice.
 * @return int.
 *
*/
// int Lattice::getSize() const {
//   return size_;
// }

/**
 * @brief Overloads the << operator to print the lattice.
 * @param os Output stream.
 * @param lattice Lattice to print.
 * @return Output stream.
*/
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getRowSize(); i++){
    for (int j = 0; j < lattice.getColumnSize(); j++) {
      os << lattice.getCell(Position(i, j)) << " ";
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Calculates the next generation of the lattice.
*/
void Lattice::nextGeneration() {
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      cells_[i][j]->nextState(*this);
    }
  }
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      cells_[i][j]->updateState();
    }
  }
  // std::cout << "antes de añadir bordes: " << std::endl;
  // std::cout << *this << std::endl;
  if (border_ == "noborder") {
    resizeBorder();
    //std::cout << "Resizing border" << std::endl;
    resizingCells();
  }
}

/**
 * @brief Resize the border of the lattice.
*/
void Lattice::resizeBorder() {
  // recorre la los bordes de la matriz, si hay una célula viva, se añade una fila o columna.
  int upperRowCondition = 0;
  int lowerRowCondition = 0;
  int leftColumnCondition = 0;
  int rightColumnCondition = 0;
  for (int column = 0; column < getColumnSize(); column++) {
    if (cells_[0][column]->getState().getSymbol() == 'X') {
      upperRowCondition = 1;
    }
    if (cells_[getRowSize() - 1][column]->getState().getSymbol() == 'X') {
      lowerRowCondition = 1;
    }
  }
  for (int row = 0; row < getRowSize(); row++) {
    if (cells_[row][0]->getState().getSymbol() == 'X') {
      leftColumnCondition = 1;
    }
    if (cells_[row][getColumnSize() - 1]->getState().getSymbol() == 'X') {
      rightColumnCondition = 1;
    }
  }
  int borders[4] = {upperRowCondition, lowerRowCondition, leftColumnCondition, rightColumnCondition};
  addBorders(borders);
}

/**
 * @brief Add the borders to the lattice.
 * @param borders Array with the borders.
*/
void Lattice::addBorders(int borders[4]) {
  if (borders[0] == 1) {
    //std::cout << "Adding upper row" << std::endl;
    cells_.resize(getRowSize() + 1, std::vector<Cell*>(getColumnSize()));
    for (int i = getRowSize() - 1; i > 0; i--) {
      for (int j = 0; j < getColumnSize(); j++) {
        cells_[i][j] = cells_[i - 1][j];
      }
    }
    for (int i = 0; i < getColumnSize(); i++) {
      cells_[0][i] = new Cell(State(0, '_'), Position(0, i));
    }
  }
  if (borders[1] == 1) {
    //std::cout << "Adding lower row" << std::endl;
    cells_.resize(getRowSize() + 1, std::vector<Cell*>(getColumnSize()));
    for (int i = 0; i < getColumnSize(); i++) {
      cells_[getRowSize() - 1][i] = new Cell(State(0, '_'), Position(getRowSize() - 1, i));
    }
  }
  if (borders[2] == 1) {
    //std::cout << "Adding left column" << std::endl;
    for (int i = 0; i < getRowSize(); i++) {
      cells_[i].resize(getColumnSize() + 1);
      for (int j = getColumnSize() - 1; j > 0; j--) {
        cells_[i][j] = cells_[i][j - 1];
      }
      cells_[i][0] = new Cell(State(0, '_'), Position(i, 0));
    }
  }
  if (borders[3] == 1) {
    //std::cout << "Adding right column" << std::endl;
    for (int i = 0; i < getRowSize(); i++) {
      cells_[i].resize(getColumnSize() + 1);
      cells_[i][getColumnSize() - 1] = new Cell(State(0, '_'), Position(i, getColumnSize() - 1));
    }
  }
}

/**
 * @brief Reasign the cells of the lattice.
*/
void Lattice::resizingCells() {
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      cells_[i][j]->setPosition(Position(i, j));
    }
  }
}

/**
 * @brief Overloads the [] operator to get the cell in the position.
 * @param position Position of the cell.
 * @return Cell.
 *
*/
Cell& Lattice::operator[](const Position& position) const {
  return *cells_[position.getXCoordinate()][position.getYCoordinate()];
}

/**
 * @brief Add the first cell to the lattice.
 * @param cell Cell to add.
*/
// void Lattice::addFirstCell(const Cell& cell) {
//   Cell* newCell = new Cell(State(cell.getState().getValue(), cell.getState().getSymbol()), cell.getPosition());
//   cells_.push_back(newCell);
// }
