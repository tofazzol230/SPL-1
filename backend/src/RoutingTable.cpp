#include "RoutingTable.h"

void RoutingTable::setDistance(const std::string& destination, int distance) {
    distances[destination] = distance;
}
int RoutingTable::getDistance(const std::string& destination) const{
    auto it = distances.find(destination);
    if (it != distances.end()){
        return it->second;
    }
    return -1;
}
bool RoutingTable::hasDestination(const std::string& destination) const{
    return distances.find(destination) != distances.end();
}
const std::unordered_map<std::string, int>&
RoutingTable::getDistances() const{
    return distances;
}