#include <stdio.h>
#include <string.h> // for memcmp function
#define SECTOR_SIZE 512
#define BOOT_SIGNATURE "\x55\xAA"
#define ASM_JMP '\xEB'
int main(int argc, char *argv[]) {

	char mbr[SECTOR_SIZE];

	if (argc != 3) {
		printf("Usage: '%s device filetowrite'\n", argv[0]);
		return 1;
	}

    FILE * fd;
    printf("%s device file pointer is at %lx \n",argv[1],argv[2]);
	fd = fopen(argv[1], "r");
	if (fd == NULL) {
		printf("Could not open %s for read \n", argv[1]);
		return 1;
	}

	fread(&mbr, SECTOR_SIZE, 1, fd);

	// check the bype number 510,511 of the first 512 bytes of sector 0

	if (memcmp(&mbr[510], BOOT_SIGNATURE, 2) && memcmp(&mbr[511], BOOT_SIGNATURE, 2)) {
		printf("Could not find MBR boot signature\n");
		fclose(fd);
		return 1;
	}
    printf("we found the boot signature bytes at the 510,511 blocks on the sector 0 \n");
    // check the first instruction at the MBR equal to opcode ASM_JMP
	if (mbr[0] != ASM_JMP){
	printf("no bootloader code detected \n");
	fclose(fd);
	return 1;
	}
	FILE * fd2;
    fd2 = fopen(argv[2], "w+");
    if (fd == NULL) {
		printf("Could not open %s for write \n", argv[2]);
		return 1;
	}
    fwrite(&mbr,SECTOR_SIZE,1,fd2);
    printf("Done dumping the MBR \n");
	}
