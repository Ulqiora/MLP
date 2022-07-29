CC=g++
BD=../build/
TEST_FILES_SOURCE=Dataset.cpp tests.cpp 
TEST_FILES_OBJ=$(addprefix $(BD),$(TEST_FILES_SOURCE:.cpp=.o))
PROJECT_FILES_SOURCE=ActivateFunction.cpp Dataset.cpp Matrix.cpp MNN.cpp GNN.cpp Layer.cpp Neuron.cpp main.cpp
PROJECT_FILES_OBJ=$(addprefix $(BD),$(PROJECT_FILES_SOURCE:.cpp=.o))
CFLAGS=-c# -Wall -Wextra -Werror
LDFLAGS=#-Wall -Wextra -Werror
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest -I./ -L./

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lsubunit -lrt -lm
endif

./$(BD)%.o: */*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: */*/*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o:	*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o:	%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)tests_file: $(TEST_FILES_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(GTESTFLAGS)

tests: ./$(BD)tests_file
	./$(BD)tests_file 

research: $(PROJECT_FILES_OBJ)
	$(CC) $(LDFLAGS) $^ -o $(BD)$@ -lpthread -lsubunit -lrt -lm
	./$(BD)research

clean: 
	rm -f $(BD)*