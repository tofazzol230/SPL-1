#include<iostream>
#include "Router.h"
#include "Link.h"

int main(){
    Router routerA("A");
    Router routerB("B");
    
    Link link(routerA.getId(), routerB.getId(), 5);

    std::cout<<"Router A: "<<link.getRouterA()<<std::endl;
    std::cout << "Router B: " << link.getRouterB()<<std::endl;
    std::cout<<"Link Cost: "<<link.getCost()<<std::endl;

    link.setCost(10);
    std::cout<<"Updated Link Cost: "<< link.getCost() << std::endl;

    return 0;
}