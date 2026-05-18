#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"
#include <vector>

class Recommender {
    private:
        MovieManager& movieMgr;
        RatingManager& ratingMgr;
        UserManager& userMgr;
    public:
        Recommender(MovieManager& m, RatingManager& r, UserManager& u);
        UserManager& getUserManager() const;
        double similaritycalculation(int user1, int user2) const;
        std::vector<Movie*> recommendMovies(int targetUser, int topK, int topN = 6);
};