#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char* key[7]={"BEGIN","END","FOR","DO","IF","THEN","ELSE"};
char symbol[7]={':' , '+' , '*' , ',' , '(' , ')' , '='};
char* kout[8]={"","Begin","End","For","Do","If","Then","Else"};
char* sout[7]={"Colon","Plus","Star","Comma","LParenthesis","RParenthesis","Assign"};
char* err="Unknown";
int reserve(char* t){
    for(int i=0; i<7; i++){
        if(strcmp(key[i],t)==0) return i+1;
    }
    return 0;
}

int main(int argc,char* argv[])
{
    char c;
    char token[1000];
    int flag;

    char *fname="a.txt";
    FILE *in;
    in=fopen(fname,"r");

    c = fgetc(in);
    while(c != EOF){
        //printf("in:%c\n",c);
        if(isspace(c)){
            c = fgetc(in);
            continue;
        }

        memset(token,'\0',sizeof(token));
        flag = 0;

        if(isalpha(c)){
            flag = 1;
            while( c != EOF && (isalpha(c) || isdigit(c)) ){
                int len = strlen(token);
                token[len] = c;
                c = fgetc(in);
            }
            int i = reserve(token);
            if(i > 0) printf("%s\n",kout[i]);
            else printf("Ident(%s)\n",token);
        }
        else if(isdigit(c)){
            flag = 1;
            while(isdigit(c)){
                int len = strlen(token);
                token[len] = c;
                c = fgetc(in);
            }
            printf("Int(%d)\n",atoi(token));
        }
        else{
            //printf("other\n");
            for(int i = 1;i <= 5; i++){
                if(c == symbol[i]){
                    flag = 1;
                    printf("%s\n",sout[i]);
                    break;
                }
            }
            if(c == symbol[0]){
                flag = 1;
                char tmp;
                tmp = fgetc(in);
                if(tmp == symbol[6]){
                    printf("%s\n",sout[6]);
                }
                else{
                    fseek(in,-1,SEEK_CUR);
                    printf("%s\n",sout[0]);
                }
            }
            c = fgetc(in);
        }
        if(flag == 0){
            printf("%s\n",err);
            break;
        }
    }
	return 0;
}
