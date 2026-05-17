#pragma once
#include "Movie.h"
#include "BaseManager.h"
#include <vector>

class MovieManager : public BaseManager{
private: 
    std::vector<Movie> movies;
public:
    MovieManager();

    void printAll() const override;
    bool isEmpty() const override;
    int size() const override;
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;

    void addMovie(const Movie& m);
    void removeMovie(const std::string &title);
    void sortbyRating();
    std::vector<Movie> findbyTitle(const std::string& title) const;
    Movie* findExactTitle(const std::string &title);
    Movie* findbyId(int id);
};