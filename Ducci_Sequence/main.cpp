#include <iostream>
#include <array>
#include "ducci.h"
#include <unistd.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(){
  //Window stuff
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ducci Sequence", sf::Style::Default, settings);

  std::vector<int> sequence = {0, 653, 10000};
  std::vector<int> zero = {0, 0, 0};
  Ducci d(sequence);

  int largest = d.getLargest();
  sf::View max;
  max.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

  max.zoom(largest/SCREEN_HEIGHT);

  window.setView(max);


  //pass in RenderTarget and RenderStates
  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }
      // window.clear();
      d.advance();
      usleep(100000);
      d.drawLargest(window, sf::RenderStates::Default);
      std::cout << d;
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
