#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue2.h"

typedef struct q_item *q_item;

struct q_item {
    int item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

queue queue_new(){
    queue q = emalloc(sizeof *q);
    q->length = 0;
    q->first = NULL;
    q->last = NULL;
    return q;
}

void enqueue(queue q, int item){

    q_item insert = emalloc(sizeof *insert);
    q_item walk;
    insert->item = item;
    if(q->first == NULL){
        q->first = insert;
        q->last = insert;
        q->length++;
    } else {
        for(walk = q->first; walk->next != NULL; walk = walk->next){}
        walk->next = insert;
        q->last = walk->next;
        q->length++;
    }
}

int dequeue(queue q){
    q_item remove = q->first;
    int temp;
    if(q->first != NULL){
        temp = q->first->item;
        if (q->first->next != NULL){
            q->first = q->first->next;
        } else {
            q->first = NULL;
        }
    }
    free(remove);
    q->length--;
    return temp;
}

void queue_print(queue q){
    q_item walk;
    if(q->first == NULL){
        return;
    }
    for(walk = q->first; walk != NULL; walk = walk->next){
        printf("[%d]", walk->item);
    }
    printf("\n");
}

int queue_size(queue q){
    return q->length;
}

queue queue_free(queue q){
    q_item walk, remove;
    if(q->first == NULL){
        free(q);
        return NULL;
    }else{
        for(walk = q->first; walk != NULL; free(remove)){
            remove = walk;
            walk = walk->next;
        }
        free(walk);
        free(q);
        return NULL;
    }
}