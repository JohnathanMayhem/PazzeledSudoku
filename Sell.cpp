#include "Sell.h"

Sell::~Sell() {
    delete predict;
}

Sell::Sell(int value, std::vector<std::pair<int, int>> group, int i, int j) {
  predict = new std::vector<int>;
  for (std::pair<int, int> k : group) {
    if (k.first == i && k.second == j) {
      continue;
    }
    neighbours.insert(k);
  }
  if (value == 0) {
    this->value = 0;
    this->status = EMPTY;
  } else {
    this->status = GIVEN;
    this->value = value;
  }
}

std::vector<int> Sell::getPredict() { return *(this->predict); }

void Sell::setValue(int value) {
  if (value == 0) {
    this->value = 0;
    this->status = EMPTY;
  } else {
    this->value = value;
    this->status = SOLVED;
  }
}

void Sell::changePredict(std::vector<int> *newPredict) {
  this->predict = newPredict;
}
int Sell::getValue() { return this->value; }

bool Sell::isValid() {
  bool result = true;
  switch (this->status) {
  case SOLVED:
    break;
  case GIVEN:
    break;
  case EMPTY:
    result = !(this->predict->empty());
    break;
  default:
    break;
  }
  return result;
}

SATUS Sell::getStatus() { return this->status; }