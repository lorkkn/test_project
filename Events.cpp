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