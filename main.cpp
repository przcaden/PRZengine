#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "src/include/ge/state/ge.hpp"
#include "src/include/pe/collisions.hpp"

class Temp : public ge::State {
public:
    Temp(ge::Data *data): ge::State(data) {
        ge::Resource<sf::Texture> texture;
        texture.load("tempTexture.config");

        temp.setTexture(texture.getResource("ytImg")[0]);
    }
    void update() {}
    void render() {
        data->window.draw(temp);
    }
private:
    sf::Sprite temp;
};

int main() {    
    // create example window
    ge::Data *data = new ge::Data();
    ge::createWindow(data, 300, 300, "temp");

    ge::Resource<sf::Texture> texture;
    texture.load("tempTexture.config");

    data->state.addState(new Temp(data));

    // Declare objects for physics
    pe::Circle c1(25, 1, 25, 25);
    pe::Circle c2(15, 2, 50, 50);
    // Declare objects for SFML
    sf::CircleShape s1(c1.rad());
    sf::CircleShape s2(c2.rad());
    s1.setFillColor(sf::Color(100, 250, 50));
    s2.setFillColor(sf::Color(250, 0, 250));

    ge::Run(data);
    // Run graphics
    while(1) {
        if (pe::circleIntercept(c1, c2)) {
            pe::rebound(c1, c2);
        }
    }

    return 0;
}
