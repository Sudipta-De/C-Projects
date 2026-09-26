#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

double calculateExpression(char expression[]) {

    double result = 0;
    double number = 0;
    char operation = '+';

    int i = 0;

    while (expression[i] != '\0') {

        if (expression[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.') {

            number = 0;

            while (isdigit(expression[i]) || expression[i] == '.') {

                if (expression[i] == '.') {
                    double decimal = 0.1;
                    i++;

                    while (isdigit(expression[i])) {
                        number += (expression[i] - '0') * decimal;
                        decimal /= 10;
                        i++;
                    }

                    break;
                }

                number = number * 10 + (expression[i] - '0');
                i++;
            }

             Apply previous operation */
            if (operation == '+') {
                result += number;
            }
            else if (operation == '-') {
                result -= number;
            }
            else if (operation == '*') {
                result *= number;
            }
            else if (operation == '/') {
                if (number == 0) {
                    printf("Error: Division by zero!\n");
                    return 0;
                }

                result /= number;
            }

            continue;
        }

         Read operator */
        if (expression[i] == '+' ||
            expression[i] == '-' ||
            expression[i] == '*' ||
            expression[i] == '/') {

            operation = expression[i];
        }

        i++;
    }

    return result;
}


int main() {

    int choice;
    int trigChoice;

    char expression1[100];
    char expression2[100];

    double num1;
    double num2;
    double result;

    double angle;
    double radians;

    char continueChoice;


    printf("\n==== Welcome to the Calculator ====\n");


    while (1) {

        printf("\n-------- Calculator MENU --------\n");
        printf("1. Addition (+)\n");
        printf("2. Subtraction (-)\n");
        printf("3. Division (/)\n");
        printf("4. Multiplication (*)\n");
        printf("5. Modulus (%%)\n");
        printf("6. Trigonometry\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        if (choice == 1) {

            printf("\n------ Addition ------\n");

            printf("Enter first number/expression: ");
            scanf(" %[^\n]", expression1);

            printf("Enter second number/expression: ");
            scanf(" %[^\n]", expression2);

            num1 = calculateExpression(expression1);
            num2 = calculateExpression(expression2);

            result = num1 + num2;

            printf("\nFirst value  = %.2f", num1);
            printf("\nSecond value = %.2f", num2);
            printf("\nResult       = %.2f\n", result);
        }

        else if (choice == 2) {

            printf("\n------ Subtraction ------\n");

            printf("Enter first number/expression: ");
            scanf(" %[^\n]", expression1);

            printf("Enter second number/expression: ");
            scanf(" %[^\n]", expression2);

            num1 = calculateExpression(expression1);
            num2 = calculateExpression(expression2);

            result = num1 - num2;

            printf("\nFirst value  = %.2f", num1);
            printf("\nSecond value = %.2f", num2);
            printf("\nResult       = %.2f\n", result);
        }

        else if (choice == 3) {

            printf("\n------ Division ------\n");

            printf("Enter first number/expression: ");
            scanf(" %[^\n]", expression1);

            printf("Enter second number/expression: ");
            scanf(" %[^\n]", expression2);

            num1 = calculateExpression(expression1);
            num2 = calculateExpression(expression2);

            if (num2 == 0) {
                printf("\nError: Cannot divide by zero.\n");
            }
            else {

                result = num1 / num2;

                printf("\nFirst value  = %.2f", num1);
                printf("\nSecond value = %.2f", num2);
                printf("\nResult       = %.2f\n", result);
            }
        }

        else if (choice == 4) {

            printf("\n------ Multiplication ------\n");

            printf("Enter first number/expression: ");
            scanf(" %[^\n]", expression1);

            printf("Enter second number/expression: ");
            scanf(" %[^\n]", expression2);

            num1 = calculateExpression(expression1);
            num2 = calculateExpression(expression2);

            result = num1 * num2;

            printf("\nFirst value  = %.2f", num1);
            printf("\nSecond value = %.2f", num2);
            printf("\nResult       = %.2f\n", result);
        }


         ================= MODULUS ================= */

        else if (choice == 5) {

            printf("\n------ Modulus ------\n");

            printf("Enter first number/expression: ");
            scanf(" %[^\n]", expression1);

            printf("Enter second number/expression: ");
            scanf(" %[^\n]", expression2);

            num1 = calculateExpression(expression1);
            num2 = calculateExpression(expression2);

            if ((int)num2 == 0) {

                printf("\nError: Cannot calculate modulus by zero.\n");
            }
            else {

                result = (int)num1 % (int)num2;

                printf("\nFirst value  = %.2f", num1);
                printf("\nSecond value = %.2f", num2);
                printf("\nResult       = %.2f\n", result);
            }
        }

        else if (choice == 6) {

            printf("\n------ Trigonometry MENU ------\n");

            printf("1. Sin\n");
            printf("2. Cos\n");
            printf("3. Tan\n");
            printf("4. Cosec\n");
            printf("5. Sec\n");
            printf("6. Cot\n");

            printf("\nEnter your choice: ");
            scanf("%d", &trigChoice);

            printf("Enter angle in degrees: ");
            scanf("%lf", &angle);

            radians = angle * M_PI / 180.0;


            switch (trigChoice) {

                case 1:

                    printf("\nsin(%.2f) = %.4f\n",
                           angle,
                           sin(radians));

                    break;


                case 2:

                    printf("\ncos(%.2f) = %.4f\n",
                           angle,
                           cos(radians));

                    break;


                case 3:

                    printf("\ntan(%.2f) = %.4f\n",
                           angle,
                           tan(radians));

                    break;


                case 4:

                    if (fabs(sin(radians)) < 0.000001) {

                        printf("\nCosec is undefined.\n");
                    }
                    else {

                        printf("\ncosec(%.2f) = %.4f\n",
                               angle,
                               1.0 / sin(radians));
                    }

                    break;


                case 5:

                    if (fabs(cos(radians)) < 0.000001) {

                        printf("\nSec is undefined.\n");
                    }
                    else {

                        printf("\nsec(%.2f) = %.4f\n",
                               angle,
                               1.0 / cos(radians));
                    }

                    break;


                case 6:

                    if (fabs(sin(radians)) < 0.000001) {

                        printf("\nCot is undefined.\n");
                    }
                    else {

                        printf("\ncot(%.2f) = %.4f\n",
                               angle,
                               cos(radians) / sin(radians));
                    }

                    break;


                default:

                    printf("\nInvalid trigonometry choice!\n");
            }
        }

        else if (choice == 7) {

            printf("\n===== Thanks for using this Calculator =====\n");

            break;
        }

        else {

            printf("\nInvalid choice! Please select between 1 and 7.\n");

            continue;
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &continueChoice);


        if (continueChoice == 'n' ||
            continueChoice == 'N') {

            printf("\n===== Thanks for using this Calculator =====\n");

            break;
        }

        else if (continueChoice == 'y' ||
                 continueChoice == 'Y') {

            printf("\nReturning to Calculator Menu...\n");
        }

        else {

            printf("\nInvalid input. Calculator will exit.\n");

            break;
        }
    }


    return 0;
}