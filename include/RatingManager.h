#pragma once
#include <iostream>
#include <vector>

class RatingManager {
    private:
        std::vector<Rating> ratings;
    public:
        RatingManager() {};
        void addRating(const Rating& r);
        void displaybyMovie(const std::string& title) const;
        void sortbyScore();
}