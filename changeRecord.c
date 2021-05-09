#include "includes.h"

char    getAnswer(char, char);
int     BySubname(DIALER*);
RECORD* FindSubnameRecord(DIALER *, char*);
int     ByPhone(DIALER*);
RECORD* FindPhoneRecord(DIALER*, char*);
void    DeleteRecord(DIALER*, RECORD*);
int     CreateRecord(DIALER*,  char*, char*);
char*   ClearPhone(char*, char*);
char    PageLetter(char*);
char*   inputSubname(char*);
char*   inputPhone(char*);
int     ChangeRecord(DIALER*, RECORD*);


/**
    -> Найти/обновить запись => Ввести фамилию => Найти запись => Выбрать действие(2):
                                                                                   ~~> Найти номер     => Выдать телефон   ~> Завершение
                                                                                   ~~> Изменить запись => Обновить         ~> Завершение
                                                                                   ~~> Удалить запись  => Удалить          ~> Завершение
*/

int ChangeBook(DIALER* PhoneBook)
{
    char choice;
    int changes = 0;
    while(true)
    {
        printf("\n\n\t\t___Найти/Обновить запись___:"
               "\n\tПо фамилии         - 1"
               "\n\tПо номеру телефона - 2"
               "\n\tВыйти              - 3");
        choice = getAnswer('1', '3');

        switch(choice)
        {
        case '1':
            changes += BySubname(PhoneBook);
            continue;
        case '2':
            changes += ByPhone(PhoneBook);
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

int BySubname(DIALER* PhoneBook)
{
    printf("\n\t\tПоиск фамилии...");
    char *subname = NULL;
    char choice;
    int changes = 0;
    RECORD* rec = NULL;
    while(true)
    {
        subname = inputSubname(subname);
        rec = FindSubnameRecord(PhoneBook, subname);
        if(rec == NULL)
        {
            printf("\n\tФамилия не содержится в телефонной книге"
                   "\n\tПопробовать ещё раз - 1"
                   "\n\tВыйти               - 2");
            choice = getAnswer('1', '2');
            if(choice == '1') continue;
            else {free(subname); free(rec); return 0;}
        }
        else
        {
            printf("\n\tЗапись найдена.");
            while(true)
            {
                printf("\n\n\t\t___Выберите действие___:"
                       "\n\tНайти номер     - 1"
                       "\n\tИзменить запись - 2"
                       "\n\tУдалить запись  - 3"
                       "\n\tВыйти           - 4");
                choice = getAnswer('1', '4');
                switch(choice)
                {
                case '1':
                    printf("\n\tСтраница - %d| Фамилия - %s|____Номер телефона - %s____|",
                           PageLetter(rec->r_subname), rec->r_subname, rec->r_phone);
                    continue;
                case '2':
                    changes += ChangeRecord(PhoneBook, rec);
                    break;
                case '3':
                    printf("\n\t3 - Удаляем запись");
                    DeleteRecord(PhoneBook, rec);
                    changes++;
                    break;
                case '4':
                    printf("\n\t4 - Отмена");
                    break;
                default:
                    printf("\n\t\t\tError!");
                    exit(UNEXPECTED_ERROR);
                }
                break;
            }
        }
        break;
    }
    free(subname);
    return changes;
}

int ByPhone(DIALER* PhoneBook)
{
    printf("\n\t\tПоиск номера телефона...");
    char *phone = NULL;
    RECORD* rec = NULL;
    char choice;
    int changes = 0;
    while(true)
    {
        phone = inputPhone(phone);
        rec = FindPhoneRecord(PhoneBook, phone);
        if(rec == NULL)
        {
            printf("\n\tНомер телефона не содержится в телефонной книге"
                   "\n\tПопробовать ещё раз - 1"
                   "\n\tВыйти               - 2");
            choice = getAnswer('1', '2');
            if(choice == '1') continue;
            else { free(phone); free(rec); return 0;}
        }
        else
        {
            printf("\n\tЗапись найдена.");
            printf("\n\t|____Фамилия - %s____| Номер телефона - %s|",
                           rec->r_subname, rec->r_phone);
            while(true)
            {
                printf("\n\n\t\t___Выберите действие___:"
                       "\n\tНайти фамилию     - 1"
                       "\n\tИзменить запись   - 2"
                       "\n\tУдалить запись    - 3"
                       "\n\tВыйти             - 4");
                choice = getAnswer('1', '4');
                switch(choice)
                {
                case '1':
                    printf("\n\tСтраница - %d|____Фамилия - %s____| Номер телефона - %s|",
                           PageLetter(rec->r_subname)+1, rec->r_subname, rec->r_phone);
                    continue;
                case '2':
                    changes += ChangeRecord(PhoneBook, rec);
                    continue;
                case '3':
                    printf("\n\t3 - Удаляем запись");
                    DeleteRecord(PhoneBook, rec);
                    changes++;
                    break;
                case '4':
                    printf("\n\t4 - Отмена");
                    break;
                default:
                    printf("\n\t\t\tError!");
                    exit(UNEXPECTED_ERROR);
                }
                break;
            }
        }
        break;
    }
    free(phone);
    return changes;
}

int ChangeSubname(DIALER *Dialer , RECORD* rec, char* subname)
{
    if(FindSubnameRecord(Dialer, subname))
        return 0;
    else
    {
        char* tempPhone = rec->r_phone;
        DeleteRecord(Dialer, rec);
        CreateRecord(Dialer, subname, tempPhone);
        free(tempPhone);
    }
    return 1;
}

int ChangePhone(DIALER *Dialer, RECORD* rec, char* phone)
{
    if(FindPhoneRecord(Dialer, phone))
        return 0;
    else
    {
        rec->r_phone = phone;
        return 1;
    }
}

int ChangeRecord(DIALER *Dialer, RECORD* rec)
{
    char choice;
    int changes = 0;
    while(true)
    {
        printf("\n\n\t\t___Обновить запись___:"
               "\n\tИзменить фамилию        - 1"
               "\n\tИзменить номер телефона - 2"
               "\n\tОтмена                  - 3");
        choice = getAnswer('1', '3');

        switch(choice)
        {
        case '1':
        {
            printf("\n\t\tВведите новую фамилию: ");
            char *newSubname = NULL;
            newSubname = inputSubname(newSubname);
            if(ChangeSubname(Dialer, rec, newSubname))
            {
                    printf("\n\tФамилия успешно обновлена.");
                    changes ++;
            }
            else
                printf("\n\tДанная фамилия совпадает с нынешней"
                       "\n\tПопробуйте ещё раз");
            free(newSubname);
            break;
        }
        case '2':
        {
            printf("\n\t\tВведите новый номер телефона: ");
            char *newPhone = NULL;
            newPhone = inputPhone(newPhone);
            if(ChangePhone(Dialer, rec, newPhone))
            {
                   printf("\n\tНомер телефона успешно обновлён");
                   changes ++;
            }
            else
                printf("\n\tДанный номер телефона совпадает с нынешним"
                       "\n\tПопробуйте ещё раз");
            free(newPhone);
            continue;
        }
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

void DeleteRecord(DIALER* PhoneBook, RECORD* rec)
{
    char letter = PageLetter(rec->r_subname);
    int *countRec = &((PhoneBook->d_pages+letter)->p_countRec);
    int numberRec;
    for(numberRec = 0; numberRec < *countRec; numberRec++)
        if(strcmp(((PhoneBook->d_pages+letter)->p_recording+numberRec)->r_subname, rec->r_subname) == 0)
            break;

    for(int i = numberRec; i < *countRec-1; i++)
    {
        //Удаляем номер телефона записи, перезаписывая(сдвигая) на записи, расположенные ниже
        PhoneBook->d_pages[letter].p_recording[i].r_phone = (char*)realloc(PhoneBook->d_pages[letter].p_recording[i].r_phone,
                                                                          strlen(PhoneBook->d_pages[letter].p_recording[i+1].r_phone) * sizeof(char));
        strcpy(PhoneBook->d_pages[letter].p_recording[i].r_phone, PhoneBook->d_pages[letter].p_recording[i+1].r_phone);

        //Удаляем наименование записи, перезаписывая(сдвигая) на записи, расположенные ниже
        PhoneBook->d_pages[letter].p_recording[i].r_subname = (char*)realloc(PhoneBook->d_pages[letter].p_recording[i].r_subname,
                                                               strlen(PhoneBook->d_pages[letter].p_recording[i+1].r_subname) * sizeof(char));
        strcpy(PhoneBook->d_pages[letter].p_recording[i].r_subname, PhoneBook->d_pages[letter].p_recording[i+1].r_subname);
    }
    free(PhoneBook->d_pages[letter].p_recording[(*countRec)-1].r_subname);
    free(PhoneBook->d_pages[letter].p_recording[(*countRec)-1].r_phone);
    (*countRec)--;
    PhoneBook->d_pages[letter].p_recording = (RECORD*)realloc(PhoneBook->d_pages[letter].p_recording,
                                                                    *countRec * sizeof(RECORD));
}
