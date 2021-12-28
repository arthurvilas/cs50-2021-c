#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL) {
        printf("Could not open raw image.\n");
        return 1;
    }

    int filenum = 0;
    char filename[8];
    bool file_being_written = false;
    FILE *img;

    uint8_t buffer[BLOCKSIZE];
    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, raw)) {

        // Start of JPEG header
        if (
        buffer[0] == 0xff && 
        buffer[1] == 0xd8 && 
        buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            
            if (file_being_written) {
                fclose(img);
            }

            filenum++;
            sprintf(filename, "%03i.jpg", filenum);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, img);
            file_being_written = true;

        } else if (file_being_written) {
            fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, img);
        }
    }
}