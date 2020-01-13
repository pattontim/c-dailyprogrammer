#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Checks if the given string is in accordance with the I before E except after C rule
// Words that do not contain ei/are not relevant to this problem like 'dog' are returned
// as true. It does not handle complex rules but instead relies on a simple heuristic
bool check(std::string word);

int main(){
 //check input text for accordance with I before E except after C rule
  std::string line;
  std::ifstream myfile ("example.txt");
  int failed = 0;
  if (myfile.is_open()){
    while (getline(myfile, line)){
      if(!check(line))
        failed++;
    }
    myfile.close();
  }
  else std::cout << "Unable to open file" << std::endl;

  //test cases
  std::cout << check("fiery") << std::endl;
  std::cout << check("ceiling") << std::endl;
  std::cout << check("programmer") << std::endl;
  std::cout << check("sleigh") << std::endl;
  std::cout << check("nuclei") << std::endl;
  std::cout << check("reimburse") << std::endl;

  if(failed) std::cout << "Number of failed words in file: " << failed << std::endl;
  return 0;
}

bool check(std::string word) {
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);

  if(word.find("cie") != -1)
    return false;
  else if(word.find("cei") != -1)
    return true;
  else
    return word.find("ei") == -1;
}
