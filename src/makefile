make:
	make clean
	make kernel.bin

## 由于现在实现的是OS，所以g++编译针对有OS的情况下做的东西都必须去掉。所以在这里使用了很多options。
GPPFLAGS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore

%.o: %.cpp
	g++ $(GPPFLAGS) -o $@ -c $<


ASFLAGS = --32
%.o: %.s
	as $(ASFLAGS) -o $@ $<


OBJS = kernel.o loader.o gdt.o
LDFLAGS = -melf_i386 -nostdlib
kernel.bin: linker.ld $(OBJS)
	ld $(LDFLAGS) -T $< -o $@ $(OBJS)

.PHONY: clean

clean:
	rm -f *.o *.bin *.exe

SOURCE_FILES = kernel.cpp linker.ld loader.s makefile types.h gdt.h gdt.cpp test.cpp io.h
send: 
	scp -r $(SOURCE_FILES) root@49.235.226.43:/root/demoOS/src/

get:
	scp root@49.235.226.43:/root/demoOS/src/kernel.bin ../bin

run:
	qemu-system-i386 -kernel ../bin/kernel.bin &