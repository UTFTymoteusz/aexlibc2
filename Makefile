CC = x86_64-pc-aex2-gcc
LD = ld
AS = nasm

ARCH ?= x86_64

MKDIR = mkdir -p

BIN      := /tmp/aex2/libc/
DEP_DEST := $(BIN)dep/
OBJ_DEST := $(BIN)obj/

CFILES   := $(shell find . -type f -name '*.c'  -not -path './arch/*') $(shell find './arch/$(ARCH)/.' -type f -name '*.c')
HFILES   := $(shell find . -type f -name '*.h'  -not -path './arch/*') $(shell find './arch/$(ARCH)/.' -type f -name '*.h')
ASMFILES := $(shell find . -type f -name '*.asm')
OBJS     := $(patsubst %.o, $(OBJ_DEST)%.o, $(CFILES:.c=.c.o) $(ASMFILES:.asm=.asm.o))

GFLAGS = -O3 -Wall -Wextra -nostdlib -pipe

INCLUDES := -I. -Iinclude/ -Iarch/$(ARCH)/ -Iarch/$(ARCH)/include/

CCFLAGS := $(GFLAGS)		\
	-ffreestanding			\
	-masm=intel				\
	-fno-stack-protector	\
	-fno-omit-frame-pointer \
	$(INCLUDES)

ASFLAGS := -felf64

LDFLAGS := $(GFLAGS)		\
	-ffreestanding			\
	-z max-page-size=0x1000 \
	-no-pie

format:
	@$(MKDIR) $(BIN)
	clang-format -style=file -i ${CFILES} ${HFILES}

all: $(OBJS)
	@printf '\033[0;93mlibc\033[0m: Building \033[0;93mcrt0.asm\033[0m\033[0K\r'
	@$(AS) $(ASFLAGS) -o $(OBJ_DEST)crt0.o crt0.asm

	@printf '\033[0;93mlibc\033[0m: Building \033[0;93mcrti.asm\033[0m\033[0K\r'
	@$(AS) $(ASFLAGS) -o $(OBJ_DEST)crti.o crti.asm

	@printf '\033[0;93mlibc\033[0m: Building \033[0;93mcrtn.asm\033[0m\033[0K\r'
	@$(AS) $(ASFLAGS) -o $(OBJ_DEST)crtn.o crtn.asm

	@$(MKDIR) $(BIN)
	ar r $(OBJ_DEST)libc.a ${OBJS}

	@printf '\033[0;93mlibc\033[0m: Done building\033[0K\n'

include $(shell find $(DEP_DEST) -type f -name *.d)

copy:
	@cp -u $(OBJ_DEST)libc.a "$(COPY_DIR)"

clean:
	rm -rf $(BIN)

$(OBJ_DEST)%.c.o : %.c
	@$(MKDIR) ${@D}
	@$(MKDIR) $(dir $(DEP_DEST)$*)

	@printf '\033[0;93mlibc\033[0m: Building \033[0;93m$(<)\033[0m\033[0K\r'
	@$(CC) $(CCFLAGS) -c $< -o $@ -MMD -MT $@ -MF $(DEP_DEST)$*.c.d

$(OBJ_DEST)%.asm.o : %.asm
	@$(MKDIR) ${@D}

	@printf '\033[0;93mlibc\033[0m: Building \033[0;93m$(<)\033[0m\033[0K\r'
	@$(AS) $(ASFLAGS) $< -o $@

install:
	-chmod a+x ./install.sh

	./install.sh
