#include <iostream>
#include <string>

std::string rollDie(int & rolls, int & faces);

int main() {
  std::cout << "/* message */" << '\n';
  std::string input;
  std::string delimiter = "d";

  int rolls;
  int faces;

  while(true){
    std::cin >> input;

    faces = stoi(input.substr(input.find(delimiter)+1, input.length()));
    rolls = stoi(input.substr(0, input.find(delimiter)));

    // std::cout << faces << std::endl;
    // std::cout << rolls << std::endl;
    std::cout << rollDie(rolls, faces) << std::endl;
  }
}

std::string rollDie(int & rolls, int & faces){
  // std::cout << rolls << " " << faces << std::endl;
  int tosses[rolls];
  int sum = 0;
  for(int i = 0; i < rolls; i++){
    tosses[i] = rand() % faces+1;
    // std::cout << "Adding random roll: " << tosses[i] << std::endl;
    sum += tosses[i];
  }
  return std::to_string(sum);
}
