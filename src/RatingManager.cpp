#include "RatingManager.h"
#include <algorithm>

RatingManager:: RatingManager() {}

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}

void RatingManager:: sortbyScore() {
    std::sort(ratings.begin(), ratings.end());
}
void RatingManager::displaybyMovie(int id, const std::string& title, const UserManager& userMgr) const {
    
    std::vector<Rating> filteredRatings;

    for(const auto &r : ratings) {
        if(r.getMovieID() == id) {
            filteredRatings.push_back(r);
        }
    }

    // 검색된 결과가 없는 경우 처리
    if(filteredRatings.empty()) {
        std::cout << "해당 영화에 대한 평가가 없습니다." << std::endl;
        return;
    }

    // 점수순 정렬 (Rating::operator< 사용)
    std::sort(filteredRatings.begin(), filteredRatings.end());

    // 제목 및 상세 평점 목록 출력
    std::cout << "=== 영화 [" << title << "] 평점 목록 ===" << std::endl;
    for(const auto &r : filteredRatings) {
        const User* user = userMgr.findbyId(r.getUserID());
        std::string name = (user != nullptr) ? user->getName() : "알 수 없는 사용자";

        std::cout << "평가한 사용자: " << name << ", 평점: " << r.getScore() << std::endl;
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