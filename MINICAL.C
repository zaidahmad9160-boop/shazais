#include <stdio.h>
int main() {
    int num1, num2, choice;

    printf("------Calculator------");
    printf("\n Enter 1 for addition");
    printf("\n Enter 2 for subtraction");
    printf("\n Enter 3 for Multiplication");
    printf("\n Enter 4 for Division");
    printf("\n Enter 5 for checking reminder");

    printf("\n Enter two numbers");
    scanf("%d%d", &num1, &num2);

    printf("\n Enter your choice (1-5) which operation");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("\nAddition = %d", num1 + num2);
            break;

        case 2:
            printf("\nSubtraction = %d", num1 - num2);
            break;

        case 3:
            printf("\nMultiplication = %d", num1 * num2);
            break;

        case 4:
            if(num2 != 0)
                printf("\nDivision = %d", num1 / num2);
            else
                printf("\nCannot divide by zero");
            break;

        case 5:
            if(num2 != 0)
                printf("\nReminder = %d", num1 % num2);
            else
                printf("\nCannot find reminder with zero");
            break;

        default:
            printf("\nInvalid choice");
    }

    return 0;
}
