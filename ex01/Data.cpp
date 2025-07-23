#include "Data.hpp"

Data::Data() : id(0), name("default"), value(0.0), active(false) {
    std::cout << "Data default constructor called" << std::endl;
}

Data::Data(int id, const std::string& name, double value, bool active) 
    : id(id), name(name), value(value), active(active) {
    std::cout << "Data parameterized constructor called" << std::endl;
}

void Data::display() const {
    std::cout << "Data { id: " << id 
              << ", name: \"" << name 
              << "\", value: " << value 
              << ", active: " << (active ? "true" : "false") 
              << " }" << std::endl;
}