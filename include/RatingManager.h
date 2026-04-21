#pragma once
#include <iostream>
#include "Rating.h"
#include <vector>

class RatingManager {
    private:
        std::vector<Rating> ratings;
    public:
        RatingManager();
        void addRating(const Rating& r);
        void displaybyMovie(const int id) const;
        void sortbyScore();
        bool hasAlreadyRated(int userId, int movieId) const;
};