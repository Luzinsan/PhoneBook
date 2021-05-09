#include "includes.h"

char* inputStr(char*);
char  stoupper(unsigned char*);

char* inputSubname(char* subname)
{
    while(true)
    {
        printf("\n\n\tВведите фамилию: ");
        subname = inputStr(subname);
        if(  subname[0] <  'А' || subname[0] >  'я'
          || subname[0] == 'Ъ' || subname[0] == 'ъ'
          || subname[0] == 'Ь' || subname[0] == 'ь')
        {
            printf("\n\tФамилия не может начинаться с буквы %c"
                   "\n\tПопробуйте ещё раз", subname[0]);
            continue;
        }
        break;
    }
    if(stoupper(subname))
        printf("\n\tРегистр заглавной буквы фамилии был изменён."
               "\n\tВ телефонную книгу введена фамилия \"%s\"", subname);
    else printf("\n\tФамилия \"%s\" успешно введена", subname);
    return subname;
}

char* inputPhone(char* phone)
{
    char flag;
    while(true)
    {
        printf("\n\n\tВведите номер телефона: ");
        phone = inputStr(phone);
        flag = 0;
        for(int i = 0; i < strlen(phone); i++)
            if  ((phone[i] <   '0' ||  phone[i] >  '9')
               && phone[i] != '-'  &&  phone[0] != '+'  &&  phone[i] != ' ')
            {
                printf("\n\tСтрока содержит символ %c"
                       "\n\tНекорректный номер телефона. Попробуйте ещё раз.", phone[i]);
                flag = 1;
                break;
            }
        if(flag) continue;
        break;
    }
    return phone;
}

char getAnswer(char a, char b)
{
    char choice;
    do{
        printf("\n\t  - ");
        choice = _getch();
        printf("%c", choice);
        if(choice < a || choice > b)
            printf("\n\tНеверно введено значение. Попробуйте ещё раз.");
    }while(choice < a || choice > b);
    return choice;
}

char* inputStr(char *string)
{
    string = (char*)malloc(sizeof(char));
    string[0] = '\0';
    int i = 0;
    do{
        string[i] = _getch();
        printf("%c", string[i]);
        if(i>0  && string[i] == '\b')
        {
            if(string[i-1]=='\t')
                printf("\b\b\b\b");
            else
                printf(" \b");
            string = (char*)realloc(string,(i+1)*sizeof(char));
            i--;
        }
        else if(i==0 && string[i] == '\b') continue;
        else if (string[i] != '\r') {string = (char*)realloc(string,(i+2)*sizeof(char)); i++;}
        else    {string[i] = '\0';    break;}
    }while(true);
    return string;
}
