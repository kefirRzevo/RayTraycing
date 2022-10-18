#include <iostream>
#include <cmath>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "include/vector.h"
#include "include/config.h"
#include "include/render.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    sf::Sprite sprite(texture);


    Material mat1 = Material(Color(255, 0, 0), 0.3, 0.2, 0.5);
    Radiation rad1 = Radiation(Color(255, 255, 255), 0.05);

    Camera cam = Camera(Vector(0, 0, -10), Vector(0, 0, 0),
                        Vector(-5, 0, 0), Vector(0, 3.75, 0));

    Light light1 = Light(Vector(10, 10, 10), rad1);
    Sphere sphere1 = Sphere(5, Vector(0, 0, 10), mat1);

    Scene scene = Scene(cam);
    scene.AddSphere(sphere1);
    scene.AddLight(light1);

    Color* pixels  = new Color[WIDTH * HEIGHT];
    scene.Draw(pixels);

    while(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        texture.update((sf::Uint8* )pixels);
        window.draw(sprite);
        window.display();
    }

    delete[] pixels;
    return 0;
}
