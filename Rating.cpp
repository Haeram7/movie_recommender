#include "Rating.h"
#include <iostream>
Rating::Rating()
    : userID(0), movieID(0), score(0.0) {}

Rating::Rating(int ui, int mi, double s)
 : userID(ui), movieID(mi) {
    if (s<0.0 || s>5.0) {
        std::cout << "Warning: Invalid score: " << s << '\n'
                  << "Must be 0.0 to 5.0, Setting to 0.0" << std::endl;
        score = 0.0; // 유효성 검사 실패 시 기본값
    } 
    else {
        score = s;
    }
}

int Rating::getUserID() const { return userID; }
int Rating::getMovieID() const { return movieID; }
double Rating::getScore() const { return score; }

void Rating::display() const {
    std::cout << "UserID : " << userID << '\n'
              << "Rated MovieID : " << movieID << '\n'
              << "Score : " << score << '\n' << "-----------------" << std::endl;
}                           