
#include <iostream>

#include "lattice.h"


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
}

int main(int argc, char** argv) {
  // Get all the arguments
  std::string args = getArgs(argc, argv);
  std::cout << "Hello, " << args << "!" << std::endl;
  int size = 0;
  std::string border = "";
  setArguments(args, size, border);
  std::cout << "Size: " << size << std::endl;
  std::cout << "Border: " << border << std::endl;

  Lattice lattice(size, border, "0110");


  return 0;
}