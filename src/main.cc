
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
void setArguments(std::string args, int& rows, int& cols, std::string& border, std::string& fileName, int& openBorderValue) {
  // ./automaton -size 12 -border =periodic
  rows = 0;
  cols = 0;
  std::string auxRows = "";
  std::string auxCols = "";
  border = "";
  for (int i = 0; i < args.size(); i++) {
    if (args[i] == '-' && args[i + 1] == 's') {
      std::cout << "Resizing... \n" << args[i + 6] << std::endl;
      // El size debe ser desde i + 7 hasta el siguiente espacio
      // El numero de columnas va desde args[i + 6] hasta el siguiente espacio
      for (int j = i + 6; j < args.size(); j++) {
        if (args[j] == ' ') {
          break;
        }
        auxRows += args[j];
      }
      for (int j = i + 6 + auxRows.size() + 1; j < args.size(); j++) {
        if (args[j] == ' ') {
          break;
        }
        auxCols += args[j];
      }
      rows = std::stoi(auxRows);
      cols = std::stoi(auxCols);
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
  int rows = 0;
  int cols = 0;
  setArguments(args, rows, cols, border, fileName, openBorderValue);
  std::cout << "Size: " << rows << " * " << cols << " Border: " << border << " File: " << fileName << " Open border value: " << openBorderValue << std::endl;
  std::string fileContent = "";
  std::cout << "Cells: \n";
  // Mientras se pulse una letra que no sea q, se seguirá ejecutando el programa.
  if (fileName != "")  {
    Lattice lattice(size, border, fileName, openBorderValue);
    CelularAutomaton automaton(lattice);
    automaton.transition();
    delete &lattice;
  } else {
    Lattice lattice(rows, cols, border);
    CelularAutomaton automaton(lattice);
    automaton.transition();
    delete &lattice;
  }
  
  // CelularAutomaton automaton(lattice);
  // automaton.transition();
  // delete &lattice;
  // std::cout << lattice << std::endl;
  // lattice.nextGeneration();
  // std::cout << lattice << std::endl;
  


  return 0;
}