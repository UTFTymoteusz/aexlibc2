#pragma once

int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

#define _toupper(a) (((a >= 'a') && (a <= 'z')) ? (a - 32) : a)
#define _tolower(a) (((a >= 'A') && (a <= 'Z')) ? (a + 32) : a)