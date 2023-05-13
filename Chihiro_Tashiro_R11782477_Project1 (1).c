

/* Chihiro_Tashiro_R11782477_Project1.c - a lexical analyzer system for arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include<string.h>

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;
char*filename;
const char *tokenName[15];
const char name[30][15]={"LETTER","DIGIT", "UNKNOWN","INT_LIT","IDENT","ASSIGN_OP","ADD_OP","SUB_OP", "MULT_OP","DIV_OP","LEFT_PAREN","RIGHT_PAREN","EQUAL_OP","SEMICOLON","NEQUAL_OP","LEQUAL_OP","GEQUAL_OP","INC_OP","DEC_OP","KEY_READ","KEY_WRITE","KEY_WHILE","KEY_DO","KEY_OD","GREATER_OP","LESSER_OP"};

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
static int lookup(char ch);
int isKeyword(char *str);
const char* getTokenName(int num);
int lex();


/******************************************************/
/* main driver */
 int main(int argc, char**argv) 
{ 
    /* Open the input data file from the command line*/
   
  
   filename = argv[1];
   
   in_fp = fopen(filename,"r");

  
   if ( in_fp )
      {
        
        printf("DCooke Analyzer ::R11782477");
        printf("\n");
        getChar();
        do {
           lex();
            
        } while (nextToken != EOF); 
       }
   else
      {
         printf("Failed to open the file\n");
        }
 
     
 
     return 0;
    }  
 

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * nextToken */
static int lookup(char ch) {
  
    switch (ch) {
        case '(':
           addChar();
            nextToken = 25;
            break;
        case ')':
            addChar();
            nextToken = 26;
            break;
        case '+':
            addChar();
            getChar();
        
            if(nextChar=='+'){
               addChar();
               nextToken=32;
            }
            else {
            nextToken = 21;
            ungetc(nextChar, in_fp);
            }
            break;
        case '-':
            addChar();
            getChar();
     
            if(nextChar=='-'){
            addChar();
            nextToken=33;
            }
            else {
            nextToken = 22;
            ungetc(nextChar, in_fp);
            }
            break;
        case '*':
            addChar();
            nextToken = 23;
            break;
        case '/':
            addChar();
            nextToken = 24;
            break;
        case '=':
            addChar();
            nextToken=27;
            break;
        case ';':
            addChar();
            nextToken=28;
            break;
        case '>':
            addChar();
            getChar();
            if( nextChar=='='){
                addChar();
                nextToken=31;
            }
           
            else {
            nextToken=39;
            ungetc(nextChar, in_fp);
            }
            break;
        case '<':
            addChar();
            getChar();

            if(nextChar=='='){
                addChar();
                nextToken=30;
            }
            else {
            nextToken=40;
            ungetc(nextChar, in_fp);
            }
            break;
        case '!':
            addChar();
            getChar();
            if (nextChar=='='){
                addChar();
                nextToken=29;
            }
            else{
                ungetc(nextChar, in_fp);
                nextToken=99;
            }
            break;
        case ':':
            addChar();
            getChar();
            if(nextChar=='='){
                addChar();
                nextToken=20;
            }
           else{
                ungetc(nextChar, in_fp); 
                nextToken=99;
            }
              break;
        default:
            addChar();
            nextToken = 99;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() 
{
    if ((nextChar = fgetc(in_fp)) != EOF) 
    {
        if (isalpha(nextChar))
            charClass = 0;
        else if (isdigit(nextChar))
            charClass = 1;
       
        else {
            charClass = 99;
            
             }
    } 
    else {
        charClass = EOF;
         }
}
 
/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* getTokenName - a function to determine token besed on nextToken integer and returns a tokenname*/
const char* getTokenName(int num){
    switch (num)
     {
        case 0:
           return name[0];
        case 1:
           return name[1];
        case 10:
           return name[3];
        case 11:
           return name[4];
        case 20:
           return name[5];
        case 21:
           return name[6];
        case 22:
           return name[7];
        case 23:
           return name[8];
        case 24:
           return name[9];
        case 25:
           return name[10];
        case 26:
           return name[11];
        case 27:
           return name[12];
        case 28:
           return name[13];
        case 29:
           return name[14];
        case 30:
           return name[15];
        case 31:
           return name[16];
        case 32:
           return name[17];
        case 33:
           return name[18];
        case 34:
           return name[19];
        case 35:
           return name[20];
        case 36:
           return name[21];
        case 37:
           return name[22];
        case 38:
           return name[23];
        case 39:
           return name[24];
        case 40:
           return name[25];
        case 99:
            return name[2];
            break;
        
     }
    return 0;
}

/*****************************************************/
/* iskeyword - a function to lookup keywords and return the 
 * flag*/
 int isKeyword(char *str){
char keywords[6][10] = {"read","write","while","do","od", "while"};
int i, flag = 0;
for(i = 0; i < 6; ++i){
if(strcmp(str,keywords[i]) == 0){
flag = 1;
break;
}
}
return flag;
}

/*****************************************************/
/* lex - a lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case 0:
            addChar();
            getChar(); 
            while (charClass == 0 || charClass == 1)
            {
                addChar();
                getChar();
            }
            
            if (isKeyword(lexeme)==1)
            {
                if(strcmp(lexeme, "read")==0){
                nextToken=34;
                }
            else if (strcmp(lexeme, "write")==0){
                nextToken=35;
                }
            else if (strcmp(lexeme, "while")==0){
                nextToken = 36;
                }
            else if (strcmp(lexeme, "do")==0){
                nextToken = 37;  
                }
            else if (strcmp(lexeme, "od")==0){
                nextToken = 38;
                }
            break;
            }
            else nextToken = 11;
            break;

        /* Parse integer literals */
        case 1:
            addChar();
            getChar();
            while (charClass == 1) {
                addChar();
                getChar();
            }
            nextToken = 10;
            break;

        /* Parentheses and operators */
        case 99:
             lookup(nextChar);
             getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF; 
            break; 
    } /* End of switch */

    if(getTokenName(nextToken)!=NULL){
    printf("%s\t\t%s\n", lexeme, getTokenName(nextToken));}
    
    return nextToken;
} /* End of function lex */

