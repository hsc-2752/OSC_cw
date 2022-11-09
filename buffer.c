#include <stdio.h> 
#include <stdlib.h> 
  

struct Buffer { 
    struct process *head, * tail; 
}; 
  

struct Buffer* newBuffer() 
{ 
    struct Buffer* b = (struct Buffer*)malloc(sizeof(struct Buffer)); 
    b -> head = NULL;
    b -> tail = NULL; 
    return b; 
} 
  

void add(struct Buffer* b, struct process* p) 
{ 
   
    if (b -> head == NULL) { 
        b -> head = p;
        b -> tail = p; 
    } 
    else{
        b -> tail -> next = p; 
        b -> tail = p; 
    }
} 
  
//since in the producer-consuemr problem we do not allow removal from empty buffer,
//we do not consider empty linked list here(need to free)
struct process* remove(struct Buffer* b) 
{ 
    struct process* temp = b -> head; 
    b-> head = b -> head -> next; 
    return temp; 
} 

