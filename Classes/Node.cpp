#include "Node.h"

Node::Node() : _input(0), _output(0), _weight(0), _deltaWeight(0) {
}

//The first layer should just feed inputs into the next layer, so values go straight to output.
void Node::SetInput(double input) {
	_output = input;
}

void Node::FeedForward(const std::vector<Node>& prevLayer) {
	for(int i = 0; i < prevLayer.size() - 1; i ++) {
		_input += (weights.at(i).weight * prevLayer.at(i)._output);
	}
	//Activation function
	//_output = _input *
}
