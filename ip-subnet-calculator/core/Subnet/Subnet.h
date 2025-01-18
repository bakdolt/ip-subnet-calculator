#ifndef Subnet_H
#define Subnet_H

#include "..\IpAddress\IpAddress.h"
#include "..\SubnetMask\SubnetMask.h"

class Subnet {
private:
	const IpAddress networkAddress;
	const SubnetMask subnetMask;

public:
	Subnet(const IpAddress networkAddress, const SubnetMask subnetMask);

	bool isValidSubnet() const;

	IpAddress getNetworkAddress() const;

	IpAddress getBroadcastAddress() const;

	int getUsableIPsCount() const;

	bool isInSubnet(const IpAddress ipAddress) const;

	bool contains(const Subnet other) const;

	SubnetMask getSubnetMask() const;

	std::string toString() const;

	bool operator==(const Subnet& other) const;
};

#endif
