# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# 파일 설정
TARGET = movie_app
SRCS = main.cpp Movie.cpp User.cpp Rating.cpp
OBJS = main.o Movie.o User.o Rating.o	

# 기본 타겟
all: $(TARGET)

# 링크: 모든 .o 파일을 연결하여 실행 파일 생성
$(TARGET): $(OBJS)
	@echo "링크 중: $^"
	$(CXX) $(CXXFLAGS) -o $@ $^

# 패턴 규칙
%.o : %.cpp
	@echo "컴파일 중: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

#헤더 의존성 / 각 .o 파일이 해당하는 .h 파일에 의존하도록 설정
main.o: Movie.h User.h Rating.h
Movie.o: Movie.h
User.o: User.h
Rating.o: Rating.h

# 정리
clean:
	@echo "정리 중..."
	rm -f $(TARGET) $(OBJS)
# 실행
run : $(TARGET)
	@echo "실행 중: $<"
	./$(TARGET)
#.PHONY: 파일이 아닌 타겟 명시
.PHONY: all clean run