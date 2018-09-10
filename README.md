# mbr-dumper
program to dump the 512 bytes mbr code from the first sector of the disk to a file , let you examine the assembly code of the bootloader

## Compile
`gcc -o mbrdumper mbrdumper.c`

## run
`./mbrdumper /dev/sda pathtodumpfile`
