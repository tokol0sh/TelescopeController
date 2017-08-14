#include <cstdio>
#include <iostream>
#include <thread>  
#include <mutex>
#include "motor.hpp"
#include "Serial/serial.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "graph.h"
#include <stack>
#include <ctime>
#include <queue>



std::stack<clock_t> tictoc_stack;
std::vector<double> Odrive_rxdata(57);
std::mutex Odrive_rxdata_mutex;

std::queue<std::string> Odrive_txdata;
std::mutex Odrive_txdata_mutex;

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
	std::string message;
	serial::Serial SerialPort("COM6", 921600, serial::Timeout::simpleTimeout(1000));
	message = "s 0 2 " + std::to_string(10000);
	SerialPort.write(message);
	
	while (SerialPort.isOpen()) {
		for (int i = 0; i < 30; i++)
		{
			message = "g 0 " + std::to_string(i);
			SerialPort.write(message);
			SerialPort.readline(buffer, 30, "\n");

			{
				std::lock_guard<std::mutex> guard(Odrive_rxdata_mutex);
				Odrive_rxdata[i] = (atof(buffer.c_str()));
			}

			buffer.clear();
			//SerialPort.flush();

			{
				std::lock_guard<std::mutex> guard(Odrive_txdata_mutex);
				if (Odrive_txdata.size() > 0) {
					SerialPort.write(Odrive_txdata.front());
					std::cout << "Position setpoint: " << Odrive_txdata.front() << "\n";
					Odrive_txdata.pop();
				}
			}
		}
	}
}



int main(int argc, char** argv) {
	std::vector<graph> graphs;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1400, 800), "Space Men");
	sf::Font font;
	std::string buffer;
	std::thread UART(uartComms);

	int i = 0;
	double gain = 0.0015;
	double position = 0.0015;


	std::cout << "Telescope Controller" << std::endl;

	
	// Load font file from disk
	if (!font.loadFromFile("../src/courier.ttf"))
	{
		std::cout << "Error loading font: courier.tff \n";
	}

	
	graphs.emplace_back(700, 100, 500, 100);
	graphs.emplace_back(100, 500, 500, 100);
	graphs.emplace_back(100, 100, 500, 100);
	graphs.emplace_back(700, 500, 500, 100);

	graphs[0].setTitle(font, "M0 Position Setpoint");
	graphs[1].setTitle(font, "DC Bus Voltage");
	graphs[2].setTitle(font, "M0 Position");
	graphs[3].setTitle(font, "FPS");


	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			position += 10.0;
			std::cout << "Position setpoint: " << position << "\n";
			{
				std::lock_guard<std::mutex> guard(Odrive_txdata_mutex);
				Odrive_txdata.push("s 0 " + std::to_string(M0_POS_SETPOINT) + ' ' + std::to_string(position));
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			position -= 10.0;
			std::cout << "Position setpoint: " << position << "\n";
			{
				std::lock_guard<std::mutex> guard(Odrive_txdata_mutex);
				Odrive_txdata.push("s 0 " + std::to_string(M0_POS_SETPOINT) + ' ' + std::to_string(position));
			}

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

		{
			std::lock_guard<std::mutex> guard(Odrive_rxdata_mutex);
			graphs[0].addDatapoint(Odrive_rxdata[VBUS_VOLTAGE]);
			graphs[1].addDatapoint(Odrive_rxdata[M0_POS_SETPOINT]);
			graphs[2].addDatapoint(Odrive_rxdata[M0_ROTOR_PLL_POS]);			
		}


		window.clear();
		for (int i = 0; i < graphs.size(); i++) {
			graphs[i].update_all(window, font);
		}


		sf::Time elapsed = clock.restart();
		graphs[3].addDatapoint(1 / elapsed.asSeconds());

		window.display();

		
	}
	UART.join();
	return 0;
}