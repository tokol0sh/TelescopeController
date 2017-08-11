#include <cstdio>
#include <iostream>
#include "motor.hpp"
#include "Serial/serial.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "graph.h"
#include <stack>
#include <ctime>



std::stack<clock_t> tictoc_stack;

void tic() {
	tictoc_stack.push(clock());
}

void toc() {
	std::cout << "Time elapsed: "
		<< ((double)(clock() - tictoc_stack.top())) / CLOCKS_PER_SEC
		<< std::endl;
	tictoc_stack.pop();
}

int main(int argc, char** argv) {

	int i = 0;
	double gain = 0.0015;
	double position = 0.0015;
	std::vector<double> Odrive_data(30);
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1400, 800), "Drawing Graphs");
	sf::Font font;
	std::string buffer;

	std::cout << "Telescope Controller" << std::endl;


	// Load font file from disk
	if (!font.loadFromFile("../src/courier.ttf"))
	{
		std::cout << "Error loading font: courier.tff \n";
	}


	printf("Motor Controller Status\n");
	serial::Serial SerialPort("COM6", 921600, serial::Timeout::simpleTimeout(1000));
	

	graph iBus(700, 100, 500, 100);
	//iBus.setPosition(700, 100);
	//iBus.setAxisLength(500, 100);
	iBus.setTitle(font, "M0 Position Setpoint");


	graph vBus(100,500,500,100);
	//vBus.setPosition(100,500);
	//vBus.setAxisLength(500,100);
	vBus.setTitle(font, "DC Bus Voltage");


	graph DEC_position(100, 100, 500, 100);
	//DEC_position.setPosition(100, 100);
	//DEC_position.setAxisLength(500, 100);
	DEC_position.setTitle(font, "M0 Position");
	
	
	std::string message;
	message = "s 0 6 " + std::to_string(0.0);
	SerialPort.write(message);

	
	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gain += 0.0001;
			message = "s 0 5 " + std::to_string(gain);
			SerialPort.write(message);

			std::cout << "Position setpoint: " << gain << "\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gain -= 0.0001;
			message = "s 0 5 " + std::to_string(gain);
			std::cout << "Position setpoint: " << gain << "\n";
			
			SerialPort.write(message);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			position += 10.0;
			message = "p 0 " + std::to_string(position) + " 0 0";
			SerialPort.write(message);

			std::cout << "Position setpoint: " << position << "\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			position -= 10.0;
			message = "p 0 " + std::to_string(position) + " 0 0";
			std::cout << "Position setpoint: " << position << "\n";

			SerialPort.write(message);
		}


		for (i = 25; i < 30; i++) 
		{

			message = "g 0 " + std::to_string(i);

			SerialPort.write(message);

			SerialPort.readline(buffer, 30, "\n");
			Odrive_data[i] = (atof(buffer.c_str()));

			buffer.clear();
			SerialPort.flush();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
			}
		}


		vBus.addDatapoint(Odrive_data[VBUS_VOLTAGE]);
		iBus.addDatapoint(Odrive_data[M0_VEL_GAIN]);
		DEC_position.addDatapoint(Odrive_data[M0_ROTOR_PLL_POS]);
		std::cout << "Position setpoint: " << Odrive_data[M0_POS_SETPOINT]  << "\n";

		window.clear();

		vBus.update(window);
		iBus.update(window);
		DEC_position.update(window);
		
		vBus.draw(window);
		iBus.draw(window);
		DEC_position.draw(window);

		vBus.drawStats(window, font);
		iBus.drawStats(window, font);
		DEC_position.drawStats(window, font);

		window.display();
		sf::Time elapsed = clock.restart();
		std::cout << "FPS: " << 1/elapsed.asSeconds() << "\n";
		
	}
	
	return 0;
}