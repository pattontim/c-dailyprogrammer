#include <deque>
#include <iostream>
#include <string>

int main(){
  std::deque<bool> kolakoskiSeq{1};
  int tally[2];

  //push starting sequence
  tally[0] = 1;
  tally[1] = 0;
  int i = 2;
  int n = 100;
  std::string output = "";
  output += "0";
  bool firstRun = true;
  // std::cout << (true ? "false":"true");

  while(i <= n){
    if(kolakoskiSeq.empty()){

    }
    tally[kolakoskiSeq.front()]++;
    // output += std::to_string(kolakoskiSeq.front()?1:0);
    if(kolakoskiSeq.front()){
      output += "1";
    } else {
      output += "0";
    }
    kolakoskiSeq.insert(kolakoskiSeq.end(), kolakoskiSeq.front()+(firstRun?0:1), (i % 2 == 0 ? 1 : 0));
    // std::cout << kolakoskiSeq.front() << std::endl;
    kolakoskiSeq.pop_front();
    i++;
    firstRun=false;
  }
  std::cout << tally[0] << ":" << tally[1] << std::endl;
  // std::cout << output << std::endl;
  // for(int i = 0; i < 10; i++){
  //   std::cout << kolakoskiSeq.at(i) << std::endl;
  // }

}
