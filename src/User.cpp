#include "User.h"
#include <string>
#include <iostream>
int User::nextID = 1; // 정적 멤버 변수 초기화

User::User() 
    : id(0), name(""), email("") {}

User::User(int ID, const std::string &n, const std::string &e) 
    : id(nextID++), name(n), email(e) {}

int User::getID() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::display() const{
    std::cout << "ID: " << id 
    << "\n" << "이름: " << name
    << "\n" << "이메일: " << email << '\n' << "--------------------------" << std::endl;
}

bool User:: operator <(const User& other) const {
    return this->name < other.name; // 이름으로 정렬
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


        