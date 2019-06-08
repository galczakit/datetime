#Simple example
```
#include <stdio.h>
#include "datetime.h"

static void printDate(const datetime* d);

int main()
{
    datetime* d1 = datetime_parse("06-Jun-2019 20:14:27");
    datetime* d2 = datetime_parse("06-Jun-2019 20:14:27");
    datetime* d3 = datetime_parse("07-Jun-2019 20:14:27");
    datetime* d4 = datetime_parse("10-Dec-2019 20:00:00");
    datetime* d5 = datetime_parse("10-Dec-2019 20:00:01");

    if (d1 == NULL || d2 == NULL || d3 == NULL || d4 == NULL || d5 == NULL)
    {
        printf ("Parse error\r\n");
        return 1;
    }

    printf ("d1 = {\r\n");
    printDate(d1);
    printf ("}\r\n\r\n");

    if (datetime_cmp(d1, d2) == 0)
    {
        printf ("d1 and d2 are equal\r\n");
    }

    if (datetime_cmp(d2, d3) == -1)
    {
        printf ("d2 is smaller than d3\r\n");
    }

    if (datetime_cmp(d3, d4) == -1)
    {
        printf ("d3 is smaller than d4\r\n");
    }

    if (datetime_cmp(d5, d4) == 1)
    {
        printf ("d5 is bigger than d4\r\n");
    }

    free(d1);
    free(d2);
    free(d3);
    free(d4);
    free(d5);
}

static void printDate(const datetime* d)
{
    printf(
        "day: %u\r\nmonth: %u\r\nyear: %u\r\nhour: %u\r\nminute: %u\r\nsecond: %u\r\n",
        d->tm_mday, d->tm_mon, d->tm_year, d->tm_hour, d->tm_min, d->tm_sec
    );
}

```
