#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main()
{
    int opt;
    printf("\n\t\t\t MATH TUTOR MENU");
    printf("\n\t\t PRESS 1: Addition");
    printf("\n\t\t PRESS 2: Subtraction");
    printf("\n\t\t PRESS 3: Multiplication");
    printf("\n\t\t PRESS 4: Division");
    printf("\n\t\t PRESS 5: EXIT");
    printf("\n\t\t ENTER YOUR CHOICE: ");
    scanf("%d", &opt);
    if(opt == 1)
    {
        Addition();
    }
    else if(opt == 2)
    {
        Subtraction();
    }
    else if(opt == 3)
    {
        Multiplication();
    }
       else if(opt == 4)
    {
        Division();
    }
    else if(opt == 5)
    {
        EXIT();
    }
}
int Addition()
{
    int a, max, num1, num2, result, answer, score = 0;
    srand(time(NULL));
    printf("Please input a number that corresponds to how many addition problem/s you want: ");
    scanf("%i", &max);
    for(a = 1; a<= max; a++)
    {
        num1 = rand()%100;
        num2 = rand()%100;
        result = num1 + num2;
        printf("%i + %i = ?: ", num1, num2);
        scanf("%i",&answer);
        if(result == answer)
        {
            printf("Correct!\n");
            score = score + 1;
        }
        else
            printf("Wrong! the correct answer is %i\n", result);
    }

     printf("Your score is %i/%i", score, max);
}
int Subtraction()
{
    int a, max, num1, num2, result, answer, score = 0;
    srand(time(NULL));
    printf("Please input a number that corresponds to how many subtraction problem/s you want: ");
    scanf("%i", &max);
    for(a = 1; a<= max; a++)
    {
        num1 = rand()%100;
        num2 = rand()%100;
        result = num1 - num2;
        printf("%i - %i = ?: ", num1, num2);
        scanf("%i",&answer);
        if(result == answer)
        {
            printf("Correct!\n");
            score = score - 1;
        }
        else
            printf("Wrong! the correct answer is %i\n", result);
    }

     printf("Your score is %i/%i", score, max);
}
int Multiplication()
{
    int a, max, num1, num2, result, answer, score = 0;
    srand(time(NULL));
    printf("Please input a number that corresponds to how many multiplication problem/s you want: ");
    scanf("%i", &max);
    for(a = 1; a<= max; a++)
    {
        num1 = rand()%100;
        num2 = rand()%100;
        result = num1 * num2;
        printf("%i * %i = ?: ", num1, num2);
        scanf("%i",&answer);
        if(result == answer)
        {
            printf("Correct!\n");
            score = score + 1;
        }
        else
            printf("Wrong! the correct answer is %i\n", result);
    }

     printf("Your score is %i/%i", score, max);
}
int Division()
{
    int a, max, num1, num2, result, answer, score = 0;
    srand(time(NULL));
    printf("Please input a number that corresponds to how many division problem/s you want: ");
    scanf("%i", &max);
    for(a = 1; a<= max; a++)
    {
        num1 = rand()%100;
        num2 = rand()%100;
        result = num1 / num2;
        printf("%i  / %i = ?: ", num1, num2);
        scanf("%i",&answer);
        if(result == answer)
        {
            printf("Correct!\n");
            score = score + 1;
        }
        else
            printf("Wrong! the correct answer is %i\n", result);
    }

     printf("Your score is %i/%i", score, max);
}
int EXIT()
{
    printf("THANK YOU!!");

}

