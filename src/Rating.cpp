#include "Rating.h"
#include <iostream>
Rating::Rating()
    : userID(0), movieID(0), score(0.0) {}

Rating::Rating(int ui, int mi, double s)
 : userID(ui), movieID(mi), score(s) {
    if (s<0.0 || s>5.0) {
        std::cout << "경고: 유효하지 않은 점수: " << s << '\n'
                  << "0.0에서 5.0 사이의 값이어야 합니다. 기본값으로 설정합니다." << std::endl;
        score = 0.0; // 유효성 검사 실패 시 기본값
    } 
}

int Rating::getUserID() const { return userID; }
int Rating::getMovieID() const { return movieID; }
double Rating::getScore() const { return score; }

void Rating::display() const {
    std::cout << "사용자 ID : " << userID << '\n'
              << "평가된 영화 ID : " << movieID << '\n'
              << "점수 : " << score << '\n' << "-----------------" << std::endl;
}
bool Rating::operator<(const Rating& other) const {
    if(this->score != other.score) {
        return this->score < other.score; // 점수로 정렬
    }
    else {
        return this->movieID < other.movieID; // 점수가 같으면 영화 ID로 정렬
    }
}

std::ostream& operator<<(std::ostream& os, const Rating& r) {
    os << "사용자 ID : " << r.userID << '\n'
       << "점수 : " << r.score;
    return os;
}