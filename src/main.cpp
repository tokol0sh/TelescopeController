#include <cstdio>
#include <iostream>
#include <thread>  
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

void uartComms() {
	std::string buffer;
	std::vector<double> Odrive_data(30);
	printf("Connect to the Odrive\n");
	serial::Serial SerialPort("COM6", 921600, serial::Timeout::simpleTimeout(1000));

	std::string message;
	message = "s 0 6 " + std::to_string(0.0);
	SerialPort.write(message);


	for (int i = 0; i < 30; i++)
	{

		message = "g 0 " + std::to_string(i);

		SerialPort.write(message);

		SerialPort.readline(buffer, 30, "\n");
		Odrive_data[i] = (atof(buffer.c_str()));

		buffer.clear();
		SerialPort.flush();
	}
}



int main(int argc, char** argv) {

	int i = 0;
	double gain = 0.0015;
	double position = 0.0015;
	std::vector<double> Odrive_data(30);
	std::vector<graph> graphs;
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1400, 800), "Space Men");
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

	
	graphs.emplace_back(700, 100, 500, 100);
	graphs.emplace_back(100, 500, 500, 100);
	graphs.emplace_back(100, 100, 500, 100);
	graphs.emplace_back(700, 500, 500, 100);

	graphs[0].setTitle(font, "M0 Position Setpoint");

	graphs[1].setTitle(font, "DC Bus Voltage");

	graphs[2].setTitle(font, "M0 Position");
	
	

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


		for (i = 0; i < 30; i++) 
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


		graphs[0].addDatapoint(Odrive_data[VBUS_VOLTAGE]);
		graphs[1].addDatapoint(Odrive_data[M0_VEL_GAIN]);
		graphs[2].addDatapoint(Odrive_data[M0_ROTOR_PLL_POS]);

		std::cout << "Position setpoint: " << Odrive_data[M0_POS_SETPOINT]  << "\n";

		window.clear();

		for (int i = 0; i < graphs.size(); i++) {
			graphs[i].update(window);
			graphs[i].draw(window);
			graphs[i].drawStats(window, font);
		}



		window.display();
		sf::Time elapsed = clock.restart();
		std::cout << "FPS: " << 1/elapsed.asSeconds() << "\n";
		
	}
	
	return 0;
}