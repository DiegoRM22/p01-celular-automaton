
#include <iostream>
#include <fstream>

#include "celular-automaton.h"

// /**
//  * @brief Transitions the lattice to the next generations.
//  * 
// */
void CelularAutomaton::transition() {
  std::cout << lattice_;
  char option;
  bool showOnlyPopulation = false;
  while (true) {
    std::cout << "Press enter to continue. \n";
    std::cin.get(option);
    printMenu();
    std::cout << "\n\nEnter an option: ";
    std::cin.get(option);
    executeOption(option, showOnlyPopulation);
    // limpiar pantalla
  }
}

void CelularAutomaton::saveToFile() {
  std::ofstream file;
  file.open("output.txt");
  file << lattice_;
  file.close();
}

void CelularAutomaton::printMenu() {
  std::cout << "Press x to quit the program. Any other character to continue. \n";
  std::cout << "Press n to calculate and show the next generation. \n";
  std::cout << "Press L to calculate and show the next five generations. \n";
  std::cout << "Press c to show only the population. \n";
  std::cout << "Press s to save the lattice to a file. \n";
  std::cout << "Press z to clean the screen. \n";
}

void CelularAutomaton::executeOption(char option, bool& showOnlyPopulation) {
  switch(option) {
    case 'x':
      exit(0);
      break;
    case 'n':
      lattice_.nextGeneration();
      if (showOnlyPopulation) {
        std::cout << lattice_.population() << std::endl;
      } else {
        std::cout << lattice_;
      }
      break;
    case 'L':
      for (int i = 0; i < 5; i++) {
        lattice_.nextGeneration();
        if (showOnlyPopulation) {
          std::cout << lattice_.population() << std::endl;
        } else {
          std::cout << lattice_;
        }
      }
      break;
    case 'c':
      showOnlyPopulation = !showOnlyPopulation;
      break;
    case 's':
      saveToFile();
      break;
    case 'z':
      std::cout << "\033[2J\033[1;1H";
      break;
    default:
      break;
  }
}