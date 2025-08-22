#include "Events.h"
#include "Windows.h"
#include "Classes.h"



int main()

{
    //settings
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "2d shooter");
    window.setFramerateLimit(90);
   
    //object initialization
    Player player;
    player.setPosition({200,200});
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    sf::Clock bullet_clock;
    sf::Clock enemy_clock;
    sf::RectangleShape sight({ 5,5 });
    sight.setFillColor(sf::Color::Black);

    window.setMouseCursorVisible(0);
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
       

        if (bullet_clock.getElapsedTime().asSeconds() > 0.2) {
            Shooting(player, bullets,bullet_clock);
        }
      
        if (enemy_clock.getElapsedTime().asSeconds() > 2) {
             
            EnemySpawn(window, player, enemies);
            enemy_clock.restart();
        }

        for (int i = 0;i < bullets.size();i++) {
            bullets[i].Movement();
        }

        EnemyMovement(window, player, enemies);
 
        for (int i = bullets.size()-1;i>=0;i--) {
          
            for (int k = enemies.size() - 1;k >= 0;k--) {

                
                if (sf::Vector2f(bullets[i].getPosition() - enemies[k].getPosition()).length() < 50) {//change to var
                   bullets.erase(bullets.begin() + i);
                   enemies[k].ChangeHP(-1);
                   enemies[k].GetShape().setFillColor(sf::Color::Red);
                   break;
                }
            }
            
        }

        for (int k = enemies.size() - 1;k >= 0;k--) {


            if (enemies[k].GetHP()<=0) {
                enemies.erase(enemies.begin() + k);
            }
        }

        //----------------------------------------------------------------------------------------------------------------

        //drawing 
        player.draw(window);
        for (int k = 0;k < enemies.size();k++) {
            enemies[k].Draw(window);
        }
        for (int k = 0;k < bullets.size();k++) {
            bullets[k].Draw(window);
        }
        window.draw(sight);


        window.display();
    }
}

