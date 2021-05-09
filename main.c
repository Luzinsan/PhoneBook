
/*
    Телефонная книга. Разработка: 28.04.2021 - 09.05.2021, 2 семестр
    Выполнила студентка группы 430-2 Лузинсан Анастасия Александровна, ТУСУР, ФСУ.
*/


/**
    Структура:
    Доступ => Создать буфер книги => Выбрать действие:
    -> Создать новую книгу                                      => Работа - [Все действия над книгой выполняются в буфере] ~> Завершение
    -> Открыть телефонную книгу => Загрузить файл книги в буфер => Работа                                                  ~> Завершение
    -> Отказаться                                                                                                          ~> Завершение
    ...
    РАБОТА:
    Выбрать действие:                                                                                                      ~> Завершение
    -> Создать запись: Ввести фамилию и номер => Найти страницу => Добавить запись => Закончить? ~да~ > Выбрать действие...
                                                                                                 ~нет~>                    ~> Завершение
    -> Найти/обновить запись => Ввести фамилию => Найти запись => Выбрать действие(2):
                                                                                   ~~> Найти номер     => Выдать телефон   ~> Завершение
                                                                                   ~~> Изменить запись => Обновить         ~> Завершение
                                                                                   ~~> Удалить запись  => Удалить          ~> Завершение
    ...
    Завершение:
    -> Сохранить книгу? |-нет - КОНЕЦ
                        да
        -> Буфер изменялся |-нет - КОНЕЦ
                           да
            => Выгрузить буфер в файл => КОНЕЦ.
*/

#include "includes.h"
char getAnswer(char, char);
int CreateNewPhoneBook(DIALER*);
int OpenPhoneBook(DIALER*);
void Completion(DIALER*, int);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("\n\tВариант 1"
           "\n\tКаждой фамилии соответствует ровно один телефон."
           "\n\tКаждому телефону соответствует ровно одна фамилия\n");

    ///Создание буфера книги
    DIALER PhoneBook;
    PhoneBook.d_pages = (PAGE*)malloc(NUMBER_PAGES*sizeof(PAGE));
    for(int i = 0; i < NUMBER_PAGES; i++)
    {
        PhoneBook.d_pages[i].p_countRec = 0;
        PhoneBook.d_pages[i].p_recording = NULL;
    }
    char choice = '2';
    int changes = 0;
    while(true)
    {
        ///Выбрать действие
        printf("\n\n\t\tВыберите действие:"
               "\n\tСоздать новую книгу               - 1"
               "\n\tОткрыть телефонную книгу из файла - 2"
               "\n\tВыйти                             - 3");
        choice = getAnswer('1', '3');

        switch(choice)
        {
        case '1':
            printf("\n\t1 - Создание новой телефонной книги...");
            changes += CreateNewPhoneBook(&PhoneBook);
            continue;
        case '2':
            printf("\n\t2 - Открыть телефонную книгу из файла...\n");
            changes += OpenPhoneBook(&PhoneBook);
            continue;
        case '3':
            printf("\n\t3 - Выход");
            break;
        default:
            printf("\n\t\t\tError!");
            exit(UNEXPECTED_ERROR);
        }
        break;
    }
    Completion(&PhoneBook, changes);

    ///Освобождение памяти
    int countRec = 0;
    for(int i = 0; i < NUMBER_PAGES ; i++)
    {
        countRec = PhoneBook.d_pages[i].p_countRec;
        for(int j = 0; j < countRec; j++)
        {
            free(PhoneBook.d_pages[i].p_recording[j].r_phone);
            free(PhoneBook.d_pages[i].p_recording[j].r_subname);
        }
        free(PhoneBook.d_pages[i].p_recording);
    }
    free(PhoneBook.d_pages);
    getch();
    return 0;
}

void printDialer(DIALER *PhoneBook)
{
    unsigned char letter = 0;

    for(int i = 0; i < 30; i++, letter++)
    {
        if(letter==26 || letter==28)
           letter++;
        if(PhoneBook->d_pages[i].p_countRec == 0) continue;
        printf("\n\t_________________________________________________________"
               "\n\t|                  Страница №%-2d - буква %c               |"
               "\n\t|_______________________________________________________|", i+1, letter+192);
        for(int j = 0; j < PhoneBook->d_pages[i].p_countRec; j++)
        {
            printf("\n\t|%3d|%30s|%20s|", j+1, PhoneBook->d_pages[i].p_recording[j].r_subname,
                                               PhoneBook->d_pages[i].p_recording[j].r_phone);
        }
        printf("\n\t|_______________________________________________________|");
    }
}
