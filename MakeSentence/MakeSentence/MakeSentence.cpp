#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // _DEBUG

char * MakeSentence(const char strings[][128])
{
	size_t size = 0;
	char * sentence = nullptr;
	for (size_t i = 0; strings[i][0] != '\0'; ++i)
	{
		for (size_t j = 0; strings[i][j] != '\0'; ++j)
		{
			size++;
		}
		size++; // for ' '
	}
	size++; //for '.'
	sentence = (char *)malloc(size);
	size_t index = 0;
	for (size_t i = 0; strings[i][0] != '\0'; ++i)
	{
		for (size_t j = 0; strings[i][j] != '\0'; ++j)
		{
			sentence[index++] = strings[i][j];
		}
		sentence[index++] = ' ';
	}
	sentence[index-1] = '.';
	sentence[index] = '\0';
	return sentence;
}
int main(int i_argc, char ** i_argl)
{
	
	const size_t bufferLength = 128;
	char strings[bufferLength][bufferLength] = {};
	unsigned int count = 0;

	while (1)
	{
		gets_s(strings[count++], bufferLength);
		if (strings[count - 1][0] == '\0')
			break;
	}

	char * pSentence = MakeSentence(strings);

	printf("The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}
