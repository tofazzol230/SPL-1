#ifndef ROUTER_H
#define ROUTER_H
#include "RoutingTable.h"

#include<string>

class Router{
private:
    std::string id;
    RoutingTable routingTable;

public:
    Router(const std::string& id);

    std::string getId() const;
    void setRoute(const std::string& destination, int distance);
    int getRoute(const std::string& destination) const;
    const RoutingTable& getRoutingTable() const;
};

#endif