#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

class Ducci : public sf::Drawable, sf::Transformable {
  int sides;
  int stage;
  std::vector<int> seq;
  friend std::ostream & operator<<(std::ostream &, const Ducci &);
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

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
  int getLargest();
  std::vector<int> getSequence();
  void drawLargest(sf::RenderTarget & target, sf::RenderStates states);
};
