#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "algorithm"

#include "Classes/Node.h"
#include "Classes/NeuralNet.h"
#include "Classes/DataInputFile.h"

std::vector<double> normalizeData(std::vector<double>& inputData) {
	auto max = std::max_element(inputData.begin(), inputData.end());
	std::cout << "Max: " << *max << std::endl;
	for (auto &value: inputData) {
		value = value / *max;
		std::cout << "Normalized datapoint: " << value << std::endl;
	}
}

int main() {
	std::string inputFileName = "C:/Users/lolgetreKt/CLionProjects/BasicNeuralNet/inputFile.txt";
	DataInputFile inputFile(inputFileName);
	std::vector<int> netTopology = inputFile.GetTopology();
	NeuralNet neuralNet(netTopology);
	int iterations = 1;
	while(!inputFile.isEof()) {
		std::cout << "iteration: " << iterations++ << std::endl;

		std::vector<double> inputs = inputFile.GetInputs();
		std::vector<double> targets = inputFile.GetTargets();

		neuralNet.SetInputs(inputs);
		neuralNet.SetExpectedOutputs(targets);

		neuralNet.FeedForward();
		neuralNet.BackPropagation();

		std::vector<double> outputs = neuralNet.GetResults();

		std::cout << "inputs: ";
		for (const auto &input: inputs) {
			std::cout << input << " ";
		}
		std::cout << std::endl;

		std::cout << "targets: ";
		for (const auto &target: targets) {
			std::cout << target << " ";
		}
		std::cout << std::endl;

		std::cout << "outputs: ";
		for (const auto &output: outputs) {
			std::cout << output << " ";
		}
		std::cout << std::endl;
		std::cout << "errors: ";
		for(int i = 0; i < outputs.size(); i++) {
			std::cout << targets[i] - outputs[i] << " ";
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
}
