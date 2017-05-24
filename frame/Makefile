DIR_INC = ./
DIR_SRC = ./
DIR_OBJ = ./
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = frame

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g3  -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ)  -o $@
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
	
.PHONY:clean
clean:
	rm -rf *.o
#find ${DIR_OBJ} -name *.o -exec rm -rf {}