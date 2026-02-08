#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_CAP 16

#define shift(count, args) \
    do {                   \
        *count -= 1;       \
        *args += 1;        \
    } while (0)

int numbers[STACK_CAP];
int stack_count = 0;

void push(int number)
{
    numbers[stack_count++] = number;
}

int pop()
{
    return numbers[--stack_count];
}

void print_stack()
{
    printf("[ ");
    size_t i = 0;
    for (; i < stack_count-1; ++i) {
        printf("%d, ", numbers[i]);
    }
    printf("%d ]\n", numbers[i]);
}

void parse_input(char ***buf, int *count)
{
    int number = 0;
    int rhs = 0;
    int lhs = 0;

    while (*count > 0) {
        switch (***buf) {
        case '+': {
            rhs = pop();
            lhs = pop();
            push(lhs + rhs);
        } break;
        case '-': {
            rhs = pop();
            lhs = pop();
            push(lhs - rhs);
        } break;
        case '*': {
            rhs = pop();
            lhs = pop();
            push(lhs * rhs);
        } break;
        case '/': {
            rhs = pop();
            lhs = pop();
            assert(rhs != 0 && "Division by zero!");
            push(lhs / rhs);
        } break;
        default: {
            while (***buf) {
                number = number * 10 + ***buf - '0';
                **buf += 1;
            }
            push(number);
            number = 0;
        } break;
        }
        shift(count, buf);
    }
}

void help()
{
    printf("[ERROR] No argument is provided!\n");
    printf("[USAGE] ./main <n> <n> <+,-,*,/> ...\n");
    printf("        * (star sign) must be escaped when run on terminal\n");
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        help();
        return 1;
    }

    shift(&argc, &argv);

    parse_input(&argv, &argc);
    print_stack();
    
    return 0;
}
