#include "UserManager.h"
#include <iostream>
#include <algorithm>

UserManager::UserManager() {};
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

void UserManager::printAll() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return; // 출력 후 바로 함수 종료
    }
    for (const auto &u : users){
        std::cout << u << std::endl; // User 클래스의 operator << 오버로딩을 이용하여 사용자 정보 출력
 }
}