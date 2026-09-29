#ifndef ROUTER_H
#define ROUTER_H

#include<string>

class Router{
private:
    std::string id;

public:
    Router(const std::string& id);

    std::string getId() const;
};

#endif