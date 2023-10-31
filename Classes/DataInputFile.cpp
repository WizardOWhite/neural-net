//
// Created by lolgetreKt on 10/30/2023.
//
#include "DataInputFile.h"

DataInputFile::DataInputFile(const std::string& inputFileName) {
	inFile.open(inputFileName.c_str());
	if(!inFile.is_open()) {
		std::cout << "Failed to open file." << std::endl;
		exit(1);
	}
	else std::cout << "opened file" << std::endl;
}

std::vector<int> DataInputFile::GetTopology() {
	std::vector<int> topology;
	std::string line;
	std::string label;
	getline(inFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(label.compare("topology:") != 0 || ss.eof()) {
		std::cout << "Incorrect file formatting at: " << label << std::endl;
		exit(1);
	}
	while(!ss.eof()) {
		int value;
		ss >> value;
		topology.push_back(value);
	}
	return topology;
}

std::vector<double> DataInputFile::GetInputs() {
	std::vector<double> inputs;
	std::string line;
	std::string label;
	getline(inFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(label.compare("input:") != 0 || ss.eof()) {
		std::cout << "Incorrect file formatting at: " << label << std::endl;
		exit(1);
	}
	while(!ss.eof()) {
		double value;
		ss >> value;
		inputs.push_back(value);
	}
	return inputs;
}

std::vector<double> DataInputFile::GetTargets() {
	std::vector<double> targets;
	std::string line;
	std::string label;
	getline(inFile, line);
	std::stringstream ss(line);
	ss >> label;
	if(label.compare("target:") != 0 || ss.eof()) {
		std::cout << "Incorrect file formatting at: " << label << std::endl;
		exit(1);
	}
	while(!ss.eof()) {
		double value;
		ss >> value;
		targets.push_back(value);
	}
	return targets;
}

