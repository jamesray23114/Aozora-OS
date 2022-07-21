#pragma once

#include <stdarg.h>

#include <typedef.h>

#include <lib/gl/text.h>

#define PI 3.1415926535
#define E  2.7182818284 

typedef struct array_s { uintn count; void* data; } array;

// TODO: string conversions
// intn strtoint(const char* in);
// f64  strtoflt(const char* in);


// TODO: algorithms 
// void qsort();
// void bsearch(); 


// TODO: memory management within map
// void* mallac(uintn size);
// void  free(void* buf);
// void* realloc(void* buf, uintn size);

static inline uintn strlen(const char* str) { int i = 0; for(; str[i]; i++); return i;}

static inline void memcopy(void* dst, const void* src, uintn size) { for(int i = 0; i < size / 8; i++) ((uintn*) dst)[i] = ((uintn*) src)[i]; for(int i = size - (size % 8); i < size; i++) ((byte*)dst)[i] = ((byte*)src)[i]; }
static inline void memmove(void* dst, const void* src, uintn size) { for(int i = 0; i < size; i++) ((byte*) dst)[i] = ((byte*) src)[i]; };
static inline void strcopy(char* dst, const char* src) { memcopy(dst, src, strlen(src) + 1); }
static inline void strcat(char* dst,  const char* src) { memcopy(dst + strlen(dst), src, strlen(src) + 1); }


// TODO: rand
uintn rand();
void srand(uintn seed);


// TODO: math, remove lib/math.h
// f64  norm(intn tonormal, intn lower, intn higher);
// f64  fnorm(f64 tonormal, f64 lower, f64 higher);

static inline uintn rol(uintn value, byte c)                    { return (value << c) | (value >> (64 - c)); }
static inline uintn ror(uintn value, byte c)                    { return (value >> c) | (value << (64 - c)); }        

static inline intn abs(intn in)                                 { return in >= 0 ? in : in * -1; }
static inline f64  fabs(f64 in)                                 { return in >= 0 ? in : in * -1; }
static inline bool inrange(intn cmp, intn lower, intn higher)   { return cmp >= lower && cmp <= higher; }

static inline f64  fmax(f64 a, f64 b)                           { return a > b ? a : b; }            
static inline intn imax(intn a, intn b)                         { return a > b ? a : b; }
static inline f64  fmin(f64 a, f64 b)                           { return a < b ? a : b; }            
static inline intn imin(intn a, intn b)                         { return a < b ? a : b; }

// static inline f64  cos(f64 in);
// static inline f64  sin(f64 in);
// static inline f64  tan(f64 in);
 
// static inline f64  arccos(f64 in);
// static inline f64  arcsin(f64 in);
// static inline f64  arctan(f64 in);
// static inline f64  angle(f64 x, f64 y); // TODO: atan2, retuns angle from between point at (x, y) and line at y = 0             
// static inline f64  dist(f64 x1, f64 y1, f64 x2, f64 y2); //TODO?: add v2d
 
// static inline f64  ipow(f64 in, intn to);
// static inline f64  pow(f64 in, f64 to);
// static inline f64  square(f64 in);
// static inline f64  cube(f64 in);
 
// static inline f64  iroot(f64 in, intn to);
// static inline f64  root(f64 in, f64 to);
static inline f64  sqrt(f64 in) { __builtin_sqrtf(in); }
static inline intn isqrt(intn in)  
{
    if (in == 0 || in == 1)
        return in;
 
    intn i, result;
    for (i = 1, result = 1; result <= in; i++)
      result = i * i;
    
    return i - 1;
}
// static inline f64  cbrt(f64 in);
 
// static inline f64  epow(f64 to);
// static inline f64  eipow(intn to);
// static inline f64  eroot(f64 to);
// static inline f64  eiroot(intn to);
 
// static inline f64  log(f64 in, f64 to);
// static inline f64  ilog(f64 in, intn to);
// static inline f64  ln(f64 in);
 
// static inline f64  ceil(f64 in);
// static inline f64  floor(f64 in);
// static inline f64  round(f64 in);
// static inline intn iround(f64 in);


