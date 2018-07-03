#include <vector>

class Ducci {
  int sides;
  std::vector<int> seq;

public:
  Ducci();
  Ducci(std::vector<int> v);
  //is a constructor with unlimited argument possible? Aka with no vector medium, just values? ex Ducci(100, 100, ...)

  bool addSide(int value);
  bool setSide(int index, int value);
  int getSide(int index);
  bool removeSide(int index);
  void advance();
  bool isBinary();
};
