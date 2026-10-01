#ifndef LINK_H
#define LINK_H

#include <string>

class Link{
private:
    std::string routerA;
    std::string routerB;
    int cost;
public:
    Link(const std::string& routerA,const std::string& routerB,int cost);

    std::string getRouterA() const;
    std::string getRouterB() const;
    int getCost() const;

    void setCost(int cost);
};

#endif
