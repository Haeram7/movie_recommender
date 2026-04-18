#include "UserManager.h"

UserManager::UserManager() {};
void UserManager::addUser(const User &u) {
    for(const auto &user : users) {
        if(u.getName() == user.getName() && u.getID() == user.getID()) {
            std::cout << "같은 사용자가 이미 존재합니다. : " << user.getName() << std::endl;
            return; // 중복된 사용자 이름은 추가하지 않음
        }
    }
    users.push_back(u);
}

void UserManager::removeUser(const std::string &name) {
    users.erase(std::remove_if(users.begin(), users.end(),
        [&name](const User& u) { return u.getName() == name; }),
        users.end());
    // 람다 함수를 통하여 조건에 맞는 요소들(이름이 일치하는 사용자)을 뒤로 밀어버리고 모두 제거
}

std::vector<User> UserManager::findbyName(const std::string &name) const {
    std::vector<User> results;
    for(const auto &u : users){
        if(u.getName() == name){
            results.push_back(u);
        }
    }
    return results; // 일치하는 사용자가 없는 경우 빈 벡터 반환
}
void::UserManager::sortbyName() {
    std::sort(users.begin(), users.end());
    // User 클래스의 operator < 연산자 오버로딩을 이용하여 ID 기준 오름차순 정렬
}

void printAll() const {
    for (const auto &u : users){
        std::cout << u << std::endl; // User 클래스의 operator << 오버로딩을 이용하여 사용자 정보 출력
 }
}