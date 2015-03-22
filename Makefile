################################################################################################################
#
#				通用Makefile模板
#
#################################################################################################################
PROJECT_TOP_DIR=$(shell cd ./; pwd)
PROJECT_BIN_DIR=$(PROJECT_TOP_DIR)/bin
PROJECT_SRC_DIR=$(PROJECT_TOP_DIR)/src
PROJECT_INC_DIR=$(PROJECT_TOP_DIR)/inc
PROJECT_LIB_DIR=$(PROJECT_TOP_DIR)/lib
PROJECT_OBJ_DIR=$(PROJECT_TOP_DIR)/obj
MKDIR := mkdir -p

CC := gcc
TARGETS = netdisk

PUB_INC_DIR	= /usr/include
PUB_LIB_DIR	= /usr/lib

SKYEYE_INC	= -I$(PUB_INC_DIR) 		
SKYEYE_LIB	= -L$(PUB_LIB_DIR)		

CFLAGS := -I$(PROJECT_INC_DIR) $(SKYEYE_INC) 
LDFLAG := -L$(PROJECT_LIB_DIR) $(SKYEYE_LIB) -lpthread -lcurl -lpolarssl

src :=$(wildcard $(PROJECT_SRC_DIR)/*.c)
dir := $(notdir $(src))
PROJECT_OBJ := $(patsubst %.c,%.o,$(dir) )
	
PROJECT_ALL_OBJS := $(addprefix $(PROJECT_OBJ_DIR)/, $(PROJECT_OBJ))
	
all:$(PROJECT_SRC_DIR) $(PROJECT_ALL_OBJS)
	$(CC) $(CFLAGS) $(PROJECT_ALL_OBJS) -o $(PROJECT_BIN_DIR)/$(TARGETS) $(LDFLAG)
	
$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -fr $(PROJECT_OBJ_DIR)/*
	rm -fr $(PROJECT_BIN_DIR)/$(TARGETS)	
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(MKDIR) $(PROJECT_LIB_DIR)