#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    // 각 객체로 이루어진 벡터 선언
    std::vector<Movie> movies;
    std::vector<User> users;
    std::vector<Rating> ratings;

    // 영화 객체 생성, emplace_back을 사용하여 내부에서 직접 생성
    movies.emplace_back(1, "Oldboy", "Thriller", 2003);
    movies.emplace_back(2, "Interstellar", "Sci-Fi", 2014);
    movies.emplace_back(3, "Oppenheimer", "Drama", 2023);
    movies.emplace_back(4, "Frozen", "Animation", 2013);
    
    // 사용자 객체 생성, emplace_back을 사용하여 내부에서 직접 생성
    users.emplace_back(1, "Haeram", "uhaelam86@gmail.com");
    users.emplace_back(2, "Alice", "alice@naver.com");

    // 평점 객체 생성, emplace_back을 사용하여 내부에서 직접 생성
    ratings.emplace_back(1, 1, 3.5); // Haeram
    ratings.emplace_back(1, 3, 5.0); // Haeram
    ratings.emplace_back(1, 4, 2.7); // Haeram
    ratings.emplace_back(2, 1, 7.0); // Alice, 유효성 검사 확인
    ratings.emplace_back(2, 2, 4.5); // Alice
    ratings.emplace_back(2, 4, 4.1); // Alice

    // 각 영화에 대한 평점 추가 및 평균 평점 출력
    std::cout << "===== Updating Movie Ratings =====" << std::endl;
    for(const auto& r : ratings) {
        for(auto& m : movies) { // 영화 객체에 대한 값이 수정되므로 const 제거
            if(m.getId() == r.getMovieID()) {
                m.addRating(r.getScore());
                std::cout << "ID: " << m.getId() 
                << ", Updated Average Rating: " << m.getAverageRating() << std::endl;
            }
        }
    }
    // 영화 정보(평점 포함) 출력
    std::cout << "===== Movie Information =====" << std::endl;
    for(const auto& a : movies) {
        a.display();
    }
    // 사용자 정보 출력
    std::cout << "===== User Information =====" << std::endl;
    for(const auto& u : users) {
        u.display();   
    }
    // 평점 정보 출력
    std::cout << "===== Rating Information =====" << std::endl;
    for(const auto& r : ratings) {
        r.display();    
    }
    return 0;
}