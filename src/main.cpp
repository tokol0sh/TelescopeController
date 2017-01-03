#include <cstdio>
#include <iostream>
#include "motor.hpp"
#include "Serial/serial.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "graph.h"

/*
void SerialThread(MOTOR_Vars_t* RA_motor)
{
std::vector<uint8_t> buffer;

serial::Serial SerialPort("COM7", 115200, serial::Timeout::simpleTimeout(1000));
SerialPort.read(buffer);
//SerialPort.write(buffer);
if (buffer.size() > sizeof(RA_motor) - 1)
{
memcpy(&RA_motor, &buffer[0], sizeof(RA_motor));
std::cout << "Flag_enableSys: " << RA_motor.Flag_enableSys << " Flag_enableForceAngle: " << RA_motor.Flag_enableForceAngle << " V_bias: " << RA_motor.V_bias.value[2] << " Vbus: " << RA_motor.VdcBus_kV / pow(2, 24) * 1000 << " MotorSpeedTrajectory: " << RA_motor.SpeedTraj_krpm / pow(2, 24) * 1000 << "\r";
//std::cout << "Flag_enableFieldWeakening: " << RA_motor.Flag_enableFieldWeakening << std::endl;
//std::cout << "Flag_enableSys: " << RA_motor.Flag_enableSys << std::endl;
buffer.clear();
SerialPort.flush();
}

}
*/





int main(int argc, char** argv) {


	MOTOR_Vars_t RA_motor;
	MOTOR_Vars_t DEC_motor;
	std::cout << "size of motor struct: " << sizeof(RA_motor) << std::endl;
	std::cout << "bool size: " << sizeof(RA_motor.Flag_enableFieldWeakening)<< std::endl;
	std::cout << "CtrlState size: " << sizeof(RA_motor.CtrlState) << std::endl;
	std::cout << "EstState size: " << sizeof(RA_motor.EstState) << std::endl;
	std::cout << "UserErrorCode size: " << sizeof(RA_motor.UserErrorCode) << std::endl;
	std::cout << "long size: " << sizeof(RA_motor.IdRef_A) << std::endl;
	std::cout << "float size: " << sizeof(RA_motor.MagnCurr_A) << std::endl;
	std::cout << "mathvec3 size: " << sizeof(RA_motor.I_bias) << std::endl;

	std::cout << "1: " << (long)&RA_motor.Flag_enableSys - (long)&RA_motor << std::endl;
	std::cout << "2: " << (long) &RA_motor.Flag_Run_Identify - (long)&RA_motor << std::endl;
	std::cout << "3: " << (long)&RA_motor.Flag_MotorIdentified - (long)&RA_motor << std::endl;
	std::cout << "4: " << (long)&RA_motor.Flag_enableForceAngle - (long)&RA_motor << std::endl;
	std::cout << "5: " << (long)&RA_motor.Flag_enableFieldWeakening - (long)&RA_motor << std::endl;
	std::cout << "6: " << (long)&RA_motor.Flag_enableRsRecalc - (long)&RA_motor << std::endl;
	std::cout << "7: " << (long)&RA_motor.Flag_enableUserParams - (long)&RA_motor << std::endl;
	std::cout << "8: " << (long)&RA_motor.Flag_enableOffsetcalc - (long)&RA_motor << std::endl;
	std::cout << "9: " << (long)&RA_motor.Flag_enablePowerWarp - (long)&RA_motor << std::endl;
	std::cout << "10: " << (long)&RA_motor.Flag_enableSpeedCtrl - (long)&RA_motor << std::endl;
	//std::cout << "11: " << (long)&RA_motor.lala - (long)&RA_motor << std::endl;

	std::cout << "12: " << (long)&RA_motor.CtrlState - (long)&RA_motor.Flag_enableSpeedCtrl << std::endl;
	std::cout << "13: " << (long)&RA_motor.EstState - (long)&RA_motor << std::endl;
	std::cout << "14: " << (long)&RA_motor.UserErrorCode - (long)&RA_motor << std::endl;
	std::cout << "15: " << (long)&RA_motor.CtrlVersion - (long)&RA_motor << std::endl;


	sf::RenderWindow window(sf::VideoMode(800, 800), "Drawing Graphs");
	sf::Font font;
	std::vector<uint8_t> buffer;

	// Load font file from disk
	if (!font.loadFromFile("src/courier.ttf"))
	{
		std::cout << "Error loading font: courier.tff \n";
	}


	printf("Motor Controller Status\n");
	serial::Serial SerialPort("COM7", 115200, serial::Timeout::simpleTimeout(1000));
	
	graph vBus(100,100,300,100);
	vBus.setPosition(100,500);
	vBus.setAxisLength(500,100);
	vBus.setTitle(font, "DC Bus Voltage");
	
	while (window.isOpen())
	{
		SerialPort.write("A");
		SerialPort.read(buffer, sizeof(RA_motor));
		if ((buffer.size() >= sizeof(RA_motor) ))
		{
			memcpy(&RA_motor, &buffer[0], sizeof(RA_motor));
			std::cout << "Flag_enableSys: " << RA_motor.Flag_enableSys << " Flag_enableOffsetcalc: " << RA_motor.Flag_enableOffsetcalc << " V_bias: " << RA_motor.V_bias.value[2] / pow(2, 24)  << " Vbus: " << RA_motor.VdcBus_kV / pow(2, 24) * 1000 << " MotorSpeedTrajectory: " << RA_motor.SpeedTraj_krpm / pow(2, 24) * 1000 << "\r";
			//std::cout << "Power of 2: " << pow(9.5210223, 2.0) << std::endl;
			//std::cout << "Flag_enableSys: " << RA_motor.Flag_enableSys << std::endl;
			buffer.clear();
			SerialPort.flush();
		}
		buffer.clear();
		SerialPort.flush();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (event.type == sf::Event::Resized)
		{
			std::cout << "new width: " << event.size.width << std::endl;
			std::cout << "new height: " << event.size.height << std::endl;
		}

		vBus.addDatapoint((RA_motor.VdcBus_kV / pow(2, 24)) * 1000);
		window.clear();
		vBus.update(window);
		
		vBus.draw(window);
		vBus.drawStats(window, font);
		window.display();
	}
	
	return 0;
}