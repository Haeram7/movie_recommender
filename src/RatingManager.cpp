#include "RatingManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

RatingManager:: RatingManager() {}

void RatingManager::printAll() const {
    for(const auto &r : ratings) {
        r->display();
    }
}

bool RatingManager::isEmpty() const {
    return ratings.empty();
}

int RatingManager::size() const {
    return ratings.size();
}
void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // 헤더 스킵
    while(getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // \r 제거하여 오류 방지
        }
        std::stringstream ss(line);
        std::string token;
        int userID, movieID;
        double score;

        try {
            getline(ss, token, '|'); userID = stoi(token);
            getline(ss, token, '|'); movieID = stoi(token);
            getline(ss, token); score = stod(token);
            ratings.push_back(std::make_unique<Rating>(userID, movieID, score));
        }
        catch(...) {
            continue; // 형식 오류는 건너뜀
        }
    }
    file.close();
}
void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    file << "userID|movieID|score" << std::endl;
    for(const auto &r : ratings) {
        file << r->getUserID() << "|" << r->getMovieID() << "|" << r->getScore() << std::endl;
    }
    file.close();
}

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(std::make_unique<Rating>(r));
}

void RatingManager::displaybyMovie(int id, const std::string& title, const UserManager& userMgr) const {
    
    std::vector<const Rating*> filteredRatings;

    for(const auto &r : ratings) {
        if(r->getMovieID() == id) {
            filteredRatings.push_back(r.get());
        }
    }

    // 검색된 결과가 없는 경우 처리
    if(filteredRatings.empty()) {
        std::cout << "해당 영화에 대한 평가가 없습니다." << std::endl;
        return;
    }

    std::sort(filteredRatings.begin(), filteredRatings.end(), [](const Rating* a, const Rating* b) {
    return *b < *a; 
});

    // 제목 및 상세 평점 목록 출력
    std::cout << "=== 영화 [" << title << "] 평점 목록 ===" << std::endl;
    for(const auto &r : filteredRatings) {
        const User* user = userMgr.findbyId(r->getUserID());
        std::string name = (user != nullptr) ? user->getName() : "알 수 없는 사용자";

        std::cout << "평가한 사용자: " << name << ", 평점: " << r->getScore() << std::endl;
    }
}

void RatingManager:: sortbyScore() {
    std::sort(ratings.begin(), ratings.end(), [](const std::unique_ptr<Rating>& a, const std::unique_ptr<Rating>& b) {
        return *b < *a; 
    });
}

void RatingManager::sortbyID() {
    std::sort(ratings.begin(), ratings.end(), [](const std::unique_ptr<Rating>& a, const std::unique_ptr<Rating>& b) {
        if (a->getUserID() == b->getUserID()) {
            return a->getMovieID() < b->getMovieID(); // userID가 같으면 movieID로 정렬
        }
        return a->getUserID() < b->getUserID(); // userID로 정렬
    });
}

// 이미 해당 유저-영화 조합의 평점이 존재하면 true, 아니면 false 반환
bool RatingManager::hasAlreadyRated(int userId, int movieId) const {
    for (const auto& r : ratings) {
        if (r->getUserID() == userId && r->getMovieID() == movieId) {
            return true; // 중복 발견
        }
    }
    return false; // 중복 없음
}

std::vector<const Rating*> RatingManager::getUserRatings(int userID) const {
    std::vector<const Rating*> userRatings;
    for (const auto& r : ratings) {
        if (r->getUserID() == userID) {
            userRatings.push_back(r.get());
        }
    }
    return userRatings;
}

const std::vector<std::unique_ptr<Rating>>& RatingManager::getAllRatings() const {
    return ratings; // 모든 평점 반환
}
