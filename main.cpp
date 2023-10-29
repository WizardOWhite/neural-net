#include <iostream>
#include <vector>
#include "Classes/Node.h"
#include "Classes/NeuralNet.h"
#include "algorithm"

std::vector<double> normalizeData(std::vector<double>& inputData) {
	auto max = std::max_element(inputData.begin(), inputData.end());
	std::cout << "Max: " << *max << std::endl;
	for (auto &value: inputData) {
		value = value / *max;
		std::cout << "Normalized input: " << value << std::endl;
	}
}



int main() {
	std::vector<double> inputs {312,532,856};
	normalizeData(inputs);
	std::vector<int> netTopology {3, 3, 3};
	NeuralNet neuralNet(netTopology);
	neuralNet.FeedInputs(inputs);
	neuralNet.FeedForward();
	return 0;
}
