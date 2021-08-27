#ifndef GE_HPP
#define GE_HPP

#include <SFML/Graphics.hpp>
#include "state.hpp"

namespace ge {
    struct Data {
        sf::RenderWindow window;
        sf::Clock clock;
        unsigned int width;
        unsigned int height;
        state::Handler state;
    };

    inline void createWindow(Data *data, unsigned int w, unsigned int h, const char *title) {
        data->width = w;
        data->height = h;
        data->window.create(sf::VideoMode(w, h), title, sf::Style::Fullscreen);
    }

    // Set main run. Update rate is 60 times per second.
    inline void Run(Data *data, float ups = 1.0f/60.0f) {
        float dt = data->clock.getElapsedTime().asSeconds();
        float new_dt = 0.0f, elapsed = 0.0f;

        // Loop while graphics window is open
        while(data->window.isOpen()) {
            new_dt = data->clock.getElapsedTime().asSeconds();
            elapsed += new_dt - dt;
            dt = new_dt;

            // Update time if exceeding rate
            if(elapsed > ups) {
                data->state.update();
                elapsed -= ups;
            }

            // Render
            data->window.clear();
            data->state.render();
            data->window.display();
        }
    }
}

#endif
