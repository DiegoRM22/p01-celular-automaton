
#include <iostream>

#include "lattice.h"
#include "cell.h"


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

void setArguments(std::string args, int& size, std::string& border) {
  size = 0;
  border = "";
  for (int i = 0; i < args.size(); i++) {
    if (args[i] == '-' && args[i + 1] == 's') {
      size = args[i + 6] - '0';
    }
    if (args[i] == '-' && args[i + 1] == 'b') {
      for (int j = i + 8; j < args.size(); j++) {
        if (args[j] == ' ') {
          break;
        }
        border += args[j];
      }
    }
  }
  // Eliminar el b= del string border
  border = border.substr(2, border.size());
}

std::vector<Cell> createCellsArray(std::string cells) {
  std::vector<Cell> cellsArray;
  for (int i = 0; i < cells.size(); i++) {
    if (cells[i] == '0') {
      cellsArray.push_back(Cell(State(), i));
    } else {
      cellsArray.push_back(Cell(State(1, cells[i]), i));
    }
  }
  return cellsArray;
}

int main(int argc, char** argv) {
  // Get all the arguments
  std::string args = getArgs(argc, argv);
  std::cout << "Hello, " << args << "!" << std::endl;
  int size = 4;
  std::string border = "";
  setArguments(args, size, border);
  std::cout << "Size: " << size << std::endl;
  std::cout << "Border: " << border << std::endl;
  std::vector<Cell> cells = createCellsArray("0110");
  Lattice lattice(size, border, cells);
  //std::cout << lattice << std::endl;
  lattice.nextGeneration();


  return 0;
}