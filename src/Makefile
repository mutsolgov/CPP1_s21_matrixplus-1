CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

SRC = s21_matrix_oop.cpp
HDR = s21_matrix_oop.h
TEST = test_s21_matrix.cpp

LIB = s21_matrix_oop.a

TEST_EXE = test_matrix

all: $(LIB) $(TEST_EXE)

$(LIB): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -c $(SRC)
	ar rcs $(LIB) s21_matrix_oop.o

$(TEST_EXE): $(TEST) $(LIB) $(HDR)
	$(CXX) $(CXXFLAGS) -I/path/to/googletest/include -pthread $(TEST) $(LIB) -L/path/to/googletest/lib -lgtest -lgtest_main -o $(TEST_EXE)

test: $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f *.o $(LIB) $(TEST_EXE)
