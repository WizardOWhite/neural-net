#include <cmath>
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
				Node newNode(0, i, j);
				layer.push_back(newNode);
			}
			else {
				Node newNode(topology[i - 1] + numBiasNodes, i, j);
				layer.push_back(newNode);
			}
			if(j == topology[i] - 1) {
				for(int k = 0; k < numBiasNodes; k++) {
					Node newNode(0, i, j+k+1);
					newNode.SetOutput(biasNodeBias);
					layer.push_back(newNode);
				}
			}
		}
		Net.push_back(layer);
	}
}

void NeuralNet::SetInputs(const std::vector<double> &inputValues) {
	if(inputValues.size() != Net[0].size() - numBiasNodes) {
		std::cout << "Input size: " << inputValues.size()
		<< " not equal to first layer size: " << Net[0].size() << std::endl;
		exit(1);
	}
	int i = 0;
	for(i = 0; i < inputValues.size(); i++) {
		Net[0][i].SetOutput(inputValues.at(i));
	}
}
//For each layer after the first, feed the inputs and calculate the outputs
void NeuralNet::FeedForward() {
	for (int i = 1; i < Net.size(); i++) {
		for(int j = 0; j < Net[i].size() - numBiasNodes; j++) {
			Net[i][j].FeedForward(Net.at(i - 1));
		}
	}
}

void NeuralNet::BackPropagation() {
	_outputValues = GetResults();
	double rmsError = 0;
	for (int i = 0; i < _outputValues.size() - numBiasNodes; i++) {
		double error = (_expectedOutputValues[i] - _outputValues[i]);
		error = error * error;
		rmsError += error;
	}
	rmsError = rmsError / _outputValues.size() - numBiasNodes;
	rmsError = sqrt(rmsError);

	auto &outputLayer = Net[Net.size()-1];
	for(int i = 0; i < outputLayer.size() - numBiasNodes; i++) {
		outputLayer[i].CalculateOutputGradients(_expectedOutputValues[i]);
	}

	for(int i = Net.size() - 2; i > 0; i--) {
		auto &hiddenLayer = Net[i];
		auto &nextLayer = Net[i+1];
		for (auto &node: hiddenLayer) {
			node.CalculateHiddenGradients(nextLayer);
		}
	}

	for(int i = Net.size() - 1; i > 0; i--) {
		auto &currentLayer = Net[i];
		auto &prevLayer = Net[i-1];
		for(int i = 0; i < currentLayer.size() - numBiasNodes; i++) {
			currentLayer[i].UpdateWeights(prevLayer);
		}
	}
}

std::vector<double> NeuralNet::GetResults() {
	std::vector<double> outputValues;
	for(int i = 0 ; i < Net[Net.size()-1].size() - numBiasNodes; i++) {
		outputValues.push_back(Net[Net.size()-1][i].GetOutput());
	}
	return outputValues;
}

void NeuralNet::SetExpectedOutputs(const std::vector<double> &expectedOutputs) {
	if(expectedOutputs.size() != Net[Net.size()-1].size() - numBiasNodes) {
		std::cout << "Expected output size not equal to last layer size." << std::endl;
		exit(1);
	}
	_expectedOutputValues = expectedOutputs;
}



