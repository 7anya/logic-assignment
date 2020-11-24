/* Logic Homework 3, Part 1 */
/* Team Number: X */
/* Team Members:
1. <Tanya Prasad> <ID 2018B5A71054H>
2. <Virag Lakhani> <ID 2018B5A70973H>
3. <Soumit Mishra> <ID 2018B5A70429H>
4. <Dinank Vashishtha> <ID 2018B5A71055H>
*/

#include <stdio.h>

#include <string.h>

#define MAX 100 // macro indicating the maximum size of stack




/***************************************************************/
/********************stack operations***************************/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.

void push(char data, char stack[], int *top) {
    if (*top != MAX - 1) // if stack is not full
    {
        *top = *top + 1;
        stack[*top] = data;
    } else {
        printf("Could not insert data, Stack is full.\n");
    }
}


// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.

char pop(char stack[], int *top) {
    char data;

    if (*top != -1) //checking whether stack contains some elements
    {
        data = stack[*top];
        *top = *top - 1;
        return data;
    } else {
        printf("Could not retrieve data, Stack is empty.\n");
        return 'e';
    }
}

// NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable 
// would be reflected in the calling function



/***************************************************************/
/********************* implementation **************************/

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)

char eval_formula(int n, char formula[], char operand_val[]) {
    char operand_stack[MAX];  // character array to implement operand stack
    char operator_stack[MAX]; // character array to implement operator stack
    int operand_top = -1; // integer pointing to the top of the operand stack
    int operator_top = -1;  // integer pointing to the top of the operand stack

    // Complete the implementation function to calculate the final valuation of the formula
    char result;
    int len = strlen(formula);
    for (int i = 0; i < len; ++i) {
        if (formula[i] > 48 && formula[i] <= 57) {
            int ind = formula[i] - 48;
            //printf("Index:%d\t",ind);
            char tvalue = operand_val[ind - 1];
            push(tvalue, operand_stack, &operand_top);
//            push(formula[i], operand_stack, &operand_top);

        } else if (formula[i] == '~' || formula[i] == 'V' || formula[i] == '^' || formula[i] == '>') {
            push(formula[i], operator_stack, &operator_top);
        } else if (formula[i] == '(') {
            push(formula[i], operator_stack, &operator_top);

        } else if (formula[i] == ')') {
            while (operator_stack[operator_top] != '(') {
                //process
                if (operator_stack[operator_top] == 'V' || operator_stack[operator_top] == '^' ||
                    operator_stack[operator_top] == '>') {
                    /*
                    a. Pop-out two truth values from the operand stack; let’s say it is T and F.
                    b. Pop-out operation from operator stack. Let’s say it is V.
                    c. Perform T V F and push the result to the operand stack.
                          */

                    char first = pop(operand_stack, &operand_top);
                    char second = pop(operand_stack, &operand_top);
                    char operator = pop(operator_stack, &operator_top);
                    if (operator == 'V') {
                        if (first == 'F' && second == 'F')
                            result = 'F';
                        else
                            result = 'T';

                    } else if (operator == '^') {
                        if (first == 'T' && second == 'T')
                            result = 'T';
                        else
                            result = 'F';
                    } else if (operator == '>') {
                        if (second == 'T' && first == 'F')
                            result = 'F';
                        else
                            result = 'T';
                    }
                    push(result, operand_stack, &operand_top);
                } else {
                    /*
                    a. Pop-out one truth value from the operand stack
                    b. Pop-out operation from operator stack.
                    c. Perform the operation on the operand and push the result back to the operand stack.
                    */
                    char first = pop(operand_stack, &operand_top);
                    char oper = pop(operator_stack, &operator_top);
                    char result;
                    if (first == 'T')
                        result = 'F';
                    else
                        result = 'T';
                    push(result, operand_stack, &operand_top);


                }

                //process ends
            }
            pop(operator_stack, &operator_top);
        }
//        printf("for");
    }


    return operand_stack[operand_top];


}





/***************************************************************/
/***********************main function***************************/

int main() {
    int n; // number of operands
    char formula[MAX]; // character array to store the input formula
    char operand_val[10]; // array to store the valuation of operands (either T or F)
    scanf("%d", &n); //Inputting integer n
    scanf("%s", formula);
    scanf("%s", operand_val);
    printf("%c", eval_formula(n, formula, operand_val));


    return 0;

}
