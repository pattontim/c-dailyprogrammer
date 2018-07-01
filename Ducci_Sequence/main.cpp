#include <cmath>
#include <iostream>
#include <array>

//Like saying, this will take any size, we make the size generic at compile time
template<std::size_t SIZE>
void advanceDucci(std::array<int, SIZE> & seq);

//see if template will work with args
template<std::size_t SIZE>
void printDucci(std::array<int, SIZE> & seq);

template<std::size_t SIZE>
void advanceDucci(std::array<int, SIZE> & seq) {
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
  int boolVal = -1;
  for(int i = 0; i < seq.size(); i++){
    while(seq[i] == 0)
      i++;
    if(boolVal == -1)
      boolVal = seq[i];
    if(seq[i] != 0 && seq[i] != boolVal)
      return false;
  }
  // if(boolVal == 0)
    return true;
}

int main(){
  std::array<int, 5> sequence = {10, 12, 41, 62, 31};
  printDucci(sequence);
  int i = 1;

  while(!binaryDucci(sequence) && i < 30){
    advanceDucci(sequence);
    printDucci(sequence);
    i++;
  }
  std::array<int, 5> pattern = sequence;
  std::array<int, 5> zero = {0, 0, 0, 0};

  advanceDucci(sequence);
  printDucci(sequence);
  i++;
  while(sequence != pattern && sequence != zero){
    advanceDucci(sequence);
    printDucci(sequence);
    i++;
  }
  std::cout << i << " steps" << std::endl;
}
