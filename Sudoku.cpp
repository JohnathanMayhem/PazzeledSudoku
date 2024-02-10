#include "Sudoku.h"

Sudoku::~Sudoku() {
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      delete table[i][j];
    }
  }
  
}

Sudoku::Sudoku(int **arr, const int &n,
               std::vector<std::vector<std::pair<int, int>>> groups)
    : n(n) {
  this->solved = 0;
  table.resize(n);
  for (int i = 0; i < n; i++) {
    table[i].resize(n);
  }

  for (std::vector<std::pair<int, int>> i : groups) {
    for (std::pair<int, int> j : i) {
      table[j.first][j.second] = new Sell(arr[j.first][j.second], i, j.first, j.second);
      solved += (table[j.first][j.second]->getStatus() == GIVEN) ? 1: 0;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; ++j) {
      std::cout<<table[i][j]->getValue()<<" ";
    }
    std::cout<<"\n";
  }
}

bool Sudoku::checkRulles(std::vector<std::pair<int, int>*> &changed) {
  bool hasChanged = false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (table[i][j]->getStatus() == EMPTY) {
        std::set<int> exeptValues;
        for (int k = 0; k < n; ++k) {
          if (table[i][k]->getStatus() == SOLVED ||
              table[i][k]->getStatus() == GIVEN) {
            exeptValues.insert(table[i][k]->getValue());
          }
        }
        for (int k = 0; k < n; ++k) {
          if (table[k][j]->getStatus() == SOLVED ||
              table[k][j]->getStatus() == GIVEN) {
            exeptValues.insert(table[k][j]->getValue());
          }
        }
        for (std::pair<int, int> k : table[i][j]->neighbours) {
          if (table[k.first][k.second]->getStatus() == SOLVED ||
              table[k.first][k.second]->getStatus() == GIVEN) {
            exeptValues.insert(table[k.first][k.second]->getValue());
          }
        }
        std::vector<int> *newPredict = new std::vector<int>;
        for (int k = 1; k <= n; ++k) {
          if (exeptValues.count(k)) {
            continue;
          }
          newPredict->push_back(k);
        }
        table[i][j]->changePredict(newPredict);
        if (table[i][j]->getPredict().size() == 1) {
          table[i][j]->setValue(table[i][j]->getPredict().at(0));
          hasChanged = true;
          solved += 1;
          std::pair<int, int>* a = new std::pair<int, int>;
          a->first = i;
          a->second = j;
          changed.push_back(a);
        }
      }
    }
  }
  return hasChanged;
}

std::pair<int, int>* Sudoku::findMin() {
  unsigned long min = n+1;
  std::pair<int, int> *res = NULL;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (table[i][j]->getPredict().size() < min && table[i][j]->getStatus() == EMPTY) {
        min = table[i][j]->getPredict().size();
        if (res != NULL) {
          free(res);
        }
        res = new std::pair<int, int>;
        res->first = i;
        res->second = j;
      }
    } 
  }
  return res;
}

bool Sudoku::tryPut() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; ++j) {
      std::cout<<table[i][j]->getValue()<<" ";
    }
    std::cout<<"\n";
  }
  std::cout<<"______________________\n";
  std::vector<std::pair<int, int>*> changed;
  int count = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (!(table[i][j]->isValid())) {
        return false;
      }
      if (table[i][j]->getStatus() == EMPTY) {
        count += 1;
      }
    }
  }
  if (count == 0) {
    return true;
  }
  std::pair<int, int> pos = *findMin();
  for (int i = 0; i < table[pos.first][pos.second]->getPredict().size(); i++) {
    table[pos.first][pos.second]->setValue(table[pos.first][pos.second]->getPredict()[i]);
    while (this->checkRulles(changed)){}
    if (tryPut()) {
      return true;
    } else {
      for (std::pair<int, int> *j : changed) {
        table[j->first][j->second]->setValue(0);
      }
      table[pos.first][pos.second]->setValue(0);

    }
  }
  return false;
}

void Sudoku::solveSudoku() {
  std::vector<std::pair<int, int>*> cheked;
  while (this->checkRulles(cheked)) {}
  if (this->tryPut()) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; ++j) {
        std::cout<<table[i][j]->getValue()<<" ";
      }
      std::cout<<"\n";
    }
    
  }
}