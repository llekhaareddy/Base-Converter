#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "NewTypeDef.h"
/*
Lekha Reddy
Base Calculator 
Displays values in octal, hex, binary, and decimal representations. Performs certain bit-wise and arithmetic options.
*/

/*takes a binary string and returns
the unsigned short value that it is equivalent to*/
unsigned short get_binary_op(bin_str bin)
{
    unsigned short value = 0;
    int bits = strlen(bin) - 1;
    int power = 1;
    int i;
    /*for loop adds power to value whenever bit is 1*/
    for(i = bits; i >= 0; i--)
    {
        if (bin[i] == '1'){
            value += power;
        }
        power *= 2;
    }
return value;
}

/* this function converts a given unsigned short value to 
its equivalent binary form as a bin_str type*/
void convert_to_binary(short val, bin_str bin)
{
    unsigned short value = val;
    int i;
    int power = 32768;
    /*for loop walks through the passed in
    binary string from left to right*/
    for (i = 0; i < strlen(bin); i++){
        /* insert spacing */
        if((i + 1)%5 == 0){
            bin[i] = ' ';
        }
        /* inserts 1's and 0's */
        else{
            if (value >= power){
                bin[i] = '1';
                value -= power;  
    }
            else{
                bin[i] = '0';
            }
        power /= 2;
        }
    }
}  

/*prints menu and returns the option chosen by the user */
char print_menu(void)
{
    char valid_input[17] = "BOHDSCQ&|^~<>+-N"; 
    char input_option[10] = "D";
    char cap_input_option;
    int valid = 0;
    while (valid == 0)
    {
    printf("\n");
    printf("Please select one of the following options: \n");
    printf("\n");
    printf("B  Binary Mode             &  AND with Value           +  Add to Value\n");
    printf("O  Octal Mode              |  OR  with Value           -  Subtract from Value\n");
    printf("H  Hexadecimal Mode        ^  XOR with Value           N  Negate Value\n");
    printf("D  Decimal Mode            ~  Complement Value\n");
    printf("\n");
    printf("C  Clear Value       <  Shift Value Left\n");
    printf("S  Set Value         >  Shift Value Right\n");
    printf("\n");
    printf("Q  Quit \n");
    printf("\n");
    printf("Option: ");
    scanf(" %s", input_option);
    /*makes chosen option an uppercase character*/
    cap_input_option = toupper(input_option[0]);
    if (!strchr("Q", cap_input_option))
        printf("%s\n", input_option);
    else{
        printf("%s", input_option);
    }
    /*checks if option chosen is valid or invalid*/
    if (strlen(input_option) == 1 && strchr(valid_input, cap_input_option)){
        valid = 1;
    }
    else{
        printf("\n\nInvalid option: %s\n", input_option);
        valid = 0;
    }
    }

return cap_input_option;
}

/* prints the box above the menu that holds the conversions */
void print_bases(short val, char mode)
{
 
    bin_str bin_val = "0000000000000000000";    
    convert_to_binary(val, bin_val);
    char mode_string[4] = "Dec";

    /* changes string that indicates the mode */
    if(mode == 'D')
        strcpy(mode_string,"Dec");
    if(mode == 'H')
        strcpy(mode_string,"Hex");
    if(mode == 'O')
        strcpy(mode_string,"Oct");
    if(mode == 'B')
        strcpy(mode_string,"Bin");

    printf("\n");
    printf("****************************************\n");
    printf("* Base Values:         Input Mode: %s *\n", mode_string);
    printf("*   Binary  :  %s     *\n", bin_val);
    printf("*   Hex     :  %04hX                    *\n", val);
    printf("*   Octal   :  %06ho                  *\n", val);
    printf("*   Decimal :  %-10hd              *\n", val);
    printf("****************************************\n");
}

/* scans the number input by the user and interprets it based 
on the mode */
short get_operand(char mode)
{
    short op_val;
    bin_str bin_holder;

    if(mode == 'B'){
    scanf("%s", bin_holder);
    printf("%s\n", bin_holder);
    op_val = get_binary_op(bin_holder);
    }

    if(mode == 'H'){
    scanf("%hX", &op_val);
    printf("%hX\n", op_val);
    }

    if(mode == 'O'){
    scanf("%06ho", &op_val);
    printf("%ho\n", op_val);
    }

    if(mode == 'D'){
    scanf("%hd", &op_val);
    printf("%hd\n", op_val);
    }
    return op_val;  
}


/* gets value that user wants to add and adds it
to the current value */
void add(short *val, char mode)
{
short new_val;
short value;

value = *val;
new_val = get_operand(mode);
*val += new_val;

/* detecting for overflow */
if (new_val > 0 && value > 0 && *val < 0){
    printf("Positive Overflow\n");
}

if (new_val < 0 && value < 0 && *val > 0){
    printf("Negative Overflow\n");
}
}
    
/* gets the value that the user wants to subtract
and subtracts it from the current value */
void subtract(short *val, char mode)
{
short value;
short new_val;

value = *val;
new_val = get_operand(mode);
*val -= new_val;

/* detecting for overflow */
if (new_val > 0 && value < 0 && *val >0){
    printf("Negative Overflow\n");
}
if (new_val < 0 && value > 0 && *val <0){
    printf("Positive Overflow\n");
}
}

/* sets global variables */ 
int main(void) {
    short val = 0;
    char option;
    char mode = 'D';
    bin_str bin[20];
    int positions;
    short second_val;

while(1)
{

  print_bases(val, mode);
 
    option = print_menu();    
    char modetype[20];
    /* cases for user input */
   switch(option){
        case 'D':
            mode = 'D';
            strcpy(modetype, "decimal");
            printf("Mode is Decimal\n");
            break;
        case 'B':
            mode = 'B';
            strcpy(modetype, "binary");
            printf("Mode is Binary\n");
            break;
        case 'H':
            mode = 'H';
            strcpy(modetype, "hex");
            printf("Mode is Hexadecimal\n");
            break;
        case 'O':
            mode = 'O';
            strcpy(modetype, "octal");
            printf("Mode is Octal\n");
            break;
        case 'C':
            val = 0;
            break;
        case 'S':
            if (strlen(modetype) == 0)
                strcpy(modetype, "decimal");
            printf("Enter %s value: ",modetype);
            val = get_operand(mode);
            break;
        case 'Q':
            return 0;
        case '&':
            printf("Enter %s value: ", modetype);
            val &= get_operand(mode);
            break;
        case '|':
            printf("Enter %s value: ", modetype);
            val |= get_operand(mode);
            break;
        case '^':
            printf("Enter %s value: ", modetype);
            val ^= get_operand(mode);
            break;
        case '~':
            val = ~val;
            break;
        case '<':
            printf("Enter number of positions to left shift value: ");
            scanf("%d", &positions);
            printf("%d\n", positions);
            val <<= positions;
            break;
        case '>':
            printf("Enter number of positions to right shift value: ");
            scanf("%d", &positions);
            printf("%d\n", positions);
            val >>= positions;
            break;
        case '+':
            printf("Enter %s value: ", modetype);
            add(&val, mode);
            break;
        case '-':
            printf("Enter %s value: ", modetype);
            subtract(&val, mode);
            break;
        case 'N':
            val = val * -1;
            break;

    }
}
    return 0;
}
