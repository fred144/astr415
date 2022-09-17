#include <stdio.h>
#include <assert.h>

struct dates_s {
    int month;
    int day;
    int year;
};

void showdate(struct date_s *date)
{
    assert(date != NULL);
    (void) printf("Date = %02i/%02i/%4i\n",date->month,date->day,date->year);
}

void main(void)
{
    struct date_s date;

    date.month = 1;
    date.day = 27;
    date.year = 2004;
    showdate(&date);
}

// benchmark
// output to screen
// save screen output to a text file 