#pragma once
#include "User.h"
#include <vector>

class UserManager {
    private:
        std::vector<User> users;
    public:
        UserManager();
        void addUser(const User &u);
        User* findbyName(const std::string &name);
        void sortbyName();
        void printAll() const;
        bool isempty() const;
        const User* findbyId(int id) const;
};