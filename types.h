#ifndef _TYPES_H_
#define _TYPES_H_

// #define int8_t signed char
// #define uint8_t unsigned char
// #define int16_t signed short
// #define uint16_t unsigned short
// #define int32_t signed long
// #define uint32_t unsigned long

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;

#define LEFT_SHIFT( var, bits )   ((var) << (bits))
#define RIGHT_SHIFT( var, bits )  ((var) >> (bits))
//#define BIT_STATE( var, bit )     ((var) >> ((bit) & 1)) 
#define BIT_STATE( var, bit )     ((((var) >> (bit)) & 1) != 0 ? 1 : 0)
#define BIT_SET( var, bit )       ((var) |= ( 1 << (bit)))
#define BIT_RESET( var, bit )     ((var) &= ~(1 << (bit)))
#define BIT_INVERT( var, bit )    ((var) ^= ( 1 << (bit)))
#define _delay( cuentas )         for(uint32_t cDelay = 0 ; cDelay < (cuentas) ; cDelay++)

#endif