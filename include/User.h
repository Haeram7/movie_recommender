#pragma once
#include <string>
class User {
    private :
        static int nextID; // 고유 ID 생성을 위한 정적 멤버 변수
        int id;
        std::string name;
        std::string email;
    public :
        User();
        User(const std::string &n, const std::string &e);
        int getID() const;
        std::string getName() const;
        std::string getEmail() const;
        void display() const; 
        bool operator <(const User& other) const;
        bool operator >(const User& other) const;
        friend std::ostream& operator<<(std::ostream& os, const User& u);
};