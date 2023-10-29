#include "NeuralNet.h"

NeuralNet::NeuralNet(const std::vector<int>& topology) {
	for (const auto &item: topology) {
		if(item <= 0) {
			std::cout << "Invalid topology." << std::endl;
			exit(1);
		}
	}
	for(int i = 0; i < topology.size(); i++) {
		std::vector<Node> layer;
		for(int j = 0; j < topology[i]; j++) {
			if(i == 0) {
				Node newNode(0, i + 1, j + 1);
				layer.push_back(newNode);
			}
			else {
				Node newNode(topology[i - 1], i + 1, j + 1);
				layer.push_back(newNode);
			}
		}
		Net.push_back(layer);
	}
}

void NeuralNet::FeedInputs(const std::vector<double> &inputValues) {
	if(inputValues.size() != Net.at(0).size()) {
		std::cout << "Input size: " + inputValues.size()
		<< " not equal to first layer size: " + Net.at(0).size() << std::endl;
		exit(1);
	}
	for(int i = 0; i < inputValues.size(); i++) {
		Net.at(0).at(i).SetInput(inputValues.at(i));
	}

}
//For each layer after the first, feed the inputs and calculate the outputs
void NeuralNet::FeedForward() {
	for (int i = 1; i < Net.size(); i++) {
		for(int j = 0; j < Net.at(i).size(); j++) {
			Net.at(i).at(j).FeedForward(Net.at(i - 1));
		}
	}
}

void NeuralNet::BackPropagation(const std::vector<double> &targets) {

}

std::vector<double> NeuralNet::GetResults() {
	std::vector<double> outputValues;
	for (const auto &node: Net.at(Net.size()-1)) {
		outputValues.emplace_back(node.GetOutput());
	}
}



