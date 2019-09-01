#ifndef HFILE
#define HFILE

#include "model.hpp"
#include <stdlib.h>
#include <stdio.h>

stringBuffer readByteFile(char *filename)
{
    FILE *pFile;
    pFile = fopen(filename, "rb");
    fseek(pFile, 0, SEEK_END);
    long fsize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fsize);
    fread(buffer, fsize, 1, pFile);
    fclose(pFile);

    stringBuffer stringbuffer = {};
    stringbuffer.buffer = buffer;
    stringbuffer.curPos = 0;
    stringbuffer.size = fsize;

    return stringbuffer;
}

#endif