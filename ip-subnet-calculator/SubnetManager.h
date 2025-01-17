#ifndef SubnetManager_H
#define SubnetManager_H

#include <vector>
#include "Subnet.h"

class SubnetManager {
public:
	bool areSubnetsOverlapping(const Subnet& subnet1, const Subnet& subnet2);

	std::vector<Subnet> splitSubnet(const Subnet& subnet, int newPrefixLength);

	Subnet mergeSubnets(const Subnet& subnet1, const Subnet& subnet2);
};

#endif // !SubnetManager_H

