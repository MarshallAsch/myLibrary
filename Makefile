BUILD_DIR = out/
LIB_DIR = lib/
INCLUDE_DIR = .


# lists of .c files
MY_LIB_SRC = mystring.c myinput.c
MY_STRUCT_LIB_SRC = ArrayList.c queue.c


TEST_SRC = testing.c

# lists of .o files
MY_LIB_OBJ = $(addprefix $(BUILD_DIR), $(patsubst %.c, %.o, $(MY_LIB_SRC)))
MY_STRUCT_LIB_OBJ = $(addprefix $(BUILD_DIR), $(patsubst %.c, %.o, $(MY_STRUCT_LIB_SRC)))

TEST_OBJ = $(addprefix $(BUILD_DIR), $(patsubst %.c, %.o, $(TEST_SRC)))


# my list of libraries
LIBRARIES = $(LIB_DIR)libmylib.a $(LIB_DIR)libmystruct.a

# list of all the excecutables to build


LIBS = -L$(LIB_DIR) -lmylib -lmystruct
CC = gcc
CFLAG =  -c -Werror -Wall -Wextra -pedantic -ansi -g  -I$(INCLUDE_DIR) -fPIC -O2
LFLAG =  $(LIBS)



all:  test $(LIBRARIES)
	./test


#**********************************
#
#	BUILDING CODE FOR DB
#
#**********************************

test: $(TEST_OBJ)  $(LIBRARIES)
	$(CC) $(TEST_OBJ) -o $@ $(LFLAG)


#**********************************
#
#
#	BUILDING LIBRARIES
#
#
#**********************************


$(LIB_DIR)libmylib.a: $(MY_LIB_OBJ) | $(LIB_DIR)
	ar cr $@ $(MY_LIB_OBJ)

$(LIB_DIR)libmystruct.a: $(MY_STRUCT_LIB_OBJ) | $(LIB_DIR)
	ar cr $@ $(MY_STRUCT_LIB_OBJ)



#**********************************
#
#
#
#		OTHER STUFF
#
#
#**********************************


#generic build a C file with a header file
$(BUILD_DIR)%.o: %.c %.h  | $(BUILD_DIR)
	$(CC) $(CFLAG) $< -o $@

#generic build a C file with no header file
$(BUILD_DIR)%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAG) $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(LIB_DIR):
	mkdir $(LIB_DIR)

.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r $(LIB_DIR)
