#include "UserManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

UserManager::UserManager() {};

void UserManager::printAll() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return; // 출력 후 바로 함수 종료
    }
    for (const auto &u : users){
        std::cout << u << std::endl; // User 클래스의 operator << 오버로딩을 이용하여 사용자 정보 출력
 }
}

bool UserManager::isEmpty() const {
    return users.empty(); // 사용자 목록이 비어있는지 여부 반환
}

int UserManager::size() const {
    return users.size(); // 사용자 목록의 크기 반환
}

void UserManager::loadFromFile(const std::string& filename)  {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // 헤더 스킵
    while(getline(file, line)) {
        if (line.empty()) continue; // 빈 줄 방어
        std::stringstream ss(line);
        std::string token;
        int id;
        std::string name, email;

        try {
            getline(ss, token, ','); id = stoi(token);
            getline(ss, token, ','); name = token;
            getline(ss, token); email = token;
            users.emplace_back(id, name, email);
        }
        catch(...) {
            continue; // 형식 오류는 건너뜀
        }
    }
    User::setNextID(users.size() + 1); // 다음 ID는 현재 사용자 수 + 1
    file.close();
}
void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }
    file << "id,name,email" << std::endl;
    for(const auto &u : users) {
        file << u.getID() << "," << u.getName() << "," << u.getEmail() << std::endl;
    }
    file.close();
}

void UserManager::addUser(const User &u) {
    for(const auto &user : users) {
        if(u.getName() == user.getName()) {
            std::cout << "같은 사용자가 이미 존재합니다 : " << user.getName() << std::endl;
            return; // 중복된 사용자 이름은 추가하지 않음
        }
    }
    users.push_back(u);
}

User* UserManager::findbyName(const std::string &name) {
    for(auto &u : users){
        if(u.getName() == name){
            return &u; // 일치하는 사용자가 있으면 해당 사용자 객체의 포인터를 반환
        }
    }
    return nullptr; // 일치하는 사용자가 없는 경우 nullptr 반환
}
void UserManager::sortbyName() {
    std::sort(users.begin(), users.end());
    // User 클래스의 operator < 연산자 오버로딩을 이용하여 이름 기준 오름차순 정렬
}



const User* UserManager::findbyId(int id) const {
    for (const auto &u : users) {
        if (u.getID() == id) {
            return &u; // const User* 타입을 반환하게 됩니다.
        }
    }
    return nullptr;
}