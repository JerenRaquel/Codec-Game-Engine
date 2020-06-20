SFML_FILE_PATH := "/mnt/c/Program Files (x86)/SFML 2.5.1"

GXX := g++ -g -Wall -Werror

HEADER_DIR := Engine/lib
SOURCE_DIR := Engine/src

HEADER_FILES := $(shell find $(HEADER_DIR) -name '*.hpp')
SOURCE_FILES := $(shell find $(SOURCE_DIR) -name '*.cpp')
ENGINE := Engine/Engine.hpp
MAIN_FILE := main.cpp
OUTPUT_FILE := Game

Create: $(MAIN_FILE) $(HEADER_FILES) $(SOURCE_FILES)
	$(GXX) -c $(MAIN_FILE) -o CompiledFile.o
	$(GXX) $(SOURCE_FILES) CompiledFile.o -o $(OUTPUT_FILE) -lsfml-graphics -lsfml-window -lsfml-system
	rm CompiledFile.o

Clean: Create
	rm $(OUTPUT_FILE)