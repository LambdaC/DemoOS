#ifndef __TYPES_H
#define __TYPES_H

/*
写OS时，有时候在乎的只是字节数，所以为了更直观地看到每个变量是多少位，可以定义一些类型别名
*/

typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

#endif