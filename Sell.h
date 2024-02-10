#pragma once
#include <set>
#include <unordered_set>
#include <vector>
enum SATUS { GIVEN, SOLVED, EMPTY };

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Sell {
private:
  SATUS status;
  std::vector<int> *predict;

  int n;
  int value = 0;

public:
  std::unordered_set<std::pair<int, int>, pair_hash> neighbours;
  Sell(int value, std::vector<std::pair<int, int>> group, int i, int j);
  ~Sell();
  std::vector<int> getPredict();
  SATUS getStatus();
  void changePredict(std::vector<int> *newPredict);
  void setValue(int value);
  int getValue();
  bool isValid();
};
