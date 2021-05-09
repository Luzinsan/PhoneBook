#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define UNEXPECTED_ERROR -4
#define NUMBER_PAGES 30
#define CODE_UNSIGNED_LETTER_A 192

typedef struct
{
    char* r_subname;
    char* r_phone;
}RECORD;

typedef struct
{
    int p_countRec;
    RECORD *p_recording;
}PAGE;

typedef struct
{
    PAGE *d_pages;
}DIALER;


#endif // INCLUDES_H_INCLUDED
