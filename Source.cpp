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
    std::vector<Bullet> bullets;
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
        //make bullet a class(circle, angle, speed)
        //make enemy a class(circle,hp)
        player.Movement(window);
        player.headMovement(sight);
        sight.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
       

        if (bullet_clock.getElapsedTime().asSeconds() > 0.1) {
            Shooting(player, bullets, bullet_clock, 0.1);
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
            bullets[i].Movement();
        }
 
        for (int i = bullets.size()-1;i>=0;i--) {
          
            for (int k = enemies.size() - 1;k >= 0;k--) {

                
                if (sf::Vector2f(bullets[i].getPosition() - enemies[k].getPosition()).length() < 50) {
                   bullets.erase(bullets.begin() + i);
                   enemies.erase(enemies.begin() + k);
                   break;
                }
            }
            
        }

        //----------------------------------------------------------------------------------------------------------------

        //drawing 
        player.draw(window);
        for (int k = 0;k < enemies.size();k++) {
            window.draw(enemies[k]);
        }
        for (int k = 0;k < bullets.size();k++) {
            bullets[k].Draw(window);
        }
        window.draw(sight);


        window.display();
    }
}

