#ifndef SubnetMask_H
#define SubnetMask_H

#include "NetworkEntity.h"

class SubnetMask : public NetworkEntity{
private:
	int prefixLength;

	void setPrefixLength();

public:
	SubnetMask(const std::string inputMask);

	SubnetMask(const bool inputBinary[4][8]);

	SubnetMask(int prefixLength);

	bool isValidBinary() const;
	
	int getPrefixLength() const;
};

#endif // !SubnetMask_H