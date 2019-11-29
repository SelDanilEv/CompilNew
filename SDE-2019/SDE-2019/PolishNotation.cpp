#include "pch.h"

using namespace std;

char intToChar(int x)
{
	switch (x)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default: return '\0';
	}
}

LT::Entry findOperator(LT::Entry *entry, short* priority, short count, short max)
{
	short currentPrior = max;
	short index = -1;
	while (index == -1)
	{
		for (int i = 0; i < count; i++) {

			if (priority[i] == currentPrior)
			{
				if (entry[i].used == false)
				{
					return entry[i];
				}
			}
		}
		currentPrior--;
	}
}




bool polishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
{
	short counter = 0;
	short buffershort;
	short countOfAllInputLex = 0;
	short countOfOperators;
	short countOfParameters = 0;
	bool isAFunction = false;
	int startLex = lextable_pos;
	do {
		countOfAllInputLex++;
		if (lextable.table[lextable_pos].lexema != LEX_LEFTTHESIS && lextable.table[lextable_pos].lexema != LEX_RIGHTTHESIS)
			counter++;
		if (lextable.table[lextable_pos].lexema == LEX_COMMA && lextable.table[lextable_pos - 2].lexema != LEX_LEFTTHESIS)
			counter++;
		lextable_pos++;
	} while (lextable.table[lextable_pos].lexema != LEX_SEMICOLON);

	LT::Entry bufferEntry;

	LT::Entry *AlmostAllEntries = new LT::Entry[32];
	short counter1 = 0;
	LT::Entry *inputOperEntries = new LT::Entry[16];
	short counter2 = 0;
	short *operatorPriority = new short[16];
	short currentPriority = 0;
	short maxPriority = 1;

	countOfOperators = 0;


	lextable_pos = startLex;
	buffershort = 0;

	for (int i = 0; (i < countOfAllInputLex + 1) || lextable.table[startLex + i - 1].lexema == LEX_SEMICOLON; i++)
	{
		if (lextable.table[startLex + i].lexema == LEX_ID)
			if (idtable.table[lextable.table[startLex + i].idxTI].idtype == IT::F)
				isAFunction = true;
		switch (lextable.table[lextable_pos + i].lexema)
		{
		case LEX_LEFTTHESIS:
			currentPriority = currentPriority + 2;
			if (maxPriority <= currentPriority)
				maxPriority = currentPriority + 1;
			continue;
		case LEX_RIGHTTHESIS:
			currentPriority = currentPriority - 2;
			continue;
		case LEX_OPERATOR:         // тут все v 
			inputOperEntries[counter2] = lextable.table[lextable_pos + i];
			operatorPriority[counter2] = currentPriority;
			inputOperEntries[counter2].index = buffershort;
			if (lextable.table[lextable_pos + i].value == '*' || lextable.table[lextable_pos + i].value == '/')
				operatorPriority[counter2]++;
			counter2++;

			AlmostAllEntries[counter1] = lextable.table[lextable_pos + i];
			AlmostAllEntries[counter1].index = buffershort;
			counter1++;
			buffershort++;
			countOfOperators++;
			continue;
		default:
			if (isAFunction)
			{
				countOfParameters = 0;
				bufferEntry = lextable.table[startLex + i];
				bufferEntry.lexema = '@';

				i++;

				while (lextable.table[lextable_pos + i].lexema != LEX_RIGHTTHESIS)
				{
					if (lextable.table[lextable_pos + i].lexema == LEX_LITERAL || lextable.table[lextable_pos + i].lexema == LEX_ID)
					{
						countOfParameters++;
						AlmostAllEntries[counter1] = lextable.table[lextable_pos + i];
						AlmostAllEntries[counter1].index = buffershort;
						AlmostAllEntries[counter1].used = true;
						counter1++;
						buffershort++;
					}
					i++;
				}
				AlmostAllEntries[counter1] = bufferEntry;
				AlmostAllEntries[counter1].index = buffershort;
				AlmostAllEntries[counter1].used = true;
				counter1++;
				buffershort++;
				bufferEntry.idxTI = -1;
				bufferEntry.used = true;
				bufferEntry.index = buffershort;
				bufferEntry.lexema = intToChar(countOfParameters);
				AlmostAllEntries[counter1] = bufferEntry;
				counter1++;
				buffershort++;
				isAFunction = false;
			}
			else
			{
				AlmostAllEntries[counter1] = lextable.table[lextable_pos + i];
				AlmostAllEntries[counter1].index = buffershort;
				if (AlmostAllEntries[counter1].lexema == LEX_SEMICOLON)
					AlmostAllEntries[counter1].used = false;
				counter1++;
				buffershort++;
			}
			break;
		}
	}
	if (currentPriority != 0)                         //ошибка неверно расставленны скобки
	{
		delete[] AlmostAllEntries;
		delete[] inputOperEntries;
		delete[] operatorPriority;
		return false;
	}
	int r = 0;
	while (r < countOfOperators)
	{
		bufferEntry = findOperator(inputOperEntries, operatorPriority, countOfOperators, maxPriority);
		AlmostAllEntries[bufferEntry.index - 1].used = true;
		AlmostAllEntries[bufferEntry.index].used = true;
		for (int i = 0; i < countOfOperators; i++)
			if (inputOperEntries[i].index == bufferEntry.index)
				inputOperEntries[i].used = true;
		if (AlmostAllEntries[bufferEntry.index + 1].used != true)          
		{
			AlmostAllEntries[bufferEntry.index + 1].used = true;
			AlmostAllEntries[bufferEntry.index] = AlmostAllEntries[bufferEntry.index + 1];
			bufferEntry.used = true;
			AlmostAllEntries[bufferEntry.index + 1] = bufferEntry;
		}
		else
		{
			int p = 1;
			while (AlmostAllEntries[bufferEntry.index + p].used == true)
			{
				AlmostAllEntries[bufferEntry.index + p - 1] = AlmostAllEntries[bufferEntry.index + p];
				p++;
			}
			bufferEntry.used = true;
			AlmostAllEntries[bufferEntry.index + p - 1] = bufferEntry;
		}
		r++;
	}

	for (int i = 0; (i < counter + 1) && AlmostAllEntries[i - 1].lexema != LEX_SEMICOLON; i++)
	{
		std::cout << AlmostAllEntries[i].lexema << AlmostAllEntries[i].value;
		lextable.table[startLex + i] = AlmostAllEntries[i];
		buffershort = i;
	}
	bufferEntry.idxTI = -1;
	bufferEntry.index = -1;
	bufferEntry.lexema = LATTICE;
	bufferEntry.used = false;
	bufferEntry.value = NULL;
	for (int k = buffershort + 1; k < countOfAllInputLex + 1; k++)
	{
		AlmostAllEntries[k] = bufferEntry;
		lextable.table[startLex + k] = bufferEntry;
	}
	delete[] AlmostAllEntries;
	delete[] inputOperEntries;
	delete[] operatorPriority;

	std::cout << NEWLINE;

	return true;
}