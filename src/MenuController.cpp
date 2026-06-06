#include "MenuController.h"
#include <map>
#include <algorithm>

MenuController::MenuController(MovieManager& movieMgr, UserManager& userMgr, RatingManager& ratingMgr, Recommender& recommender)
    : movieMgr(movieMgr), userMgr(userMgr), ratingMgr(ratingMgr), recommender(recommender) {}

// 1. 영화 추가
void MenuController::handleAddMovie() {
    std::string title, genre;
    int year;

    std::cout << "영화 제목: ";
    std::getline(std::cin, title);
    if (movieMgr.findExactTitle(title) != nullptr) {
        throw std::runtime_error("이미 시스템에 동일한 이름의 영화가 존재합니다.");
    }
    std::cout << "장르: ";
    std::getline(std::cin, genre);
    std::cout << "개봉 연도: ";
    std::cin >> year;
    std::cin.ignore(100, '\n'); // 버퍼 정리
    Movie newMovie(title, genre, year);
    movieMgr.addMovie(newMovie); 
}

// 2. 제목으로 검색
void MenuController::handleSearchMovie() {
    if(movieMgr.isEmpty()) { 
        throw std::runtime_error("영화 목록이 비어 있습니다."); 
    }
    std::string searchTitle;
    std::cout << "검색할 영화 제목: ";
    std::getline(std::cin, searchTitle);

    auto results = movieMgr.findbyTitle(searchTitle);
    if (results.empty()) { 
        throw std::runtime_error("일치하는 영화가 없습니다.");
    }
    else {
        std::cout << "검색 결과:\n";
        for (const auto& m : results) {
            std::cout << *m << std::endl;
        }
    }
}

// 3. 평점순 정렬 출력
void MenuController::handleSortMovie() {
    if(movieMgr.isEmpty()) {
        throw std::runtime_error("영화 목록이 비어 있습니다.");
    }
    movieMgr.sortbyRating();
    std::cout << Color::CYAN << "========== 정렬된 영화 목록 ==========" << Color::RESET << std::endl;
    movieMgr.printAll();
}
// 4. 플랫폼 통계 출력
void MenuController::handlePlatformDashboard() {
    if(movieMgr.isEmpty() && ratingMgr.isEmpty() && userMgr.isEmpty()) {
        throw std::runtime_error("데이터가 부족합니다.");
    }

    // 🟢 가장 인기 있는 장르 계산 (누적 평점 등록 수 기준)
    std::map<std::string, int> genreCounts;
    const auto& allRatings = ratingMgr.getAllRatings();

    for (const auto& r : allRatings) {
        // 평점 뒤에 숨은 영화 객체를 찾아 장르 카운트 증가
        Movie* movie = movieMgr.findbyId(r->getMovieID());
        if (movie != nullptr) {
            genreCounts[movie->getGenre()]++;
        }
    }

    std::string popularGenre = "데이터 없음";
    int maxCount = 0;
    for (const auto& pair : genreCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            popularGenre = pair.first;
        }
    }
    std::cout << Color::YELLOW << " 📊  MOVIE RECOMMENDER SYSTEM DASHBOARD   " << Color::RESET << std::endl;
    std::cout << " • 총 등록된 영화 수    : " << movieMgr.size() << " 편" << std::endl;
    std::cout << " • 총 가입된 사용자 수  : " << userMgr.size() << " 명" << std::endl;
    std::cout << " • 누적 수집된 평점 수  : " << ratingMgr.size() << " 개" << std::endl;
    std::cout << " • 시스템 내 인기 장르  : "
              << popularGenre << " (총 " << maxCount << "개 평점 기록)" << std::endl;  
}

// 5. 사용자 추가
void MenuController::handleAddUser() {
    std::string name, email;
    std::cout << "사용자 이름: ";
    std::getline(std::cin, name);
    if (userMgr.findbyName(name) != nullptr) {
        throw std::runtime_error("동일한 이름의 사용자가 존재합니다.");
    }
    std::cout << "이메일: ";
    std::getline(std::cin, email);

    User newUser(name, email);
    userMgr.addUser(newUser);
}
// 6. 사용자 목록 출력
void MenuController::handlePrintUsers() {
    if(userMgr.isEmpty()) {
        throw std::runtime_error("사용자 목록이 비어 있습니다.");
    }
    std::cout << Color::GREEN << " ===== 사용자 목록 =====" << Color::RESET << std::endl;
    userMgr.printAll();
}
// 7. 사용자 별 평점 출력
void MenuController::handleDisplayRatingsByUser() {
    if(userMgr.isEmpty()) {
        throw std::runtime_error("사용자 목록이 비어 있습니다.");
    }
    std::string userName;
    std::cout << "평점을 볼 사용자 이름: ";
    std::getline(std::cin, userName);
    User* user = userMgr.findbyName(userName);
    if (user != nullptr) {
        std::vector<const Rating*> userRatings = ratingMgr.getUserRatings(user->getID());
        if (userRatings.empty()) {
            throw std::runtime_error("해당 사용자가 평가한 영화가 없습니다.");
        }
        std::sort(userRatings.begin(), userRatings.end(), [](const Rating* a, const Rating* b) {
            return a->getScore() > b->getScore();
        }); // 점수순 정렬 후 출력
        std::cout << "=== 사용자 [" << user->getName() << "]의 평점 목록 ===" << std::endl;
        for (const auto& r : userRatings) {
            Movie* movie = movieMgr.findbyId(r->getMovieID());
            std::string title = (movie != nullptr) ? movie->getTitle() : "알 수 없는 영화";
            std::cout << "영화 제목: " << title << ", 평점: " << r->getScore() << std::endl;
        }
    } else {
        throw std::runtime_error("일치하는 사용자가 목록에 없습니다.");
    }
}

