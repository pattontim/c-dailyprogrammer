#include <iostream>
#include <array>
#include "ducci.h"
#include <unistd.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FONT_SIZE = 24;

int main(){
  //Window stuff
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ducci Sequence", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  std::vector<int> sequence = {543, 300, 225};
  Ducci d(sequence);

  sf::RectangleShape largeButton(sf::Vector2f(240, 45));
  largeButton.setPosition(sf::Vector2f(SCREEN_WIDTH-300, 100));

  sf::Font font;
  if(!font.loadFromFile("inconsolata.ttf")){
    std::cout << "Font not found, please download a font." << std::endl;
    return 0;
  }

  sf::Text largeText("Draw Largest", font, FONT_SIZE);
  largeText.setColor(sf::Color::Black);
  largeText.setPosition(largeButton.getPosition().x + 25, largeButton.getPosition().y + largeButton.getLocalBounds().height/2 -FONT_SIZE/1.5);

  int largest = d.getLargest();
  sf::View max;
  max.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

  sf::CircleShape shape(5);
  shape.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

  //scale largest based on screen height
  if(largest > SCREEN_HEIGHT)
     max.zoom(largest/SCREEN_HEIGHT);
   window.setView(max);

  d.populate(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

  //pass in RenderTarget and RenderStates
  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
          if(event.mouseButton.button == sf::Mouse::Left){
            std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
            if(largeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
              window.clear();
              while(d.advance()){
                usleep(100000);
                d.drawLargest(window, sf::RenderStates::Default);
                std::cout << d;
                window.display();
                }
              } else {
                window.draw(d);
                window.display();
                while(d.advance()){
                  window.draw(d);
                  window.draw(shape);
                  usleep(1000000);
                  d.populate(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                  window.display();
                }
                  }
            }
      }
      window.draw(largeButton);
      window.draw(largeText);
      window.display();
  }

  std::cout << "Steps: " << d.getStage() << std::endl;

  return 0;

}
