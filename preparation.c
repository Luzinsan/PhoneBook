#include "includes.h"

char PageLetter(char *subname)
{
    char letter = subname[0];
    switch(letter)
    {//ЪЫЬЭЮЯ: Ы->Ъ;  Э->Ы;  Ю->Ь; Я->Э
        case 'Ы': letter--; break;
        case 'Э': case 'Ю': case 'Я': letter -= 2;
    }
    letter -= CODE_UNSIGNED_LETTER_A;
    return letter;
}

char* ClearPhone(char* phone, char *ClPhone)
{
    //printf("\n\t%d", strlen(phone));
    ClPhone = (char*)realloc(ClPhone, strlen(phone) * sizeof(char));
    strcpy(ClPhone, phone);
    char *pch = strtok(ClPhone, " -");
    char flag = 0;
    while (pch)
    {
        if(flag)
        {
            ClPhone = (char*)realloc(ClPhone,
                             (strlen(ClPhone)+strlen(pch)) * sizeof(char));
            strcat(ClPhone, pch);
        }
        else flag = 1;
        pch = strtok(NULL, " -");
    }
    free(pch);

    if(strstr(ClPhone, "+7")) strcpy(ClPhone, ClPhone+2);
    //printf("\n\t%s len = %d", ClPhone, strlen(ClPhone));
    return ClPhone;
}

/** Приводит все содержащиеся в строке буквы
(как латинские, так и кириллицу) к верхнему регистру.
*/
char stoupper(unsigned char *str)
{//unsigned для того, чтобы все коды были распределены в положительной стороне, как в таблице.
 //Иначе бы кирилица отображалась отрицательным кодом.
    //Если встречается буква на латинице
    char flag = 0;
    if (str[0] >= 97 && str[0] <= 122)
    {
        //То её же буква в верхнем регистве находится на 32 позиции ниже
        str[0] -= 32;
        flag = 1;
    }
    //Если это кириллица
    if (str[0] >= 224 && str[0] <= 255)
    {
        str[0] -= 32;//Такая же разница
        flag = 1;
    }
    return flag;
}
