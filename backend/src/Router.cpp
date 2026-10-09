#include "Router.h"

Router::Router(const std::string& id){
    this->id = id;
}
std::string Router::getId() const{
    return id;
}
void Router::setRoute(const std::string&destination,int distance){
    routingTable.setDistance(destination,distance);
}
int Router::getRoute(const std::string&destination)const{
    return routingTable.getDistance(destination);
}
const RoutingTable& Router::getRoutingTable()const{
    return routingTable;
}