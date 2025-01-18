#ifndef NetworkEntity_H
#define NetworkEntity_H

#include <string>

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
	NetworkEntity(const std::string inputAddress);

	NetworkEntity(const int inputDecimal[4]);

	NetworkEntity(const bool inputBinary[4][8]);

	bool isValidString() const;

	bool isValidDecimal() const;

	std::string getDecimal() const;

	std::string getBinary() const;

	unsigned int getInteger() const;

	bool** getBinaryArray() const;

};

#endif // !NetworkEntity_H