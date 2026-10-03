#include<iostream>
#include "Router.h"
#include "Link.h"
#include "Network.h"

int main(){
    Router routerA("A");
    Router routerB("B");
    Router routerC("C");
    
    Link linkAB(routerA.getId(), routerB.getId(), 5);
    Link linkBC(routerB.getId(), routerC.getId(), 5);

    Network network;

    network.addRouter(routerA);
    network.addRouter(routerB);
    network.addRouter(routerC);

    network.addLink(linkAB);
    network.addLink(linkBC);

    /*std::cout<<"Router A: "<<link.getRouterA()<<std::endl;
    std::cout << "Router B: " << link.getRouterB()<<std::endl;
    std::cout<<"Link Cost: "<<link.getCost()<<std::endl;*/
    std::cout<<"Routers:"<<std::endl;

    for(const Router& router:network.getRouters()) {
      std::cout<<"- "<<router.getId()<<std::endl;
    }

    std::cout<<"\nLinks:"<<std::endl;

    for(const Link& link:network.getLinks()){
        std::cout<<"- "<< link.getRouterA()<<"<-> "<<link.getRouterB()<<" | Cost: "<< link.getCost()<< std::endl;
    }
    return 0;
}