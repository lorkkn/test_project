#pragma once
#include <SFML/Graphics.hpp>

#define playerSize 50

class Player
{
private:
	sf::RectangleShape body;
	sf::ConvexShape head;
public:
	Player() {
        head.setPointCount(3);
        head.setPoint(0, { 0.f, -30.f });
        head.setPoint(1, { -25.f, 20.f });
        head.setPoint(2, { 25.f, 20.f });
        head.setFillColor(sf::Color::Green);
        head.setOutlineColor(sf::Color::Black);
        head.setOutlineThickness(2.f);
        body.setSize({ 100,50 });
        body.setFillColor(sf::Color::Yellow);
        body.setOrigin({ 50 ,25 });
    }
    void Movement(sf::RenderWindow& window) {
        sf::Vector2f offset;
        int vel = 5;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            offset.y += -vel;
            body.setRotation(sf::degrees(0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            offset.y += vel;
            body.setRotation(sf::degrees(0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.x += -vel;
            body.setRotation(sf::degrees(90));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.x += vel;
            body.setRotation(sf::degrees(90));
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.y += vel - sqrt(vel * vel * 0.5);
            offset.x += vel - sqrt(vel * vel * 0.5);
            body.setRotation(sf::degrees(135));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.y += -vel + sqrt(vel * vel * 0.5);
            offset.x += -vel + sqrt(vel * vel * 0.5);
            body.setRotation(sf::degrees(315));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.y += vel - sqrt(vel * vel * 0.5);
            offset.x += -vel + sqrt(vel * vel * 0.5);
            body.setRotation(sf::degrees(45));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.y += -vel + sqrt(vel * vel * 0.5);
            offset.x += vel - sqrt(vel * vel * 0.5);
            body.setRotation(sf::degrees(225));

        }




        
        sf::Vector2u wSize = window.getSize();
        sf::Vector2f newPosition = body.getPosition() + offset;
        if (newPosition.x <0 + playerSize / 2 || newPosition.x > wSize.x - playerSize / 2) {
            offset.x = 0;
        }
        if (newPosition.y <0 + playerSize / 2 || newPosition.y > wSize.y - playerSize / 2) {
            offset.y = 0;
        }

        body.move(offset);
        head.move(offset);
    }
    void setPosition(sf::Vector2f position) {
        body.setPosition(position);
        head.setPosition(position);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(body);
        window.draw(head);
    }
    void headMovement(sf::RectangleShape sight) {
        sf::Vector2f direction = sight.getPosition() - head.getPosition();

        head.setRotation(sf::degrees(90)+direction.angle());
    }
    sf::Vector2f getPosition() {
        return head.getPosition();
    }
    sf::Angle getAngle() {
        return head.getRotation();
    }
};

class Bullet {
private:
    sf::CircleShape bullet;
    sf::Angle angle;
    int speed;
public:
    Bullet(sf::Vector2f position, sf::Angle angle_t, int speed_t) {
        angle = angle_t;
        speed = speed_t;
        bullet.setPosition(position);
        bullet.setFillColor(sf::Color::Black);
        bullet.setRadius(5);
    }
    void Movement() {
        sf::Vector2f offset_b(speed, angle);
        bullet.move(offset_b);
    }
    sf::Vector2f getPosition() {
        return bullet.getPosition();
    }
    void Draw(sf::RenderWindow& window) {
        window.draw(bullet);
    }
    
};

class Enemy {
private:
    sf::CircleShape enemy;
    int hp;
public:
    Enemy(sf::Vector2f pos) {
        enemy.setOrigin(sf::Vector2f(50, 50));
        enemy.setPosition(pos);
        enemy.setRadius(50);
        enemy.setFillColor(sf::Color::Magenta);
        hp = 2;
    }
    void ChangeHP(int change) {
        hp += change;
    }
    void SetHP(int sethp) {
        hp = sethp;
    }
    int GetHP() {
        return hp;
    }
    void Draw(sf::RenderWindow& window) {
        window.draw(enemy);
    }
    sf::Vector2f getPosition() {
        return enemy.getPosition();
    }
    void move(sf::Vector2f mov) {
        enemy.move(mov);
    }
    sf::CircleShape& GetShape() {
        return enemy;
    }
};