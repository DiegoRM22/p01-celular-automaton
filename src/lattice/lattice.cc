
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
  // First line contains the number of rows and columns.
  getline(file, line);
  int rows = line[0] - '0';
  int columns = line[2] - '0';
  cells_.resize(rows, std::vector<Cell*>(columns));
  std::cout << "Rows: " << rows << " Columns: " << columns << std::endl;
  // Read the initial state of the lattice.
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
 * @brief Destructor of the lattice.
*/
Lattice::~Lattice() {
  for (int i = 0; i < cells_.size(); i++) {
    for (int j = 0; j < cells_[i].size(); j++) {
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
      os << lattice.getCell(Position(i, j));
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Calculates the next generation of the lattice.
*/
void Lattice::nextGeneration() {
  std::cout << "Next generation" << std::endl;
  for (int i = 0; i < getRowSize(); i++) {
    for (int j = 0; j < getColumnSize(); j++) {
      std::cout << "Next state of cell: " << i << " " << j << std::endl;
      cells_[i][j]->nextState(*this);
    }
  }
}

/**
 * @brief Add the first cell to the lattice.
 * @param cell Cell to add.
*/
// void Lattice::addFirstCell(const Cell& cell) {
//   Cell* newCell = new Cell(State(cell.getState().getValue(), cell.getState().getSymbol()), cell.getPosition());
//   cells_.push_back(newCell);
// }
