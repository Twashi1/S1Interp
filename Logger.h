#pragma once
#include <fstream>

std::ofstream myfile;

void Log(const char* message) {
	myfile.open("log.txt");
	myfile << message;
	myfile.close();
}

void LogError(const char* message) {
	myfile.open("log.txt");
	myfile << "ERROR: " << message;
	myfile.close();
}