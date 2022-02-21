#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list* create_list()
{
    list* src;

    src = (list*)malloc(sizeof(list));
    src->head = NULL;
    src->tail = NULL;
    src->size = 0;

    return src;
}

void pushBack(list* src, void_pointer element)
{
    listnode* add_node = (listnode*)malloc(sizeof(listnode));

    add_node->data = element;

    if (src->head == NULL) {
        src->head = add_node;
        src->tail = add_node;
        src->head->prev = NULL;
        src->head->next = NULL;
    }
    else {
        add_node->prev = src->tail;
        add_node->next = NULL;
        src->tail->next = add_node;
        src->tail = add_node;
    }

    ++src->size;
}

bool insert_node(list* src, void_pointer element, int index)
{
    if (src->size <= index) {
        printf("해당하는 index에 node가 없습니다");
        return false;
    }

    listnode* add_node = (listnode*)malloc(sizeof(listnode));

    add_node->data = element;

    if (index == 0) {
        add_node->next = src->head;
        add_node->prev = NULL;
        src->head->prev = add_node;
        src->head = add_node;

        ++src->size;

        return true;
    }

    else if (index == src->size - 1) {
        add_node->prev = src->tail;
        add_node->next = NULL;
        src->tail->next = add_node;
        src->tail = add_node;

        ++src->size;

        return true;
    }

    listnode* temp = src->head;

    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }

    add_node->next = temp;
    add_node->prev = temp->prev;
    temp->prev = add_node;
    temp = add_node;

    ++src->size;
    return true;
}

bool delete_node(list* src, int index)
{
    if (src->size <= index || src->head == NULL) {
        printf("유효한 index가 아니거나, 리스트가 생성되지 않았습니다");
        return false;
    }

    if (index == 0) {
        src->head = src->head->next;
        src->head->prev = NULL;

        return true;
    }

    else if (index == src->size - 1) {
        src->tail = src->tail->prev;
        src->tail->next = NULL;

        return true;
    }

    listnode* temp = src->head;

    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }

    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;

    free(temp);
    return true;
}

void_pointer searchNode(list* src, int index)
{
    listnode* temp = src->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    void_pointer data = temp->data;

    return data;
}

void releaseList(list* src)
{
    listnode* temp = src->head;
    listnode* next_temp = temp->next;

    if (src->head == NULL) {
        printf("리스트가 생성되지 않았습니다");
    }

    while (true) {
        free(temp->data);
        free(temp);
        temp = next_temp;
        if (temp == NULL) {
            break;
        }
        next_temp = next_temp->next;
    }

    free(src);
}