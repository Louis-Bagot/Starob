#include "mmi.h"

using namespace std;
// source for mmi(: man-machine interface)

void initField(char field[FX][FY]){
  for (size_t i = 0; i < FX; i++) {
    for (size_t j = 0; j < FY; j++) {
      field[i][j]='.';
    }
  }
}

void updateField(char field[FX][FY], const Hero perso, const std::vector<Foe*> vFoe){
  initField(field);
  for (size_t i = 0; i < vFoe.size(); i++) {
    field[vFoe[i]->getPos().x][vFoe[i]->getPos().y]=vFoe[i]->getChar();
  }
  field[perso.getPos().x][perso.getPos().y]=perso.getChar();
  field[perso.getPosShield().x][perso.getPosShield().y]=perso.getCharShield();
}


void displayFieldConsole(char const field[FX][FY]){
  system("clear");
  for (size_t i = 0; i < FX; i++) {
    for (size_t j = 0; j < FY; j++) {
      cout << field[i][j];
    }
    cout << endl;
  }

}

void displayLife(const Hero perso){
  for (size_t i = 0; i < (unsigned)perso.getLife(); i++) {
    std::cout << "|";
  }
  std::cout << "" << std::endl;
}

bool abortGame(){
  return ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)));
}

void testSFML() {
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1920, 1200), "Tests SFML");
    sf::Texture texture;
    sf::Event event;
    sf::Sprite sprite;
    window.setFramerateLimit(60);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        if (!texture.loadFromFile("sprites/texture.jpg"))
          {
            //  cout >> "Error" >> endl;
          }


        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
    }
}
