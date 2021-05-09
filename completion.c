#include "includes.h"

/**
    Завершение:
    -> Сохранить книгу? |-нет - КОНЕЦ
                        да
        -> Буфер изменялся |-нет - КОНЕЦ
                           да
            => Выгрузить буфер в файл => КОНЕЦ.
*/

void printDialer(DIALER*);
char getAnswer(char, char);
int  CreateRecord(DIALER*,  char*, char*);
int  CreateNewPhoneBook(DIALER*);
void UploadToFile(DIALER*);
char* inputStr(char*);


int OpenPhoneBook(DIALER *PhoneBook)
{
    FILE *fp;
    //char name[] = "PhoneBook.txt";

    char *name = NULL;
    printf("\n\tВведите имя файла, откуда загружать телефонную книгу: ");

    while((fp = fopen(inputStr(name), "r")) == NULL)
        printf("\n\tНе удалось открыть файл"
               "\n\tВведите другой путь: ");

    char c, flag_name_phone = 0;
    int changes = 0;
    char* subname = NULL, *phone = NULL;
    int j = 1;
    for(int i = 0; fscanf(fp, "%c", &c) == 1; i++, j++)
    {
        if(c == '|')
        {
            flag_name_phone = 1;
            subname[j-1] = '\0';
            j = 0;
            continue;
        }
        else if(c == '\r')
        {
            flag_name_phone = 0;
            phone[j-1] = '\0';
            j = 0;
            CreateRecord(PhoneBook,subname, phone);
            continue;
        }
        else if(flag_name_phone == 0)
        {
            subname = realloc(subname, j*sizeof(char));
            subname[j-1] = c;
        }
        else if(flag_name_phone == 1)
        {
            phone = realloc(phone, j*sizeof(char));
            phone[j-1] = c;
        }
    }

    printDialer(PhoneBook);
    changes += CreateNewPhoneBook(PhoneBook);
    fclose(fp);
    free(name); free(subname); free(phone);
    return changes;
}

void Completion(DIALER *PhoneBook, int changes)
{
    printf("\n\tСохранить книгу?");
    char choice;
    printf("\n\tда    - 1"
           "\n\tнет   - 2");
    choice = getAnswer('1', '2');
    if(choice == '1')
        if(changes)//Буфер изменялся
        {
            printf("\n\tКоличество изменений(запись/обновление/удаление) = %d", changes);
            UploadToFile(PhoneBook);    //Выгрузить буфер в файл
        }
        else printf("\n\tВ телефонной книге не было произведено никаких изменений.");
}

void UploadToFile(DIALER *PhoneBook)
{
    FILE *f;
    //char name[] = "PhoneNewBook.txt";
    char *name = NULL;
    printf("\n\tВведите имя файла, куда загрузить обновлённую/новую телефонную книгу: ");

    while((f = fopen(inputStr(name), "a")) == NULL)
            printf("\n\tНе удалось открыть файл"
                   "\n\tВведите другой путь: ");

    unsigned char letter = 0;
    for(int i = 0; i < 30; i++, letter++)
    {
        if(letter==26 || letter==28)
           letter++;

        if(PhoneBook->d_pages[i].p_countRec == 0) continue;
        fprintf(f, "\n\t_________________________________________________________"
                   "\n\t|                  Страница №%-2d - буква %c               |"
                   "\n\t|_______________________________________________________|", i+1, letter+192);
        for(int j = 0; j < PhoneBook->d_pages[i].p_countRec; j++)
        {
            RECORD* record = PhoneBook->d_pages[i].p_recording;
            fprintf(f, "\n\t|%3d|%30s|%20s|", j+1, record[j].r_subname, record[j].r_phone);
        }
        fprintf(f, "\n\t|_______________________________________________________|");
    }
    fprintf(f, "\n");
    fclose(f);
    printf("\n\tЗагрузка телефонной книги в файл %s успешно завершена."
            "\n\tПросмотреть телефонную книгу?", name);
    free(name);

    char choice;
    printf("\n\tда    - 1"
           "\n\tнет   - 2");
    choice = getAnswer('1', '2');
    if(choice == '1')
        printDialer(PhoneBook);
}
