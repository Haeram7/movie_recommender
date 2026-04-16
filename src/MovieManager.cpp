#include "MovieManager.h"

MovieManager::MovieManager() {}

void MovieManager::addMovie(const Movie& m) {
    for(const auto &movie : movies) {
        if(m.getTitle() == movie.getTitle() && m.getReleaseYear() == movie.getReleaseYear()) {
            std::cout << "같은 영화가 이미 존재합니다. : " << movie.getTitle() << std::endl;
            return; // 중복된 영화는 추가하지 않음
        }
    }
    movies.push_back(m);
}

void MovieManager::removeMovie(const std::string &title) {
    movies.erase(std::remove_if(movies.begin(), movies.end(),
        [&title](const Movie& m) { return m.getTitle() == title; }),
        movies.end());
    // 람다 함수를 통하여 조건에 맞는 요소들(제목이 일치하는 영화)을 뒤로 밀어버리고 모두 제거
}

void MovieManager::printAll() const {
    for (const auto &m : movies){
        std::cout << m << std::endl; // Movie 클래스의 operator << 오버로딩을 이용하여 영화 정보 출력
 }
}

void MovieManager::sortbyRating() {
    std::sort(movies.begin(), movies.end());
    // Movie 클래스의 operator < 연산자 오버로딩을 이용하여 평점 기준 오름차순 정렬
}

std::vector<Movie> MovieManager::findbyTitle(const std::string &title) const{
    std::vector<Movie> results;
    for(const auto &m : movies){
        if(m.getTitle().find(title) != std::string::npos){
            results.push_back(m);
        } // 사용자 편의성을 위해 제목에 검색어가 포함되어 있는 경우 결과에 추가
    }
    return results;
}

