# 1. 컴파일러 및 컴파일 옵션 설정
CXX = g++
# -g (디버깅), include 폴더 경로 추가
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

# 2. 디렉토리 설정
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# 3. 파일 설정
TARGET = movie_app
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 4. 기본 빌드 타겟
all: $(TARGET)

# 5. 실행 파일 링크 규칙
$(TARGET): $(OBJS)
	@echo "링크 중: $^"
	$(CXX) $(CXXFLAGS) -o $@ $^

# 6. 객체 파일 컴파일 규칙
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "컴파일 중: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 7. 정리
clean:
	@echo "정리 중..."
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# 8. 실행
run: $(TARGET)
	@echo "실행 중: $(TARGET)"
	./$(TARGET)

# 파일 이름과 타겟 이름의 충돌을 방지
.PHONY: all clean run