
#include <iostream>
#include <fstream>

#include "lattice/lattice.h"
#include "cell/cell.h"
#include "celular-automaton/celular-automaton.h"


/**
 * @brief Get the arguments from the command line.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return std::string All the arguments concatenated.
*/
std::string getArgs(int argc, char** argv) {
  std::string args;
  for (int i = 1; i < argc; i++) {
    args += argv[i];
    if (i < argc - 1) {
      args += " ";
    }
  }
  return args;
}

/**
 * @brief Set the arguments from the command line.
 * @param args All the arguments concatenated.
 * @param size Size of the lattice.
 * @param border Border of the lattice.
 * @param fileName Name of the file to read the initial state of the lattice.
 * @param openBorderValue Value of the open border.
*/
void setArguments(std::string args, int& size, std::string& border, std::string& fileName, int& openBorderValue) {
  // ./automaton -size 12 -border =periodic
  size = 0;
  border = "";
  for (int i = 0; i < args.size(); i++) {
    if (args[i] == '-' && args[i + 1] == 's') {
      // El size debe ser desde i + 7 hasta el siguiente espacio
      for (int j = i + 6; j < args.size(); j++) {
        if (args[j] == ' ') {
          break;
        }
        size = size * 10 + (args[j] - '0');
      }
    }
    if (args[i] == '-' && args[i + 1] == 'b') {
      for (int j = i + 8; j < args.size(); j++) {
        if (args[j] == ' ') {
          // -border =open v=1
          // Obtener el valor de la frontera
          if (args[j + 1] == 'v') {
            openBorderValue = args[j + 3] - '0';
          }
          break;
        }
        border += args[j];
      }
    }
    // -init for files.
    if (args[i] == '-' && args[i + 1] == 'i') {
      for (int j = i + 6; j < args.size(); j++) {
        if (args[j] == ' ') {
          break;
        }
        fileName += args[j];
      }
    }
  }
  // Eliminar el b= del string border
  border = border.substr(2, border.size());
}

/**
 * @brief Create a vector of cells from a string.
 * @param cells String with the cells.
 * @return std::vector<Cell> Vector of cells.
*/
// std::vector<Cell> createCellsArray(std::string cells) {
//   std::vector<Cell> cellsArray;
//   for (int i = 0; i < cells.size(); i++) {
//     if (cells[i] == '0') {
//       cellsArray.push_back(Cell(State(0, '_'), i));
//     } else {
//       cellsArray.push_back(Cell(State(1, 'X'), i));
//     }
//   }
//   return cellsArray;
// }

/**
 * @brief Main function.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return int 0 if the program ends correctly.
*/
int main(int argc, char** argv) {
  // Get all the arguments
  std::string args = getArgs(argc, argv);
  int size = 4;
  std::string border = "";
  std::string fileName = "";
  int openBorderValue = 0;
  setArguments(args, size, border, fileName, openBorderValue);

  std::string fileContent = "";
  std::cout << "Cells: \n";
  // Mientras se pulse una letra que no sea q, se seguirá ejecutando el programa.
  Lattice lattice(size, border, fileName, openBorderValue);
  std::cout << lattice << std::endl;
  lattice.nextGeneration();
  std::cout << lattice << std::endl;

  return 0;
}