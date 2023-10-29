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
		Net.emplace_back(layer);
		for(int j = 0; j < topology.at(i); j++) {
			if(i == 0)
				layer.emplace_back(0, i+1, j+1);
			else
				layer.emplace_back(topology.at(i-1), i+1, j+1);
		}
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
		for(int j = 0; i < Net.at(i).size(); j++) {
			Net.at(i).at(j).FeedForward(Net.at(i));
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



