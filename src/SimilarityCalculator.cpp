#include "SimilarityCalculator.h"
#include <cstdlib> 
int SimilarityCalculator::calculator(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2
) {
    int commonCount = 0; // 공통으로 본 영화 수
    int scoreDiffSum = 0; // 평점 차이의 합

    for(const Rating& r1 : user1) {
        for(const Rating& r2 : user2) {
            if(r1.getMovieId() == r2.getMovieId()) { 
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore()); // 평점 차이의 절대값을 더함
            }
        }
    }

    if(commonCount == 0) return -100; // 공통으로 본 영화가 없으면 유사도 점수는 매우 낮음

    return commonCount * 10 - scoreDiffSum; // 유사도 공식
}