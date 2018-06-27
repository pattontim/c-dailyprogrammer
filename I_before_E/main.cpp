#include <iostream>
#include <string>

bool check(std::string word);

int main(){
//test cases
 std::cout << check("fiery");
 std::cout << check("ceiling");
 std::cout << check("programmer");
 std::cout << check("sleigh");
 std::cout << check("nuclei");
 std::cout << check("reimburse");
}

bool check(std::string word) {
  return word.find("cei") != -1 || word.find("ei") == -1;
}
