#include "Recommender.h"
#include <cmath> // abs()를 double에 사용하기 위해 변경
#include <algorithm>
#include <iostream>
#include "Timer.h"

Recommender::Recommender(MovieManager& m, RatingManager& r, UserManager& u) : movieMgr(m), ratingMgr(r), userMgr(u) {}

double Recommender::similaritycalculation(const std::vector<const Rating*>& targetRatings, int user2) const {
    int commonCount = 0;
    double diffSum = 0.0;

    const auto& ratings2 = ratingMgr.getUserRatings(user2);

    for(const auto* rating1 : targetRatings) { 
        for(const auto* rating2 : ratings2) {
            if(rating1->getMovieID() == rating2->getMovieID()) {
                commonCount++;
                diffSum += std::abs(rating1->getScore() - rating2->getScore());
                break;
            }
        }
    }
    if(commonCount == 0) return -1.0; 
    return 10.0 * commonCount - diffSum; 
}


std::vector<std::pair<int, double>> Recommender::getTopKNeighbors(int targetUser, int topK) const {
    const auto& targetRatings = ratingMgr.getUserRatings(targetUser);

    std::set<int> otherUserID;
    for(const auto& r : ratingMgr.getAllRatings()) {
        if(r->getUserID() != targetUser) {
            otherUserID.insert(r->getUserID());
        }
    }

    std::vector<std::pair<int, double>> similarities;
    for(int other : otherUserID) {
        double sim = similaritycalculation(targetRatings, other);
        if(sim >= 0.0) {
            similarities.emplace_back(other, sim);
        }   
    }

    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    size_t unsignedTopK = static_cast<size_t>(topK);
    if(similarities.size() > unsignedTopK) {
        similarities.resize(unsignedTopK);
    }
    return similarities;
}

std::map<int, std::pair<double, double>> Recommender::accumulateMovieScores(
    const std::vector<std::pair<int, double>>& neighbors, 
    const std::set<int>& watchedMovies) const {
    
    std::map<int, std::pair<double, double>> movieScores;
    const double POSITIVE_RATING_CRITERIA = 7.0; // 매직 넘버 제거

    for(const auto& neighbor : neighbors) {
        int uID = neighbor.first;
        double sim = neighbor.second;

        for(const auto* r : ratingMgr.getUserRatings(uID)) {
            if(watchedMovies.find(r->getMovieID()) != watchedMovies.end()) {
                continue; 
            }
            if(r->getScore() >= POSITIVE_RATING_CRITERIA) { 
                movieScores[r->getMovieID()].first += sim * r->getScore(); 
                movieScores[r->getMovieID()].second += 1.0; 
            }
        }
    }
    return movieScores;
}

std::vector<Movie*> Recommender::recommendMovies(int targetUser, int topK, int topN) {
    Timer t("Recommender::recommendMovies");
    
    const auto& target = ratingMgr.getUserRatings(targetUser);
    if(target.empty()) return {};

    std::set<int> watchedMovies;
    for(const auto* r : target) {
        watchedMovies.insert(r->getMovieID());
    }

    auto similarities = getTopKNeighbors(targetUser, topK);
    if(similarities.empty()) return {};

    auto movieScores = accumulateMovieScores(similarities, watchedMovies);
    if(movieScores.empty()) return {};

    std::vector<std::pair<int, double>> scoredMovies;
    for(const auto& pair : movieScores) {
        double weightedScore = pair.second.first / pair.second.second; 
        scoredMovies.emplace_back(pair.first, weightedScore);
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    std::vector<Movie*> recommendations;
    size_t unsignedTopN = static_cast<size_t>(topN);
    size_t limit = std::min(unsignedTopN, scoredMovies.size());

    for(size_t i = 0; i < limit; i++) {
        Movie* movie = movieMgr.findbyId(scoredMovies[i].first);
        if(movie != nullptr) {
            recommendations.push_back(movie); 
        }
    }
    return recommendations;
}