#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

struct Data {
    int         id;
    std::string name;
    double      value;
    bool        active;
    
    Data();
    Data(int id, const std::string& name, double value, bool active);
    
    void display() const;
};

#endif