#include "Node.h"

Node::Node(int numInputs) : _input(0), _output(0) {
}

//The first layer should just feed inputs into the next layer, so values go straight to output.
void Node::SetInput(double input) {
	_output = input;
}

void Node::FeedForward(const std::vector<Node>& prevLayer) {
	for(int i = 0; i < prevLayer.size() - 1; i ++) {
		_input += (inputWeights.at(i).weight * prevLayer.at(i)._output);
	}
	//Activation function
	//_output = _input *
}
