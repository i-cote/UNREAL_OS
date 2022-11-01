#include <stdint.h>

#define NULL ((void *)0)

char *strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++) != '\0')
        /* nothing */;
	return tmp;
}

char *strncopy(char *dest, const char *src, uint32_t n) {
    char *tmp = dest;
    while (n-- && (*dest++ = *src++) != '\0')
        /* nothing */;
    return tmp;
}

int strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, uint32_t n){
    while (n-- && *s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strtol(const char *str, char **endptr, int base) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str != '\0') {
        result *= base;
        if (*str >= '0' && *str <= '9') {
            result += *str - '0';
        } else if (*str >= 'a' && *str <= 'f') {
            result += *str - 'a' + 10;
        } else if (*str >= 'A' && *str <= 'F') {
            result += *str - 'A' + 10;
        } else {
            break;
        }
        str++;
    }
    if (endptr != NULL) {
        *endptr = (char *)str;
    }
    return result * sign;
}

//https://aticleworld.com/implement-strtok-function-in-c/
unsigned int is_delim(char c, char *delim)
{
    while(*delim != '\0')
    {
        if(c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

//https://aticleworld.com/implement-strtok-function-in-c/
char *my_strtok(char *srcString, char *delim)
{
    static char *backup_string; // start of the next search
    if(!srcString)
    {
        srcString = backup_string;
    }
    if(!srcString)
    {
        // user is bad user
        return NULL;
    }
    // handle beginning of the string containing delims
    while(1)
    {
        if(is_delim(*srcString, delim))
        {
            srcString++;
            continue;
        }
        if(*srcString == '\0')
        {
            // we've reached the end of the string
            return NULL; 
        }
        break;
    }
    char *ret = srcString;
    while(1)
    {
        if(*srcString == '\0')
        {
            /*end of the input string and
            next exec will return NULL*/
            backup_string = srcString;
            return ret;
        }
        if(is_delim(*srcString, delim))
        {
            *srcString = '\0';
            backup_string = srcString + 1;
            return ret;
        }
        srcString++;
    }
}