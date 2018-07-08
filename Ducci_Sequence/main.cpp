#include <iostream>
#include <array>
#include "ducci.h"
#include <unistd.h>

int main(){
  //Window stuff
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ducci Sequence");

  std::vector<int> sequence = {0, 653, 1854};
  std::vector<int> zero = {0, 0, 0};
  Ducci d(sequence);

  int largest = d.getLargest();
  sf::View max(sf::FloatRect(0, 0, largest, largest));
  // sf::View max(sf::Vector2f(largest/2, largest/2), sf::Vector2f(largest, largest));
  // max.setSize(largest, largest);
  // max.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

  window.setView(max);
  window.clear();

  //pass in RenderTarget and RenderStates

  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }
      window.clear();
      d.drawLargest(window, sf::RenderStates::Default);
      sleep(1);
      d.advance();
      window.display();
  }

  std::cout << "Largest value: " << d.getLargest() << std::endl;

  while(!d.isBinary()){
    std::cout << d;
    d.advance();
  }
  std::cout << d;
  sequence = d.getSequence();
  d.advance();

  while(d.getSequence() != zero && d.getSequence() != sequence){
    std::cout << d;
    d.advance();
  }
  std::cout << d;
  std::cout << "Steps: " << d.getStage() << std::endl;

  return 0;

}
