#ifndef BASICNEURALNET_NODE_H
#define BASICNEURALNET_NODE_H

#include <vector>
#include <iostream>

struct Weight {
	double weight;
	double deltaWeight;
};

struct Position {
	int layerNumber;
	int nodeNumber;
};

class Node {
private:
	double _input;
	double _output;
	std::vector<Weight> inputWeights;
public:
	Position _nodePosition;
	Node(int numInputs, int layerNumber, int nodeNumber);
	void SetInput(double input);
	void FeedForward(const std::vector<Node>& prevLayer);
};

#endif //BASICNEURALNET_NODE_H
