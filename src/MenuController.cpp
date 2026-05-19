#include "MenuController.h"
#include <algorithm>

MenuController::MenuController(MovieManager& movieMgr, UserManager& userMgr, RatingManager& ratingMgr, Recommender& recommender)
    : movieMgr(movieMgr), userMgr(userMgr), ratingMgr(ratingMgr), recommender(recommender) {}

// 1. 영화 추가
void MenuController::handleAddMovie() {
    std::string title, genre;
    int year;

    std::cout << "영화 제목: ";
    std::getline(std::cin, title);
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
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::string searchTitle;
    std::cout << "검색할 영화 제목: ";
    std::getline(std::cin, searchTitle);

    auto results = movieMgr.findbyTitle(searchTitle);
    if (results.empty()) {
        std::cout << "검색 결과가 없습니다." << std::endl;
    } else {
        std::cout << "검색 결과:\n";
        for (const auto& m : results) {
            std::cout << m << std::endl;
        }
    }
}
// 3. 전체 목록 출력
void MenuController::handlePrintMovies() {
    if(movieMgr.isEmpty()) {
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::cout << " ===== 영화 목록 =====\n";
    movieMgr.printAll();
}
// 4. 평점순 정렬 출력
void MenuController::handleSortMovie() {
    if(movieMgr.isEmpty()) {
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }
    movieMgr.sortbyRating();
    std::cout << "영화가 평점순으로 정렬되었습니다." << std::endl;
    handlePrintMovies();
}
// 5. 사용자 추가
void MenuController::handleAddUser() {
    std::string name, email;
    std::cout << "사용자 이름: ";
    std::getline(std::cin, name);
    std::cout << "이메일: ";
    std::getline(std::cin, email);

    User newUser(name, email);
    userMgr.addUser(newUser);
}
// 6. 사용자 목록 출력
void MenuController::handlePrintUsers() {
    if(userMgr.isEmpty()) {
        std::cout << "사용자 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::cout << " ===== 사용자 목록 =====\n";
    userMgr.printAll();
}
// 7. 사용자 별 평점 출력
void MenuController::handleDisplayRatingsByUser() {
    if(userMgr.isEmpty()) {
        std::cout << "사용자 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::string userName;
    std::cout << "평점을 볼 사용자 이름: ";
    std::getline(std::cin, userName);
    User* user = userMgr.findbyName(userName);
    if (user != nullptr) {
        std::vector<Rating> userRatings = ratingMgr.getUserRatings(user->getID());
        if (userRatings.empty()) {
            std::cout << "해당 사용자가 평가한 영화가 없습니다." << std::endl;
            return;
        }
        std::sort(userRatings.begin(), userRatings.end()); // 점수순 정렬 후 출력
        std::cout << "=== 사용자 [" << user->getName() << "]의 평점 목록 ===" << std::endl;
        for (const auto& r : userRatings) {
            Movie* movie = movieMgr.findbyId(r.getMovieID());
            std::string title = (movie != nullptr) ? movie->getTitle() : "알 수 없는 영화";
            std::cout << "영화 제목: " << title << ", 평점: " << r.getScore() << std::endl;
        }
    } else {
        std::cout << "일치하는 사용자가 목록에 없습니다." << std::endl;
    }
}

// 8. 평점 입력
void MenuController::handleAddRating() {
    std::string userName, movieTitle;
    double score;

    std::cout << "사용자 이름: ";
    std::getline(std::cin, userName);
    User* user = userMgr.findbyName(userName);
    if (!user) {
        std::cout << "일치하는 사용자가 목록에 없습니다." << std::endl;
        return; // 일치하는 사용자가 없으면 종료
    }

    std::cout << "영화 제목: ";
    std::getline(std::cin, movieTitle);
    Movie* movie = movieMgr.findExactTitle(movieTitle);
    if (!movie) {
        std::cout << "일치하는 영화가 목록에 없습니다." << std::endl;
        return; // 영화 없으면 종료
    }
    if (ratingMgr.hasAlreadyRated(user->getID(), movie->getID())) {
        std::cout << "이미 해당 영화에 평점을 남기셨습니다. 중복 평가는 불가능합니다." << std::endl;
        return; // 평가를 막고 메인 메뉴로 돌려보냄
    }
    std::cout << "점수 입력 (0.0 - 10.0): ";
    std::cin >> score;
    std::cin.ignore(100, '\n'); // 버퍼 정리


    Rating newRating(user->getID(), movie->getID(), score);
    ratingMgr.addRating(newRating);
    movie->addRating(score); // 영화의 평점 업데이트
    std::cout << "평점이 추가되었습니다. 업데이트된 평점 : " << movie->getAverageRating() << std::endl;
}
// 9. 영화별 평점 보기
void MenuController::handleDisplayRatingsByMovie() {
    if(movieMgr.isEmpty()) {
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }

    std::string movieTitle;
    std::cout << "평점을 볼 영화 제목: ";
    std::getline(std::cin, movieTitle);

    Movie* movie = movieMgr.findExactTitle(movieTitle); 

    if (movie != nullptr) {
        ratingMgr.displaybyMovie(movie->getID(), movie->getTitle(), userMgr);
    } else {
        std::cout << "일치하는 영화가 목록에 없습니다." << std::endl;
    }
}
// 10. 영화 추천
void MenuController::handleRecommendation() {
    std:: string userName;
    std::cout << "추천을 받을 사용자 이름: ";
    std::getline(std::cin, userName);

    User* user = userMgr.findbyName(userName);
    if (user == nullptr) {
        std::cout << "일치하는 사용자가 목록에 없습니다." << std::endl;
        return; // 일치하는 사용자가 없으면 종료
    }
    std::cout << "사용자들의 평가를 분석 중... "<< std::endl;
    std::vector<Movie*> recommendations = recommender.recommendMovies(user->getID(), 4); // 상위 4명과 유사한 사용자들의 평점을 분석하여 최대 6개의 영화 추천
    if(recommendations.empty()) {
        std::cout << "평가 데이터가 없거나 추천할 영화가 없습니다." << std::endl;
    } 
    else {
        std::cout << "====== 추천 영화 목록 ======\n";
        for (const auto& m : recommendations) {
            std::cout << *m << std::endl;
        }
    }
}