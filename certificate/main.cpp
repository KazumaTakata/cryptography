#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "model.hpp"
#include "file.hpp"

using namespace std;
Node *Parser(stringBuffer stringbuffer);
Node *ParseElement(stringBuffer stringbuffer);

Node *ParseElement(stringBuffer *stringbuffer)
{

    Node *newnode = new Node;

    newnode->tag = stringbuffer->buffer[stringbuffer->curPos];

    unsigned char length = stringbuffer->buffer[stringbuffer->curPos + 1];
    int accutualLength = length;
    int dataIndex = 0;
    if (length & 1 << 7)
    {
        int end = (length - (1 << 7));
        dataIndex = end;
        for (int i = 0; i < end; i++)
        {
            accutualLength = stringbuffer->buffer[stringbuffer->curPos + 2 + i] * pow(256, (end - i));
        };
    }

    // constructed tag
    if (newnode->tag & 1 << 5)
    {
        newnode->contructed = true;
        newnode->length = accutualLength;
        stringBuffer newStringbuffer = {};
        newStringbuffer.size = accutualLength;
        newStringbuffer.curPos = 0;
        newStringbuffer.buffer = &stringbuffer->buffer[stringbuffer->curPos + dataIndex];
        Node *childNode = Parser(newStringbuffer);
        newnode->children = childNode;
    }
    else
    {
        newnode->contructed = false;
        newnode->length = accutualLength;
        newnode->value = generageRawData(stringbuffer->buffer, accutualLength);
    }

    stringbuffer->curPos += accutualLength;

    return newnode;
}

Node *Parse(stringBuffer stringbuffer)
{
    Node *rootNode;
    Node *youngestNode = NULL;
    bool root = true;

    while (stringbuffer.size > stringbuffer.curPos)
    {
        Node *newnode = ParseElement(stringbuffer);

        if (youngestNode != NULL)
        {
            youngestNode->next = newnode;
            youngestNode = newnode;
        }

        if (root)
        {
            rootNode = newnode;
            youngestNode = newnode;
            root = false;
        }
    }

    return rootNode;
}

int main()
{
    stringBuffer stringbuffer = readByteFile("cert.der");

    for (int i = 0; i < stringbuffer.size; i++)
        printf("%u ", stringbuffer.buffer[i]);

    return 0;
}
