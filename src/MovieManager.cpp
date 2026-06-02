#include "MovieManager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Timer.h"

MovieManager::MovieManager() {}

void MovieManager::printAll() const {
    for (const auto &m : movies){
        std::cout << *m << std::endl; // Movie 클래스의 operator << 오버로딩을 이용하여 영화 정보 출력
 }
}

bool MovieManager::isEmpty() const {
    return movies.empty(); // 영화 목록이 비어있는지 여부 반환
}

int MovieManager::size() const {
    return movies.size(); // 영화 목록의 크기 반환
}

void MovieManager::loadFromFile(const std::string& filename) {
    Timer t("MovieManager::loadFromFile");
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    std::string line;
    getline(file, line); // 헤더 스킵
    while(getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // \r 제거하여 오류 방지
        }
        std::stringstream ss(line);
        std::string token;
        try {
            getline(ss, token, '|'); std::string title = token;
            getline(ss, token, '|'); std::string genre = token;
            getline(ss, token, '|'); int year = stoi(token);
            getline(ss, token, '|'); double total = stod(token);
            getline(ss, token); int count = stoi(token);
            movies.push_back(std::make_unique<Movie>(title, genre, year, total, count));
        } catch(...) {
            continue; 
        }
    }
    Movie::setNextID(movies.size() + 1); // 다음 ID는 현재 영화 수 + 1
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    file << "title|genre|year|totalrating|count" << std::endl;
    for(const auto &m : movies) {
        file << m->getTitle() << "|" << m->getGenre() << "|" << m->getReleaseYear() << "|" << m->getAverageRating() * m->getRatingCount() << "|" << m->getRatingCount() << std::endl;
    }
    file.close();
}

void MovieManager::addMovie(const Movie& m) {
    for(const auto &movie : movies) {
        if(m.getTitle() == movie->getTitle()) {
            std::cout << "같은 영화가 이미 존재합니다. : " << movie->getTitle() << std::endl;
            return; // 중복된 영화는 추가하지 않음
        }
    }
    movies.push_back(std::make_unique<Movie>(m));
    std::cout << "영화가 추가되었습니다: " << m.getTitle() << std::endl;
}

void MovieManager::sortbyRating() {
    std::sort(movies.begin(), movies.end(), [](const std::unique_ptr<Movie>& a, const std::unique_ptr<Movie>& b) {
        return *a > *b;
    });
}

std::vector<Movie*> MovieManager::findbyTitle(const std::string &title) const{
    std::vector<Movie*> results;
    for(const auto &m : movies){
        if(m->getTitle().find(title) != std::string::npos){
            results.push_back(m.get());
        } // 사용자 편의성을 위해 제목에 검색어가 포함되어 있는 경우 결과에 추가
    }
    return results;
}

const std::vector<std::unique_ptr<Movie>>& MovieManager::getAllMovies() const {
    return movies; 
}

Movie* MovieManager::findExactTitle(const std::string &title) {
    for (auto &m : movies) { 
        if (m->getTitle() == title) {
            return m.get(); // 일치하는 영화가 있으면 해당 영화 객체의 포인터를 반환
        }
    }
    return nullptr;
}

Movie* MovieManager::findbyId(int id) {
    for (auto &m : movies) {
        if (m->getID() == id) {
            return m.get();
        }
    }
    return nullptr; // 일치하는 영화가 없는 경우 nullptr 반환
}

void MovieManager::resetAllMovieRatings() {
    for (auto& m : movies) {
        m->resetRatings(); 
    }
}

