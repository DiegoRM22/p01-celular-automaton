

#include "celular-automaton.h"

/**
 * @brief Transitions the lattice to the next generations.
 * 
*/
void CelularAutomaton::transition() {
  std::cout << "Press q to quit the program. Any other character to continue. \n";
  std::cout << lattice_;
  char option;
    while (true) {
    std::cin.get(option);
    if (option == 'q') {
      break;
    }
    
    lattice_.nextGeneration();
    std::cout << lattice_;
  }
}