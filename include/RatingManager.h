#pragma once
#include <iostream>
#include "Rating.h"
#include <vector>
#include "UserManager.h"

class RatingManager {
    private:
        std::vector<Rating> ratings;
    public:
        RatingManager();
        void addRating(const Rating& r);
        void displaybyMovie(int id, const std::string& title, const UserManager& userMgr) const;
        void sortbyScore();
        bool hasAlreadyRated(int userId, int movieId) const;
        
};