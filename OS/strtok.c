#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
    char *src="hello friends whatsup";
    char *str=malloc(sizeof(char)*strlen(src));
    char *delim=" ";
    char *token;
    strcpy(str,src);
    token=strtok(str,delim);
    //while(token)
    //{
        printf("%s\n",token);
        token=strtok(NULL,delim);
        printf("%s\n",token);
        token=strtok(NULL,delim);
        printf("%s\n",token);
    //}
    return 0;
}