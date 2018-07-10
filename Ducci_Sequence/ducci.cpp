//TODO declare const methods...
#include "ducci.h"

Ducci::Ducci(){ seq = {}; sides = 1;}
Ducci::Ducci(std::vector<int> v){
  seq = v;
  stage = 1;
  sides = v.size();
}

void Ducci::addSide(int value){
  seq.push_back(value);
}

bool Ducci::setSide(int index, int value) {
  return seq.at(index) = value;
}

int Ducci::getSide(int index){
  return seq.at(index);
}

bool Ducci::removeSide(int index){
}

void Ducci::draw(sf::RenderTarget & target, sf::RenderStates states) const {
}

void Ducci::drawLargest(sf::RenderTarget & target, sf::RenderStates states) {
  int largest = getLargest();
  sf::CircleShape shape(largest/2, sides);
  sf::FloatRect triRect = shape.getLocalBounds();
  shape.setOrigin(triRect.left + triRect.width/2.0f, triRect.top + triRect.height/2.0f);
  shape.setPosition(sf::Vector2f(target.getSize().x/2.0f, target.getSize().y/2.0f));

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1.0, 255.0);
  shape.setFillColor(sf::Color(dist(mt), dist(mt), dist(mt)));
  // shape.rotate(10);
  target.draw(shape);
}

void Ducci::advance(){
  int first = getSide(0);

  std::vector<int>::iterator duc_iter;
  //use iter difference as i
  for(duc_iter = seq.begin(); duc_iter < seq.end()-1; duc_iter++){
    setSide(duc_iter - seq.begin(), std::abs(*duc_iter - *(duc_iter + 1)));
  }
  //why is std required here but not in main?
  setSide(duc_iter-seq.begin(), std::abs(*duc_iter - first));
  stage++;
}

bool Ducci::isBinary(){
  //for zero array and first value
  int first = -1;
  std::vector<int>::iterator duc_iter;
  //use iter difference
  for(duc_iter = seq.begin(); duc_iter < seq.end(); duc_iter++){
    while(*duc_iter == 0)
      duc_iter++;
    if(first == -1)
      first = *duc_iter;
    if(*duc_iter != 0 && *duc_iter != first)
      return false;
  }
  return true;
}

int Ducci::getStage(){
  return stage;
}

int Ducci::getLargest(){
  int largest = 0;
  std::vector<int>::const_iterator duc_iter;
  for(duc_iter = seq.begin(); duc_iter != seq.end(); duc_iter++){
    if(*duc_iter > largest){
      // std::cout << "setting largest: " << *duc_iter << std::endl;
      largest = *duc_iter;
    }
  }
  return largest;
}

std::vector<int> Ducci::getSequence(){
  return seq;
}

std::ostream & operator<<(std::ostream & strm, const Ducci & d){
  strm << "[";
  std::vector<int>::const_iterator duc_iter;
  for(duc_iter = d.seq.begin(); duc_iter != d.seq.end()-1; duc_iter++){
    strm << *duc_iter << ", ";
  }
  return strm << *(duc_iter) << "]" << std::endl;
}
