#include "Subnet.h"

Subnet::Subnet(const IpAddress networkAddress, const SubnetMask subnetMask) :
	networkAddress(networkAddress),
	subnetMask(subnetMask) {
	if (!isValidSubnet()) throw new std::exception("invalid subnet");
}

bool Subnet::isValidSubnet() const
{
	bool** addressBinary = networkAddress.getBinaryArray();
	bool** maskBinary = subnetMask.getBinaryArray();
	for (int i = 3; i >= 0; --i) {
		for (int j = 7; j >= 0; --j) {
			if (!maskBinary[i][j] && addressBinary[i][j]) return false;
			if (maskBinary[i][j])return true;
		}
	}
	return true;
}

IpAddress Subnet::getNetworkAddress() const
{
	return networkAddress;
}

IpAddress Subnet::getBroadcastAddress() const
{
	bool** addressBinary = networkAddress.getBinaryArray();
	bool** maskBinary = subnetMask.getBinaryArray();
	bool newAddressBinary[4][8];
	for (int i = 3; i >= 0; --i) {
		for (int j = 7; j >= 0; --j) {
			newAddressBinary[i][j] = (addressBinary[i][j] ||!maskBinary[i][j]);
		}
	}
	return IpAddress(newAddressBinary);
}

int Subnet::getUsableIPsCount() const
{
	int prefixLength = subnetMask.getPrefixLength();
	int hostBitsCount = 32 - prefixLength;
	return (1 << hostBitsCount) - 2;
}

bool Subnet::isInSubnet(const IpAddress ipAddress) const
{
	return ipAddress.getNetworkAddress(subnetMask) == networkAddress;
}

bool Subnet::contains(const Subnet other) const {
	return isInSubnet(other.getNetworkAddress()) && isInSubnet(other.getBroadcastAddress());
}

SubnetMask Subnet::getSubnetMask() const
{
	return subnetMask;
}

std::string Subnet::toString() const
{
	return networkAddress.getDecimal() + "/" + std::to_string(subnetMask.getPrefixLength());
}

bool Subnet::operator==(const Subnet& other) const {
	return this->networkAddress == other.networkAddress &&
		this->subnetMask.getInteger() == other.subnetMask.getInteger();
}



