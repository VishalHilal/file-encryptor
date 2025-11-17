CXX = g++ 
CXXFLAGS = -std=c++17 -g -Wall -I. -Istc/app/encrypt_decrypt -Isrc/app/file_handling -Isrc/app/processes

MAIN_TARGET = encrypt_decrypt 
CRYPTION_TARGET = cryption

MAIN_SRC = main.cpp \
		   src/app/processes/ProcessManagement.cpp \
		   src/app/file_handling/IO.cpp \
		   src/app/file_handling/ReadEnv.cpp \
		   src/app/encrypt_decrypt/Cryption.cpp

CRYPTION_SRC = src/app/encrypt_decrypt/CryptionMain.cpp \
			   src/app/encrrypt_decrypt/Cryption.cpp \
			   src/app/file_handling/IO.cpp \
			   src/app/file_handling/ReadEnv.cpp

MAIN_OBJ = $ (MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $ (CRYPTION_SRC:.cpp=.o)

all: $ (MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) _c $< -o $@

clean:
	rm -rf &(MAIN_OBJ) $(CRYPTON_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET)


.PHONY:clean all



















		