// 8. 평점 입력
void MenuController::handleAddRating() {
    std::string userName, movieTitle;
    double score;

    std::cout << "사용자 이름: ";
    std::getline(std::cin, userName);
    User* user = userMgr.findbyName(userName);
    if (user == nullptr) {
        throw std::runtime_error("일치하는 사용자가 목록에 없습니다.");
    }

    std::cout << "영화 제목: ";
    std::getline(std::cin, movieTitle);
    Movie* movie = movieMgr.findExactTitle(movieTitle);
    if (!movie) {
        throw std::runtime_error("일치하는 영화가 목록에 없습니다.");
    }
    if (ratingMgr.hasAlreadyRated(user->getID(), movie->getID())) {
        throw std::runtime_error("이미 해당 영화에 평점을 남기셨습니다. 중복 평가는 불가능합니다.");
    }
    std::cout << "점수 입력 (0.0 - 10.0): ";
    std::cin >> score;
    std::cin.ignore(100, '\n'); // 버퍼 정리


    Rating newRating(user->getID(), movie->getID(), score);
    ratingMgr.addRating(newRating);
    movie->addRating(score); // 영화의 평점 업데이트
    std::cout << "평점이 추가되었습니다. 업데이트된 평점 : " << Color::GREEN << movie->getAverageRating() << Color::RESET << std::endl;
}
// 9. 영화별 평점 보기
void MenuController::handleDisplayRatingsByMovie() {
    if(movieMgr.isEmpty()) {
        throw std::runtime_error("영화 목록이 비어 있습니다.");
    }

    std::string movieTitle;
    std::cout << "평점을 볼 영화 제목: ";
    std::getline(std::cin, movieTitle);

    Movie* movie = movieMgr.findExactTitle(movieTitle); 

    if (movie != nullptr) {
        ratingMgr.displaybyMovie(movie->getID(), movie->getTitle(), userMgr);
    } else {
        throw std::runtime_error("일치하는 영화가 목록에 없습니다.");
    }
}
// 10. 영화 추천
void MenuController::handleRecommendation() {
    std:: string userName;
    std::cout << "추천을 받을 사용자 이름: ";
    std::getline(std::cin, userName);

    User* user = userMgr.findbyName(userName);
    if (user == nullptr) {
        throw std::runtime_error("일치하는 사용자가 목록에 없습니다.");
    }
    std::cout << "사용자들의 평가를 분석 중... "<< std::endl;
    std::vector<Movie*> recommendations = recommender.recommendMovies(user->getID(), 4); // 상위 4명과 유사한 사용자들의 평점을 분석하여 최대 6개의 영화 추천
    if(recommendations.empty()) {
        throw std::runtime_error("평가 데이터가 없거나 추천할 영화가 없습니다.");
    } 
    else {
        std::cout << Color::MAGENTA << "======== 추천 영화 목록 ========" << Color::RESET << std::endl;
        for (const auto& m : recommendations) {
            std::cout << *m << std::endl;
        }
    }
}

void MenuController::printMenu() const {
    std::cout << Color::BOLD << Color::YELLOW << "========================================" << Color::RESET << std::endl;
    std::cout << Color::BOLD << Color::YELLOW << "      🎬 MOVIE RECOMMENDER SYSTEM      " << Color::RESET << std::endl;
    std::cout << Color::BOLD << Color::YELLOW << "========================================" << Color::RESET << std::endl;

    std::cout << Color::CYAN << "\n[ 🎥 영화 관리 ]" << Color::RESET << std::endl;
    std::cout << "  1. 영화 추가" << std::endl;
    std::cout << "  2. 제목으로 검색" << std::endl;
    std::cout << "  3. 평점순 정렬 출력" << std::endl;
    
    std::cout << Color::YELLOW << "\n[ 📊 시스템 분석 ]" << Color::RESET << std::endl;
    std::cout << "  4. 플랫폼 통계 대시보드 조회" << Color::RESET << std::endl;

    std::cout << Color::GREEN << "\n[ 👤 사용자 관리 ]" << Color::RESET << std::endl;
    std::cout << "  5. 사용자 추가" << std::endl;
    std::cout << "  6. 사용자 목록 출력" << std::endl;
    std::cout << "  7. 사용자 별 평점 출력" << std::endl;

    std::cout << Color::MAGENTA << "\n[ 🌟 평점 및 추천 ]" << Color::RESET << std::endl;
    std::cout << "  8. 평점 입력" << std::endl;
    std::cout << "  9. 영화별 평점 출력" << std::endl;
    std::cout << " 10. 사용자별 영화 추천" << std::endl;

    std::cout << "\n  0. 프로그램 종료" << std::endl;
    std::cout << Color::BOLD << "\n 선택 > " << Color::RESET;
}