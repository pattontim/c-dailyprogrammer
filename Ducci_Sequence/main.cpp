#include <iostream>
#include <array>
#include "ducci.h"
#include <unistd.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FONT_SIZE = 24;

void resetDefaults(Ducci & duc);

int main(){
  //Window stuff
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ducci Sequence", sf::Style::Default, settings);
  window.setVerticalSyncEnabled(true);

  std::vector<int> sequence;
  Ducci d;
  resetDefaults(d);

  int largest = d.getLargest();
  double scalefactor = 1+((largest*1.25)/SCREEN_HEIGHT);

  //Text and buttons
  sf::Font font;
  if(!font.loadFromFile("inconsolata.ttf")){
    std::cout << "Font not found, please download a font." << std::endl;
    return 0;
  }

  sf::RectangleShape largeButton(sf::Vector2f(240, 45));
  largeButton.setPosition(sf::Vector2f(SCREEN_WIDTH-300, 100));

  sf::RectangleShape defaultButton(sf::Vector2f(240, 45));
  defaultButton.setPosition(sf::Vector2f(SCREEN_WIDTH-300, 150));

  sf::Text largeText("Draw Largest", font, FONT_SIZE);
  largeText.setColor(sf::Color::Black);
  largeText.setPosition(largeButton.getPosition().x + 25, largeButton.getPosition().y + largeButton.getLocalBounds().height/2 -FONT_SIZE/1.5);

  sf::Text defaultText("Draw All Sides", font, FONT_SIZE);
  defaultText.setColor(sf::Color::Black);
  defaultText.setPosition(defaultButton.getPosition().x + 25, defaultButton.getPosition().y + defaultButton.getLocalBounds().height/2 -FONT_SIZE/1.5);

  // sf::CircleShape shape(5);
  // shape.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

  sf::View max;
  max.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

  //scale largest based on screen height
  if(largest*2 > SCREEN_HEIGHT){
    max.zoom(scalefactor);
  }

  window.setView(max);

  d.populate(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
  //pass in RenderTarget and RenderStates
  while (window.isOpen()) {
      // window.clear();
      window.draw(d);
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
          if(event.mouseButton.button == sf::Mouse::Left){
            // window.clear();
            window.setView(max);
            std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
            if(largeButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
              window.clear();
              window.display();
              do {
                usleep(100000);
                d.drawLargest(window, sf::RenderStates::Default);
                std::cout << d;
                window.display();
              } while (d.advance());
                usleep(1000000);
              } else if(defaultButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                window.clear();
                window.display();
                do{
                  window.draw(d);
                  // window.draw(shape);
                  usleep(100000);
                  d.populate(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                  window.display();
                } while (d.advance());
                usleep(1000000);
              } else {

              }
            }
      }
      resetDefaults(d);
      window.setView(window.getDefaultView());
      window.draw(largeButton);
      window.draw(largeText);
      window.draw(defaultButton);
      window.draw(defaultText);
      window.display();
  }

  std::cout << "Steps: " << d.getStage() << std::endl;

  return 0;

}

void resetDefaults(Ducci & duc){
  std::vector<int> reset = {1000, 643, 345};
  duc = Ducci(reset);
}
