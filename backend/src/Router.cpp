#include "Router.h"

Router::Router(const std::string& id){
    this->id = id;
}
std::string Router::getId() const{
    return id;
}