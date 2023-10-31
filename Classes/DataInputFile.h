
#ifndef BASICNEURALNET_DATAINPUTFILE_H
#define BASICNEURALNET_DATAINPUTFILE_H

#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

class DataInputFile {
private:
	std::ifstream inFile;
public:
	DataInputFile(const std::string& inputFileName);
	bool isEof() { return inFile.eof();}
	std::vector<int> GetTopology();
	std::vector<double> GetInputs();
	std::vector<double> GetTargets();
};

#endif //BASICNEURALNET_DATAINPUTFILE_H
