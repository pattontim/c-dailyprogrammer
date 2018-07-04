#include <vector>
#include <cmath>
#include <iostream>

class Ducci {
  int sides;
  int stage;
  std::vector<int> seq;
  friend std::ostream & operator<<(std::ostream &, const Ducci &);

public:
  Ducci();
  Ducci(std::vector<int> v);
  //is a constructor with unlimited argument possible? Aka with no vector medium, just values? ex Ducci(100, 100, ...)

  void addSide(int value);
  bool setSide(int index, int value);
  int getSide(int index);
  bool removeSide(int index);
  void advance();
  bool isBinary();
  int getStage();
};
