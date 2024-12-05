TARGET := main
CC := gcc
C_FLAGS := -Wall
BUILD_DIR := build

VPATH := src # Makes it possible to add just main.c instead of src/main,c to SRC
VPATH += build # Makes it possible to add just main.c instead of src/main,c to SRC
INCLUDE := -Iinc # Adds dir "inc" to include paths


# Can be done like this if wants to list manually every source file
SRC := main.c
SRC += frame.c
SRC += frame_vector.c
SRC += vector.c
SRC += priority.c

# Or like this to get all .c files from src dir
#SRC := $(shell find src -name *.c)

# In the contents of SRC, take everything that has the pattern %.c and return it changed for %.o
OBJ := $(SRC:%.c=%.o)
BUILD_OBJ := $(OBJ:%.o=$(BUILD_DIR)/%.o)

# Makes "main" executable from the compiled .o files
# Depends on build dir to create it if it does not exist
$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(BUILD_OBJ) -o $(BUILD_DIR)/$(TARGET)

# Makes each .o file from the .c file
$(OBJ): %.o: %.c
	$(CC) $(C_FLAGS) $(INCLUDE) -c $^ -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)