# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread

# Paths
SRC_DIR = src
OBJ_DIR = obj
DATA_DIR = data

# Source Files
SOURCES = $(SRC_DIR)/user/User.cpp \
          $(SRC_DIR)/question/Question.cpp \
          $(SRC_DIR)/answer/Answer.cpp \
          $(SRC_DIR)/sentimentAnalyzer/SentimentAnalyzer.cpp \
          $(SRC_DIR)/search/SearchEngine.cpp \
          $(SRC_DIR)/threadManager/ThreadManager.cpp \
          $(SRC_DIR)/databaseManager/DatabaseManager.cpp \
          $(SRC_DIR)/utility/Utility.cpp

# Object Files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Server-specific object files
SERVER_OBJECTS = $(OBJ_DIR)/server.o $(OBJECTS)

# Client-specific object files - ADD SentimentAnalyzer.o HERE
CLIENT_OBJECTS = $(OBJ_DIR)/client.o $(OBJ_DIR)/user/User.o $(OBJ_DIR)/sentimentAnalyzer/SentimentAnalyzer.o

# Targets
all: server client

# Compile all .cpp files into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Ensure obj directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Server target (linking only necessary files)
server: $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o server $(SERVER_OBJECTS)

# Client target (linking only necessary files)
client: $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o client $(CLIENT_OBJECTS)

# Clean up
clean:
	rm -rf $(OBJ_DIR) server client