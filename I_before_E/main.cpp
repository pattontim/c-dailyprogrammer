#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool check(std::string word);

int main(){
//test cases
 std::cout << check("fiery");
 std::cout << check("ceiling");
 std::cout << check("programmer");
 std::cout << check("sleigh");
 std::cout << check("nuclei");
 std::cout << check("reimburse");

  std::string line;
  std::ifstream myfile ("english.txt");
  int exc = 0;
  if (myfile.is_open()){
    while (getline(myfile, line)){
      if(!check(line))
        exc++;
    }
    myfile.close();
  }
  else std::cout << "Unable to open file" << std::endl;


  std::cout << std::endl << exc << std::endl;
  return 0;

 //check all english words
}

bool check(std::string word) {
  //TODO search all instances in words
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);

  if(word.find("cie") != -1)
    return false;
  else if(word.find("cei") != -1)
    return true;
  else
    return word.find("ei") == -1;
}
