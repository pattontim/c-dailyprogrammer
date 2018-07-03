#include <cmath>
#include <iostream>
#include <array>
#include "ducci.h"

template<std::size_t SIZE>
void advanceDucci(std::array<int, SIZE> & seq);

template<std::size_t SIZE>
void printDucci(std::array<int, SIZE> & seq);

template<std::size_t SIZE>
void advanceDucci(std::array<int, SIZE> & seq) {
  //handle loop around behaviour
  int first = seq[0];
  for(int i = 0; i < seq.size() - 1; i++)
    seq[i] = abs(seq[i] - seq[i+1]);
  seq[seq.size()-1] = abs(seq[seq.size()-1] - first);
}

template<std::size_t SIZE>
void printDucci(std::array<int, SIZE> & seq) {
    std::cout << "[";
    for (int j = 0; j < seq.size()-1; j++)
      std::cout << seq[j] << "; ";
    std::cout << seq[seq.size()-1];
    std::cout << "]" << std::endl;
}


template<std::size_t SIZE>
bool binaryDucci(std::array<int, SIZE> & seq) {
  //for zero array and first value
  int first = -1;
  for(int i = 0; i < seq.size(); i++){
    while(seq[i] == 0)
      i++;
    if(first == -1)
      first = seq[i];
    if(seq[i] != 0 && seq[i] != first)
      return false;
  }
  return true;
}

int main(){
  std::array<int, 5> sequence = {10, 12, 41, 62, 31};
  std::array<int, 5> zero = {0, 0, 0, 0};
  printDucci(sequence);
  int i = 1;

  //Enters the binary phase of the Ducci sequence
  while(!binaryDucci(sequence)){
    advanceDucci(sequence);
    printDucci(sequence);
    i++;
  }
  std::array<int, 5> pattern = sequence;

  advanceDucci(sequence);
  printDucci(sequence);
  i++;
  //begins to look for pattern according to first
  while(sequence != pattern && sequence != zero){
    advanceDucci(sequence);
    printDucci(sequence);
    i++;
  }
  std::cout << i << " steps" << std::endl;
}
