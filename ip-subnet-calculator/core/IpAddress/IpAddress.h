#ifndef IpAddress_H
#define IpAddress_H

#include "..\SubnetMask\SubnetMask.h"
#include "..\NetworkEntity\NetworkEntity.h"

class IpAddress : public NetworkEntity {
private:
public:
	IpAddress(const std::string inputAddress);

	IpAddress(const int inputDecimal[4]);

	IpAddress(const bool inputBinary[4][8]);

	IpAddress getNetworkAddress(const SubnetMask mask) const;

	IpAddress getBroadcastAddress(const SubnetMask mask) const;

	bool operator==(const IpAddress& other) const;

};

#endif // !IpAddress_H
