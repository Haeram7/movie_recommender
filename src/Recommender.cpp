#include "Recommender.h"
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>

Recommender::Recommender(MovieManager& m, RatingManager& r, UserManager& u) : movieMgr(m), ratingMgr(r), userMgr(u) {}

UserManager& Recommender::getUserManager() const { return userMgr; } 

double Recommender::similaritycalculation(int user1, int user2) const {
    int commonCount = 0;
    double diffSum = 0.0;

    for(const auto& rating1 : ratingMgr.getUserRatings(user1)) {
        for(const auto& rating2 : ratingMgr.getUserRatings(user2)) {
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
    return 10 * commonCount - diffSum; // 유사도 계산 (값이 클수록 유사)
}

std::vector<Movie*> Recommender::recommendMovies(int targetUser, int topK, int topN) {
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
        if(sim >= 0) {
            similarities.emplace_back(other, sim);
        }   
    }
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
    return a.second > b.second; // 유사도 내림차순 정렬
    });

    int k = 0;
    if(similarities.size() > topK) {
        similarities.resize(topK); // 상위 K명으로 벡터 크기 조절
        k = topK;
    }
    else {
        k = similarities.size(); // 실제 유사한 사용자 수로 K 조정
    }

    std::set<int> watchedMovies; // 이미 평가한 영화 ID set
    for(const auto& r : target) {
        watchedMovies.insert(r.getMovieID());
    }

    std::map<int, std::pair<double, double>> movieScores; // 영화 ID와 <유사도 가중치 합, 추천 횟수> 매핑
    for(int i = 0; i<k;i++) {
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
    if(scoredMovies.size() < topN) {
        topN = scoredMovies.size(); // 실제 추천할 영화 수로 N 조정
    }
    for(int i = 0; i<topN && i<scoredMovies.size(); i++) {
        recommendations.push_back(movieMgr.findbyId(scoredMovies[i].first));
    } //
    return recommendations;
}