#include "Movie.h"
#include <iostream>

int Movie::nextID = 1; // 정적 멤버 변수 초기화
// 기본 생성자
Movie::Movie()
    : id(0),
      title(""), genre(""), releaseYear(0),
      totalRating(0.0), ratingCount(0) {} // 초기화 리스트로 기본값 설정

// 4인자 생성자
Movie::Movie(const std::string& title,
             const std::string& genre, int year)
    : id(nextID++), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {
        if(year < 1888 || year > 2100) { // 영화의 역사적 시작과 미래 예측 범위
            std::cout << "경고: 유효하지 않은 개봉 연도: " << year << '\n'
                      << "기본 연도(2020)로 설정합니다." << std::endl;
            releaseYear = 2000; // 유효성 검사 실패 시 기본값
        }
      }

int         Movie::getID()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }
void Movie::setReleaseYear(int year) { 
    if(year < 1888 || year > 2100) { // 영화의 역사적 시작과 미래 예측 범위
        std::cout << "경고: 유효하지 않은 개봉 연도: " << year << '\n'
                  << "기본 연도로 설정합니다." << std::endl;
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
    if (r < 0.0 || r > 10.0) {
        std::cout << "경고: 유효하지 않은 점수: " << r << '\n'
                  << "0.0에서 10.0 사이의 값이어야 합니다." << std::endl;
        return;    // 유효성 검사
    }
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {           
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << " 개의 평가)"
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

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.getTitle() << " (" << m.getReleaseYear() << ") - "
       << m.getAverageRating() << " (" << m.getRatingCount() << " 개의 평가)" << '\n' << "---------------------------";
    return os;
}