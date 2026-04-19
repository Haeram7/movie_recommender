#pragma once
#include <iostream>
class Rating {
    private:
        int userID, movieID;
        double score;
    public:
        Rating();
        Rating(int ui, int mi, double s);
        int getUserID() const;
        int getMovieID() const;
        double getScore() const;
        void display() const;
        bool operator <(const Rating& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Rating& r);
};