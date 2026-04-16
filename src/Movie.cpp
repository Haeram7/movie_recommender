#include "Movie.h"
#include <iostream>

// 기본 생성자
Movie::Movie()
    : id(0),
      title(""), genre(""), releaseYear(0),
      totalRating(0.0), ratingCount(0) {} // 초기화 리스트로 기본값 설정

// 4인자 생성자
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {}

int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }
void Movie::setReleaseYear(int year) { 
    if(year < 1888 || year > 2100) { // 영화의 역사적 시작과 미래 예측 범위
        std::cout << "Warning: Invalid release year: " << year << '\n'
                  << "Setting to default year." << std::endl;
        releaseYear = 0; // 유효성 검사 실패 시 기본값
        return;
    }
    else {
        releaseYear = year;
    }
}

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;   // 0 나눗셈 방어
    return totalRating / ratingCount;   
}

void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) {
        std::cout << "Warning: Invalid score: " << r << '\n'
                  << "Must be 0.0 to 5.0"<< std::endl;
        return;    // 유효성 검사
    }
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {           
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  Ratings: " << getAverageRating()
              << " (" << ratingCount << " reviews)"
              << std::endl;
}

bool Movie::operator <(const Movie& other) const {
    if(this->getAverageRating() != other.getAverageRating()) {
        return this->getAverageRating() < other.getAverageRating();
    }
    return this->getTitle() < other.getTitle();
}

bool Movie::operator > (const Movie& other) const {
    return other < *this; // < 연산자 재활용
}

bool Movie::operator ==(const Movie& other) const {
    return this ->getTitle() == other.getTitle() && 
           this ->getReleaseYear() == other.getReleaseYear();
}

bool Movie::operator !=(const Movie& other) const {
    return !(*this == other);
}

bool Movie::operator <=(const Movie& other) const {
    return !(*this > other);
}

bool Movie::operator >=(const Movie& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Movie& m) const {
    os << m.getTitle() << " (" << m.getReleaseYear() << ") - "
       << m.getAverageRating() << " (" << m.getRatingCount() << " reviews)";
    return os;
}