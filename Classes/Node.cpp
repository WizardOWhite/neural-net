#include "Node.h"

Node::Node(int numInputs) : _input(0), _output(0) {
	for(int i = 0; i < numInputs; i++) {
		auto randomWeight = static_cast<double>(std::rand()) / RAND_MAX;
		inputWeights.emplace_back(Weight{randomWeight, 0});
		//std::cout << "Random weight: " << randomWeight << std::endl;
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
	//_output = _input *
}
