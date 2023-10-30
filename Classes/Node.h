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
	double _gradient;
	std::vector<Weight> inputWeights;
	double learningRate = 0.15;
	double alpha = 0.5;
public:
	Position _nodePosition;
	Node(int numInputs, int layerNumber, int nodeNumber);
	void SetInput(double input);
	void FeedForward(const std::vector<Node>& prevLayer);
	double GetOutput() const;
	void CalculateOutputGradients(double expectedOutput);
	void CalculateHiddenGradients(std::vector<Node> &nextLayer);
	void UpdateWeights(std::vector<Node> &prevLayer);
	double ActivationFunctionDerivative(double output);
	double SumOfDOW(std::vector<Node> &vector);
	double GetInputWeight(int position);
};

#endif //BASICNEURALNET_NODE_H
