gcc -MD -fno-builtin -nostdinc -fno-stack-protector -D_KERN_ -Ikern -Ikern/kern -I. -m32 -O0 -c -o entry.o entry.S
ld -o kernel -nostdlib -e start -m elf_i386 -Ttext=0x00100000 entry.o -b binary