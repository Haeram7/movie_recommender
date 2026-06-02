#include "Recommender.h"
#include <cmath> // abs()를 double에 사용하기 위해 변경
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include "Timer.h"

Recommender::Recommender(MovieManager& m, RatingManager& r, UserManager& u) : movieMgr(m), ratingMgr(r), userMgr(u) {}

double Recommender::similaritycalculation(int user1, int user2) const {
    int commonCount = 0;
    double diffSum = 0.0;

    std::vector<Rating> ratings1 = ratingMgr.getUserRatings(user1);
    std::vector<Rating> ratings2 = ratingMgr.getUserRatings(user2);
    for(const auto& rating1 : ratings1) {
        for(const auto& rating2 : ratings2) {
            if(rating1.getMovieID() == rating2.getMovieID()) {
                commonCount++;
                diffSum += std::abs(rating1.getScore() - rating2.getScore());
                break;
            }
        }
    }
    if(commonCount == 0) {
        return -1.0; // 엣지 케이스 (공통 평가가 없는 경우)
    }
    return 10 * commonCount - diffSum; // 유사도 계산 (값이 클수록 유사, 10 * 공통 - 점수 차이)
}

std::vector<Movie*> Recommender::recommendMovies(int targetUser, int topK, int topN) {
    Timer t("Recommender::recommendMovies");
    std::vector<Rating> target = ratingMgr.getUserRatings(targetUser);
    if(target.empty()) {
        return {};
    } // 엣지 케이스, 빈 벡터 반환 (평가가 없는 사용자)

    std::set<int> otherUserID; // 중복 사용자 ID 방지 위해 set 사용
    for(const auto& r : ratingMgr.getAllRatings()) {
        if(r.getUserID() != targetUser) {
            otherUserID.insert(r.getUserID());
        }
    }
    std::vector<std::pair<int, double>> similarities; // 사용자ID, 유사도 매핑
    for(int other : otherUserID) {
        double sim = similaritycalculation(targetUser, other);
        if(sim >= 0) { // 엣지 케이스 고려
            similarities.emplace_back(other, sim);
        }   
    }
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
    return a.second > b.second; // 유사도 내림차순 정렬
    });

    size_t unsignedTopK = static_cast<size_t>(topK); // 경고 방지 위해 size_t로 변환
    size_t k = 0; // 실제 유사한 사용자 수가 topK보다 적을 수 있으므로 조정 필요 
    if(similarities.size() > unsignedTopK) {
        similarities.resize(unsignedTopK); // 상위 K명으로 벡터 크기 조절
        k = unsignedTopK;
    }
    else {
        k = similarities.size(); // 실제 유사한 사용자 수로 K 조정
    }

    std::set<int> watchedMovies; // 이미 평가한 영화 ID set
    for(const auto& r : target) {
        watchedMovies.insert(r.getMovieID());
    }

    std::map<int, std::pair<double, double>> movieScores; // 영화 ID와 <유사도 가중치 합, 추천 횟수> 매핑
    for(size_t i = 0; i<k;i++) {
        int uID = similarities[i].first;
        double sim = similarities[i].second;
        for(const auto& r : ratingMgr.getUserRatings(uID)) {
            if(watchedMovies.find(r.getMovieID()) != watchedMovies.end()) {
                continue; // 이미 평가한 영화는 건너뜀
            }
            if(r.getScore() >= 7.0) { // 긍정적 평가만 반영(유사도 가중치로 계산하기 위해 / 부정적 평가가 추천되는 경우 방지)
                movieScores[r.getMovieID()].first += sim * r.getScore(); // 유사도 가중치 합산
                movieScores[r.getMovieID()].second += 1; // 추천 횟수 카운트
            }
        }
    }
    std::vector<std::pair<int, double>> scoredMovies; // 영화 ID와 최종 점수(가중치 / 추천 횟수) 매핑
    for(const auto& pair : movieScores) {
        int movieID = pair.first;
        double weightedScore = pair.second.first / pair.second.second; // 유사도 가중치 평균 계산
        scoredMovies.emplace_back(movieID, weightedScore);
    }
    std::sort(scoredMovies.begin(), scoredMovies.end(), [](const auto& a, const auto& b) {
    return a.second > b.second; // 최종 점수 내림차순 정렬
    });

    std::vector<Movie*> recommendations;
    size_t unsignedTopN = static_cast<size_t>(topN); // 경고 방지 위해 size_t로 변환

    if(scoredMovies.size() < unsignedTopN) {
        unsignedTopN = scoredMovies.size(); // 실제 추천할 영화 수로 N 조정
    }
    for(size_t i = 0; i<unsignedTopN && i<scoredMovies.size(); i++) {
        Movie* movie = movieMgr.findbyId(scoredMovies[i].first); // 영화 ID로 영화 객체 찾아서 추천 목록에 추가
        if(movie != nullptr) {
            recommendations.push_back(movie); 
        } // 존재하지 않는 영화에 대한 평가가 있을 수 있으므로 nullptr 체크(엣지 케이스)
    }
    return recommendations;
}