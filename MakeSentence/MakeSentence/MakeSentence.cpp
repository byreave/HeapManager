#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // _DEBUG

char * MakeSentence(const char * strings[])
{

}
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