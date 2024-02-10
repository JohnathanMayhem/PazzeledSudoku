#pragma once
#include <iostream>
#include "Sell.h"


class Sudoku {
private:
  std::vector<std::vector<Sell*>> table;
  int n;
  int solved;

public:
  Sudoku(int **arr, const int &n,
         std::vector<std::vector<std::pair<int, int>>> groups);
  ~Sudoku();
  bool checkRulles(std::vector<std::pair<int, int>*> &changed);
  bool tryPut();
  void solveSudoku();
  std::pair<int, int>* findMin();
};
