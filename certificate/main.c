/* fseek example */
#include <stdio.h>
#include <stdlib.h>

typedef struct FileBuffer
{
    unsigned char *buffer;
    int size;
    int curPos;

} FileBuffer;

FileBuffer readByteFile(char *filename)
{
    FILE *pFile;
    pFile = fopen(filename, "rb");
    fseek(pFile, 0, SEEK_END);
    long fsize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fsize);
    fread(buffer, fsize, 1, pFile);
    fclose(pFile);

    FileBuffer fileBuffer = {};
    fileBuffer.buffer = buffer;
    fileBuffer.curPos = 0;
    fileBuffer.size = fsize;

    return fileBuffer;
}
int main()
{
    FileBuffer fileBuffer = readByteFile("cert.der");

    for (int i = 0; i < fileBuffer.size; i++)
        printf("%u ", fileBuffer.buffer[i]);

    return 0;
}
