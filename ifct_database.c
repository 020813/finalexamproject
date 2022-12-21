#include <stdio.h>
#include <stdlib.h>

#include "ifct_database.h"

#define LIST_END -1


typedef struct node{
	int index;
	void* obj;
	void* next;
	void* prev;
} node_t;


static node_t* list_database = NULL;
static node_t* listPtr = NULL;
static int list_cnt = 0;



static node_t* genNode(void)
{
	
	node_t* ndPtr = (node_t*)malloc(sizeof(node_t));
	if (ndPtr != NULL)
	{
		ndPtr->next = NULL;
		ndPtr->obj = NULL;
		ndPtr->prev = NULL;
	}
	
	return ndPtr;
}

static node_t* ifctList(int index)
{
	node_t* ndPtr = list_database;
	if (listPtr != NULL && listPtr->index <= index)
	{
		ndPtr = listPtr;
	}
	
	
	if (index <-1)
	{
		printf("[ERROR] ifctList() : either list is null or index is wrong! (offset : %i)\n", index);
        return NULL;
	}
	if (index >= list_cnt)
    {
        printf("[ERROR] ifctList() : index is larger than length (len:%i, index:%i)\n", list_cnt, index);
        return NULL;
    }
    
    
    while (ndPtr != NULL)
    {
        if (ndPtr->index == index)
            break;
        ndPtr = ndPtr->next;
    }
    
    return ndPtr;
}


{
    int index=0;
    node_t* ndPtr = list_database;
    
    while ( ndPtr != NULL )
    {
        ndPtr->index = index++;
        ndPtr = ndPtr->next; 
    }
    
    return index;
}



int ifctdb_addTail(void* obj)
{
    node_t* ndPtr;
    node_t* newNdPtr;
    
    
    if (obj == NULL)
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : input object indicates NULL!\n");
        return -1;
    }
    
    
    newNdPtr = genNode();
    if (newNdPtr == NULL)
    {
        printf("[ERROR] ifsdb_addTail() : Failed to do addTail : Failed to create a node\n");
        return -1; 
    }
    newNdPtr->obj = obj;
    
    
    if (list_database == NULL)
    {
        list_database = newNdPtr;
        newNdPtr->index = 0;
    }
    else
    {
        ndPtr = ifctList(list_cnt-1);
        ndPtr->next = newNdPtr;
        newNdPtr->prev = ndPtr;
        newNdPtr->index = ndPtr->index+1;
    }
    
    listPtr = newNdPtr;
    
    list_cnt++;
    
    return 0;
}



int ifctdb_deleteData(int index)
{
    node_t* ndPrevPtr;
    node_t* ndNextPtr;
    node_t* delNdPtr;
    
   
    if ( (delNdPtr = ifctList(index)) == NULL)
    {
        printf("[ERROR] ifctdb_deleteData() : Failed to do deleteData : input index is invalid (%i)!\n", index);
        return -1;
    }
    
    ndPrevPtr = delNdPtr->prev;
    if (ndPrevPtr != NULL)
    {
        ndPrevPtr->next = delNdPtr->next;
    }
    ndNextPtr = delNdPtr->next;
    if (ndNextPtr != NULL)
    {
        ndNextPtr->prev = delNdPtr->prev;
    }
    
    free(delNdPtr->obj);
    free(delNdPtr);
    
    list_cnt--;
    
    if (list_cnt == 0)
    {
        list_database = NULL;
    }
    else
    {
        updateIndex();
    }
    
    return 0;
}


int ifctdb_len(void)
{
    return list_cnt;
}



void* ifctdb_getData(int index)
{
    void* obj = NULL;
    node_t* ndPtr;
    
   
    if ((ndPtr = ifctList(index)) != NULL)
    {
        obj = (void*)ndPtr->obj;
        listPtr = ndPtr;
    }
    
    if (obj == NULL)
        printf("[ERROR] ifctdb_len() : there is no data of index %i\n", index);
    
    return obj;
}
