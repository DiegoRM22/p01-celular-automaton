
#include <iostream>
#include <fstream>

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
Lattice::Lattice(int size, std::string border, std::vector<Cell> cells, const int openBorderValue) {
  // El constructor del retículo crea las células en memoria dinámica.
  size_ = size;
  border_ = border;
  openBorderValue_ = openBorderValue;
  // Usar memoria dinámica para crear las células.
  for (int i = 0; i < cells.size(); i++) {
    Cell* cell = new Cell(State(cells[i].getState().getValue(), cells[i].getState().getSymbol()), i);
    cells_.push_back(cell);
  }
}

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
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == '0') {
          Cell* cell = new Cell(State(0, '_'), i);
          cells_.push_back(cell);
        } else if (line[i] == '1') {
          Cell* cell = new Cell(State(1, 'X'), i);
          cells_.push_back(cell);
        }
      }
    }
  }
  if (size_ != cells_.size()) {
    std::cout << "El tamaño del retículo no coincide con el número de células." << std::endl;
    exit(1);
  }
}

/**
 * @brief Get the cell in the position.
 * @param position Position of the cell.
 * @return Cell.
 *
*/
Cell Lattice::getCell(int position) const {
  return *cells_[position];
}

/**
 * @brief Set the cell in the position.
 * @param cell Cell to set.
 * @param position Position of the cell.
*/
void Lattice::setCell(Cell cell, int position) {
  *cells_[position] = cell;
}

/**
 * @brief Destructor of the lattice.
*/
Lattice::~Lattice() {
  for (int i = 0; i < cells_.size(); i++) {
    delete cells_[i];
  }
}

/**
 * @brief Get the size of the lattice.
 * @return int.
 *
*/
int Lattice::getSize() const {
  return size_;
}

/**
 * @brief Overloads the << operator to print the lattice.
 * @param os Output stream.
 * @param lattice Lattice to print.
 * @return Output stream.
*/
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.getSize(); i++) {
    os << lattice.getCell(i);
  }
  return os;
}

/**
 * @brief Calculates the next generation of the lattice.
*/
void Lattice::nextGeneration() {
  for (int cell = 0; cell < size_; cell++) {
    cells_[cell]->nextState(*this);
  }
  for (int cell = 0; cell < size_; cell++) {
    cells_[cell]->updateState();
  }
}

/**
 * @brief Add the first cell to the lattice.
 * @param cell Cell to add.
*/
void Lattice::addFirstCell(const Cell& cell) {
  Cell* newCell = new Cell(State(cell.getState().getValue(), cell.getState().getSymbol()), cell.getPosition());
  cells_.push_back(newCell);
}
