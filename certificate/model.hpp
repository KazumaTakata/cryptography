#ifndef HMODEL
#define HMODEL

#include <stdlib.h>

typedef struct stringBuffer
{
    unsigned char *buffer;
    int size;
    int curPos;

} stringBuffer;

typedef struct RawData
{
    unsigned char *buffer;
    int size;
} RawData;

RawData *generageRawData(unsigned char *buffer, int size)
{
    RawData *rawdata = new RawData;
    unsigned char *copy = (unsigned char *)malloc(size * sizeof(unsigned char));
    for (int i = 0; i < size; i++)
    {
        copy[i] = buffer[i];
    }

    rawdata->buffer = copy;
    rawdata->size = size;

    return rawdata;
}

typedef struct Node
{
    bool contructed;
    int length;
    unsigned char tag;
    RawData *value;
    Node *children;
    Node *next;
} Node;

#endif
