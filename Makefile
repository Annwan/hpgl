### programs
CC=i686-w64-mingw32-gcc
RM=rm -rf

### flags
__FLAGS=-march=i386 -std=c99 -Wall -Werror
ifdef RELEASE
CCFLAGS=$(__FLAGS) -O2
else
CCFLAGS=$(__FLAGS) -Og -g -DDEBUG
# DEBUG is a preproc macro used my the `log' module
endif
COMPFLAG=-c
OUT=-o

### libs
LIBS=

### sources
SRC=$(patsubst %,src/%.c,main graphics hpglparse hpglrun log)
OBJ=$(patsubst src/%.c,build/%.o,$(SRC))

### executable name
EXEC=build/main.exe

### "command" targets
.PHONY: build run clean mrproper
build: $(EXEC)
run: build
	wine $(EXEC)
clean:
	$(RM) $(OBJ)
mrproper: clean
	$(RM) $(EXEC)

### compiling target
$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $^ $(LIBS) $(OUT) $@

build/%.o: src/%.c
	$(CC) $(CCFLAGS) $(COMPFLAG) $< $(OUT) $@

build/main.o build/graphics.o build/hpglparse.o build/log.o: src/log.h
build/main.o build/graphics.o: src/graphics.h
build/hpglparse.o build/hpglrun.o: src/hpglparse.h
build/hpglrun.o: src/hpglrun.h

