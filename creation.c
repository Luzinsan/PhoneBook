#include "includes.h"

char    PageLetter(char *subname);
RECORD* FindSubnameRecord(DIALER*, char*);
RECORD* FindPhoneRecord(DIALER*, char*);
char    getAnswer(char, char);
int     PreCreateRecord(DIALER*);
int     ChangeBook(DIALER*);
char*   inputSubname(char*);
char*   inputPhone(char*);
void    printDialer(DIALER*);
int     CreateRecord(DIALER*,  char*, char*);

/**
    -> Создать запись: Ввести фамилию и номер => Найти страницу => Добавить запись => Закончить? ~да~ > Выбрать действие...
                                                                                                 ~нет~>                    ~> Завершение
*/

int CreateNewPhoneBook(DIALER* PhoneBook)
{
    char choice;
    int changes = 0;
    while(true)
    {
        printf("\n\n\t\t___Выберите действие___:"
               "\n\tСоздать новую запись  - 1"
               "\n\tНайти/Обновить запись - 2"
               "\n\tОтмена                - 3");
        choice = getAnswer('1', '3');

        switch(choice)
        {
        case '1':
            changes += PreCreateRecord(PhoneBook);
            continue;
        case '2':
            changes += ChangeBook(PhoneBook);
            continue;
        case '3':
            break;
        default:
            printf("\n\tError!!!");
            exit(UNEXPECTED_ERROR);
        }
        break;
    }
    return changes;
}

int PreCreateRecord(DIALER* PhoneBook)
{

    printf("\n\t\tСоздание записи...");

    char *subname = NULL;
    subname = inputSubname(subname);

    char *phone = NULL;
    phone = inputPhone(phone);

    switch(CreateRecord(PhoneBook, subname, phone))
    {
        case 1:
            printf("\n\tЗапись успешно создана!");
            //printDialer(PhoneBook);
            free(subname);
            free(phone);
            return 1;
        case 0:
            printf("\n\tЗапись с такой фамилией уже существует. Попробуйте ещё раз.");
            free(subname);
            free(phone);
            return 0;
        case -1:
            printf("\n\tЗапись с таким номером телефона уже существует. Попробуйте ещё раз.");
            free(subname);
            free(phone);
            return 0;
        default:
            printf("\n\t\tError!!!");
            exit(UNEXPECTED_ERROR);
    }
}

int CreateRecord(DIALER *Dialer,  char *subname, char *phone)
{
    char letter = PageLetter(subname);

    if(FindSubnameRecord(Dialer, subname))
        return 0;
    if(FindPhoneRecord(Dialer, phone))
        return -1;

    int*   countRec = &(Dialer->d_pages[letter].p_countRec);
    (*countRec)++;
    Dialer->d_pages[letter].p_recording = (RECORD*)realloc(Dialer->d_pages[letter].p_recording,
                                                           *countRec * sizeof(RECORD));
    int currentRec;
    for(currentRec = *countRec-2; currentRec >= 0; currentRec--)
        if(strcmp(Dialer->d_pages[letter].p_recording[currentRec].r_subname,subname) > 0)
            Dialer->d_pages[letter].p_recording[currentRec+1] = Dialer->d_pages[letter].p_recording[currentRec];
        else break;


    //printf("\n\t%s |/|",subname);
    (Dialer->d_pages[letter].p_recording+currentRec+1)->r_subname = (char*)malloc(strlen(subname) * sizeof(char));
    (Dialer->d_pages[letter].p_recording+currentRec+1)->r_phone   = (char*)malloc(strlen(phone) * sizeof(char));
    strcpy((Dialer->d_pages[letter].p_recording+currentRec+1)->r_subname, subname);
    strcpy(Dialer->d_pages[letter].p_recording[currentRec+1].r_phone, phone);
    //printf("\n\t%s | %s |/ %d | %d |",Dialer->d_pages[letter].p_recording[currentRec+1].r_subname,
    //                    Dialer->d_pages[letter].p_recording[currentRec+1].r_phone, letter, currentRec+1);
    return 1;
}
