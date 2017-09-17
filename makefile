export CXX := clang++-5.0
export CXXFLAGS := --std=c++1z

all: server_test client_test
.PHONY: clean

server_test: server_test.cpp server.hpp
	${CXX} ${CXXFLAGS} server_test.cpp -o $@ -lpthread

client_test: client_test.cpp client.hpp
	${CXX} ${CXXFLAGS} client_test.cpp -o $@

clean: server_test client_test
	rm $^
