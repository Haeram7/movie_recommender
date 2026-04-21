# 1. 컴파일러 및 컴파일 옵션 설정
CXX = g++
# -g 옵션(디버깅)과 c++17, 그리고 include 폴더 경로를 추가했습니다.
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

# 2. 디렉토리 설정
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# 3. 실행 파일 이름
TARGET = movie_app

# 4. 소스 및 오브젝트 파일 자동 감지
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 5. 기본 빌드 타겟
all: $(TARGET)

# 6. 실행 파일 링킹 규칙
$(TARGET): $(OBJS)
	@echo "링크 중: $^"
	$(CXX) $(CXXFLAGS) -o $@ $^

# 7. 개별 오브젝트 파일 컴파일 규칙
# $<: 현재 컴파일되는 소스 파일, $@: 생성되는 오브젝트 파일
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "컴파일 중: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 8. 정리 규칙
clean:
	@echo "정리 중..."
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# 9. 실행 규칙
run: $(TARGET)
	@echo "실행 중: $(TARGET)"
	./$(TARGET)

# 파일 이름과 타겟 이름의 충돌을 방지
.PHONY: all clean run