/*
------------------------------------------------------------
Practical No. 4
Aim:
To implement Predictive Parsing (LL(1)) in C.
------------------------------------------------------------

Grammar Used:
E  → T E'
E' → + T E' | ε
T  → i

Where:
i  → identifier
+  → operator
$  → end of input symbol
ε  → empty (epsilon)

------------------------------------------------------------

Concept:
Predictive parsing is a top-down parsing technique.
It uses:
- A stack
- An input buffer
- Grammar rules
- One lookahead symbol (LL(1))

The parser predicts which production to apply
without backtracking.

------------------------------------------------------------

Sample Input:
i+i$

Expected Output:
String Accepted!

------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>

/* Stack to store grammar symbols */
char stack[50];
int top = -1;

/* Push a symbol onto stack */
void push(char c) {
    stack[++top] = c;
}

/* Pop a symbol from stack */
char pop() {
    return stack[top--];
}

int main() {
    char input[50];
    int i = 0;      // Input pointer
    char x;         // Top of stack symbol

    /* Display grammar */
    printf("Grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | ε\n");
    printf("T  -> i\n\n");

    /* Read input string */
    printf("Enter input string (end with $): ");
    scanf("%s", input);

    /* Initialize stack with end marker and start symbol */
    push('$');
    push('E');

    printf("\nStack\tInput\tAction\n");

    /* Parsing loop */
    while (top >= 0) {
        x = stack[top];   // Get top of stack

        printf("%s\t%s\t", stack, &input[i]);

        /* If terminal matches input symbol */
        if (x == input[i]) {
            pop();
            i++;
            printf("Match %c\n", x);
        }

        /* Apply production E → T E' */
        else if (x == 'E') {
            pop();
            push('E');
            push('T');
            printf("E -> T E'\n");
        }

        /* Apply production T → i */
        else if (x == 'T' && input[i] == 'i') {
            pop();
            push('i');
            printf("T -> i\n");
        }

        /* Apply production E' → + T E' */
        else if (x == 'E' && input[i] == '+') {
            pop();
            push('E');
            push('T');
            push('+');
            printf("E' -> + T E'\n");
        }

        /* Apply epsilon production E' → ε */
        else if (x == 'E' && input[i] == '$') {
            pop();
            printf("E' -> ε\n");
        }

        /* Error condition */
        else {
            printf("Error\n");
            return 0;
        }
    }

    /* Final acceptance check */
    if (input[i] == '$')
        printf("\nString Accepted!\n");
    else
        printf("\nString Rejected!\n");

    return 0;
}