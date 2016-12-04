#include "graph.h"

void graph::setPosition(float x, float y) {
	xOffset = x;
	yOffset = y;
}

float graph::getPosition() {
	return xOffset;
}

void graph::setAxisLength(float xlen, float ylen) {
	xAxis = xlen;
	yAxis = ylen;
}

float graph::getAxisLength() {
	return xAxis;
}

void graph::setTitle(sf::Font &font, char text[]) {

	title.setFont(font);
	title.setString(text);
	title.setCharacterSize(24);
	title.setPosition(xOffset + 25, yOffset - 5 - 24);
}

void graph::drawStats(sf::RenderWindow &window, sf::Font &font) {
	//Draw some stats below the graph. Input selects which stats to draw (min/max, avg, RMS, current val, etc)
	sf::Text currentValue;
	currentValue.setFont(font);
	currentValue.setCharacterSize(24);
	currentValue.setPosition(xOffset + 200, yOffset + 200);
	currentValue.setString(std::to_string(currentVal));

	sf::Text CurrentValue;
	CurrentValue.setFont(font);
	CurrentValue.setCharacterSize(24);
	CurrentValue.setPosition(xOffset, yOffset + 200);
	CurrentValue.setString("Current Value:");


	sf::Text rmstValue;
	rmstValue.setFont(font);
	rmstValue.setCharacterSize(24);
	rmstValue.setPosition(xOffset + 200, yOffset + 200 + 30);
	RMSvalue = sqrtf((1.0 / xAxis) * RMSvalue);
	rmstValue.setString(std::to_string(RMSvalue));

	sf::Text RmstValue;
	RmstValue.setFont(font);
	RmstValue.setCharacterSize(24);
	RmstValue.setPosition(xOffset, yOffset + 200 + 30);
	RmstValue.setString("RMS Value:");


	window.draw(currentValue);
	window.draw(CurrentValue);
	window.draw(rmstValue);
	window.draw(RmstValue);

}

void graph::draw(sf::RenderWindow &window) {
	sf::VertexArray chartAxis(sf::LinesStrip, 4);
	chartAxis[0].position = sf::Vector2f(0 + xOffset, 0 + yOffset);
	chartAxis[1].position = sf::Vector2f(0 + xOffset, 2 * yAxis + yOffset);
	chartAxis[2].position = sf::Vector2f(0 + xOffset, yAxis + yOffset);
	chartAxis[3].position = sf::Vector2f(xAxis + xOffset, yAxis + yOffset);
	chartAxis[0].color = sf::Color::Green;
	chartAxis[1].color = sf::Color::Green;
	chartAxis[2].color = sf::Color::Green;
	chartAxis[3].color = sf::Color::Green;
	window.draw(chartAxis);
	window.draw(title);
}

void graph::addDatapoint(float data) {
	dataPoints.push_back(data);
	while (dataPoints.size() > xAxis) {
		dataPoints.erase(dataPoints.begin());
	}
}

void graph::update(sf::RenderWindow &window) {
	sf::VertexArray chart(sf::LinesStrip, 0);
	chart.clear();
	for (int i = 0; i < dataPoints.size(); i++) {
		float x = i;
		float y = *(dataPoints.begin() + i);

		currentVal = yAxis - y;
		RMSvalue += pow((yAxis - y), 2.0);
		chart.append(sf::Vertex(sf::Vector2f(x + xOffset, y + yOffset), sf::Color::Blue));
	}
	window.draw(chart);
}
