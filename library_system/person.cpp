#include "person.hh"
#include <iostream>

Person::Person(std::string name, std::string email, std::string address):
    name_(name), email_(email), address_(address)
{

}

Person::~Person()
{

}

std::string Person::get_name() const
{
    return name_;
}

void Person::print_info() const
{
    std::cout << "Name: " << name_ << std::endl;
    std::cout << "Email: " << email_ << std::endl;
    std::cout << "Address: " << address_ << std::endl;
}
