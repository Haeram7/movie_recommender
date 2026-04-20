#include "RatingManager.h"
#include <algorithm>

RatingManager:: RatingManager() {}

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}

void RatingManager:: sortbyScore() {
    std::sort(ratings.begin(), ratings.end(), [](const Rating& a, const Rating& b) {
        return a.getScore() < b.getScore(); // 점수 기준 오름차순 정렬
    });
}

void RatingManager:: displaybyMovie(const int id) const {
    for(const auto &r : ratings)    {
        if(r.getMovieID() == id) {
            std::cout << r << std::endl; // Rating 클래스의 operator << 오버로딩을 이용하여 평가 정보 출력
        }
    }
}