#pragma once


class BaseManager {
    public:
        virtual ~BaseManager() {} // 소멸자

        // 순수 가상함수를 통해 각 Movie, User, Rating 매니저 클래스에 공통적으로 필요한 인터페이스 정의
        virtual void printAll() const = 0;
        virtual bool isEmpty() const = 0;
        // 파일 입출력
        virtual void loadFromFile(const std::string& filename) = 0;
        virtual void saveToFile(const std::string& filename) const = 0;
        
};