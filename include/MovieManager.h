#pragma once
#include "Movie.h"
#include <vector>

class MovieManager {
private: 
    std::vector<Movie> movies;
public:
    MovieManager();

    void addMovie(const Movie& m);
    void removeMovie(const std::string &title);
    void printAll() const;
    void sortbyRating();
    Movie* findbyTitle(const std::string& title) const;
}