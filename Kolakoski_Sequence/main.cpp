#include <deque>
#include <iostream>
#include <string>

const int ITERATIONS = 10;

int main(){
  std::deque<bool> kolakoskiSeq{1};
  int tally[2];

  //push starting sequence
  tally[0] = 1;
  tally[1] = 0;
  int i = 2;
  int n = ITERATIONS;
  std::string output = "";
  output += "1";
  bool firstRun = true;


  while(i <= n){
    tally[kolakoskiSeq.front()]++;
    // necessary because output is a string.
    output += kolakoskiSeq.front()+1;

    //implement the algorithm
    kolakoskiSeq.insert(kolakoskiSeq.end(), 
      kolakoskiSeq.front()+(firstRun?0:1), 
      (i % 2 == 0 ? 1 : 0));

    // std::cout << kolakoskiSeq.front() << std::endl;
    kolakoskiSeq.pop_front();
    i++;
    firstRun=false;

  }

  // Print the queue for debugging purposes
  // std::cout << tally[0] << ":" << tally[1] << std::endl;
  // std::cout << output << std::endl;
  // for(int i = 0; i < kolakoskiSeq.size(); i++){
  //   std::cout << kolakoskiSeq.at(i) << std::endl;
  // }

}
