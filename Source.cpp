#include "Events.h"
#include "Windows.h"
#include "Classes.h"



int main()

{
    //settings
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2d shooter");
    window.setFramerateLimit(60);
   
    //object initialization
    Player player;
    player.setPosition({200,200});
    std::vector<sf::CircleShape> bullets;
    std::vector<sf::Angle> angles; 
    std::vector<sf::CircleShape> enemies;
    sf::Clock bullet_clock;
    sf::Clock enemy_clock;
    sf::RectangleShape sight({ 5,5 });
    sight.setFillColor(sf::Color::Black);


    //main loop
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
        

        //game logic
        //-----------------------------------------------------------------------------------------------------------------
        player.Movement(window);
        player.headMovement(sight);
        sight.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
       
         if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)&&bullet_clock.getElapsedTime().asSeconds()>0.3) {
             sf::CircleShape bullet1(5);
             bullet1.setFillColor(sf::Color::Black);
             bullet1.setPosition(player.getPosition());
             bullets.push_back(bullet1);

             angles.push_back(player.getAngle()+sf::degrees(-90));
             bullet_clock.restart();
         }

         if (enemy_clock.getElapsedTime().asSeconds() > 2) {
             
             sf::CircleShape enemy_temp;
             int radius = 50;
             enemy_temp.setOrigin(sf::Vector2f(50, 50));
             enemy_temp.setPosition(sf::Vector2f(getRandomNumber(50,window.getSize().x-50),getRandomNumber(0, window.getSize().y)));
             enemy_temp.setRadius(radius);
             enemy_temp.setFillColor(sf::Color::Red);
             enemies.push_back(enemy_temp);
             enemy_clock.restart();
         }

        
        
        for (int i = 0;i < bullets.size();i++) {
             sf::Vector2f offset_b(15, angles[i]);
             bullets[i].move(offset_b);
             window.draw(bullets[i]);
        }
 
        for (int i = bullets.size()-1;i>=0;i--) {
          
            for (int k = enemies.size() - 1;k >= 0;k--) {

                sf::Vector2f distance = bullets[i].getPosition() - enemies[k].getPosition();
                if (distance.length() < 50) {
                   bullets.erase(bullets.begin() + i);
                   angles.erase(angles.begin() + i);
                   enemies.erase(enemies.begin() + k);
                   break;
                }
            }
            
        }

        //-----------------------------------------------------------------------------------------------------------------

        //drawing 
        player.draw(window);
        for (int k = 0;k < enemies.size();k++) {
            window.draw(enemies[k]);
        }
        window.draw(sight);


        window.display();
    }
}

