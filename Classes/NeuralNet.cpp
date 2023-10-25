#include "NeuralNet.h"

NeuralNet::NeuralNet(const std::vector<int>& topology) {
	for(int i = 0; i < topology.size(); i++) {
		Net.emplace_back(topology.at(i));
	}
}

void NeuralNet::FeedInputs(const std::vector<double> &inputValues) {
	for(int i = 0; i < inputValues.size() - numBiasNodes; i++) {
		Net.at(0).at(i).SetInput(inputValues.at(i));
	}

}
//For each layer after the first, feed the inputs and calculate the outputs
void NeuralNet::FeedForward(const std::vector<double> &inputs) {
	for (int i = 1; i < Net.size(); i++) {
		for(int j = 0; i < Net.at(i).size() - 1; j++) {
			Net.at(i).at(j).FeedForward(Net.at(i));
		}
	}
}

void NeuralNet::BackPropagation(const std::vector<double> &targets) {

}

std::vector<double> NeuralNet::GetResults() {
	return std::vector<double>();
}



