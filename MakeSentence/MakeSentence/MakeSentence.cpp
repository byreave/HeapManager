// MakeSentence.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif // _DEBUG

const int MAX = 100;
char* MakeSentence(const char* _str[]);

void main(int i_argc, char ** i_argl)
{
	const char * strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	char * pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}

char* MakeSentence(const char* _str[]) {

	// length of valid value in the array
	size_t i_length = 0;
	for (size_t i = 0; i < MAX; i++)
	{
		if (_str[i] == NULL)
			break;
		i_length++;
	}

	size_t i_sizeBuffer = 0;
	int* i_sizeWord = new int[i_length];

	for (int i = 0; i < i_length; i++)
	{
		i_sizeWord[i] = 0;
	}

	for (size_t i = 0; i < i_length; i++)
	{
		for (size_t j = 0; j < MAX; j++)
		{
			char* temp = (char*)(_str[i]) + j;
			if (*temp == 0)
				break;
			i_sizeBuffer++;
			i_sizeWord[i] += 1;
		}
	}


	// space and end dot and terminal
	i_sizeBuffer += (i_length + 1);



	char* sentence =  (char*)malloc(i_sizeBuffer);
	size_t i_count =0;
	for (size_t i = 0; i < i_length; i++)
	{
		for (size_t j  = 0; j < i_sizeWord[i]; j++)
		{
			char* temp = (char*)(_str[i]) + j;
			
			*(sentence + j + i_count) = *temp;
		}
		i_count += (i_sizeWord[i] + 1);

		*(sentence + i_count-1) = ' ';
	}
	delete i_sizeWord;
	*(sentence + i_sizeBuffer - 2) = '.';
	*(sentence + i_sizeBuffer - 1) = '\0';

	

	return sentence;
}