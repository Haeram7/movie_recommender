#include "User.h"
#include <string>
#include <iostream>
int User::nextID = 1; // 정적 멤버 변수 초기화

User::User() 
    : name(""), email("") {}

User::User(const std::string &n, const std::string &e) 
    : id(nextID++), name(n), email(e) {}
User::User(int id, const std::string &n, const std::string &e) 
    : id(id), name(n), email(e) {}
void User::setNextID(int num) {
    nextID = num;
}
int User::getID() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }


std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID: " << u.id 
       << "\n이름: " << u.name
       << "\n이메일: " << u.email << '\n' << "--------------------------";
    return os;
}   


        