#include "User.h"
#include <string>
#include <iostream>
User::User() 
    : id(0), name(""), email("") {}

User::User(int ID, const std::string &n, const std::string &e) 
    : id(ID), name(n), email(e) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::display() const{
    std::cout << "ID: " << id 
    << "\n" << "Name: " << name
    << "\n" << "Email: " << email << '\n' << "--------------------------" << std::endl;
}

        