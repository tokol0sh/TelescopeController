#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class graph {
public:
	float xOffset, yOffset, xAxis, yAxis, currentVal, RMSvalue = 0;
	std::vector<float> dataPoints;
	int index;
	sf::Text title;
	sf::Text currentValue;
	sf::Text CurrentValue;
	sf::Text rmstValue;
	sf::Text RmstValue;


	graph(float x, float y, float w, float h) : xOffset(x), yOffset(y), xAxis(w), yAxis(h), dataPoints(500,0), index(0){
	}

	void setPosition(float x, float y);
	float getPosition();
	void setAxisLength(float xlen, float ylen);
	float getAxisLength();
	void setTitle(sf::Font &font, char text[]);
	void drawStats(sf::RenderWindow &window, sf::Font &font);
	void draw(sf::RenderWindow &window);
	void addDatapoint(float data);
	void update(sf::RenderWindow &window);

};