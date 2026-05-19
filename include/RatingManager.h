#pragma once
#include <iostream>
#include "BaseManager.h"
#include "Rating.h"
#include <vector>
#include "UserManager.h"

class RatingManager : public BaseManager {
    private:
        std::vector<Rating> ratings;
    public:
        RatingManager();
        void printAll() const override;
        bool isEmpty() const override;
        int size() const override;
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) const override;

        void addRating(const Rating& r);
        void displaybyMovie(int id, const std::string& title, const UserManager& userMgr) const;
        void sortbyScore();
        void sortbyID();
        bool hasAlreadyRated(int userId, int movieId) const;
       
        std::vector<Rating> getUserRatings(int userID) const;
        std::vector<Rating> getAllRatings() const;
        
};