#include "Events.h"
#include "Windows.h"



int main()

{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2d shooter");
   
    window.setFramerateLimit(60);
    sf::RectangleShape player({ playerSize*2,playerSize });//player
    sf::ConvexShape head;
    head.setPointCount(3);
    head.setPoint(0, { 0.f, -30.f });   
    head.setPoint(1, { -25.f, 20.f });  
    head.setPoint(2, { 25.f, 20.f });   
    head.setFillColor(sf::Color::Green);
    head.setOutlineColor(sf::Color::Black);
    head.setOutlineThickness(2.f);
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin({ playerSize ,playerSize/2 });
    player.setPosition({200,200});
    std::vector<sf::CircleShape> bullets;
    std::vector<sf::Angle> angles;
    
    std::vector<sf::CircleShape> enemies;

    sf::CircleShape enemy;
    enemy.setPosition(sf::Vector2f(200,200));
    enemy.setRadius(50);
    enemy.setFillColor(sf::Color::Red);
    enemy.setOrigin(sf::Vector2f(50, 50));
    
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
        
        PlayerMovement(window, player);

         sf::Vector2f direction = sight.getPosition() - player.getPosition();

         head.setRotation(sf::degrees(90)+direction.angle());

         sight.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
         
       
         head.setPosition(player.getPosition());

         
         if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)&&bullet_clock.getElapsedTime().asSeconds()>0.3) {
             sf::CircleShape bullet1(5);
             bullet1.setFillColor(sf::Color::Black);
             bullet1.setPosition(head.getPosition());
             bullets.push_back(bullet1);

             angles.push_back(direction.angle());
             bullet_clock.restart();
         }
        window.draw(player);
        
        for (int i = 0;i < bullets.size();i++) {
             sf::Vector2f offset_b(15, angles[i]);
             bullets[i].move(offset_b);
             window.draw(bullets[i]);
        }
 
        for (int i = 0;i < bullets.size();i++) {
          /*  if (bullets[i].getPosition().y > window.getSize().y-200) {
                bullets.erase(bullets.begin()+i);
                angles.erase(angles.begin() + i);
           }*/

            sf::Vector2f distance = bullets[i].getPosition() - enemy.getPosition();
            if (distance.length()<50) {
                bullets.erase(bullets.begin() + i);
                angles.erase(angles.begin() + i);
                enemy.setRadius(50);
            }
            
        }

        window.draw(enemy);
        window.draw(head);
        window.draw(sight);


        window.display();
    }
}

