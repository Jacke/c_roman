/******************************************************
 Program to convert a decimal number to roman numerals
 * 
 * Enter a number: 1996
 * Roman numerals: mmxii
 * 
 ******************************************************/
 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

char * decimal_to_roman(int num) 
{   
    int rem;
    char * resultStorage = (char *) malloc(sizeof("mcmdcdcxclxlxixvivi"));
    char * result = resultStorage;
    //if((result = malloc(19+1)) != NULL){
    result[0] = '\0';
    //}
    // printf("Enter a number: ");
    // scanf("%d", &num);
    // printf("Roman numerals: ");        
    
    while(num != 0)
    {
    
        if (num >= 1000)       // 1000 - m
        {
           strcat(result, "m");
           num -= 1000;
        }
 
        else if (num >= 900)   // 900 -  cm
        {
           strcat(result, "cm");
           num -= 900;
        }        
 
        else if (num >= 500)   // 500 - d
        {           
           strcat(result, "d");
           num -= 500;
        }
 
        else if (num >= 400)   // 400 -  cd
        {
           strcat(result, "cd");
           num -= 400;
        }
 
        else if (num >= 100)   // 100 - c
        {
           strcat(result, "c");
           num -= 100;                       
        }
 
        else if (num >= 90)    // 90 - xc
        {
           strcat(result, "xc");
           num -= 90;                                              
        }
 
        else if (num >= 50)    // 50 - l
        {
           strcat(result, "l");
           num -= 50;                                                                     
        }
 
        else if (num >= 40)    // 40 - xl
        {
           strcat(result, "xl");           
           num -= 40;
        }
 
        else if (num >= 10)    // 10 - x
        {
           strcat(result, "x");
           num -= 10;           
        }
 
        else if (num >= 9)     // 9 - ix
        {
           strcat(result, "ix");
           num -= 9;                         
        }
 
        else if (num >= 5)     // 5 - v
        {
           strcat(result, "v");
           num -= 5;                                     
        }
 
        else if (num >= 4)     // 4 - iv
        {
           strcat(result, "iv");
           num -= 4;                                                            
        }
 
        else if (num >= 1)     // 1 - i
        {
           strcat(result, "i");
           num -= 1;                                                                                   
        }
    }
    return result;
}