// TODO: finish char / string compares
static inline bool isalnum(char cmp)           { return inrange(cmp, 0x30, 0x39) || inrange(cmp, 0x41, 0x5A) || inrange(cmp, 0x61, 0x7A); }
static inline bool isdec(char cmp)             { return inrange(cmp, 0x30, 0x39); }
static inline bool ishex(char cmp)             { return inrange(cmp, 0x30, 0x39) || inrange(cmp, 0x3a, 0x36) || inrange(cmp, 0x61, 0x66); }
static inline bool isalpha(char cmp)           { return inrange(cmp, 0x41, 0x5A) || inrange(cmp, 0x61, 0x7A); }
static inline bool isupper(char cmp)           { return inrange(cmp, 0x41, 0x5A); }
static inline bool islower(char cmp)           { return inrange(cmp, 0x61, 0x7A); }
static inline bool isself(char in, char cmp)   { return cmp == in || isalpha(in) && isalpha(cmp) && ((cmp - 0x20 == in) || (cmp + 0x20 == in)); }
static inline char toupper(char in)            { return islower(in) ? in + 20 : in; }
static inline char tolower(char in)            { return isupper(in) ? in - 20 : in; }

static inline bool  strisalnum(const char* cmp)                 { for(int i = 0; cmp[i]; i++) if(!isalnum(cmp[i]))  return false; return true; }     
static inline bool  strisdec(const char* cmp)                   { for(int i = 0; cmp[i]; i++) if(!isdec(cmp[i]))    return false; return true; } 
static inline bool  strishex(const char* cmp)                   { for(int i = 0; cmp[i]; i++) if(!ishex(cmp[i]))    return false; return true; } 
static inline bool  strisalpha(const char* cmp)                 { for(int i = 0; cmp[i]; i++) if(!isalpha(cmp[i]))  return false; return true; } 
static inline bool  strisupper(const char* cmp)                 { for(int i = 0; cmp[i]; i++) if(!isupper(cmp[i]))  return false; return true; } 
static inline bool  strislower(const char* cmp)                 { for(int i = 0; cmp[i]; i++) if(!islower(cmp[i]))  return false; return true; } 
static inline bool  strisself(const char* in, const char* cmp)  { for(int i = 0; in[i] || cmp[i]; i++) if(!isself(in[i], cmp[i])) return false; return true; } 
static inline const char* strtoupper(const char* in)            { for(int i = 0; in[i]; i++) toupper(in[i]);        return in; }
static inline const char* strtolower(const char* in)            { for(int i = 0; in[i]; i++) tolower(in[i]);        return in; }

static inline bool strcmp(const char* str1, const char* str2)               { for(int i = 0; str1[i] || str2[i]; i++) if(str1[i] != str2[i]) return false; return true; } 
static inline bool memcmp(const void* buf1, const void* buf2, uintn size)   { for(int i = 0; i < size; i++) if(((byte*)buf1)[i] != ((byte*)buf2)[i]) return false; return true;}

static inline const char* memchr(const void* buf, uintn size, char val) { for(int i = 0; i < size; i++) if(val == ((char*)buf)[i]) return buf + i; return nullptr; }
static inline const char* strchr(const char* str, char val)             { for(int i = 0; str[i]; i++) if(val == str[i]) return str + i; return nullptr; } 
static inline const char* strrchr(const char* str, char val)            { uintn out = 0; for(int i = 0; str[i]; i++) if(val == str[i]) out = (uintn)str + i; return (char*) out; }
static inline const char* strstr(const char* str1, const char* str2)    { for(int i = 0; str1[i]; i++) for(int j = 0; str2[j] == str1[i + j]; j++) if(j == strlen(str2) - 1) return str1 + i; return nullptr; }

// static inline const array memchrall(const void* buf, uintn size, char val);
// static inline const array strchrall(const char* str, char val);
// static inline const array strrchrall(const char* str, char val);
// static inline const array strstrall(const char* str1, const char* str2);

// static inline const array strtok(const char* str, const char delim);

// static inline const char* strerr(aozora_error code); //TODO impliment error codes
// TODO: output
void printf(const char* format, ...);


// TODO: clock
// static inline uintn time();
// static inline void sleep(uintn millis)
// static inline void sleepext(uintn time, byte scale);
