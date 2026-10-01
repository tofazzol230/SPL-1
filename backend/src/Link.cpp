#include "Link.h"

Link::Link(const std::string& routerA,const std::string& routerB,int cost){
    this->routerA=routerA;
    this->routerB=routerB;
    this->cost=cost;
}

std::string Link::getRouterA() const{
    return routerA;
}
std::string Link::getRouterB() const{
    return routerB;
}
int Link::getCost() const{
    return cost;
}
void Link::setCost(int cost){
    this->cost=cost;
}