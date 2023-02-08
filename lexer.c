/* front.c - a lexical analyzer for simple arithmetic expression */
#include <regex.h>
#include <stdio.h>
#include <ctype.h>

/*global declarations */
/* Variables */

int charClass;
char lexeme[100];
char nextChar; 
int lexLen; 
int token;
int nextToken;
int countLex = 0;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/*Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token Codes */
#define INT_LIT 10
#define FLOAT_LIT 11
#define IDENT 12
#define ASSIGN_OP 21
#define ADD_OP 20
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MODU 25
#define LEFT_PAREN 26
#define RIGHT_PAREN 27
#define LEFT_CURLY 28
#define RIGHT_CURLY 29
#define SEMICO 30
#define EQ 31
#define NOT_EQ 32
#define LESS_EQ 33
#define LESSTH 34
#define GRE_EQ 35
#define GRE 36
#define NO 37
#define START 38
#define END 39
#define IF_STMT 40
#define ELSE_STMT 41
#define WHILE_STMT 42
#define AAND 43
#define OOR 44
#define DOLLARS 45 
#define DOLLARSS 46
#define DOLLARSSS 47

/************************************************************/
/* main driver */
int main(void) {
    /* open the input data file and proces its contents */
    if((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }
    return 0;
}
/***********************************************************/
/* lookup - function to look up operators and parentheses 
    and return the token */
int lookup(char ch) {
    if (ch == 'lecture') {
        addChar();
        nextToken = START;
    } else if (ch == 'haha') {
        addChar();
        nextToken = END;
    } else if (ch == 'ha') {
        addChar();
        nextToken = IF_STMT;   
    } else if (ch == 'during') {
        addChar();
        nextToken = WHILE_STMT;
    } else if (ch == 'ehh') {
        addChar();
        nextToken == AAND;
    } else if (ch == 'uhh') {
        addChar();
        nextToken == OOR;
    } else if (ch == 'lol') {
        addChar();
        nextToken == ELSE_STMT;
    } else if (ch == '$') {
        addChar();
        nextToken == DOLLARS;
    } else if (ch == '$$') {
        addChar();
        nextToken == DOLLARSS;
    } else if (ch == '$$$') {
        addChar();
        nextToken == DOLLARSSS;
    }
    else {

    switch(ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')': 
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '=': 
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-': 
            addChar();
            nextToken = SUB_OP;
            break;
        case '*': 
            addChar();
            nextToken = MULT_OP;
        case '/':
            addChar();
            nextChar = DIV_OP;
            break;
        case '%':
            addChar();
            nextChar = MODU;
            break;
        case '{':
            addChar();
            nextChar = LEFT_CURLY;
            break;
        case '}':
            addChar();
            nextChar = RIGHT_CURLY;
            break;
        case ';':
            addChar();
            nextChar = SEMICO;
            break;
        case '!=':
            addChar();
            nextChar = NOT_EQ;
            break;
        case '==':
            addChar();
            nextChar = EQ;
            break;
        case '<=':
            addChar();
            nextChar = LESS_EQ;
            break;
        case '<':
            addChar();
            nextChar = LESSTH;
        case '>=':
            addChar();
            nextChar = GRE_EQ;
            break;
        case '>': 
            addChar();
            nextChar = GRE;
            break;
        case '!':
            addChar();
            nextChar = NO;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
    }
}

/************************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    } else
        printf("Error - lexeme is too long \n");
}

/************************************************************/
/* getChar - a function to get the next character of 
            input and determine its character class */
void getChar(void) {
    if ((nextChar = getc(in_fp)) != EOF) {
        if(isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else 
            charClass = UNKNOWN;
    }
    else 
        charClass = EOF;
}

/************************************************************/
/* getNonBlank - a function to call getChar until it returns
                a non-whitespace character */
void getNonBlank(void) {
    while (isspace(nextChar))
        getChar();
}

/************************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex(void) {
    lexLen = 0;
    getNonBlank();
    switch(charClass) {
        /* Identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Integer Literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            } 
            nextToken = INT_LIT;
            break;

        /* Parantheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case EOF: 
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = '\0';
            break;
    }   /* End of switch */
    countLex++;
    printf("Your program has %d lexemes!\n", countLex);
    printf("Next token is: %d, Next lexeme is %s\n",
    nextToken, lexeme);
    return nextToken;
} /* End of funtion lex */