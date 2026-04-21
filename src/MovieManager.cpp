#include "MovieManager.h"
#include <algorithm>


MovieManager::MovieManager() {}

void MovieManager::addMovie(const Movie& m) {
    for(const auto &movie : movies) {
        if(m.getTitle() == movie.getTitle()) {
            std::cout << "같은 영화가 이미 존재합니다. : " << movie.getTitle() << std::endl;
            return; // 중복된 영화는 추가하지 않음
        }
    }
    movies.push_back(m);
    std::cout << "영화가 추가되었습니다: " << m.getTitle() << std::endl;
}


void MovieManager::removeMovie(const std::string& title) {
    // 제목이 일치하는 객체 찾기
    auto it = std::find_if(movies.begin(), movies.end(), 
        [&title](const Movie& m) { 
            return m.getTitle() == title; 
        });

    // 객체가 존재하면 벡터에서 삭제
    if (it != movies.end()) {
        movies.erase(it);
        std::cout << "성공적으로 삭제되었습니다." << std::endl;
    } else {
        std::cout << "해당 제목의 영화가 목록에 없습니다." << std::endl;
    }
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

Movie* MovieManager::findExactTitle(const std::string &title) {
    for (auto &m : movies) { 
        if (m.getTitle() == title) {
            return &m; // 일치하는 영화가 있으면 해당 영화 객체의 포인터를 반환
        }
    }
    return nullptr;
}
