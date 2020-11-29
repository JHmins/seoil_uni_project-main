#ifndef __DATA_H
#define __DATA_H

typedef struct _data_t
{
    float temp;
    float humi;

}data_t;


extern data_t data;

void init_data(void);


#endif