#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct stack_s {
    int array[10];
    int count;
    list_t * event_fullNempty;
    event_t * event_empty;
    event_t * event_full;
};

stack_t * stack_new(void) {
    stack_t * s =malloc(sizeof(struct stack_s));
    s->count = 0;
    s->event_fullNempty = list_new();
    s->event_empty = NULL;
    s->event_full=NULL;
    return s;
}

void stack_free(stack_t * self) {
    int count = list_getCount(self->event_fullNempty);
    int i;
    for (i = 0; i < count; i++) {
        event_t * ev = list_pop_back(self->event_fullNempty);
        free(ev);
    }
    list_free(self->event_fullNempty);
    free(self);
}

int stack_getCount(stack_t * self) {
    return self->count;
}

void stack_push(stack_t * self, int val) {
    if(stack_isFull(self)){
        if ((NULL != self->event_full)
        && (NULL != self->event_full->callback)) {
        stack_full_fn fn = (stack_full_fn)self->event_full->callback;
        fn(self->event_full->receiver, self, val);
    }
    return;
    }
    self->array[self->count] = val;
    self->count++;
}

int stack_pop(stack_t * self) {
    int val = self->array[self->count - 1];
    self->count--;
    if(stack_isEmpty(self)){
        if ((NULL != self->event_empty)
        && (NULL != self->event_empty->callback)) {
        stack_emp_fn fn = (stack_emp_fn)self->event_empty->callback;
        fn(self->event_empty->receiver, self);
    }
    }
    return val;
}

void stack_subscribeEmp(stack_t * self, void * receiver, stack_emp_fn callback) {
    self->event_empty = malloc(sizeof(struct event_s));
    self->event_empty->receiver = receiver;
    self->event_empty->callback = callback;
}

void stack_subscribeFull(stack_t * self, void * receiver, stack_full_fn callback) {
    self->event_full = malloc(sizeof(struct event_s));
    self->event_full->receiver = receiver;
    self->event_full->callback = callback;
}

void stack_subscribeEmpNFull(stack_t * self, void * receiver, stack_empNfull_fn callback) {
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = callback;
    list_push_back(self->event_fullNempty, sb);
}

static void stack_empty(void* receiver, stack_t * sender){
    stack_t * self=(stack_t *)receiver;
    if(stack_isEmpty(self)){
        int count = list_getCount(self->event_fullNempty);
    int i;
    for (i = 0; i < count; i++) {
        event_t * ev = list_getEl(self->event_fullNempty, i);
        if (NULL != ev->callback) {
            stack_empNfull_fn fn = ev->callback;
            fn(ev->receiver);
        }
    }
        stack_free(self);
        stack_free(sender);
        exit(0);
    }
    int val=stack_pop(self);
    stack_push(sender, val);
    return;
}

stack_emp_fn stack_getEmpFn(stack_t * self){
    return &stack_empty;
}

static void stack_full(void* receiver, stack_t * sender, int val){
    stack_t * self=(stack_t *)receiver;
    if(stack_isFull(self)){
        int count = list_getCount(self->event_fullNempty);
    int i;
    for (i = 0; i < count; i++) {
        event_t * ev = list_getEl(self->event_fullNempty, i);
        if (NULL != ev->callback) {
            stack_empNfull_fn fn = ev->callback;
            fn(ev->receiver);
        }
    }
        stack_free(self);
        stack_free(sender);
        exit(0);
    }
    stack_push(self, val);
    return;
}

stack_full_fn stack_getFullFn(stack_t * self){
    return &stack_full;
}

void stack_print(stack_t * self){
    int i;
    for(i=0;i<self->count;i++){
            printf("%3i", self->array[i]);
    }
}

int stack_isFull(stack_t * self){
    if (self->count==10){
        return 1;
    }
    else return 0;
}

int stack_isEmpty(stack_t * self){
    if (self->count==0){
        return 1;
    }
    else return 0;
}
