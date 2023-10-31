#include "Node.h"
#include <cmath>

Node::Node(int numInputs, int layerNumber, int nodeNumber) : _input(0), _output(0), _nodePosition{layerNumber, nodeNumber} {
	for(int i = 0; i < numInputs; i++) {
		auto randomWeight = static_cast<double>(std::rand()) / RAND_MAX;
		inputWeights.emplace_back(Weight{randomWeight, 0});
		/*std::cout << "Random weight: " << randomWeight
		<< " || Layer: " << layerNumber + 1
		<< " || Node: " << nodeNumber + 1 << std::endl;*/
	}
}

void Node::SetOutput(double input) {
	_output = input;
}

void Node::FeedForward(const std::vector<Node>& prevLayer) {
	for(int i = 0; i < prevLayer.size(); i ++) {
		_input += (inputWeights.at(i).weight * prevLayer.at(i)._output);
	}
	//Activation function
	_output = tanh(_input);
	//std::cout << _nodePosition.layerNumber << ":" << _nodePosition.nodeNumber << ": " << _input << " -> " << _output << std::endl;
}

double Node::GetOutput() const {
	return _output;
}

void Node::CalculateHiddenGradients(std::vector<Node> &nextLayer) {
	double derivativesOfWeights = SumOfDOW(nextLayer);
	_gradient = derivativesOfWeights * ActivationFunctionDerivative(_output);
}

void Node::UpdateWeights(std::vector<Node> &prevLayer) {
	for(int i = 0; i < prevLayer.size(); i++) {
		Node &node = prevLayer[i];
		double oldDeltaWeight = inputWeights[i].deltaWeight;

		double newDeltaWeight = learningRate * node._output * _gradient + alpha * oldDeltaWeight;
		inputWeights[i].deltaWeight = newDeltaWeight;
		inputWeights[i].weight += newDeltaWeight;
	}

}

void Node::CalculateOutputGradients(double expectedOutput) {
	double delta = expectedOutput - _output;
	_gradient = delta * ActivationFunctionDerivative(_output);
}

double Node::ActivationFunctionDerivative(double output) {
	return 1.0 - (output * output);
}

double Node::SumOfDOW(std::vector<Node> &nextLayer) {
	double sum = 0;

	for(int i = 0; i < nextLayer.size() - 1; i++) {
		sum += nextLayer[i].GetInputWeight(_nodePosition.nodeNumber) * nextLayer[i]._gradient;
	}
	return sum;
}

double Node::GetInputWeight(int position) {
	return inputWeights[position].weight;
}
