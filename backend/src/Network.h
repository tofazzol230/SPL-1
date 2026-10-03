#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Router.h"
#include "Link.h"

class Network {
private:
    std::vector<Router> routers;
    std::vector<Link> links;

public:
    void addRouter(const Router& router);
    void addLink(const Link& link);

    const std::vector<Router>& getRouters() const;
    const std::vector<Link>& getLinks() const;
};

#endif