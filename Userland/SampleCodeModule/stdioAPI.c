
#include <stdarg.h>
#include <syscallsAPI.h>
#include <string.h>
#include <stdioAPI.h>


/*void putChar(char c) {
    printChar(c);
    return;
}
*/

char getChar() {
    char c[2] = {0};
    sys_read_asm(1,c,1);
    return c[0];
}


int printf(const char* str, ...) {
    va_list vl;
	int i = 0, j=0;
		char buff[100]={0}, tmp[20];
		va_start( vl, str ); 
		while (str && str[i])
		{
		  	if(str[i] == '%')
		  	{
 		    i++;
 		    switch (str[i]) 
 		    {
	 		    case 'c': 
	 		    {
	 		        buff[j] = (char)va_arg( vl, int );
	 		        j++;
	 		        break;
	 		    }
	 		    case 'd': 
	 		    {
	 		        itoa(va_arg( vl, int ), tmp, 10);
	 		        strcpy(&buff[j], tmp);
	 		        j += strlen(tmp);
		           break;
		        }
		        case 'x': 
		        {
		           itoa(va_arg( vl, int ), tmp, 16);
		           strcpy(&buff[j], tmp);
		           j += strlen(tmp);
		           break;
		        }
                case 's':
                {
                    char * str = va_arg( vl, char *);
                    strcpy(&buff[j], str);
                    j += strlen(str);
                    break;
                }
        	}
     	} 
     	else 
	    {
	       	buff[j] =str[i];
	       	j++;
	    }
	    i++;
	} 
    sys_write_asm(1,buff,j);
    va_end(vl);
    return j;
}

int scanf(const char* str, ...) {
    va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0}, tmp[20], c;
    char *out_loc;
    sys_read_asm(1,buff,100);
 	va_start( vl, str );
 	i = 0;
 	while (str && str[i])
 	{
 	    if (str[i] == '%') 
 	    {
 	       i++;
 	       switch (str[i]) 
 	       {
 	           case 'c': 
 	           {
	 	           *(char *)va_arg( vl, char* ) = buff[j];
	 	           j++;
	 	           ret ++;
	 	           break;
 	           }
 	           case 'd': 
 	           {
	 	           *(int *)va_arg( vl, int* ) =strtol(&buff[j], &out_loc, 10);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	            case 'x': 
 	            {
	 	           *(int *)va_arg( vl, int* ) =strtol(&buff[j], &out_loc, 16);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	        }
 	    } 
 	    else 
 	    {
 	        buff[j] =str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}

/* A utility function to reverse a string  */
void reverse(char * str, int length)
{
    int tmp;
    for(int i=0; i < length/2; i++)
    {
        tmp = str[i];
        str[i] = str[length-i-1];
        str[length-i-1] = tmp;
    }
}

void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
  
    return str;
}