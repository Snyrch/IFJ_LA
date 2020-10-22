// lexikalni analyzator
#include <stdio.h>
#include <ctype.h>
#include "str.h"
#include "scaner.h"


int getNextToken(string *attr)
// hlavni funkce lexikalniho analyzatoru
{
	int state = 0;
	int c;
  //int comment_bool = 0;
  
	// vymazeme obsah atributu a v pripade identifikatoru
	// budeme postupne do nej vkladat jeho nazev
	strClear(attr);
	while (1)
	{
		// nacteni dalsiho znaku
		c = getchar();

		switch (state)  
		{
		case 0:
      if (c == '\n')
        return END_OF_LINE;
			// zakladni stav automatu
			if (isspace(c))
				// bila mista - ignorovat
				state = 0;
			else if (c == '/')
      {
				// komentar
        state = 1;
      }	
			else if((isalpha(c)) || (c == '_'))
			// identifikator nebo klicove slovo
			{
				strAddChar(attr, c);
				state = 5;
			}
      else if (isdigit(c))
      {
				strAddChar(attr, c);
        state = 8;
      }
      else if (c == '"')
      {
        state = 9;
      }
      else if (c == '!')
      {
        state = 10;
      }
      else if (c == '<')
      {
        state = 11;
      }
      else if (c == '>')
      {
        state = 12;
      }
			else if (c == ':')
				// operator :=
				state = 6;
			else if (c == '=')
				// operator ==
				state = 7;
      else if (c == '+')
        return PLUS;
      else if (c == '-')
        return MINUS;
      else if (c == '*')
        return MULTIPLY;
      else if (c == ';')
        return SEMICOLON;
      else if (c == ',')
        return COMA;
			else if (c == '{')
				return LEFT_VINCULUM;
			else if (c == '}')
				return RIGHT_VINCULUM;
      else if (c == '[')
				return LEFT_BRR;
			else if (c == ']')
				return RIGHT_BRR;
      else if (c == '(')
				return LEFT_BR;
			else if (c == ')')
				return RIGHT_BR;
			else if (c == EOF)
				return END_OF_FILE;
			else
				return LEX_ERROR;

			break;
    case 1:
      // rozcestnik pro '/'
      if (c == '/') {
        state = 2;
      }
      else if (c == '*') {
        state = 3;
      }
      else {
        ungetc(c, stdin);
        return  DIVIDE; 
      }

		case 2:
			// komentar na jeden rade
			if (c == '\n')
				state = 0;
			else
					// komentar pokracuje libovolnymi znaky, zustan ve stavu 1,
					// ale kontroluj, zda neprijde EOF (neukonceny komentar)
					if (c == EOF) return LEX_ERROR;
			break;

    case 3:
      // vice radkovy komentar
      if (c == '*') {
        state = 4;
      }
      else
					// komentar pokracuje libovolnymi znaky, zustan ve stavu 1,
					// ale kontroluj, zda neprijde EOF (neukonceny komentar)
					if (c == EOF) return LEX_ERROR;
			break;
    
    case 4:
      // konec viceradkoveho komentare
      if (c == EOF) return LEX_ERROR;
      if (c == '/') {
        state = 0;
      }
      else {
        state = 3;
      }
      break;

		case 5:
			// identifikator nebo klicove slovo
			if (isalnum(c))
				// identifikator pokracuje
				strAddChar(attr, c);
			else
			// konec identifikatoru
			{
        //vrati posledni znak zpet do fronty
        ungetc(c, stdin);
				// kontrola, zda se nejedna o klicove slovo
				if (strCmpConstStr(attr, "else") == 0)
					return ELSE;
				else if (strCmpConstStr(attr, "float64") == 0)
					return FLOAT64;
				else if (strCmpConstStr(attr, "for") == 0)
					return FOR;
				else if (strCmpConstStr(attr, "func") == 0)
					return FUNC;
				else if (strCmpConstStr(attr, "if") == 0)
					return IF;
				else if (strCmpConstStr(attr, "int") == 0)
					return INT;
				else if (strCmpConstStr(attr, "package") == 0)
					return PACKAGE;
				else if (strCmpConstStr(attr, "return") == 0)
					return RETURN;
				else if (strCmpConstStr(attr, "string") == 0)
					return STRING;
				else
					// jde o identifikator
					return ID;
			}
			break;

		case 6:
			// pokracovani operatoru ++
			if (c == '=')
				return ASSIGN;
			else
				return LEX_ERROR;
			break;

		case 7:
			// pokracovani operatoru = nebo ==
			if (c == '=')
				return DOUBLE_EQUAL;
			else
      {
        ungetc(c, stdin);
        return EQUAL;
      }
			break;

    case 8:
      // cisla
      if (isdigit(c)) 
      {
				// cislo pokracuje
				strAddChar(attr, c);
      }
      else
      {
        ungetc(c, stdin);
        return NUM;
      }
      break;

    case 9:
      // text mezi " "
        if (c == '"') 
        {
         return TEXT; 
        }
        else if (c == '\\') 
        {
          //strAddChar(attr, c);
          state = 13;
        }
        else
        {
         strAddChar(attr, c);
        }
        break;

    case 10:
      // !=
      if (c == '=') 
        return NOT_EQUAL; 
      else
        return LEX_ERROR;
      break;

    case 11:
      // !=
      if (c == '=') 
        return LESS_AND_EQUAL; 
      else
        return LESS;
      break;

    case 12:
      // !=
      if (c == '=') 
        return GREAT_AND_EQUAL; 
      else
        return GREAT;
      break;

    case 13:
      // !=
      if (c == 'n')
      {
        strAddChar(attr, '\n');
        state = 9;
      }
      else if (c == '\\')
      {
        strAddChar(attr, '\\');
        state = 9;
      }
      else if (c == 't')
      {
        strAddChar(attr, 't');
        state = 9;
      }
      else if (c == '"')
      {
        strAddChar(attr, '"');
        state = 9;
      }
      else 
        return LEX_ERROR;
      break;

		}
	}
}