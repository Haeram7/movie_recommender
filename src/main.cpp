#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "RatingManager.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "Recommender.h"
#include <iostream>

// 1. 영화 추가
void handleAddMovie(MovieManager& movieMgr) {
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
// 2. 영화 제거
void handleRemoveMovie(MovieManager& movieMgr) {
    std::string title;
    std::cout << "삭제할 영화 제목: ";
    std::getline(std::cin, title);
    movieMgr.removeMovie(title);
}
// 3. 제목으로 검색
void handleSearchMovie(const MovieManager& movieMgr) {
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
// 4. 전체 목록 출력
void handlePrintMovies(const MovieManager& movieMgr) {
    if(movieMgr.isEmpty()) {
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::cout << " ===== 영화 목록 =====\n";
    movieMgr.printAll();
}
// 5. 평점순 정렬 출력
void handleSortMovies(MovieManager& movieMgr) {
    if(movieMgr.isEmpty()) {
        std::cout << "영화 목록이 비어 있습니다." << std::endl;
        return;
    }
    movieMgr.sortbyRating();
    std::cout << "영화가 평점순으로 정렬되었습니다." << std::endl;
    handlePrintMovies(movieMgr);
}
// 6. 사용자 추가
void handleAddUser(UserManager& userMgr) {
    std::string name, email;
    std::cout << "사용자 이름: ";
    std::getline(std::cin, name);
    std::cout << "이메일: ";
    std::getline(std::cin, email);

    User newUser(name, email);
    userMgr.addUser(newUser);
}
// 7. 사용자 목록 출력
void handlePrintUsers(const UserManager& userMgr) {
    if(userMgr.isEmpty()) {
        std::cout << "사용자 목록이 비어 있습니다." << std::endl;
        return;
    }
    std::cout << " ===== 사용자 목록 =====\n";
    userMgr.printAll();
}
// 8. 평점 입력
void handleAddRating(RatingManager& ratingMgr, UserManager& userMgr, MovieManager& movieMgr) {
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
void handleDisplayRatingsByMovie(RatingManager& ratingMgr, MovieManager& movieMgr, UserManager& userMgr) {
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
void handleRecommendation(Recommender& recommender) {
    std:: string userName;
    std::cout << "추천을 받을 사용자 이름: ";
    std::getline(std::cin, userName);

    User* user = recommender.getUserManager().findbyName(userName);
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

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;
    Recommender recommender(movieMgr, ratingMgr, userMgr);
    int choice = -1;

    // 프로그램 시작 시 파일에서 데이터 로드
    std::cout << "데이터를 불러오는 중..." << std::endl;
    movieMgr.loadFromFile("data/movies.csv");
    userMgr.loadFromFile("data/users.csv");
    ratingMgr.loadFromFile("data/ratings.csv");
    std::cout << "데이터 로드 완료!" << std::endl;

    // csv 파일에서 영화와 평점 데이터를 불러온 후 각 영화 객체의 평점을 초기화(중복 방지)
    // 평점 데이터를 기반으로 영화의 총 평점과 평가 수를 업데이트
    movieMgr.resetAllMovieRatings();
    for (const auto& rating : ratingMgr.getAllRatings()) {
        Movie* movie = movieMgr.findbyId(rating.getMovieID());
        if (movie != nullptr) {
            movie->addRating(rating.getScore());
        }
    }

    while(true) {
        std::cout << "==== Movie Recommender System ==== \n\n" 
                << "[ 영화 ]\n" <<  " 1. 영화 추가 \n" << " 2. 영화 제거 \n" << " 3. 제목으로 검색 \n" 
                << " 4. 전체 목록 출력 \n" << " 5. 평점순 정렬 출력 \n\n"
                << "[ 사용자 ]\n" << " 6. 사용자 추가 \n" << " 7. 사용자 목록 출력 \n\n"
                << "[ 평점 ] \n" << " 8. 평점 입력 \n" << " 9. 영화별 평점 보기 \n\n"
                << "[ 추천 ] \n" << " 10. 영화 추천 \n\n"  
                << " 0. 종료 \n\n" << " 선택 > "; 
        std::cin >> choice;

        if (std::cin.fail()) { // 숫자가 아닌 입력이 들어왔을 때 예외처리
            std::cin.clear();            // 버퍼 제거
            std::cin.ignore(100, '\n');  // 입력 버퍼에 남아있는 쓰레기 문자들('a' 등)을 지움
            std::cout << "\n 잘못된 입력입니다! 0에서 10 사이의 숫자만 입력해주세요.\n" << std::endl;
            
            continue; 
        }
        std::cin.ignore(100, '\n'); // 버퍼의 개행 문자 제거

        if(choice == 0) {
            std::cout << "데이터 저장 후 프로그램을 종료합니다." << std::endl;
            break;
        }
        switch(choice) {
            case 1: handleAddMovie(movieMgr); break;
            case 2: handleRemoveMovie(movieMgr); break;
            case 3: handleSearchMovie(movieMgr); break;
            case 4: handlePrintMovies(movieMgr); break;
            case 5: handleSortMovies(movieMgr); break;
            case 6: handleAddUser(userMgr); break;
            case 7: handlePrintUsers(userMgr); break;
            case 8: handleAddRating(ratingMgr, userMgr, movieMgr); break;
            case 9: handleDisplayRatingsByMovie(ratingMgr, movieMgr, userMgr); break;
            case 10: handleRecommendation(recommender); break;
            default: std::cout << "잘못된 선택입니다. 다시 시도해주세요." << std::endl; continue; // 잘못된 입력은 메뉴로 돌아가기
        }
        // 기능을 수행한 후 메뉴로 돌아가기 전
    std::cout << "\n작업 완료. [엔터를 누르시면 메뉴로 돌아갑니다]";

    // 사용자가 새롭게 엔터를 칠 때까지 화면을 멈춤
    std::cin.get();   
    }
    
    // 프로그램 종료 시 파일에 데이터 저장
    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    return 0;
}
    
