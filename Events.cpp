#include "Events.h"

void onResize(sf::RenderWindow& window) {

	sf::Vector2u size = window.getSize();

	if (size.x < 800)
		size.x = 800;
	if (size.y < 600)
		size.y = 600;

	window.setSize(size);

	sf::View view(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(size.x),static_cast<float>(size.y) }));
	window.setView(view);
}

void PlayerMovement(sf::RenderWindow& window, sf::RectangleShape& player) {
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
		offset.y += vel - sqrt(vel * vel * 0.5);
		offset.x += vel - sqrt(vel * vel * 0.5);
		player.setRotation(sf::degrees(135));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		offset.y += -vel + sqrt(vel * vel * 0.5);
		offset.x += -vel + sqrt(vel * vel * 0.5);
		player.setRotation(sf::degrees(315));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		offset.y += vel - sqrt(vel * vel * 0.5);
		offset.x += -vel + sqrt(vel * vel * 0.5);
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
	if (newPosition.x <0 + playerSize / 2 || newPosition.x > wSize.x - playerSize / 2) {
		offset.x = 0;
	}
	if (newPosition.y <0 + playerSize / 2 || newPosition.y > wSize.y - playerSize / 2) {
		offset.y = 0;
	}

	player.move(offset);

}


void Shooting(Player player, std::vector<Bullet>& bullets, sf::Clock& bullet_clock) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) ) {
		Bullet bullet(player.getPosition(), player.getAngle() + sf::degrees(-90), 30);
		bullets.push_back(Bullet(player.getPosition(), player.getAngle() + sf::degrees(-90), 30));
		bullet_clock.restart();
	}
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void EnemySpawn(sf::RenderWindow &window,Player &player, std::vector<Enemy>& enemies) {
	
	sf::Vector2f point;
	sf::Vector2f distance;
	int counter = 0;
	do {
		point.x = getRandomNumber(50, window.getSize().x - 50);
		point.y = getRandomNumber(50, window.getSize().y - 50);
		distance.x = point.x - player.getPosition().x;
		distance.y = point.y - player.getPosition().y;
		counter++;
		if (counter > 5) break;
	} while (distance.length()<200);
	Enemy enemy(point);
	enemies.push_back(enemy);
}

void EnemyMovement(sf::RenderWindow& window, Player& player, std::vector<Enemy>& enemies) {
	sf::Vector2f offset;
	int speed = 2;
	for(int i = 0; i < enemies.size();i++){
	offset= player.getPosition() - enemies[i].getPosition();
	offset = offset.normalized();
	offset.x *= speed;
	offset.y *= speed;
	enemies[i].move(offset);
	}
	
   
}