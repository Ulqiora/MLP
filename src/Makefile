CC=g++
BD=../build/
TEST_FILES_SOURCE=Dataset.cpp tests.cpp 
TEST_FILES_OBJ=$(addprefix $(BD),$(TEST_FILES_SOURCE:.cpp=.o))
CFLAGS=-c# -Wall -Wextra -Werror
LDFLAGS=#-Wall -Wextra -Werror
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest -I./ -L./

./$(BD)%.o: */*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)tests_file: $(TEST_FILES_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(GTESTFLAGS)
tests: ./$(BD)tests_file
	./$(BD)tests_file