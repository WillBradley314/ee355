CXX = g++-13

CXXFLAGS = -g -std=c++17 -Wall

TARGET = test_network

SRCS = test_network.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
