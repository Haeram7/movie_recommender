#pragma once
#include "Movie.h"
#include "BaseManager.h"
#include <vector>
#include <memory>

class MovieManager : public BaseManager{
private: 
    std::vector<std::unique_ptr<Movie>> movies;
public:
    MovieManager();

    void printAll() const override;
    bool isEmpty() const override;
    int size() const override;
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;

    void addMovie(const Movie& m);
    void sortbyRating();
    std::vector<Movie*> findbyTitle(const std::string& title) const;
    const std::vector<std::unique_ptr<Movie>>& getAllMovies() const;
    Movie* findExactTitle(const std::string &title);
    Movie* findbyId(int id);
    void resetAllMovieRatings(); // 모든 영화의 평점 초기화 메서드 추가
};