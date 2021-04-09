#include<stdio.h>
#include<string.h>
char stack[50];
char infix[50];
char postfix[50];
char prefix[50];
int stacktop = -1;
int inftop = -1;
int posttop = -1;
int pretop = -1;
int len;
char revstr[50];
int strtop = -1;
char infrev[50];
int infrevtop = -1;

int rev(char arr[])
{
    int leng;
    leng = strlen(arr);
    for (int r = leng-1; r>=0; r--)
    {
        infrev[++infrevtop] = arr[r];
    }
    
}

int strrev(char arr[])
{
    int leng;
    leng = strlen(arr);
    for (int r = leng-1; r>=0; r--)
    {
        revstr[++strtop] = arr[r];
    }
}
void pushstack(char ele)
{
    stack[++stacktop] = ele;
}
void pushpost(char ele)
{
    postfix[++posttop] = ele;
}

void pushpre(char ele)
{
    prefix[++pretop] = ele;
}
void popstack()
{
    stack[stacktop--];
}

void poppost()
{
    postfix[posttop--];
}
int priority(char ele)
{
    switch (ele)
    {
        case '#': return -1;
        case '(': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
    }
}

int inftopos(char arr[])
{
    pushstack('#');
    for (int i = 0; i<len; i++)
    {
        char el = arr[i];
        if (isdigit(el))
        {
            pushpost(el);
        }
        else if (el == ')')
        {
            while (stack[stacktop] != '(')
            {
                char trans = stack[stacktop];
                pushpost(trans);
                popstack();
            }
            popstack();
        }
        else if (el == '(')
        {
            pushstack(el);
        }
        else
        {
            if (priority(el) > priority(stack[stacktop]))
            {
                pushstack(el);
            }
            else
            {
                while (priority(stack[stacktop])>=priority(el))
                {
                    char trans = stack[stacktop];
                    pushpost(trans);
                    popstack();
                }
                pushstack(el);
            }
        }
    }
    while (stack[stacktop] != '#')
    {
        char trans = stack[stacktop];
        pushpost(trans);
        popstack();
    }
}

void toggle(char arr[])
{
    for (int i = 0; i<len; i++)
    {
        if (arr[i] == '(')
        {
            pushpre(')');
        }
        else if (arr[i] == ')')
        {
            pushpre('(');
        }
        else
        {
            pushpre(arr[i]);
        }
    }
}
int main()
{
    printf("Enter the infix expression: ");
    scanf("%s",infix);
    printf("\nThe given infix expression is: %s",infix);
    len = strlen(infix);
    rev(infix);
    printf("\nUpdated infix: %s",infrev);
    toggle(infrev);
    inftopos(prefix);
    strrev(postfix);
    printf("\nThe corresponding prefix expression is: %s",revstr);
    return 0;
}
