#include "includes.h"

char PageLetter(char *subname);
char* ClearPhone(char*, char*);

RECORD* FindSubnameRecord(DIALER *Dialer, char* subname)
{
    char  letter = PageLetter(subname);
    int countRec = Dialer->d_pages[letter].p_countRec;
    for(int i = 0; i < countRec ; i++)
    {
        //printf("\n\t%s | %s",Dialer->d_pages[letter].p_recording[i].r_subname, subname);
        if(strcmp(Dialer->d_pages[letter].p_recording[i].r_subname, subname)==0)
            return Dialer->d_pages[letter].p_recording+i;

    }
    return NULL;
}

RECORD* FindPhoneRecord(DIALER *Dialer, char* phone)
{
    char *ClPhone1 = NULL, *ClPhone2 = NULL;
    for(int i = 0; i < 30 ; i++)
    {
        int    countRec = Dialer->d_pages[i].p_countRec;
        for(int j = 0; j < countRec; j++)
        {
            //printf("\n\t%s | %s",Dialer->d_pages[i].p_recording[j].r_phone, phone);
            ClPhone1 = ClearPhone(Dialer->d_pages[i].p_recording[j].r_phone, ClPhone1);
            ClPhone2 = ClearPhone(phone,                                     ClPhone2);
            if(strcmp(ClPhone1, ClPhone2) == 0)
            {
                free(ClPhone1); free(ClPhone2);
                return Dialer->d_pages[i].p_recording+j;
            }
        }
    }
    free(ClPhone1); free(ClPhone2);
    return NULL;
}
