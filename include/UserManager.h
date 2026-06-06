#pragma once
#include "User.h"
#include "BaseManager.h"
#include <vector>
#include <memory>
#include <cctype>
#include <algorithm>
class UserManager : public BaseManager {
    private:
        std::vector<std::unique_ptr<User>> users;
    public:
        UserManager();
        
        void printAll() const override;
        bool isEmpty() const override;
        int size() const override;
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) const override;

        void addUser(const User &u);
        User* findbyName(const std::string &name) const;
        
        const User* findbyId(int id) const;
        std::string toLowerString(std::string str) const;
        
};