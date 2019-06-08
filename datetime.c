#include "datetime.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define SHORT_MONTH_LEN 3U
#define MONTHS_COUNT 12U

static bool is_digit(char c);
static bool is_letter(char c);
static void moveStrPointerToNextDigit(char** ptr);
static uint8_t get2DigitFromStr(const char* str);
static uint8_t getMonthFromStr(const char* shortMonth);
static uint16_t getYearFromStr(const char* yearStr);


static const char shortMonths[MONTHS_COUNT][SHORT_MONTH_LEN] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};


int datetime_cmp(const datetime* date1, const datetime* date2)
{
    //TODO: do it better
    int result;

    if (date1->tm_year == date2->tm_year)
    {
        if (date1->tm_mon == date2->tm_mon)
        {
            if (date1->tm_mday == date2->tm_mday)
            {
                if (date1->tm_hour == date2->tm_hour)
                {
                    if (date1->tm_min == date2->tm_min)
                    {
                        if (date1->tm_sec == date2->tm_sec)
                        {
                            result = 0;
                        }
                        else
                        {
                            result = ((date1->tm_sec < date2->tm_sec) ? -1 : 1);
                        }
                    }
                    else
                    {
                        result = ((date1->tm_min < date2->tm_min) ? -1 : 1);
                    }
                }
                else
                {
                    result = ((date1->tm_hour < date2->tm_hour) ? -1 : 1);
                }
            }
            else
            {
                result = ((date1->tm_mday < date2->tm_mday) ? -1 : 1);
            }
        }
        else
        {
            result = ((date1->tm_mon < date2->tm_mon) ? -1 : 1);
        }
    }
    else
    {
        result = ((date1->tm_year < date2->tm_year) ? -1 : 1);
    }

    return result;
}

datetime* datetime_parse(char* datetimeStr)
{
    datetime* result = NULL;

    if (datetimeStr != NULL)
    {
        result = malloc(sizeof(datetime));
        moveStrPointerToNextDigit(&datetimeStr);
        result->tm_mday = get2DigitFromStr(datetimeStr);

        if (result->tm_mday != 255)
        {
            datetimeStr += 3;
            result->tm_mon = getMonthFromStr(datetimeStr);

            if (result->tm_mon < MONTHS_COUNT)
            {
                moveStrPointerToNextDigit(&datetimeStr);
                result->tm_year = getYearFromStr(datetimeStr);

                if (result->tm_year != 0)
                {
                    datetimeStr += 4;
                    moveStrPointerToNextDigit(&datetimeStr);
                    result->tm_hour = get2DigitFromStr(datetimeStr);

                    if (result->tm_hour != 255)
                    {
                        datetimeStr += 2;
                        moveStrPointerToNextDigit(&datetimeStr);
                        result->tm_min = get2DigitFromStr(datetimeStr);

                        if (result->tm_min != 255)
                        {
                            datetimeStr += 2;
                            moveStrPointerToNextDigit(&datetimeStr);
                            result->tm_sec = get2DigitFromStr(datetimeStr);

                            if (result->tm_sec == 255)
                            {
                                free(result);
                                result = NULL;
                            }
                        }
                        else
                        {
                            free(result);
                            result = NULL;
                        }
                    }
                    else
                    {
                        free(result);
                        result = NULL;
                    }
                }
                else
                {
                    free(result);
                    result = NULL;
                }
            }
            else
            {
                free(result);
                result = NULL;
            }
        }
        else
        {
            free(result);
            result = NULL;
        }
    }

    return result;
}


static bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static bool is_letter(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static uint8_t getMonthFromStr(const char* shortMonth)
{
    bool equal;
    size_t i;
    uint8_t result = 255;

    if (shortMonth[0] != '\0')
    {
        for (i = 0; i < MONTHS_COUNT; i++)
        {
            equal = true;

            for (size_t j = 0; j < SHORT_MONTH_LEN; j++)
            {
                if (shortMonth[j] == '\0' || shortMonth[j] != shortMonths[i][j])
                {
                    equal = false;
                    break;
                }
            }

            if (equal == true)
            {
                result = i;
                break;
            }
        }
    }

    return result;
}

static uint16_t getYearFromStr(const char* yearStr)
{
    uint16_t result = 0;

    if (is_digit(yearStr[0]) && is_digit(yearStr[1]) && is_digit(yearStr[2]) && is_digit(yearStr[3]))
    {
        result += (yearStr[0] - '0');
        result *= 10;
        result += (yearStr[1] - '0');
        result *= 10;
        result += (yearStr[2] - '0');
        result *= 10;
        result += (yearStr[3] - '0');
    }

    return result;
}

static uint8_t get2DigitFromStr(const char* str)
{
    uint8_t result = 255;

    if (is_digit(str[0]) && is_digit(str[1]))
    {
        result = 0;
        result += (str[0] - '0');
        result *= 10;
        result += (str[1] - '0');
    }

    return result;
}

static void moveStrPointerToNextDigit(char** ptr)
{
    while (**ptr != '\0' && is_digit(**ptr) == false)
    {
        (*ptr)++;
    }
}
