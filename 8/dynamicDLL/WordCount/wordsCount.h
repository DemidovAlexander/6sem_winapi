#ifdef WORDSCOUNT_EXPORTS
#define WORDSCOUNT_API __declspec(dllexport) 
#else
#define WORDSCOUNT_API __declspec(dllimport) 
#endif

extern "C" WORDSCOUNT_API int WordsCount( const wchar_t* text );