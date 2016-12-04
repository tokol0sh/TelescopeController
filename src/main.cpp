#include <cstdio>
#include <iostream>
#include "motor.hpp"
#include "Serial/serial.h"

int main(int argc, char** argv) {

	MOTOR_Vars_t RA_motor;
	MOTOR_Vars_t DEC_motor;
	std::cout << "size of motor struct: " << sizeof(RA_motor) << std::endl;
	std::vector<uint8_t> buffer;

	printf("Motor Controller Status\n");
	serial::Serial SerialPort("COM2", 115200, serial::Timeout::simpleTimeout(1000));

	while (1) {
		if (!SerialPort.available()) {
		}
		else {
			SerialPort.read(buffer);
			SerialPort.write(buffer);
			if (buffer.size() > sizeof(RA_motor)) {
   				memcpy(&RA_motor, &buffer[0], sizeof(buffer));
				std::cout << "something from motorstruct: " << RA_motor.Flag_enableForceAngle << std::endl;
				buffer.clear();
			}
		}
	}
	
	return 0;
}