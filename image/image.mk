ifneq ($(TOOLS_MK),1)
TOOLS_MK=1
ifeq ($(OS),Windows_NT)
RM=del
CP=copy
else
RM=rm -f
CP=cp
endif
CC=gcc
CFLAGS += -Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O2
endif
export RM CP CC
endif
IMAGE_MK=1
ifeq ($(OS),Windows_NT)
CFLAGS += -I$(CURDIR)/include -L$(CURDIR)/lib
endif
ifeq ($(PAMPREFIX),1)
CFLAGS += -DPAMPREFIX
endif
export IMAGE_MK CFLAGS
