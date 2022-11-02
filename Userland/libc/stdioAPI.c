
#include <stdarg.h>
#include <stdint.h>
#include <syscallsAPI.h>
#include <string.h>
#include <stdioAPI.h>
#include <stdio.h>
#include <color.h>

// Prints a character to the screen
// Arguments: character to print
void putChar(char c) {
    sys_write_asm(STDOUT, &c, 1, white);
    return;
}


// Returns a character pressed by the user
char getChar() {
    char c[2] = {0};
	//We are going to read only one character
	//Fd is one because we are reading from keyboard
    __uint64_t count = sys_read_asm(1,c,1);
	if(count)
    	return c[0];
	else
		return -1;
}

// Prints on screen a string with a given color
// Arguments: string to print, color, and variable number of arguments to format the string
// Returns: number of characters printed
int printfColor(const char* str, Color color, ...) {
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
    sys_write_asm(1,buff,j,color);
    va_end(vl);
    return j;
}

// Reads a string from the keyboard
// Arguments: string to format, and variable number of arguments to format the string
// Returns: number of characters read
int scanf(const char* str, ...) {
    va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0};
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
				case 's':
				{
					char * str = va_arg( vl, char *);
					strcpy(str, &buff[j]);
					j += strlen(str);
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

// Implementation of itoa(). Converts an integer to a string
// Arguments: number to convert, string to store the result, base
// Returns: string with the number converted
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
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
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

// Clears the screen
void clearScreen() {
	sys_print_asm(3,0,0);
}

/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}