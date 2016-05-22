#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stack_s stack_t;

typedef
    void
    (*stack_emp_fn)
    (void * receiver, stack_t * sender);

typedef
    void
    (*stack_full_fn)
    (void * receiver, stack_t * sender, int val);

typedef
    void
    (*stack_empNfull_fn)
    (void * receiver);

stack_t * stack_new(void);
void stack_free(stack_t * self);

int stack_getCount(stack_t * self);
void stack_print(stack_t * self);
void stack_push(stack_t * self, int val);
int stack_pop(stack_t * self);
void stack_subscribeEmp(stack_t * self, void * receiver, stack_emp_fn callback);
void stack_subscribeFull(stack_t * self, void * receiver, stack_full_fn callback);
void stack_subscribeEmpNFull(stack_t * self, void * receiver, stack_empNfull_fn callback);
stack_emp_fn stack_getEmpFn(stack_t * self);
stack_full_fn stack_getFullFn(stack_t * self);
int stack_isFull(stack_t * self);
int stack_isEmpty(stack_t * self);

#endif // STACK_H_INCLUDED
