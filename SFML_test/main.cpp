#include <SFML/Graphics.hpp>

int main(){
  sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Works");
  // window.setVerticalSyncEnabled(true); // call it once, after creating the window

  // sf::CircleShape shape(80, 3);
  sf::Vertex vertex(sf::Vector2f(10, 50), sf::Color::Red, sf::Vector2f(100, 100)  );
  sf::VertexArray triangle(sf::Triangles, 3);

  // define the position of the triangle's points
  triangle[0].position = sf::Vector2f(10, 10);
  triangle[1].position = sf::Vector2f(100, 10);
  triangle[2].position = sf::Vector2f(100, 100);
  // define the color of the triangle's points
  triangle[0].color = sf::Color::Red;
  triangle[1].color = sf::Color::Blue;
  triangle[2].color = sf::Color::Green;
  // no texture coordinates here, we'll see that later

  // shape.setFillColor(sf::Color::Red);
  // shape.setPosition(200, 200);
  // triangle.position = sf::Vector2f(10, 20);

  while(window.isOpen()){

    //must be called to respond to changes, aka resizing and closing.
    sf::Event event;
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(triangle);
    window.display();
  }
  return 0;
}
