#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#include "fstream"
#include "iostream"
#include "random"

const int NUM_PIXELS = 47040000;
const int NUM_LABELS = 60000;

class NeuralNet {
public:
	NeuralNet() {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distribution(0., 1.);

		for(int i = 0; i < 10; i++) {
			for (int j = 0; j < 784; j++) {
				weights1[i][j] = distribution(mt);
			}
		}
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 10; j++) {
				weights2[i][j] = distribution(mt);
			}
		}
	}

	void feedForward() {
		for(int n = 0; n < NUM_LABELS; n++) {
			uint8_t expectedLabel[10] = {0,0,0,0,0,0,0,0,0,0};
			expectedLabel[labels[n]] = 1;
			//first layer
			for(int i = 0; i < 10; i++) {
				for(int j = 0; j < 784; j++) {
					sums[0][i] += float((pixels[i] / 255.) * weights1[i][j]);
				}
				sums[0][i] = tanh(sums[0][i]);
			}
			//second layer
			for(int i = 0; i < 10; i++) {
				for(int j = 0; j < 10; j++) {
					sums[1][i] += float((sums[1][i]) * weights2[i][j]);
				}
			}
		}
	}

	void readImages(const std::string &fileName);
	void readLabels(const std::string &fileName);

private:
	uint8_t labels[NUM_LABELS]{};
	uint8_t pixels[NUM_PIXELS]{};
	float sums[2][10]{};
	float weights1[10][784]{};
	float weights2[10][10]{};

	int topology[3] = {784, 10, 10};
};

void NeuralNet::readImages(const std::string &fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if(!file.is_open()) {
		printf("Error opening file.");
		exit(1);
	}

	int magicNumber, numImages, imageWidth, imageHeight;
	file.read(reinterpret_cast<char*>(&magicNumber), sizeof magicNumber);
	file.read(reinterpret_cast<char*>(&numImages), sizeof numImages);
	file.read(reinterpret_cast<char*>(&imageHeight), sizeof imageHeight);
	file.read(reinterpret_cast<char*>(&imageWidth), sizeof imageWidth);

	for(int i = 0; i < NUM_PIXELS; i++) {
		file.read(reinterpret_cast<char*>(&this->pixels[i]), sizeof(this->pixels[i]));
	}
}

void NeuralNet::readLabels(const std::string &fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if(!file.is_open()) {
		printf("Error opening file.");
		exit(1);
	}

	int magicNumber, numLabels;
	file.read(reinterpret_cast<char*>(&magicNumber), sizeof magicNumber);
	file.read(reinterpret_cast<char*>(&numLabels), sizeof numLabels);

	for(int i = 0; i < NUM_LABELS; i++) {
		file.read(reinterpret_cast<char*>(&this->labels[i]), sizeof(this->labels[i]));
	}
}

int main() {

	/*std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> distribution(0., 1.);

	std::string fileName;

	float pixels[784];
	for(auto &pixel : pixels) {
		pixel = distribution(mt);
	}

	float weights[10][784];

	for(auto &weightArray : weights) {
		for(float weight : weightArray) {
			weight = distribution(mt);
		}
	}

	float sums[10];

	for (auto sum : sums) {
		sum = 0.;
	}

	for(int i = 0; i < 10; i++) {
		for (int j = 0; j < 784; ++j) {
			sums[i] += weights[i][j] * pixels[j];
		}
	}*/


	std::string imageFileName = "./MNIST/train-images.idx3-ubyte";
	std::string labelFileName = "./MNIST/train-labels.idx1-ubyte";
	int timesToTrain = 10;

	NeuralNet net{};
	net.readImages(imageFileName);
	net.readLabels(labelFileName);

	for(int i = 0; i < timesToTrain; i++) {
		net.feedForward();
	}

	return 0;
}
#pragma clang diagnostic pop