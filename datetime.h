#ifndef DATETIME_H_
#define DATETIME_H_

#include <time.h>


typedef struct tm datetime;





extern int datetime_cmp(const datetime* date1, const datetime* date2);

extern datetime* datetime_parse(char* datetimeStr);



#endif /* DATETIME_H_ */
