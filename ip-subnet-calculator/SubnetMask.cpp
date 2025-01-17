#include "SubnetMask.h"

SubnetMask::SubnetMask(const std::string inputMask) : NetworkEntity(inputMask) {
	if (!isValidBinary()) throw WrongArumentException();
	setPrefixLength();
}

SubnetMask::SubnetMask(const bool inputBinary[4][8]) : NetworkEntity(inputBinary)
{
	if (!isValidBinary()) throw WrongArumentException();
	setPrefixLength();
}

SubnetMask::SubnetMask(int inputPrefixLength) : SubnetMask([&]() {
	if (!(1 <= inputPrefixLength && inputPrefixLength <= 31)) {
		throw WrongArumentException();
	}
	bool tempBinary[4][8] = {};
	for (int i = 0; i < 4 && inputPrefixLength > 0; ++i) {
		for (int j = 0; j < 8 && inputPrefixLength > 0; ++j, --inputPrefixLength) {
			tempBinary[i][j] = 1;
		}
	}
	return tempBinary;
}()) {}


bool SubnetMask::isValidBinary() const {
	int flag = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (flag == 0 && bin[i][j]) flag = 1;
			if (flag == 1 && !bin[i][j]) flag = 2;
			if (flag == 2 && bin[i][j])return false;
		}
	}
	return true;
}

void SubnetMask::setPrefixLength() {
	prefixLength = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (bin[i][j]) ++prefixLength;
			else break;
		}
	}
}

int SubnetMask::getPrefixLength() const {
	return prefixLength;
}