#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    static int nextID; // 고유 ID 생성을 위한 정적 멤버 변수
    int         id;
    std::string title, genre;
    int         releaseYear;
    double      totalRating;    // averageRating 제거
    int         ratingCount;    // 추가

public:
    Movie();                    // 기본 생성자 추가
    Movie(const std::string& title,
          const std::string& genre, int year);
    Movie(const std::string& title, const std::string& genre,
          int year, double totalRating, int ratingCount); // 평점 포함 생성자 추가

    int         getID()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  // getYear → getReleaseYear
    double      getAverageRating()   const;  // getRating → getAverageRating
    int         getRatingCount()     const;
    void setReleaseYear(int year);  
    void addRating(double r);               
    static void setNextID(int num);
    void resetRatings(); // 평점 초기화 메서드 추가

    bool operator <(const Movie& other) const;
    bool operator >(const Movie& other) const;
    bool operator ==(const Movie& other) const;
    bool operator !=(const Movie& other) const;
    /*
    bool operator <=(const Movie& other) const;
    bool operator >=(const Movie& other) const;
    */
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
    };