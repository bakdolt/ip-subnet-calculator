#include "IpAddress.h"

IpAddress::IpAddress(const std::string inputAddress) : NetworkEntity(inputAddress) {}

IpAddress::IpAddress(const int inputDecimal[4]) : NetworkEntity(inputDecimal) {}

IpAddress::IpAddress(const bool inputBinary[4][8]) : NetworkEntity(inputBinary) {}

IpAddress IpAddress::getNetworkAddress(const SubnetMask mask) const {
	bool newBinaryAddress[4][8];
	bool** maskbinary = mask.getBinaryArray();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			newBinaryAddress[i][j] = (this->bin[i][j] && maskbinary[i][j]);
		}
	}
	return IpAddress(newBinaryAddress);
}

IpAddress IpAddress::getBroadcastAddress(const SubnetMask mask) const {
	bool newBinaryAddress[4][8];
	bool** maskbinary = mask.getBinaryArray();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 8; ++j) {
			newBinaryAddress[i][j] = (this->bin[i][j] || !maskbinary[i][j]);
		}
	}
	return IpAddress(newBinaryAddress);
}

bool IpAddress::operator==(const IpAddress& other) const
{
	return this->address == other.address;
}
