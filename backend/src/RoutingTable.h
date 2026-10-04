#ifndef ROUTING_TABLE_H
#define ROUTING_TABLE_H

#include<string>
#include<unordered_map>

class RoutingTable{
private:
    std::unordered_map<std::string, int> distances;
public:
    void setDistance(const std::string& destination,int distance);
    int getDistance(const std::string& destination) const;
    bool hasDestination(const std::string& destination) const;
    const std::unordered_map<std::string,int>& getDistances() const;
};
#endif