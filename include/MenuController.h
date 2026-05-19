// 메뉴 컨트롤러 클래스, 메인 비중을 낮추기 위해 설계
#pragma once
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

class MenuController {
    private:
        MovieManager& movieMgr;
        UserManager& userMgr;
        RatingManager& ratingMgr;
        Recommender& recommender;
    public:
        MenuController(MovieManager& movieMgr, UserManager& userMgr, RatingManager& ratingMgr, Recommender& recommender);
        void handleAddMovie();
        void handleSearchMovie();
        void handlePrintMovies();
        void handleSortMovie();
        void handleAddUser();
        void handlePrintUsers();
        void handleDisplayRatingsByUser();
        void handleAddRating();
        void handleDisplayRatingsByMovie();
        void handleRecommendation();
};