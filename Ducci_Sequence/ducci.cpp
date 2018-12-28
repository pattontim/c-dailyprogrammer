// Provides methods for calculating steps in a ducci sequence and visualization methods via SFML
// Implements required SFML methods

#include "ducci.h"
#include "utility.h"

Ducci::Ducci(){ seq = {}; sides = 1; firstSeq = {}; zero = std::vector<int>(sides, 0);}
Ducci::Ducci(std::vector<int> v){
  seq = v;
  stage = 1;
  sides = v.size();
  firstSeq = {};
  zero = std::vector<int>(sides, 0);
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

void Ducci::populate(int cx, int cy){
  // TODO: add support for other shapes
  vertices = sf::VertexArray(sf::TrianglesFan, 3);

  vertices.clear();
  // sf::Vector2f centre(cx, cy);
  // Place each point equidistant from centre
  vertices.append(sf::Vertex(sf::Vector2f(cx, cy-seq[0])));
  vertices.append(sf::Vertex(sf::Vector2f(round(cx+(sin(Utility::degreeToRad(60))*seq[1])), round(cy+(sin(Utility::degreeToRad(30))*seq[1])))));
  vertices.append(sf::Vertex(sf::Vector2f(round(cx-(cos(Utility::degreeToRad(30))*seq[2])), round(cy+(sin(Utility::degreeToRad(30))*seq[2])))));

  // Generate a random colour
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(1.0, 255.0);
  vertices[0].color = sf::Color(dist(mt), dist(mt), dist(mt));
  vertices[1].color = sf::Color(dist(mt), dist(mt), dist(mt));
  vertices[2].color = sf::Color(dist(mt), dist(mt), dist(mt));

}

void Ducci::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(vertices);
}

// Creates a triangle with all 3 sides equidistant to the largest side in the current sequence
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

/*
*   Advances the sequence to the next phase according to the algorithm.
*/
void Ducci::advancePrimitive(){
  int first = getSide(0);

  std::vector<int>::iterator duc_iter;
  //use iter difference as i
  for(duc_iter = seq.begin(); duc_iter < seq.end()-1; duc_iter++){
    setSide(duc_iter - seq.begin(), std::abs(*duc_iter - *(duc_iter + 1)));
  }
  //std required here but not in main, investigate
  setSide(duc_iter-seq.begin(), std::abs(*duc_iter - first));
  stage++;
}


/*
*   Returns if the sequence is binary, formally k(Y,Y,Y), Y element of {1,0}.
*/
bool Ducci::isBinary(){
  int first = -1;
  std::vector<int>::iterator duc_iter;
  //use iter difference
  for(duc_iter = seq.begin(); duc_iter != seq.end(); duc_iter++){
    while(*duc_iter == 0 && first == -1)
      duc_iter++;
    if(first == -1){
      first = *duc_iter;
      // std::cout << "Setting first: " << first << std::endl;
    }
    if(*duc_iter != 0 && *duc_iter != first){
      // std::cout << "Returning false when *duc_iter = " << *duc_iter << std::endl;
      return false;
    }
  }
  return true;
}

/*
*   Checks the sequence against termination conditions and advances the sequence accordingly.
*/
bool Ducci::advance(){
  if(!isBinary()){
    advancePrimitive();
  } else if (seq == zero || seq == firstSeq){
    return false;
  } else {
    if(firstSeq.empty()){
      //TODO checking against first sequence
      firstSeq = seq;
      // std::cout << "Setting first sequence: " << this << std::endl;
      // std::vector<int>::iterator duc_iter;
      // //use iter difference as i
      // for(duc_iter = seq.begin(); duc_iter < seq.end(); duc_iter++){
      //   // setSide(duc_iter - seq.begin(), std::abs(*duc_iter - *(duc_iter + 1)));
      //   std::cout << *duc_iter << ", ";
      // }
    }
    advancePrimitive();
  }
  // std::cout << firstSeq << std::endl;
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
