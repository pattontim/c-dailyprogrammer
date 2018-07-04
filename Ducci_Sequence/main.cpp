#include <iostream>
#include <array>
#include "ducci.h"

int main(){
  std::vector<int> sequence = {10, 12, 41, 62, 31};
  Ducci d(sequence);

  while(!d.isBinary()){
    std::cout << d;
    d.advance();
  }
    std::cout << d;
}
