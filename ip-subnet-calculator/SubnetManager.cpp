#include "SubnetManager.h"

bool SubnetManager::areSubnetsOverlapping(const Subnet& subnet1, const Subnet& subnet2)
{
    return (subnet1.isInSubnet(subnet2.getNetworkAddress()) || subnet2.isInSubnet(subnet1.getNetworkAddress()));
}

std::vector<Subnet> SubnetManager::splitSubnet(const Subnet& subnet, int newPrefixLength)
{
    int originalPrefixLength = subnet.getSubnetMask().getPrefixLength();
    if (newPrefixLength < originalPrefixLength) {
        throw std::exception("new prefix must be longer than original prefix");
    }

    int numberOfSubnets = 1 << (newPrefixLength - originalPrefixLength);
    std::vector<Subnet> smallerSubnets;

    bool** binaryNetworkAddress = subnet.getNetworkAddress().getBinaryArray();
    bool smallerSubnetsBinaryMask[4][8] = {};

    for (int i = 0; i < 32; ++i) {
        *(*smallerSubnetsBinaryMask + i) = (i < newPrefixLength) ? 1 : 0;
    }
    SubnetMask newSubnetMask(smallerSubnetsBinaryMask);

   for (int i = 0; i < numberOfSubnets; ++i) {

        bool newBinaryAddress[4][8];
        for (int j = 0; j < 4; ++j) {
            std::memcpy(newBinaryAddress[j], binaryNetworkAddress[j], 8 * sizeof(bool));
        }

        for (int j = 0; j < newPrefixLength - originalPrefixLength; ++j) {
            *(*newBinaryAddress + originalPrefixLength + j) = ((i >> (newPrefixLength - originalPrefixLength - 1 - j)) & 1);
        }

        IpAddress newNetworkAddress(newBinaryAddress);
        smallerSubnets.emplace_back(newNetworkAddress, newSubnetMask);
    }

   return smallerSubnets;
}

Subnet SubnetManager::mergeSubnets(const Subnet& subnet1, const Subnet& subnet2)
{
    if (subnet1 == subnet2) {
        return subnet1;
    }

    const Subnet* firstSubnet;
    const Subnet* secondSubnet;
    if (subnet1.getNetworkAddress().getInteger() < subnet2.getNetworkAddress().getInteger()) {
        firstSubnet = &subnet1;
        secondSubnet = &subnet2;
    }
    else {
        firstSubnet = &subnet2;
        secondSubnet = &subnet1;
    }

    if (firstSubnet->contains(*secondSubnet)) {
        return *firstSubnet;
    }

    if (firstSubnet->getSubnetMask().getPrefixLength() != secondSubnet->getSubnetMask().getPrefixLength()) {
        throw std::exception("prefixes must be equal");
    }

    int prefixLength = firstSubnet->getSubnetMask().getPrefixLength() - 1;

    unsigned int firstBroadcast = firstSubnet->getBroadcastAddress().getInteger();
    unsigned int secondNetwork = secondSubnet->getNetworkAddress().getInteger();

    if (firstBroadcast != secondNetwork - 1) {
        throw std::exception("subnets must be adjacent");
    }

    SubnetMask subnetMask(prefixLength);

    return Subnet(firstSubnet->getNetworkAddress(), subnetMask);
}

