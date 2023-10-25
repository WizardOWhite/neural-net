#include "Node.h"
#include <cmath>

Node::Node(int numInputs, int layerNumber, int nodeNumber) : _input(0), _output(0), _nodePosition{layerNumber, nodeNumber} {
	for(int i = 0; i < numInputs; i++) {
		auto randomWeight = static_cast<double>(std::rand()) / RAND_MAX;
		inputWeights.emplace_back(Weight{randomWeight, 0});
		std::cout << "Random weight: " << randomWeight
		<< " || Layer: " << layerNumber
		<< " || Node: " << nodeNumber << std::endl;
	}
}

//The first layer should just feed inputs into the next layer, so values go straight to output.
void Node::SetInput(double input) {
	_output = input;
}

void Node::FeedForward(const std::vector<Node>& prevLayer) {
	for(int i = 0; i < prevLayer.size(); i ++) {
		_input += (inputWeights.at(i).weight * prevLayer.at(i)._output);
	}
	//Activation function
	_output = tanh(_input);
}
