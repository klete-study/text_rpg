#pragma once

typedef void* void_pointer;

struct stack {
    void_pointer* data;
    int stack_size;
};

stack* create();

void push(stack* src, void_pointer element);

void pop(stack* src);

void_pointer stack_top(stack* src);

void_pointer search(stack* src, int index);

bool is_empty(stack* src);

void releaseStack(stack* src);