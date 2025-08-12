#include "Events.h"

#define pSize 50

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2d shooter");
   
    window.setFramerateLimit(60);
    sf::RectangleShape player({ pSize*2,pSize });//player
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin({ pSize ,pSize/2 });
    player.setPosition({200,200});

    sf::RectangleShape sight({ 5,5 });//sight
    sight.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::Resized>())
            {
                onResize(window);
            }

        }

        window.clear(sf::Color::White);
        
        sf::Vector2f offset;
        int vel = 5;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            offset.y += -vel;
            player.setRotation(sf::degrees(0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            offset.y += vel;
            player.setRotation(sf::degrees(0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.x += -vel;
            player.setRotation(sf::degrees(90));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.x += vel;
            player.setRotation(sf::degrees(90));
        }
       
       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.y += vel-sqrt(vel * vel * 0.5);
            offset.x += vel-sqrt(vel * vel * 0.5);
            player.setRotation(sf::degrees(135));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.y += -vel+sqrt(vel*vel*0.5);
            offset.x += -vel+sqrt(vel * vel * 0.5);
            player.setRotation(sf::degrees(315));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            offset.y += vel - sqrt(vel * vel * 0.5);
            offset.x += -vel+sqrt(vel * vel * 0.5);
            player.setRotation(sf::degrees(45));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            offset.y += -vel + sqrt(vel * vel * 0.5);
            offset.x += vel - sqrt(vel * vel * 0.5);
            player.setRotation(sf::degrees(225));

        }

         sf::Vector2f pPosition = player.getPosition();
         sf::Vector2u wSize = window.getSize();
         sf::Vector2f newPosition = pPosition + offset;
         if (newPosition.x <0+pSize/2 || newPosition.x > wSize.x - pSize/2) {
             offset.x = 0;
         }
         if (newPosition.y <0+pSize/2 || newPosition.y > wSize.y - pSize/2) {
             offset.y = 0;
         }
        
         player.move(offset);

      


       


        window.draw(player);


        window.display();
    }
}