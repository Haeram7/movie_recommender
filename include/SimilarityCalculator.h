#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public: 
    // 두 사용자의 평점 목록을 받아 유사도 점수 반환
    static int calculator(
        const std::vector<Rating>& user1, 
        const std::vector<Rating>& user2
    );
};