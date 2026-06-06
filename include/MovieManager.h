#pragma once
#include "Movie.h"
#include "BaseManager.h"
#include <vector>
#include <memory>
#include <cctype>

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
    Movie* findExactTitle(const std::string &title) const;
    Movie* findbyId(int id);
    void resetAllMovieRatings(); 
    std::string toLowerString(std::string str) const;
};