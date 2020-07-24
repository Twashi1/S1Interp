#pragma once
#include <fstream>

std::ofstream myfile;

template <class... T>
void FileLog(std::string sep = "\n", T... message) {
	myfile.open("log.txt");

	std::vector<T> vec = { message... };

	for (T m : vec) {
		myfile << m << sep;
	}
	myfile.close();
}

template <class... T>
std::ostream& LogTo(std::ostream& os, std::string sep="\n", T... message) {
	std::vector<T> vec = { message... };

	for (T m : vec) {
		os << "[ERROR]: " << message << sep;
	}
	return os;
}