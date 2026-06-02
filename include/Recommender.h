#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"
#include <vector>
#include <map>
#include <set>

class Recommender {
    private:
        MovieManager& movieMgr;
        RatingManager& ratingMgr;
        UserManager& userMgr;

        std::vector<std::pair<int, double>> getTopKNeighbors(int targetUser, int topK) const;
        std::map<int, std::pair<double, double>> accumulateMovieScores(
            const std::vector<std::pair<int, double>>& neighbors, 
            const std::set<int>& watchedMovies) const;
    public:
        Recommender(MovieManager& m, RatingManager& r, UserManager& u);
        double similaritycalculation(const std::vector<const Rating*>& targetRatings, int user2) const;
        std::vector<Movie*> recommendMovies(int targetUser, int topK, int topN = 6); // 6개 추천
};