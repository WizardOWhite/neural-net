#ifndef BASICNEURALNET_NODE_H
#define BASICNEURALNET_NODE_H

#include <vector>
#include <iostream>

struct Weight {
	double weight;
	double deltaWeight;
};

class Node {
private:
	double _input;
	double _output;
	std::vector<Weight> inputWeights;
public:
	Node(int numInputs);
	void SetInput(double input);
	void FeedForward(const std::vector<Node>& prevLayer);
};

#endif //BASICNEURALNET_NODE_H
