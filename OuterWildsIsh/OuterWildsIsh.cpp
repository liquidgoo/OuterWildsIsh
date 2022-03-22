#include "SFML/Graphics.hpp"
#include "Engine.h"
#include <vector>
#include "SpaceShip.h"

int main(int argc, char** argv) {
    sf::RenderWindow renderWindow(sf::VideoMode(1600, 900), "Outer Wilds...ish...");
    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    renderWindow.setKeyRepeatEnabled(false);
    sf::Event event;
    sf::Clock clock;
    float time;
    Engine engine = Engine();

    std::vector<sf::ConvexShape*> convShapes;
    convShapes.push_back(new sf::ConvexShape(8));
    convShapes[0]->setPoint(0, sf::Vector2f(0.7f, 3.2f));
    convShapes[0]->setPoint(1, sf::Vector2f(10.4f, 3.9f));
    convShapes[0]->setPoint(2, sf::Vector2f(23.2f, 6.5f));
    convShapes[0]->setPoint(3, sf::Vector2f(45.9f, 15.3f));
    convShapes[0]->setPoint(4, sf::Vector2f(45.9f, 19.4f));
    convShapes[0]->setPoint(5, sf::Vector2f(23.2f, 28.2f));
    convShapes[0]->setPoint(6, sf::Vector2f(10.4f, 30.8f));
    convShapes[0]->setPoint(7, sf::Vector2f(0.7f, 31.5f));
    engine.appendBody(convShapes[0], sf::Vector2f(-2000, -400), sf::Vector2f(0, -std::sqrt(200000000 / 2000.0f)), 0.0f,
        10.0f, 0.1f);


    SpaceShip player(engine.getFirst());
    sf::Texture spaceship;
    spaceship.setSmooth(true);
    if (!spaceship.loadFromFile("assets/destroyer.png")) {}
    convShapes[0]->setTexture(&spaceship);


    std::vector<sf::CircleShape*> cShapes;
    cShapes.push_back(new sf::CircleShape(1000));
    cShapes.push_back(new sf::CircleShape(200));
    cShapes.push_back(new sf::CircleShape(100));
    cShapes.push_back(new sf::CircleShape(300));
    cShapes.push_back(new sf::CircleShape(50));
    cShapes.push_back(new sf::CircleShape(20));
    cShapes.push_back(new sf::CircleShape(15));
    std::vector<sf::Texture*> textures;
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures.push_back(new sf::Texture());
    textures[0]->loadFromFile("assets/planets/sun.png");
    textures[1]->loadFromFile("assets/planets/planet_045.png");
    textures[2]->loadFromFile("assets/planets/planet_079.png");
    textures[3]->loadFromFile("assets/planets/planet_097.png");
    textures[4]->loadFromFile("assets/planets/planet_066.png");
    textures[5]->loadFromFile("assets/planets/planet_068.png");
    textures[6]->loadFromFile("assets/planets/planet_003.png");
    cShapes[0]->setTexture(textures[0]);
    cShapes[1]->setTexture(textures[1]);
    cShapes[2]->setTexture(textures[2]);
    cShapes[3]->setTexture(textures[3]);
    cShapes[4]->setTexture(textures[4]);
    cShapes[5]->setTexture(textures[5]);
    cShapes[6]->setTexture(textures[6]);
    engine.appendBody(cShapes[0], sf::Vector2f(0, 0), sf::Vector2f(0, 0), 0.01f, 200000000.0f, 0.0f);
    engine.appendBody(cShapes[1], sf::Vector2f(-2000, 0000), sf::Vector2f(0, -std::sqrt(200000000 / 2000.0f)), 0.1f,
        5000000.0f, 0.2f);
    engine.appendBody(cShapes[2], sf::Vector2f(0, -4000), sf::Vector2f(-std::sqrt(200000000.0f / 4000), 0), -0.5f,
        10000000.0f, 1.0f);
    engine.appendBody(cShapes[3], sf::Vector2f(0, 7000), sf::Vector2f(-std::sqrt(200000000.0f / 7000), 0), 0.05f,
        15000000.0f, 0.1f);
    engine.appendBody(cShapes[4], sf::Vector2f(-2400, 0),
        sf::Vector2f(0, -std::sqrt(200000000.0f / 2450.549f) + std::sqrt(5000000 / 400)), -0.2f,
        1000000.0f, 1.0f);
    engine.appendBody(cShapes[5], sf::Vector2f(300, -4000), sf::Vector2f(-std::sqrt(200000000.0f / 4000), 15), 1.0f,
        20.0f, 1.0f);
    engine.appendBody(cShapes[6], sf::Vector2f(-300, -4000), sf::Vector2f(-std::sqrt(200000000.0f / 4000), 15), -1.0f,
        15.0f, 1.0f);


    convShapes.push_back(new sf::ConvexShape(5));
    convShapes.push_back(new sf::ConvexShape(4));
    convShapes.push_back(new sf::ConvexShape(4));
    convShapes[1]->setPoint(0, sf::Vector2f(0, 0));
    convShapes[1]->setPoint(1, sf::Vector2f(-5, 25));
    convShapes[1]->setPoint(2, sf::Vector2f(15, 45));
    convShapes[1]->setPoint(3, sf::Vector2f(50, 20));
    convShapes[1]->setPoint(4, sf::Vector2f(30, -5));

    convShapes[2]->setPoint(0, sf::Vector2f(0, 0));
    convShapes[2]->setPoint(1, sf::Vector2f(30, 30));
    convShapes[2]->setPoint(2, sf::Vector2f(55, 20));
    convShapes[2]->setPoint(3, sf::Vector2f(65, -10));

    convShapes[3]->setPoint(0, sf::Vector2f(0, 0));
    convShapes[3]->setPoint(1, sf::Vector2f(24, 24));
    convShapes[3]->setPoint(2, sf::Vector2f(44, 16));
    convShapes[3]->setPoint(3, sf::Vector2f(52, -8));
    textures.push_back(new sf::Texture());
    textures[7]->loadFromFile("assets/ast.png");
    convShapes[1]->setTexture(textures[7]);
    convShapes[2]->setTexture(textures[7]);
    convShapes[3]->setTexture(textures[7]);

    engine.appendBody(convShapes[1], sf::Vector2f(-320, 7000), sf::Vector2f(-std::sqrt(20000000.0f / 7000), 0), 0.0f,
        10.0f, 0.2f);
    engine.appendBody(convShapes[2], sf::Vector2f(-320, 7060), sf::Vector2f(-std::sqrt(20000000.0f / 7000), 0), 0.0f,
        8.0f, 0.2f);
    engine.appendBody(convShapes[3], sf::Vector2f(-320, 6940), sf::Vector2f(-std::sqrt(20000000.0f / 7000), 0), 0.0f,
        7.0f, 0.2f);


    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1600, 900));

    sf::Texture back;
    if (!back.loadFromFile("assets/Large 1024x1024/Starfields/1024x1024 Starfield 2.png")) {}
    back.setRepeated(true);
    back.setSmooth(true);
    sf::Sprite background;
    background.setTextureRect(sf::IntRect(0.0f, 0.0f, 200000.0f, 200000.0f));
    background.setPosition(sf::Vector2f(-100000, -100000));
    background.setTexture(back);

    sf::Vector2f newViewSize;
    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
            if (event.type == sf::Event::EventType::MouseWheelScrolled) {
                newViewSize = view.getSize() - sf::Vector2f(100, 56.25f) * event.mouseWheelScroll.delta;

                view.setSize(newViewSize.x < 200 ? sf::Vector2f(200, 112.5f) : newViewSize);
            }
            if (event.type == sf::Event::EventType::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    player.forward = true;
                }
                if (event.key.code == sf::Keyboard::S) {
                    player.backward = true;
                }
                if (event.key.code == sf::Keyboard::E) {
                    player.strafeR = true;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    player.strafeL = true;
                }
                if (event.key.code == sf::Keyboard::C) {
                    player.rotR = true;
                }
                if (event.key.code == sf::Keyboard::Z) {
                    player.rotL = true;
                }
                if (event.key.code == sf::Keyboard::D) {
                    player.dirRotR();
                }
                if (event.key.code == sf::Keyboard::A) {
                    player.dirRotL();
                }
                if (event.key.code == sf::Keyboard::Space) {
                    player.stabilize = true;
                }
            }
            if (event.type == sf::Event::EventType::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    player.forward = false;
                }
                if (event.key.code == sf::Keyboard::S) {
                    player.backward = false;
                }
                if (event.key.code == sf::Keyboard::E) {
                    player.strafeR = false;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    player.strafeL = false;
                }
                if (event.key.code == sf::Keyboard::C) {
                    player.rotR = false;
                }
                if (event.key.code == sf::Keyboard::Z) {
                    player.rotL = false;
                }
                if (event.key.code == sf::Keyboard::D) {
                    player.dirRotL();
                }
                if (event.key.code == sf::Keyboard::A) {
                    player.dirRotR();
                }
                if (event.key.code == sf::Keyboard::Space) {
                    player.stabilize = false;
                }
            }
        }

        time = clock.restart().asSeconds();
        player.doControl(time);
        engine.simulateNextFrame(time);


        renderWindow.clear();
        renderWindow.draw(background);
        for (sf::CircleShape* shape : cShapes) {
            renderWindow.draw(*shape);
        }
        for (sf::ConvexShape* shape : convShapes) {
            renderWindow.draw(*shape);
        }

        view.setCenter(player.getPosition());
        renderWindow.setView(view);

        renderWindow.display();
    }
}
