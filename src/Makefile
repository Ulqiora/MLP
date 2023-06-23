CC=g++
BD=../build/
TEST_FILES_SOURCE= Dataset.cpp ActivateFunction.cpp MNN.cpp Matrix.cpp GNN.cpp Layer.cpp Neuron.cpp tests.cpp 
TEST_FILES_OBJ=$(addprefix $(BD),$(TEST_FILES_SOURCE:.cpp=.o))
PROJECT_FILES_SOURCE=ActivateFunction.cpp Dataset.cpp Matrix.cpp MNN.cpp GNN.cpp Layer.cpp Neuron.cpp main.cpp
PROJECT_FILES_OBJ=$(addprefix $(BD),$(PROJECT_FILES_SOURCE:.cpp=.o))
CFLAGS=-c# -Wall -Wextra -Werror
LDFLAGS=#-Wall -Wextra -Werror
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest -I./ -L./
APP_INSTALL=$(HOME)/Applications/MLP/
APP=$(BD)NerualNetworkMLP.app

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lsubunit -lrt -lm
endif

all: install

./$(BD)%.o:	%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o:	*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: */*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: */*/*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: */*/*/*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)tests_file: $(TEST_FILES_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(GTESTFLAGS)

build:
	cp NerualNetworkMLP.pro $(BD)
	cd $(BD) && qmake NerualNetworkMLP.pro
	make -C $(BD)

install: build
	mkdir $(APP_INSTALL) 2>/dev/null
	cp -rf $(APP) $(APP_INSTALL)
	open $(APP_INSTALL)

uninstall: clean
	rm -rf $(APP_INSTALL)

tests: ./$(BD)tests_file
	./$(BD)tests_file 

research: $(PROJECT_FILES_OBJ)
	$(CC) $(LDFLAGS) $^ -o $(BD)$@ -lpthread -lsubunit -lrt -lm
	./$(BD)research

dvi:
	open ./Documentation/info.html

dist: 
	tar -cvf $(APP_INSTALL)MLP.tar $(APP_INSTALL)
	open $(APP_INSTALL)

clean: 
	rm -rf $(BD)*
	rm -rf $(BD).qmake.stash

cpplint:
	cp -f ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp ./NerualNetworkMLP/Controller/* ./NerualNetworkMLP/Model/*.* ./NerualNetworkMLP/Model/GNN/* ./NerualNetworkMLP/Model/MNN/* ./NerualNetworkMLP/View/*.cpp ./NerualNetworkMLP/View/*.h ./NerualNetworkMLP/CustomWidget/*.cpp ./NerualNetworkMLP/CustomWidget/*.h
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --suppress=unusedFunction --suppress=missingInclude --suppress=exceptRethrowCopy NerualNetworkMLP/*/*.cpp *.h

leaks:
	CK_FORK=no leaks --atExit -- $(BD)tests_file
