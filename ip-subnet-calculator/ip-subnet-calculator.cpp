// ip-subnet-calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <string>
#include "IpAddress.h"
#include "SubnetManager.h"
#include "Subnet.h"

using namespace std;

int main()
{
    /*
    string address = "192.168.1.1";
    IpAddress ipAddress1(address);

    SubnetMask mask("255.255.255.0");

    IpAddress network = ipAddress1.getNetworkAddress(mask);
    IpAddress broadcast = ipAddress1.getBroadcastAddress(mask);

    Subnet subnet(network, mask);
    cout << subnet.toString() << endl;
    */

    SubnetManager manager;
    
    /*
    std::vector<Subnet> subnets = manager.splitSubnet(subnet, 26);
    for (const Subnet& s : subnets) {
        cout << s.toString() << endl;
    }
    cout << manager.areSubnetsOverlapping(subnets[1], subnets[0]);
    */

    // Две соседние подсети с разным размером
    Subnet subnet1(IpAddress("192.168.0.0"), SubnetMask("255.255.255.128")); // /25
    // Подсеть 2 с маской /25
    Subnet subnet2(IpAddress("192.168.0.128"), SubnetMask("255.255.255.128")); // /25

    cout << subnet1.getBroadcastAddress().getInteger() << endl;
    cout << subnet2.getNetworkAddress().getInteger() << endl;

    try {
        Subnet mergedSubnet = manager.mergeSubnets(subnet1, subnet2);
        std::cout << "Merged Subnet: " << mergedSubnet.toString() << std::endl; // 192.168.0.0/23
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Cannot merge subnets: " << e.what() << std::endl;
    }
}
