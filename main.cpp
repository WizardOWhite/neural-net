#include <iostream>
#include <vector>
#include "Classes/Node.h"
#include "Classes/NeuralNet.h"

class NeuralNet;



int main() {
	std::vector<int> netTopology {3, 3, 3};
	NeuralNet neuralNet(netTopology);
	neuralNet.FeedInputs();
	neuralNet.FeedForward();
	return 0;
}
