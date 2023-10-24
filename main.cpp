#include <iostream>
#include <vector>

class Node;
class NeuralNet;

int main() {
	std::vector<int> netTopology {3, 3, 3};
	return 0;
}


class NeuralNet {
private:
	std::vector<std::vector<Node>> Net;
	std::vector<double> _inputValues;
	std::vector<double> _outputValues;
	std::vector<double> _expectedOutputValues;
public:
	NeuralNet(const std::vector<int>& topology) {
		for(int i = 0; i < topology.size(); i++) {
			Net.emplace_back(std::vector<Node>(topology.at(i)));
		}
	}
	void FeedForward(const std::vector<double>& inputs) {

	}
	void BackPropagation(const std::vector<double>& targets) {

	}
	std::vector<double> GetResults() {

	}
};

class Node {

};