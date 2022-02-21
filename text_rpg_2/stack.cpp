#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <math.h>
#include "stack.h"

stack* create()
{
    stack* src = (stack*)malloc(sizeof(stack));
    src->stack_size = 0;
    src->data = (void_pointer*)malloc(sizeof(void_pointer));
    return src;
}

void push(stack* src, void_pointer element)
{
    void_pointer* temp = (void_pointer*)realloc(src->data, sizeof(void_pointer) * (src->stack_size + 1));

    memcpy(temp + src->stack_size, element, sizeof(void_pointer));

    if (src->data != NULL) {
        src->data = NULL;
    }
    src->data = temp;
    src->stack_size++;
}

void pop(stack* src)
{
    bool data_empty = is_empty(src);
    if (data_empty == true) {
        printf("스택에 데이터가 없습니다");
        exit(0);
    }
    else {
        free(src->data[src->stack_size - 1]);
        --src->stack_size;
    }
}

void_pointer stack_top(stack* src)
{
    bool data_empty = is_empty(src);
    if (data_empty == true) {
        printf("스택에 데이터가 없습니다");
        exit(0);
    }

    return src->data[src->stack_size - 1];
}

void_pointer search(stack* src, int index)
{
    if (src->stack_size <= index) {
        printf("스택에 데이터가 없습니다");
        exit(0);
    }
    return src->data[index];
}

bool is_empty(stack* src)
{
    if (src->stack_size == 0) {
        return true;
    }
    else {
        return false;
    }
}

void releaseStack(stack* src)
{
    if (src->data == NULL) {
        return;
    }
    for (int i = 0; i < src->stack_size; ++i) {
        free(src->data[i]);
    }
    free(src->data);
    free(src);
}