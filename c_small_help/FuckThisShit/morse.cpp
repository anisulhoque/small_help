#include "morse.h"

struct node {
    char data;
    char value;
    char length;
    struct node* head;
    struct node* tail;
};

struct node* newNode(struct node* head, char data, char value, char length) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->value = value;
    node->length = length;
    node->head = head;
    return (node);
}

struct node* make(struct node* head, const char* data, const char* value, const char* length) {
    if (strlen(data) > 0) {
        struct node* node = newNode(head, data[0], value[0], length[0]);
        head->tail = node;
        head = make(node, &data[1], &value[1], &length[1]);
    }
    return head;
}

struct node* list() {
    char data[] = "+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char value[] = { 10,2,0,21,18,31,15,7,3,1,0,16,24,28,30,21,56,8,17,5,12,26,1,8,10,4,0,2,6,0,0,7,5,4,3,2,7,6,13,2,0,1,1,1,3,9,11,12 };
    char length[] = { 5,5,8,6,5,5,5,5,5,5,5,5,5,5,5,5,9,5,5,6,6,6,2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4 };

    struct node* head = newNode(0, data[0], value[0], length[0]);
    struct node* tail = make(head, &data[1], &value[1], &length[1]);
    head->head = tail;
    tail->tail = head;
    return head;
}

char* valToBin(char value, char length) {
    char* buff = (char*)malloc(sizeof(char) * length);
    buff[length] = 0;

    for (char i = length - 1; i >= 0; i--) {
        buff[i] = value % 2 + '0';
        value /= 2;
    }

    return buff;
}

char binToVal(const char* bin) {
    char val = 0;

    for (char i = 0; i < strlen(bin); i++) {
        val = val << 1;
        val += bin[i] - '0';
    }
    return val;
}

char format(char c) {
    if (c > 42 && c < 91) {
        return c;
    }
    else if (c > 96 && c < 122) {
        return c - 'a' + 'A';
    }
    else {
        return ' ';
    }
}

void (*cPtr) (const char*, char);
void stream(char* buff, char valIndex, char codec) {
    char* stream = (char*)malloc(sizeof(char) * valIndex);
    memcpy(stream, buff, valIndex);
    stream[valIndex] = 0;
    if (cPtr != 0) {
        (*cPtr)(stream, codec);
    }
}

struct node* morse;
void encode(const char* data) {
    char* buff = (char*)malloc(sizeof(char) * 256);
    char valIndex = 0;
    while (strlen(data) != 0) {
        char c = format(data[0]);
        // Streaming
        if (c == ' ') {
            buff[valIndex++] = '/';
            buff[valIndex++] = ' ';
            stream(buff, valIndex, ENCODE);
            valIndex = 0;
        }
        else {
            while (morse->data != c) {
                morse = morse->tail;
            }
            char* temp = valToBin(morse->value, morse->length);
            while (strlen(temp) != 0) {
                buff[valIndex++] = *temp++;
            }
            buff[valIndex++] = ' ';
        }
        data++;
    }
    stream(buff, valIndex, ENCODE);
    free(buff);
}

void code(char* buff, char buffIndex) {
    buff[buffIndex] = 0;
    char c = binToVal(buff);
    for (;;) {
        if (morse->value == c && morse->length == buffIndex) {
            stream(&morse->data, 1, DECODE);
            free(buff);
            break;
        }
        morse = morse->tail;
    }
}

void decode(const char* data) {
    char* buff = (char*)malloc(sizeof(char) * 16);
    char buffIndex = 0;
    while (strlen(data) != 0) {
        if (data[0] == ' ' && buffIndex > 0) {
            code(buff, buffIndex);
            buff = (char*)malloc(sizeof(char) * 16);
            buffIndex = 0;
        }
        else if (data[0] == '/') {
            char c = ' ';
            stream(&c, 1, DECODE);
        }
        else if (data[0] == '0' || data[0] == '1'){
            buff[buffIndex++] = data[0];
        }
        data++;
    }
    code(buff, buffIndex);
}

void (*fPtr[2]) (const char* data) = { decode, encode };
void input(const char* data, void output(const char*, char), char codec) {
    if (strlen(data) == 0) {
        return;
    }
    if (output == 0) {
        return;
    }
    if ((codec | ENCODE) != ENCODE) {
        return;
    }
    if (morse == 0) {
        morse = list();
    }
    if (cPtr == 0) {
        cPtr = output;
    }
    fPtr[codec](data);
}

/*
    short mark, dot or "dit" (0): 1
    longer mark, dash or "dah" (1): 111
    intra-character gap (between the dots and dashes within a character): 0
    short gap (between letters): 000
    medium gap (between words): 0000000
*/
