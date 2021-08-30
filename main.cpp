#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "src/include/ge/ge.hpp"

class Temp : public ge::State {
public:
    void update() {}
    void render() {}
};

int main() {
    // create example window
    ge::Data *data = new ge::Data();
    ge::createWindow(data, 300, 300, "temp");

    data->state.addState(new Temp());

    ge::Run(data);
    return 0;
}
