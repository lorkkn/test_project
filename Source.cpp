#include "Events.h"
#include "Windows.h"

#define pSize 50

int main()

{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2d shooter");
   
    window.setFramerateLimit(60);
    sf::RectangleShape player({ pSize*2,pSize });//player
    sf::ConvexShape head;
    head.setPointCount(3);
    head.setPoint(0, { 0.f, -30.f });   
    head.setPoint(1, { -25.f, 20.f });  
    head.setPoint(2, { 25.f, 20.f });   
    head.setFillColor(sf::Color::Green);
    head.setOutlineColor(sf::Color::Black);
    head.setOutlineThickness(2.f);
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin({ pSize ,pSize/2 });
    player.setPosition({200,200});
std::vector<sf::CircleShape> bullets;
        std::vector<sf::Angle> angles;
    sf::Clock bullet_clock;
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

         sf::Vector2f direction = sight.getPosition() - player.getPosition();

         head.setRotation(sf::degrees(90)+direction.angle());

         sight.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
         
       
         head.setPosition(player.getPosition());

         
         if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&bullet_clock.getElapsedTime().asSeconds()>0.5) {
             sf::CircleShape bullet1(5);
             bullet1.setFillColor(sf::Color::Black);
             bullet1.setPosition(head.getPosition());
             bullets.push_back(bullet1);

             angles.push_back(direction.angle());
             bullet_clock.restart();
         }
        window.draw(player);
        
        for (int i = 0;i < bullets.size();i++) {
             sf::Vector2f offset_b(5, angles[i]);
             bullets[i].move(offset_b);
             window.draw(bullets[i]);
         }

       
        window.draw(head);
        window.draw(sight);


        window.display();
    }
}