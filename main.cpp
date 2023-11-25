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


    Material  mat1 = Material(Color(0, 255, 255), 0.8, 0.5, 0.5);
    Material  mat2 = Material(Color(255, 0, 0), 1, 0.5, 0.8);
    Radiation rad1 = Radiation(Color(255, 255, 255), 0);

    Camera cam = Camera(Vector(0, 0, -30), Vector(0, 0, 0),
                        Vector(19.20, 0, 0), Vector(0, 10.8, 0));

    Light  light1  = Light(Vector(0, 0, 0), rad1);
    Light  light2  = Light(Vector(10, 10, 0), rad1);
    Sphere sphere1 = Sphere(10, Vector(  10,   10, 20), mat1);
    Sphere sphere2 = Sphere(10, Vector(-10, -10, 20), mat2);

    Scene scene = Scene(cam);
    scene.AddSphere(sphere1);
    scene.AddSphere(sphere2);
    scene.AddLight(light1);
    //scene.AddLight(light2);

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
