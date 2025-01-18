#include "NetworkEntity.h"
/*
class NetworkEntity {
protected:
	std::string address;

	int dec[4];

	bool bin[4][8];

	void setDecimalByString();

	void setStringByDecimal();

	void setBinaryByDecimal();

	void setDecimalByBinary();

	std::exception WrongArumentException() {
		return std::exception("wrong arguments given");
	}

public:
	bool isValidString() const;

	bool isValidDecimal() const;

	std::string getDecimal() const;

	std::string getBinary() const;

};
*/

NetworkEntity::NetworkEntity(const std::string inputAddress) {

	address = inputAddress;

	if (!isValidString()) {
		throw WrongArumentException();
	}

	setDecimalByString();

	if (!isValidDecimal()) {
		throw WrongArumentException();
	}

	setBinaryByDecimal();
}

NetworkEntity::NetworkEntity(const int inputDecimal[4]) {

	std::copy(inputDecimal, inputDecimal + 4, dec);

	if (!isValidDecimal()) {
		throw WrongArumentException();
	}

	setStringByDecimal();
	setBinaryByDecimal();
}

NetworkEntity::NetworkEntity(const bool inputBinary[4][8]) {
	for (int i = 0; i < 4; ++i) {
		std::memcpy(bin[i], inputBinary[i], 8 * sizeof(bool));
	}
	setDecimalByBinary();
	setStringByDecimal();
}


bool NetworkEntity::isValidString() const {
	for (const char& c : address) {
		if (!(isdigit(c) || c == '.')) return false;
	}
	return true;
}

bool NetworkEntity::isValidDecimal() const {
	for (const int& octet : dec) {
		if (!(0 <= octet && octet <= 255)) return false;
	}
	return true;
}

void NetworkEntity::setDecimalByString() {
	int sz = this->address.size();
	int currentNumber = 0;
	int currentPos = 0;
	for (int i = 0; i < sz; ++i) {
		if (isdigit(address[i])) {
			currentNumber *= 10;
			currentNumber += (address[i] - '0');
		}
		if (address[i] == '.' || i + 1 == sz) {
			dec[currentPos] = currentNumber;
			currentNumber = 0;
			++currentPos;
		}
	}
}

void NetworkEntity::setStringByDecimal() {
	std::string result;
	for (int i = 3; i >= 0; --i) {
		int temp = dec[i];
		if (temp == 0) {
			result.push_back('0');
		}
		while (temp > 0) {
			result.push_back(char(temp % 10 + '0'));
			temp /= 10;
		}
		if (i != 0) result.push_back('.');
	}
	std::reverse(result.begin(), result.end());
	this->address = result;
}

void NetworkEntity::setBinaryByDecimal() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			bin[i][8 - (j + 1)] = (dec[i] & (1 << j));
		}
	}
}

void NetworkEntity::setDecimalByBinary() {
	for (int i = 0; i < 4; ++i) {
		dec[i] = 0;
		for (int j = 0; j < 8; ++j) {
			dec[i] += bin[i][8 - (j + 1)] ? (1 << j) : 0;
		}
	}
}

std::string NetworkEntity::getDecimal() const {
	return this->address;
}

std::string NetworkEntity::getBinary() const{
	std::string result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			result.push_back(bin[i][j] ? '1' : '0');
		}
		if (i != 3) result.push_back('.');
	}
	return result;
}

unsigned int NetworkEntity::getInteger() const {
	unsigned int result = 0;
	int cur = 0;
	for (int i = 3; i >= 0; --i) {
		for (int j = 7; j >= 0; --j, ++cur) {
			result += (bin[i][j] << cur);
		}
	}
	return result;
}

bool** NetworkEntity::getBinaryArray() const
{
	bool** copy = new bool* [4];
	for (int i = 0; i < 4; ++i) {
		copy[i] = new bool[8];
		std::memcpy(copy[i], bin[i], 8 * sizeof(bool));
	}
	return copy;
}
