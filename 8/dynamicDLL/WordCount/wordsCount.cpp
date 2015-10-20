#include "wordsCount.h"
#include <wchar.h>

int WordsCount( const wchar_t* text ) {
	int wordsNumber = 0;
	int textLength = wcslen(text);
	bool isWord = false;
	
	for (int i = 0; i < textLength; ++i) {
		if (iswalnum(*(text + i)) != 0) {
			isWord = true;
		} else if (isWord) {
			isWord = false;
			++wordsNumber;
		}
	}

	if (isWord) {
		++wordsNumber;
	}

	return wordsNumber;
}

