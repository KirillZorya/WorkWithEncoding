#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <locale.h>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <codecvt>

using namespace std;

#ifdef UNICODE
typedef	wchar_t	TCHAR;
#define	TEXT(a)	L##a
#else
typedef char TCHAR;
#define TEXT(a)	a
#endif

int compare(const void* a, const void* b);
void output_for_6_8(char* input, wchar_t* w_input, TCHAR* enc, int size);
void output_for_9_11(char* input, wchar_t* w_input);
void output_for_12(std::string enc);
std::string readFile(const char* filename);
std::wstring readFile_W(const char* filename);

// output function for tasks from 6 to 8
void output_for_6_8(char* input, wchar_t* w_input, TCHAR* enc, int size) {
	std::cout << "Розмiр одного символу: " << size * 8 << " бiт" << std::endl;
	_tprintf(TEXT("Викоритстане кодування: %s"), enc);
	std::wcout << L"\nВивiд на стандартний потiк виведення ASCII рядка: " << std::endl;
	std::cout << input << std::endl;
	std::cout << "\nВивiд на стандартний потiк виведення UNICODE рядка: " << std::endl;
	std::wcout << w_input << std::endl;
	std::cout << "\nВивiд в консоль UNICODE рядка за допомогою функцiї _tprintf()" << std::endl;
	_tprintf(TEXT("%s"), w_input);
	std::cout << "\nВивiд тексту у вiкно повiдомлення" << std::endl;
	MessageBox(0, w_input, L"Output", MB_OK);
}

// delegate function for comparison in sort functions
int compare(const void* a, const void* b)
{
	return (*(wchar_t*)a - *(wchar_t*)b);
}

// output function for tasks from 9 to 11
void output_for_9_11(char* input, wchar_t* w_input) {
// sorting string w_input, using qsort and sort functions
qsort(w_input, wcslen(w_input), sizeof(wchar_t), compare);
std::sort(w_input, w_input + (wcslen(w_input)));
std::cout << "\nВивiд в консоль вiдсортованого UNICODE рядка" << std::endl;
std::wcout << w_input << std::endl;

// translation UNICODE string into ASCII string
WideCharToMultiByte(CP_ACP, 0, w_input, -1, input, wcslen(w_input), "", NULL);
std::cout << "\nВивiд в консоль вiдсортованого UNICODE рядка, що був перетворений в ASCII" << std::endl;
std::cout << input << std::endl;
}

// output function for task 12
void output_for_12(std::string enc) {

	char file[] = "test.txt";

	if (enc == "ASCII") {
		std::string text;
		text = readFile(file);
		std::cout << text << std::endl;

		std::reverse(text.begin(), text.end());
		std::cout << text << std::endl;

		std::ofstream out;
		out.open(file, std::ios::app);

		out << "\n" << text << std::endl;
		out.close();
	}
	else if (enc == "UTF-8") {
		std::wstring w_text;
		w_text = readFile_W(file);
		std::wcout << w_text << std::endl;

		std::reverse(w_text.begin(), w_text.end());
		std::wcout << w_text << std::endl;

		std::wofstream out;
		out.open(file, std::ios::app);
		out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

		out << "\n" << w_text << std::endl;
		out.close();
	}
	
}

// read from file with ASCII encoding
std::string readFile(const char* filename) {
	std::fstream fs(filename);
	fs.imbue(std::locale("Ukrainian"));
	std::stringstream wss;
	wss << fs.rdbuf();
	return wss.str();
}
// read from file with UTF-8 encoding
std::wstring readFile_W(const char* filename) {
	std::wfstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}

int main()
{
	//setting locale
	_tsetlocale(LC_ALL, TEXT("Ukrainian"));
	
	cout << "Task 2:" << endl;
	//statements to check the default encoding type
	char ASCIIchar = '121',
		ASCIIarray[] = "abc";
	wchar_t unicodechar = L'a', unicodearray[] = L"abcde";
	TCHAR univchar = _T('a'), univarray[] = _T("abcde");

	printf("Розмiр унiверсального символу: %d\nРозмiр унiверсального масиву: %d\n\n", sizeof(univchar), sizeof(univarray));
	
	cout << "Task 6-8:" << endl;
	// input data in generic format
	TCHAR* t_input = new TCHAR[128];
	_tcscpy(t_input, TEXT("\n\tПашкевич Кирило Олександрович \n\tПашкевич Олександр Васильович \n\tПашкевич Тетяна Володимиривна"));

	// input data in ASCII format
	char* input = new char[128];
	strcpy(input, "\n\tПашкевич Кирило Олександрович \n\tПашкевич Олександр Васильович \n\tПашкевич Тетяна Володимиривна");

	// input data in UNICODE format
	wchar_t* w_input = new wchar_t[strlen(input) + 1];
	MultiByteToWideChar(CP_ACP, 0, input, -1, w_input, strlen(input) + 1);

	// symbol size
	int size = sizeof(TCHAR);

	// used encoding
	TCHAR* enc = new TCHAR[16];
	if (size == 1) {
		_tcscpy(enc, TEXT("ASCII"));
	}
	else {
		_tcscpy(enc, TEXT("UNICODE"));
	}

	//calls of functions
	output_for_6_8(input, w_input, enc, size);
	output_for_9_11(input, w_input);
	output_for_12("ASCII");
}