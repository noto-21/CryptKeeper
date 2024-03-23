CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = CryptKeeper.cpp
TARGET = ck

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
