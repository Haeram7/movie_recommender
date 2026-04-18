#include "User.h"
#include <string>
#include <iostream>
User::User() 
    : id(0), name(""), email("") {}

User::User(int ID, const std::string &n, const std::string &e) 
    : id(ID), name(n), email(e) {}

int User::getID() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::display() const{
    std::cout << "ID: " << id 
    << "\n" << "이름: " << name
    << "\n" << "이메일: " << email << '\n' << "--------------------------" << std::endl;
}

bool User:: operator <(const User& other) const {
    if(this->id != other.id) {
        return this->id < other.id;
    }
    return this->name < other.name; // ID가 같을 경우 이름으로 비교하여 정렬
}

bool User:: operator >(const User& other) const {
    return other < *this; // > 연산자는 < 연산자를 이용하여 구현
}

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID: " << u.id 
       << "\n이름: " << u.name
       << "\n이메일: " << u.email;
    return os;
}   


        