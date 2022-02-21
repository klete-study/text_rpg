#pragma once

typedef void* void_pointer;

struct listnode {
	void_pointer data;
	listnode* next;
	listnode* prev;
};

struct list
{
	listnode* head;
	listnode* tail;
	int size;
};

list* create_list();

void_pointer searchNode(list* src, int index);

void pushBack(list* src, void_pointer element);

bool insert_node(list* src, void_pointer element, int index);

bool delete_node(list* src, int index);

void releaseList(list* src);