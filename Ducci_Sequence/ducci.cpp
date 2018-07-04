#include "ducci.h"

Ducci::Ducci(){ seq = {};}
Ducci::Ducci(std::vector<int> v){
  seq = v;
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
void Ducci::advance(){
  int first = getSide(0);
  for(int i = 0; i < seq.size() - 1; i++) {
    setSide(i, std::abs(seq[i] - seq[i+1]));
  }
  //why is std required here but not in main?
  setSide(seq.size() - 1, std::abs(seq[seq.size()-1] - first));
  stage++;
}
bool Ducci::isBinary(){
  //for zero array and first value
  int first = -1;
  for(int i = 0; i < seq.size(); i++){
    while(getSide(i) == 0)
      i++;
    if(first == -1)
      first = getSide(i);
    if(getSide(i) != 0 && getSide(i) != first)
      return false;
  }
  return true;
}
int Ducci::getStage(){
  return stage;
}

std::ostream & operator<<(std::ostream & strm, const Ducci & d){
  strm << "[";
  std::vector<int>::const_iterator duc_iter;
  for(duc_iter = d.seq.begin(); duc_iter != d.seq.end()-1; duc_iter++){
    strm << *duc_iter << ", ";
  }
  return strm << *(duc_iter) << "]" << std::endl;
}
