CC ?= gcc
LD = ld
AS = nasm

MKDIR = mkdir -p

BIN      := bin/
DEP_DEST := $(BIN)dep/
OBJ_DEST := $(BIN)obj/

ARCH = arch/x64/

CFILES   := $(shell find . -type f -name '*.c'  -not -path './arch/*') $(shell find './$(ARCH).' -type f -name '*.c')
HFILES   := $(shell find . -type f -name '*.h'  -not -path './arch/*') $(shell find './$(ARCH).' -type f -name '*.h')
ASMFILES := $(shell find . -type f -name '*.asm')
OBJS     := $(patsubst %.o, $(OBJ_DEST)%.o, $(CFILES:.c=.c.o) $(ASMFILES:.asm=.asm.o))

GFLAGS = -O3 -Wall -Wextra -nostdlib -pipe

INCLUDES := -I. -Iinclude/

CCFLAGS := $(GFLAGS)		\
	-ffreestanding			\
	-masm=intel				\
	-mcmodel=kernel			\
	-fno-pic				\
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
	$(AS) $(ASFLAGS) -o crt0.o crt0.asm
	$(AS) $(ASFLAGS) -o crti.o crti.asm
	$(AS) $(ASFLAGS) -o crtn.o crtn.asm

	@$(MKDIR) $(BIN)
	ar r libc.a ${OBJS}

include $(shell find $(DEP_DEST) -type f -name *.d)

clean:
	rm -rf $(BIN)

$(OBJ_DEST)%.c.o : %.c
	@$(MKDIR) ${@D}
	@$(MKDIR) $(dir $(DEP_DEST)$*)
	$(CC) $(CCFLAGS) -c $< -o $@ -MMD -MT $@ -MF $(DEP_DEST)$*.c.d

$(OBJ_DEST)%.asm.o : %.asm
	@$(MKDIR) ${@D}
	$(AS) $(ASFLAGS) $< -o $@

install:
	./install.sh
