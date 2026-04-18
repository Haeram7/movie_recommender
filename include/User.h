#pragma once
#include <string>
class User {
    private :
        int id;
        std::string name;
        std::string email;
    public :
        User();
        User(int ID, const std::string &n, const std::string &e);
        int getID() const;
        std::string getName() const;
        std::string getEmail() const;
        void display() const; 
        bool operator <(const User& other){} const;
        bool operator >(const User& other){} const;
        friend std::ostream& operator<<(std::ostream& os, const User& u)
};