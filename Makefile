
CXX := g++
AR := ar

CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude -MMD -MP

SOURCES := \
	src/pet/pet.cpp \
	src/search/search.cpp \
	src/search/favorites.cpp \
	src/matchmaker/matchmaker.cpp

OBJECTS := $(SOURCES:.cpp=.o)
DEPS := $(OBJECTS:.o=.d)

TARGET := libmaria.a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
