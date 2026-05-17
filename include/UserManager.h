#pragma once
#include "User.h"
#include "BaseManager.h"
#include <vector>

class UserManager : public BaseManager {
    private:
        std::vector<User> users;
    public:
        UserManager();
        
        void printAll() const override;
        bool isEmpty() const override;
        int size() const override;
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) const override;

        void addUser(const User &u);
        User* findbyName(const std::string &name);
        void sortbyName();
        
        const User* findbyId(int id) const;
        
};