
#pragma once

class State {
 public:
  State() : value_(0), symbol_(' ') {}
  State(int value, char symbol) : value_(value), symbol_(symbol) {}
  int getValue() const { return value_; }
  char getSymbol() const { return symbol_; }
  void setValue(int value) { value_ = value; }
  void setSymbol(char symbol) { symbol_ = symbol; }
 private:
  int value_;
  char symbol_;
};