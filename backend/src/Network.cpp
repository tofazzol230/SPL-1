#include "Network.h"

void Network::addRouter(const Router& router){
    routers.push_back(router);
}
void Network::addLink(const Link& link){
  links.push_back(link);
}
const std::vector<Router>& Network::getRouters() const{
  return routers;
}
const std::vector<Link>& Network::getLinks() const{
    return links;
}