/*
 * Exercise 4-4. Add the commands to print the top elements of the stack without
 * popping, to duplicate it, and to swap the top two elements. Add a command
 * to clear the stack.
 */
#include <stdio.h>
#include <assert.h>

void   stack_push(double);
double stack_pop(void);
double stack_top(void);
void   stack_duplicate_top_elem(void);
void   stack_swap_top_elem(void);
void   stack_clear(void);

int main(void)
{
	stack_push(20.0);
	stack_push(12);
	stack_push(23.5);

	assert(23.5 == stack_top());
	assert(23.5 == stack_pop());
	assert(12 == stack_top());

	stack_duplicate_top_elem();

	assert(12 == stack_pop());
	assert(12 == stack_top());

	stack_swap_top_elem();

	assert(20 == stack_pop());
	assert(12 == stack_top());

	stack_push(1);
	stack_push(1);
	stack_push(1);
	stack_push(1);

	stack_clear();

	assert(0.0 == stack_top());
	return 0;
}

#define MAXELEM 20

double stack[MAXELEM];
int sp = 0;

#define STACK_IS_FULL (sp == MAXELEM)
#define STACK_IS_EMPTY (sp == 0)

#define eputs(err_msg) (fprintf(stderr, err_msg "\n"))

void stack_push(double val)
{
	if (STACK_IS_FULL)
		eputs("error: stack is full");
	else
		stack[sp++] = val;
}

double stack_top(void)
{
	if (STACK_IS_EMPTY)
	{
		eputs("error: stack is empty");
		return 0.0;
	}
	return stack[sp - 1];
}

double stack_pop(void)
{
	if (STACK_IS_EMPTY)
	{
		eputs("error: stack is empty");
		return 0.0;
	}
	return stack[--sp];
}

void stack_duplicate_top_elem(void)
{
	stack_push(stack_top());
}

void stack_swap_top_elem(void)
{
	if (sp < 2)
		eputs("error: insuficient elements");
	else
	{
		double temp = stack[sp - 1];
		stack[sp - 1] = stack[sp - 2];
		stack[sp - 2] = temp;
	}
}

void stack_clear(void)
{
	sp = 0;
}
