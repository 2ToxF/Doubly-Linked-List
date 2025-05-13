CC 			:= g++
FLAGS 		:= -Wall -Wextra -Wpedantic -fpermissive -O2

SRC_DIR 	:= source
INC_DIR 	:= include
OBJ_DIR 	:= object
LOG_DIR 	:= logs

SOURCES 	:= $(wildcard $(SRC_DIR)/*.cpp)
INCLUDES 	:= $(wildcard $(INC_DIR)/*.h)
OBJECTS 	:= $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DOCS_NAME := Docs_config

all: $(OBJECTS) | $(OBJ_DIR) $(LOG_DIR)

$(OBJ_DIR):
	@mkdir $@

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDES)
	@$(CC) -c $(FLAGS) -I$(INC_DIR) $< -o $@

$(LOG_DIR):
	@mkdir $@

run: $(EXE) $(LOG_DIR)
	@$(EXE)

docs:
	doxygen $(DOCS_NAME)

clean: clean_obj clean_logs

clean_obj: $(OBJ_DIR)
	rm $(OBJ_DIR)/*.o

clean_logs: $(LOG_DIR)
	rm $(LOG_DIR)/*
