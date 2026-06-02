#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "RatingManager.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "Recommender.h"
#include "MenuController.h"
#include <iostream>

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
        Movie* movie = movieMgr.findbyId(rating->getMovieID());
        if (movie != nullptr) {
            movie->addRating(rating->getScore());
        }
    }

    MenuController controller(movieMgr, userMgr, ratingMgr, recommender);

    while(true) {
        std::cout << "==== Movie Recommender System ==== \n\n" 
                << "[ 영화 ]\n" <<  " 1. 영화 추가 \n" << " 2. 제목으로 검색 \n" 
                << " 3. 전체 목록 출력 \n" << " 4. 평점순 정렬 출력 \n\n"
                << "[ 사용자 ]\n" << " 5. 사용자 추가 \n" << " 6. 사용자 목록 출력 \n" << " 7. 사용자 별 평점 출력 \n\n"
                << "[ 평점 ] \n" << " 8. 평점 입력 \n" << " 9. 영화별 평점 출력 \n\n"
                << "[ 추천 ] \n" << " 10. 영화 추천 \n\n"  
                << " 0. 종료 \n\n" << " 선택 > "; 
        std::cin >> choice;

        if (std::cin.fail()) { // 숫자가 아닌 입력이 들어왔을 때 예외처리
            std::cin.clear();            
            std::cin.ignore(100, '\n');  // 입력 버퍼에 남아있는 쓰레기 값을 지움
            std::cout << "\n 잘못된 입력입니다! 0에서 10 사이의 숫자만 입력해주세요.\n" << std::endl;
            
            continue; 
        }
        std::cin.ignore(100, '\n'); // 버퍼의 개행 문자 제거

        if(choice == 0) {
            std::cout << "데이터 저장 후 프로그램을 종료합니다." << std::endl;
            break;
        }
        switch(choice) {
            case 1: controller.handleAddMovie(); break;
            // 영화 제거 기능은 오류를 방지하기 위해 제거
            case 2: controller.handleSearchMovie(); break;
            case 3: controller.handlePrintMovies(); break;
            case 4: controller.handleSortMovie(); break;
            case 5: controller.handleAddUser(); break;
            case 6: controller.handlePrintUsers(); break;
            case 7: controller.handleDisplayRatingsByUser(); break;
            case 8: controller.handleAddRating(); break;
            case 9: controller.handleDisplayRatingsByMovie(); break;
            case 10: controller.handleRecommendation(); break;
            default: std::cout << "잘못된 선택입니다. 다시 시도해주세요." << std::endl; continue; // 잘못된 입력은 메뉴로 돌아가기
        }
        // 기능을 수행한 후 메뉴로 돌아가기 전
    std::cout << "작업 완료. [엔터를 누르시면 메뉴로 돌아갑니다]";

    // 사용자가 새롭게 엔터를 칠 때까지 화면을 멈춤
    std::cin.get();   
    }
    ratingMgr.sortbyID(); // 프로그램 종료 전 평점 목록을 userID 기준으로 정렬하여 저장
    // 영화와 사용자 목록은 입력 받는 순서대로 ID가 부여되므로 별도의 정렬 없이 저장해도 정렬됨 
    // 프로그램 종료 시 파일에 데이터 저장
    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    return 0;
}
