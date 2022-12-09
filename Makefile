CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX_FLAGS_OPTIMIZED=-std=c++20 -O3 -Wall -Wextra -Werror -pedantic $(INCLUDES)
SRC_INPUTS=src/graph.cpp
TEST_INPUTS=tests/tests.cpp src/graph.cpp
INCLUDES_INPUTS=includes/graph.h tests/tests.hpp
INPUTS=$(SRC_INPUTS) $(INCLUDES_INPUTS)

exec: bin/exec
exec-opt: bin/exec-opt
test: bin/test

bin/exec: src/main.cpp $(INPUTS)
	${CXX} ${CXX_FLAGS} src/main.cpp ${SRC_INPUTS} -o $@

bin/exec-opt: src/main.cpp $(INPUTS)
	${CXX} ${CXX_FLAGS_OPTIMIZED} src/main.cpp ${SRC_INPUTS} -o $@

bin/test: tests/tests.cpp obj/catch.o $(INPUTS)
	${CXX} ${CXX_FLAGS} tests/tests.cpp obj/catch.o ${SRC_INPUTS} -o $@

obj/catch.o: tests/catch.cpp tests/catch.hpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec exec-opt test

clean:
	rm -fr bin/* obj/*