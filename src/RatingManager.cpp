#include "RatingManager.h"
#include <algorithm>

RatingManager:: RatingManager() {}

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}

void RatingManager:: sortbyScore() {
    std::sort(ratings.begin(), ratings.end());
}

void RatingManager::displaybyMovie(const int id) const {
    std::vector<Rating> filteredRatings;

    for(const auto &r : ratings) {
        if(r.getMovieID() == id) {
            filteredRatings.push_back(r);
        }
    }

    if(filteredRatings.empty()) {
        std::cout << "해당 영화에 대한 평가가 없습니다." << std::endl;
        return;
    }

    std::sort(filteredRatings.begin(), filteredRatings.end());

    std::cout << "=== 영화 [" << filteredRatings.front().getMovieID() << "] 평점 목록 ===" << std::endl;
    for(const auto &r : filteredRatings) {
        std::cout << r << std::endl; 
    }
}

// 이미 해당 유저-영화 조합의 평점이 존재하면 true, 아니면 false 반환
bool RatingManager::hasAlreadyRated(int userId, int movieId) const {
    for (const auto& r : ratings) {
        if (r.getUserID() == userId && r.getMovieID() == movieId) {
            return true; // 중복 발견
        }
    }
    return false; // 중복 없음
}