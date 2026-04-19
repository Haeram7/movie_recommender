#pragma once
#include "User.h"
#include <vector>

class UserManager {
    private:
        std::vector<User> users;
    public:
        UserManager();
        void addUser(const User &u);
        User* findbyName(const std::string &name) const;
        void sortbyName();
        void printAll() const;

       
}