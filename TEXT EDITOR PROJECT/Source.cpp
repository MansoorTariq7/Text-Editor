#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int x = 0;

void filename(char*&);
void password(char*& checkpas);
bool check(char* checkpass, char* pas);
void input(ifstream&, char*&, int&);
void insert(char*&, char, int&);
void texteditor(char*&, int&, char*);
void findRowsCols(char*, int&, int&);
void insertAt(char*&, char, int&, int&);
void del(char*&, int, int&);
void save(char*, char*);
void FindAllOccWord(char*&, char*, int*&, int&);
char* lowercase(char*);
void FindAllOcc(char*&, char*, int*&, int&);
void ReplacingAWord(char*&, char*, char*, int&);
void ReplacingAllWords(char*&, char*, char*, int&);
void replace(char*&, char*, int, int&, int, int);
bool serchWord(char*& A, char* B, int counter);
void Prefeix(char*&, char*, char*, int&);
void Postfeix(char*&, char*, char*, int&);
void AddPrePostfeix(char*&, char*, int, int&, int, int);
void AvgWordlength(char*, int&, int&);
void SpecialCount(char*, int&);
void SentencesCount(char*, int&);
void LargestWord(char*, int&, int&, int&);
void mergefiles(char*&, int&, char*);
void SmallestWord(char*, int&, int&, int&);
char* alphabet(char* ch);
void Aword(char*, char*&, int&, int, int&);
void find(char* text, char* word, int wsize, int& count);
bool serchalpha(char* ch, char n);
char* Encode(char*&, int);
void Decode(char*&, int);
void Paragraphcount(char*, int&);
void LargestParagraph(char*, int&);
bool serch(char*, char*, int);
void expand(int*&, int&, int, int);
void bold(int*, int, char*);
void output(char*);
void resume(char&);
void set(char*&);
int subsize(char*);
void clear(int, int);
void firstocc(char*, char*, int&, int&, int&);
void firstocc1(char*, char*, int&, int&, int&);
void AllOccs(char*&, char*, int&);
char* DECODED(char*);
void menu();
void gotoRowCol(int, int);

int main()
{
	char choice = 0;
	bool Cchoice = true;

	do
	{
		char* ch = NULL;
		int size = 0;
		char* pas = NULL;
		int psize = 0;
		char* checkpas = NULL;
		char* docu = new char[20];

		/*while (true)
		{
			char ch = 0;
			if (_kbhit())
			{
				ch = _getch();
				cout << int(ch) << " ";
			}
		}*/

		filename(docu);
		ifstream file(docu);
		input(file, ch, size);

		ifstream pass("private.txt");
		input(pass, pas, psize);

		password(checkpas);

		if (check(checkpas, pas))
		{
			system("CLS");
			output(ch);
			texteditor(ch, size, docu);
			delete[] checkpas;
			delete[] pas;
		}
		else
		{
			gotoRowCol(15, 50);
			SetConsoleTextAttribute(h, 4);
			cout << "WRONG PASSWORD";
			SetConsoleTextAttribute(h, 7);
			while (!_kbhit());
			while (_kbhit())
			{
				x = _getch();
			}
			system("CLS");
		}
		resume(choice);
		if (choice == 'y' || choice == 'Y')
		{
			system("CLS");
		}
	} while (choice == 'y' || choice == 'Y');

	return 0;
}

void filename(char*& docu)
{
	bool check = true;

	while (check)
	{
		gotoRowCol(15, 30);
		SetConsoleTextAttribute(h, 4);
		cout << "Enter the name of your doucument:	";
		SetConsoleTextAttribute(h, 3);
		cin >> docu;
		SetConsoleTextAttribute(h, 7);
		set(docu);
		gotoRowCol(15, 0);
		for (int counter = 0; counter < 120; counter++)
		{
			cout << " ";
		}
		gotoRowCol(0, 0);
		ifstream file(docu);
		if (file)
		{
			check = false;
		}
		else
		{
			gotoRowCol(15, 30);
			SetConsoleTextAttribute(h, 4);
			cout << "WARNING:	This file doesn't exit please try again.";
			while (!_kbhit());
			while (_kbhit())
			{
				x = _getch();
			}
			SetConsoleTextAttribute(h, 7);
			gotoRowCol(15, 0);
			for (int counter = 0; counter < 120; counter++)
			{
				cout << " ";
			}
		}
	}
}

void password(char*& checkpas)
{
	char n = 0;
	int size = 0;
	int temp = 72;

	gotoRowCol(15, 45);
	SetConsoleTextAttribute(h, 4);
	cout << "Enter the password:	";
	SetConsoleTextAttribute(h, 3);

	while (n != 13)
	{
		n = _getch();
		if (n != 13 && n != 8)
		{
			gotoRowCol(15, temp);
			cout << "*";
			temp++;
			insert(checkpas, n, size);
		}
		if (n == 8 && temp > 72)
		{
			temp--;
			gotoRowCol(15, temp);
			cout << " ";
			gotoRowCol(15, temp);
			del(checkpas, size, size);
		}
	}
	SetConsoleTextAttribute(h, 7);
	system("CLS");
}

bool check(char* checkpass, char* pas)
{
	if (subsize(checkpass) == subsize(pas))
	{
		for (int counter = 0; pas[counter] != 0; counter++)
		{
			if (pas[counter] != checkpass[counter])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void input(ifstream & file, char*& ch, int& size)
{
	char n = 0;

	do
	{
		n = file.get();
		if (file)
		{
			insert(ch, n, size);
		}
	} while (file);
}

void insert(char*& ch, char n, int& size)
{
	char* temp = new char[size + 2];

	for (int counter = 0; counter < size; counter++)
	{
		temp[counter] = ch[counter];
	}
	temp[size] = n;
	size++;
	temp[size] = 0;
	delete[] ch;
	ch = temp;
}

void texteditor(char*& text, int& size, char* docu)
{
	char ch = 0;
	int Rows = 30;
	int Cols = 120;
	int trows = 0;
	int tcols = 0;
	int ri = 0;
	int ci = 0;
	int dci = 0;
	bool check = true;
	char* ED = NULL;

	ED = DECODED(ED);
	findRowsCols(text, trows, tcols);
	gotoRowCol(ri, ci);
	while (check)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				if (ch == 72 && (ri - 1) >= 0)		//up arrow
				{
					ri--;
					dci -= Cols;
				}
				else if (ch == 75 && dci >= 0)		//left arrow
				{
					ci--;
					dci--;
					if (ci < 0 && ri > 0)
					{
						ri--;
						ci = Cols - 1;
					}
					if (dci == -1)
					{
						dci = 0;
						ci = 0;
					}
				}
				else if (ch == 77 && dci < size)		//right arrow
				{
					ci++;
					dci++;
					if (ci == Cols)
					{
						ci = 0;
						ri++;
					}
				}
				else if (ch == 80 && (ri + 1) <= trows && dci + Cols <= size)		//down arrow
				{
					ri++;
					dci += Cols;
				}
				else if (ch == 83 && dci < size)		//delete function
				{
					del(text, dci, size);
					cout << text + dci;
					cout << " ";
				}
				gotoRowCol(ri, ci);
			}
			else if (ch == 13)
			{
				insertAt(text, '\n', dci, size);
				size = subsize(text);
				cout << text + dci;
				for (int counter = ci; counter < Cols; counter++)
				{
					gotoRowCol(ri, counter);
					cout << " ";
				}
				ci--;
				dci--;
				gotoRowCol(ri, ci);
				findRowsCols(text, trows, tcols);
			}
			else if (ch == 8)
			{
				if (dci > 0)
				{
					del(text, dci - 1, size);
					ci--;
					dci--;
					if (ci == -1 && ri > 0)
					{
						ri--;
						ci = Cols - 1;
					}
					gotoRowCol(ri, ci);
					cout << text + dci;
					cout << " ";
					tcols--;
					if (tcols == 0)
					{
						trows--;
						tcols = Cols - 1;
					}
					if (ci < 0)
					{
						ci++;
						dci++;
					}
					gotoRowCol(ri, ci);
				}
			}
			else if (ch == 0)
			{
				ch = _getch();
				if (ch == 59)
				{
					char* word = new char[20];
					int* index = NULL;
					int isize = 0;
					int trow = 0;
					int tcol = 0;
					int tdci = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word you want to serch:	";
					SetConsoleTextAttribute(h, 3);
					cin >> word;
					SetConsoleTextAttribute(h, 7);
					set(word);
					clear(trows + 5, 0);
					FindAllOccWord(text, word, index, isize);
					bold(index, isize, word);
					firstocc(text, word, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					gotoRowCol(ri, ci);
				}
				else if (ch == 60)
				{
					char* sentence = new char[size];
					int* index = NULL;
					int isize = 0;
					int trow = 0;
					int tcol = 0;
					int tdci = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the sentence or substring to find:	";
					SetConsoleTextAttribute(h, 3);
					cin.getline(sentence, size);
					SetConsoleTextAttribute(h, 7);
					set(sentence);
					clear(trows + 5, 0);
					clear(trows + 6, 0);
					clear(trows + 7, 0);
					clear(trows + 8, 0);
					clear(trows + 9, 0);
					FindAllOcc(text, sentence, index, isize);
					bold(index, isize, sentence);
					firstocc1(text, sentence, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					gotoRowCol(ri, ci);
				}
				else if (ch == 61)
				{
					char* A = new char[20];
					char* B = new char[20];
					int trow = 0;
					int tcol = 0;
					int tdci = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word you want to replace:	";
					SetConsoleTextAttribute(h, 3);
					cin >> A;
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the replacing word:	";
					SetConsoleTextAttribute(h, 3);
					cin >> B;
					SetConsoleTextAttribute(h, 7);
					set(A);
					set(B);
					clear(trows + 5, 0);
					clear(trows + 6, 0);
					ReplacingAWord(text, A, B, size);
					firstocc(text, B, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					findRowsCols(text, trows, tcols);
					trow = trows;
					tcol = tcols;
					if (subsize(A) > subsize(B))
					{
						for (int counter = 0; counter <= subsize(A) - subsize(B); counter++)
						{
							gotoRowCol(trow, tcol);
							tcol++;
							if (tcol == 120)
							{
								tcol = 0;
								trow++;
							}
							cout << " ";
						}
					}
					gotoRowCol(ri, ci);
					size = subsize(text);
				}
				else if (ch == 62)
				{
					char* A = new char[20];
					char* B = new char[20];
					int trow = 0;
					int tcol = 0;
					int tdci = 0;
					int count = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word you want to replace:	";
					SetConsoleTextAttribute(h, 3);
					cin >> A;
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the replacing word:	";
					SetConsoleTextAttribute(h, 3);
					cin >> B;
					SetConsoleTextAttribute(h, 7);
					set(A);
					set(B);
					AllOccs(text, A, count);
					clear(trows + 5, 0);
					clear(trows + 6, 0);
					ReplacingAllWords(text, A, B, size);
					firstocc(text, B, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					findRowsCols(text, trows, tcols);
					trow = trows;
					tcol = tcols;
					if (subsize(A) > subsize(B))
					{
						for (int counter = 0; counter <= (subsize(A) - subsize(B)) * count; counter++)
						{
							gotoRowCol(trow, tcol);
							tcol++;
							if (tcol == 120)
							{
								tcol = 0;
								trow++;
							}
							cout << " ";
						}
					}
					gotoRowCol(ri, ci);
					size = subsize(text);
				}
				else if (ch == 63)
				{
					char* A = new char[20];
					char* B = new char[20];
					int trow = 0;
					int tcol = 0;
					int tdci = 0;
					int count = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word in which you want to add prefeix:	";
					SetConsoleTextAttribute(h, 3);
					cin >> A;
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the prefeix:	";
					SetConsoleTextAttribute(h, 3);
					cin >> B;
					SetConsoleTextAttribute(h, 7);
					set(A);
					set(B);
					clear(trows + 5, 0);
					clear(trows + 6, 0);
					Prefeix(text, A, B, size);
					firstocc1(text, B, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					gotoRowCol(ri, ci);
				}
				else if (ch == 64)
				{
					char* A = new char[20];
					char* B = new char[20];
					int trow = 0;
					int tcol = 0;
					int tdci = 0;
					int count = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word in which you want to add postfeix:	";
					SetConsoleTextAttribute(h, 3);
					cin >> A;
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the postfeix:	";
					SetConsoleTextAttribute(h, 3);
					cin >> B;
					SetConsoleTextAttribute(h, 7);
					set(A);
					set(B);
					clear(trows + 5, 0);
					clear(trows + 6, 0);
					Postfeix(text, A, B, size);
					firstocc1(text, B, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					gotoRowCol(ri, ci);
					size = subsize(text);
				}
				else if (ch == 65)
				{
					int words = 0;
					int alpha = 0;

					AvgWordlength(text, words, alpha);
					gotoRowCol(trows + 5, 0);
					cout << "Average Word Length:	" << alpha / words;
					while (!_kbhit());
					while (_kbhit())
					{
						x = _getch();
					}
					clear(trows + 5, 0);
					gotoRowCol(ri, ci);
				}
				else if (ch == 66)
				{
					char* substring = new char[50];
					int count = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the substring whose count you want to find:	";
					SetConsoleTextAttribute(h, 3);
					cin.getline(substring, 50);
					SetConsoleTextAttribute(h, 7);
					clear(trows + 5, 0);
					AllOccs(text, substring, count);
					gotoRowCol(trows + 5, 0);
					cout << "Substring Count:	" << count;
					while (!_kbhit());
					while (_kbhit())
					{
						x = _getch();
					}
					clear(trows + 5, 0);
					gotoRowCol(ri, ci);
				}
				else if (ch == 67)
				{
					int count = 0;

					SpecialCount(text, count);
					gotoRowCol(trows + 5, 0);
					cout << "Special Character Count:	" << count;
					while (!_kbhit());
					while (_kbhit())
					{
						x = _getch();
					}
					clear(trows + 5, 0);
					gotoRowCol(ri, ci);
				}
				else if (ch == 68)
				{
					int count = 0;

					SentencesCount(text, count);
					gotoRowCol(trows + 5, 0);
					cout << "Sentence Count:	" << count;
					while (!_kbhit());
					while (_kbhit())
					{
						x = _getch();
					}
					clear(trows + 5, 0);
					gotoRowCol(ri, ci);
				}
				else if (ch == 94)
				{
					char* word = new char[20];
					char* temp = lowercase(text);
					int* index = NULL;
					int isize = 0;
					int trow = 0;
					int tcol = 0;
					int tdci = 0;

					gotoRowCol(trows + 5, 0);
					SetConsoleTextAttribute(h, 6);
					cout << "Enter the word you want to serch:	";
					SetConsoleTextAttribute(h, 3);
					cin >> word;
					SetConsoleTextAttribute(h, 7);
					set(word);
					char* tword = lowercase(word);
					delete[] word;
					word = tword;
					clear(trows + 5, 0);
					FindAllOccWord(temp, word, index, isize);
					bold(index, isize, word);
					firstocc(temp, word, trow, tcol, tdci);
					gotoRowCol(trow, tcol);
					cout << text + tdci;
					gotoRowCol(ri, ci);
				}
			}
			else if (ch == 19)
			{
				save(text, docu);
			}
			else if (ch == 17)
			{
				int count = 0;
				int si = 0;
				int ei = 0;

				LargestWord(text, count, si, ei);
				gotoRowCol(trows + 5, 0);
				cout << "Largest-Word:	";
				for (int counter = si; counter <= ei; counter++)
				{
					cout << text[counter];
				}
				cout << "\nLength-Word:	 " << count;
				while (!_kbhit());
				while (_kbhit())
				{
					x = _getch();
				}
				clear(trows + 5, 0);
				clear(trows + 6, 0);
				gotoRowCol(ri, ci);
			}
			else if (ch == 23)
			{
				int count = 0;
				int si = 0;
				int ei = 0;

				SmallestWord(text, count, si, ei);
				gotoRowCol(trows + 5, 0);
				cout << "Smallest-Word:	";
				for (int counter = si; counter <= ei; counter++)
				{
					cout << text[counter];
				}
				cout << "\nLength-Word:	 " << count;
				while (!_kbhit());
				while (_kbhit())
				{
					x = _getch();
				}
				clear(trows + 5, 0);
				clear(trows + 6, 0);
				gotoRowCol(ri, ci);
			}
			else if (ch == 27)
			{
				check = false;
				gotoRowCol(trows, tcols);
			}
			else if (ch == 9)
			{
				menu();
				cout << text;
				gotoRowCol(0, 0);
			}
			else if (ch == 4)
			{
				Decode(ED, size);
				gotoRowCol(ri, ci);
			}
			else if (ch == 5)
			{
				ED = Encode(text, size);
				gotoRowCol(ri, ci);
			}
			else if (ch == 18)
			{
				int count = 1;

				Paragraphcount(text, count);
				gotoRowCol(trows + 5, 0);
				cout << "Paragraph-Count:	" << count;
				while (!_kbhit());
				while (_kbhit())
				{
					x = _getch();
				}
				clear(trows + 5, 0);
				gotoRowCol(ri, ci);
			}
			else if (ch == 20)
			{
				int count = 0;

				LargestParagraph(text, count);
				gotoRowCol(trows + 5, 0);
				cout << "Largest-Paragraph Word Length:	" << count;
				while (!_kbhit());
				while (_kbhit())
				{
					x = _getch();
				}
				clear(trows + 5, 0);
				gotoRowCol(ri, ci);
			}
			else if (ch == 25)
			{
				char* max = NULL;

				max = alphabet(text);
				gotoRowCol(trows + 5, 0);
				cout << "Word that contains the alphabets for highest number of other words:	" << max;
				while (!_kbhit());
				while (_kbhit())
				{
					x = _getch();
				}
				clear(trows + 5, 0);
				gotoRowCol(0, 0);
			}
			else if (ch == 21)
			{
				char* temp = NULL;
				int tsize = 0;
				char* docu1 = new char[20];
				int n = 0;

				gotoRowCol(trows + 5, 0);
				SetConsoleTextAttribute(h, 6);
				cout << "How many file do you want to merge:	";
				SetConsoleTextAttribute(h, 3);
				cin >> n;
				clear(trows + 5, 0);
				for (int counter = 0; counter < n; counter++)
				{
					SetConsoleTextAttribute(h, 4);
					gotoRowCol(trows + 5, 0);
					cout << "Enter the " << counter + 1 << " file name: ";
					SetConsoleTextAttribute(h, 3);
					cin >> docu1;
					clear(trows + 5, 0);
					mergefiles(temp, tsize, docu1);
				}
				SetConsoleTextAttribute(h, 4);
				gotoRowCol(trows + 5, 0);
				cout << "Enter the file name in which you want to merge all files: ";
				SetConsoleTextAttribute(h, 3);
				cin >> docu1;
				SetConsoleTextAttribute(h, 7);
				clear(trows + 5, 0);
				save(temp, docu1);
				if (serch(docu, docu1, 0))
				{
					gotoRowCol(0, 0);
					text = NULL;
					size = 0;
					ifstream file(docu);
					input(file, text, size);
					cout << text;
					findRowsCols(text, trows, tcols);
				}
				gotoRowCol(ri, ci);
			}
			else
			{
				insertAt(text, ch, dci, size);
				cout << text + dci;
				dci++;
				ci++;
				if (ci == Cols)
				{
					tcols = 0;
					trows++;
					ci = 0;
					ri++;
					dci++;
				}
				gotoRowCol(ri, ci);
			}
		}
	}
}

void findRowsCols(char* text, int& trows, int& tcols)
{
	trows = 0;
	tcols = 0;

	for (int counter = 0; text[counter] != '\0'; counter++)
	{
		tcols++;
		if (tcols == 120 || text[counter] == '\n')
		{
			trows++;
			tcols = 0;
		}
	}
}

void insertAt(char*& ch, char n, int& index, int& size)
{
	char* temp = new char[size + 2];
	int t = size;

	for (int counter = 0; counter < index; counter++)
	{
		temp[counter] = ch[counter];
	}
	size++;
	for (int counter = size; counter > index; counter--, t--)
	{
		temp[counter] = ch[t];
	}
	temp[index] = n;
	size++;
	temp[size - 1] = '\0';
	ch = temp;
	size = subsize(ch);
}

void del(char*& ch, int index, int& size)
{
	for (int counter = index; counter + 1 < size; counter++)
	{
		ch[counter] = ch[counter + 1];
	}
	size--;
	ch[size] = '\0';
}

void save(char* text, char* docu)
{
	ofstream file(docu);
	file << text;
}

void FindAllOccWord(char*& A, char* B, int*& index, int& isize)
{
	int Asize = subsize(A);
	int Bsize = subsize(B);
	int row = 0;
	int col = 0;
	int t = 0;
	int t1 = 0;

	for (int counter = 0; counter < Asize - Bsize + 1; counter++, col++)
	{
		t = counter + subsize(B);
		t1 = counter - 1;
		if (col == 120)
		{
			col = 0;
			row++;
		}
		if (*(A + counter) == *(B + 0))
		{
			if (serch(A, B, counter) == true && counter == 0 && (A[t] >= 32 && A[t] <= 47 || A[t] >= 58 && A[t] <= 64 || A[t] >= 91 && A[t] <= 96 || A[t] >= 123 && A[t] <= 126))
			{
				expand(index, isize, row, col);
			}
			else if (serch(A, B, counter) == true && (A[t1] >= 32 && A[t1] <= 47 || A[t1] >= 58 && A[t1] <= 64 || A[t1] >= 91 && A[t1] <= 96 || A[t1] >= 123 && A[t1] <= 126) && (A[t] >= 32 && A[t] <= 47 || A[t] >= 58 && A[t] <= 64 || A[t] >= 91 && A[t] <= 96 || A[t] >= 123 && A[t] <= 126))
			{
				expand(index, isize, row, col);
			}
			else if (serch(A, B, counter) == true && (A[t1] >= 32 && A[t1] <= 47 || A[t1] >= 58 && A[t1] <= 64 || A[t1] >= 91 && A[t1] <= 96 || A[t1] >= 123 && A[t1] <= 126) && counter == Asize - Bsize + 1)
			{
				expand(index, isize, row, col);
			}
		}
	}
}

char* lowercase(char* text)
{
	char* temp = new char[subsize(text) + 1];

	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (text[counter] >= 65 && text[counter] <= 90)
		{
			temp[counter] = text[counter] + 32;
		}
		else
		{
			temp[counter] = text[counter];
		}
	}
	temp[subsize(text)] = 0;
	return temp;
}

void FindAllOcc(char*& A, char* B, int*& index, int& isize)
{
	int Asize = subsize(A);
	int Bsize = subsize(B);
	int row = 0;
	int col = 0;

	for (int counter = 0; counter < Asize - Bsize + 1; counter++, col++)
	{
		if (col == 120)
		{
			col = 0;
			row++;
		}
		if (*(A + counter) == *(B + 0))
		{
			if (serch(A, B, counter) == true)
			{
				expand(index, isize, row, col);
			}
		}
	}
}

void ReplacingAWord(char*& text, char* B, char* C, int& size)
{
	int Bsize = subsize(B);
	int Csize = subsize(C);
	bool check = true;

	for (int counter = 0; counter < size - Bsize + 1 && check == true; counter++)
	{
		if (*(text + counter) == *(B + 0))
		{
			if (serchWord(text, B, counter))
			{
				replace(text, C, counter, size, Bsize, Csize);
				check = false;
			}
		}
	}
}

void ReplacingAllWords(char*& text, char* B, char* C, int& size)
{
	int Bsize = subsize(B);
	int Csize = subsize(C);

	for (int counter = 0; counter < size - Bsize + 1; counter++)
	{
		if (*(text + counter) == *(B + 0))
		{
			if (serchWord(text, B, counter))
			{
				replace(text, C, counter, size, Bsize, Csize);
			}
		}
	}
}

void replace(char*& text, char* C, int index, int& size, int Bsize, int Csize)
{
	int i = 0;
	int t = 0;
	if (Csize > Bsize)
	{
		t = Csize;
	}
	else
	{
		t = Bsize;
	}
	char* temp = new char[size + t + 2];

	for (int counter = 0; counter < index; counter++)
	{
		temp[counter] = text[counter];
	}
	for (int counter = index; counter < index + Csize; counter++, i++)
	{
		temp[counter] = C[i];
	}
	i = index + Bsize;
	for (int counter = index + Csize; counter < size + t - 1; counter++, i++)
	{
		temp[counter] = text[i];
	}
	if (Csize > Bsize)
	{
		size += Csize - Bsize;
	}
	else
	{
		size += Bsize - Csize;
	}
	temp[size] = 0;
	delete[] text;
	text = temp;
	set(text);
}

bool serchWord(char*& A, char* B, int counter)
{
	int Asize = subsize(A);
	int Bsize = subsize(B);
	int row = 0;
	int col = 0;
	int t = counter + subsize(B);
	int t1 = counter - 1;

	if (serch(A, B, counter) == true && counter == 0 && (A[t] >= 32 && A[t] <= 47 || A[t] >= 58 && A[t] <= 64 || A[t] >= 91 && A[t] <= 96 || A[t] >= 123 && A[t] <= 126))
	{
		return true;
	}
	else if (serch(A, B, counter) == true && (A[t1] >= 32 && A[t1] <= 47 || A[t1] >= 58 && A[t1] <= 64 || A[t1] >= 91 && A[t1] <= 96 || A[t1] >= 123 && A[t1] <= 126) && (A[t] >= 32 && A[t] <= 47 || A[t] >= 58 && A[t] <= 64 || A[t] >= 91 && A[t] <= 96 || A[t] >= 123 && A[t] <= 126))
	{
		return true;
	}
	else if (serch(A, B, counter) == true && (A[t1] >= 32 && A[t1] <= 47 || A[t1] >= 58 && A[t1] <= 64 || A[t1] >= 91 && A[t1] <= 96 || A[t1] >= 123 && A[t1] <= 126) && counter == Asize - Bsize + 1)
	{
		return true;
	}

	return false;
}

void Prefeix(char*& text, char* B, char* C, int& size)
{
	int Bsize = subsize(B);
	int Csize = subsize(C);

	for (int counter = 0; counter < size - Bsize + 1; counter++)
	{
		if (*(text + counter) == *(B + 0))
		{
			if (serchWord(text, B, counter))
			{
				AddPrePostfeix(text, C, counter, size, Bsize, Csize);
				counter += Bsize + Csize - 1;
			}
		}
	}
}

void Postfeix(char*& text, char* B, char* C, int& size)
{
	int Bsize = subsize(B);
	int Csize = subsize(C);

	for (int counter = 0; counter < size - Bsize + 1; counter++)
	{
		if (*(text + counter) == *(B + 0))
		{
			if (serchWord(text, B, counter))
			{
				AddPrePostfeix(text, C, counter + Bsize, size, Bsize, Csize);
				counter += Bsize + Csize - 1;
			}
		}
	}
}

void AddPrePostfeix(char*& text, char* C, int index, int& size, int Bsize, int Csize)
{
	int t = 0;
	if (Csize > Bsize)
	{
		t = Csize;
	}
	else
	{
		t = Bsize;
	}
	char* temp = new char[size + t + 2];
	int i = 0;

	for (int counter = 0; counter < index; counter++)
	{
		temp[counter] = text[counter];
	}
	for (int counter = index; counter < index + Csize; counter++, i++)
	{
		temp[counter] = C[i];
	}
	i = index;
	for (int counter = index + Csize; counter <= size + t + 1; counter++, i++)
	{
		temp[counter] = text[i];
	}
	size += t - 1;
	temp[size + 1] = 0;
	delete[] text;
	text = temp;
	set(text);
	size = subsize(text);
}

void AvgWordlength(char* text, int& words, int& alpha)
{
	words = 0;
	alpha = 0;

	for (int counter = 0; text[counter] != 0; counter++)
	{
		if ('A' <= text[counter] && 'Z' >= text[counter] || 'a' <= text[counter] && 'z' >= text[counter])
		{
			alpha++;
		}
		if (text[counter] == ' ')
		{
			words++;
		}
	}
}

void SpecialCount(char* text, int& count)
{
	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (text[counter] >= 32 && text[counter] <= 47 || text[counter] >= 58 && text[counter] <= 64 || text[counter] >= 91 && text[counter] <= 96 || text[counter] >= 123 && text[counter] <= 126)
		{
			count++;
		}
	}
}

void SentencesCount(char* text, int& count)
{
	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (text[counter] == '.')
		{
			count++;
		}
	}
}

void LargestWord(char* text, int& count, int& si, int& ei)
{
	si = 0;
	int max = 0;

	for (int counter = si; text[counter] != ' '; counter++)
	{
		max++;
		ei++;
	}
	for (int counter = ei + 1; text[counter] != 0; counter++)
	{
		if (text[counter] == ' ' || text[counter] == '\n' || text[counter] == '.')
		{
			if (max < count)
			{
				max = count;
				ei = counter - 1;
				si = ei - max;
			}
			count = 0;
		}
		else
		{
			count++;
		}
	}
	count = max;
}

void mergefiles(char*& temp, int& size, char* docu)
{
	ifstream file(docu);
	input(file, temp, size);
}

void SmallestWord(char* text, int& count, int& si, int& ei)
{
	si = 0;
	int min = 0;

	for (int counter = si; text[counter] != ' ' && text[counter] != '.'; counter++)
	{
		min++;
		ei++;
	}
	for (int counter = ei + 1; text[counter] != 0; counter++)
	{
		if (text[counter] == ' ' || text[counter] == '\n' || text[counter] == '.')
		{
			if (min > count && min > 1)
			{
				min = count;
				ei = counter - 1;
				si = ei - min;
			}
			count = 0;
		}
		else
		{
			count++;
		}
	}
	count = min;
}

char* alphabet(char* text)
{
	char* word = NULL;
	int wsize = 0;
	int count = 0;
	char* max = NULL;
	int mcount = 0;
	int i = 0;
	bool check = true;

	for (int counter = 0; text[counter] != 0; counter++)
	{
		Aword(text, word, wsize, counter, i);
		if (word && word[0] != ' ')
		{
			find(text, word, wsize, count);
		}
		if (mcount < count)
		{
			max = NULL;
			int m = 0;
			for (int k = 0; word[k] != 0; k++)
			{
				insert(max, word[k], m);
			}
			mcount = count;
		}
		counter += i;
		word = NULL;
		wsize = 0;
		i = 0;
	}
	return max;
}

void Aword(char* text, char*& word, int& wsize, int index, int& i)
{
	for (int counter = index; text[counter] != ' ' && text[counter] != 0; counter++)
	{
		if (text[counter] >= 'A' && text[counter] <= 'Z' || text[counter] >= 'a' && text[counter] <= 'z' || text[counter] >= '0' && text[counter] <= '9')
		{
			insert(word, text[counter], wsize);
		}
		i++;
	}
}

void find(char* text, char* word, int wsize, int& count)
{
	char* word1 = NULL;
	int wsize1 = 0;
	count = 0;
	int i = 0;

	for (int counter = 0; text[counter] != 0; counter++)
	{
		Aword(text, word1, wsize1, counter, i);
		if (wsize1 < wsize && word1)
		{
			int t = 0;
			for (int i = 0; word && word1[i] != 0 && word1[0] != ' '; i++)
			{
				if (serchalpha(word, word1[i]))
				{
					t++;
				}
			}
			if (t >= wsize1)
			{
				count++;
			}
		}
		counter += i;
		word1 = NULL;
		wsize1 = 0;
		i = 0;
		if (counter == subsize(text))
		{
			counter--;
		}
	}
}

bool serchalpha(char* ch, char n)
{
	bool check = false;

	for (int i = 0; ch[i] != 0 && check == false; i++)
	{
		if (ch[i] == n)
		{
			check = true;
		}
	}
	return check;
}

char* Encode(char*& text, int size)
{
	ofstream file("ProcessedFileEcoded.txt");
	ofstream file1("TEXT.txt");
	char ch = 128;
	int n = 0;
	char* temp = new char[size];
	char* ED = new char[size + 1];

	for (int counter = 0; counter < 128; counter++)
	{
		temp[counter] = ch;
		ch++;
	}
	for (int counter = 0; text[counter] != 0; counter++)
	{
		n = int(text[counter]);
		ED[counter] = temp[n];
		file << temp[n];
		file1 << temp[n];
	}
	ED[size] = 0;
	gotoRowCol(0, 0);
	cout << ED;
	/*while (!_kbhit());
	while(_kbhit())
	{
		x = _getch();
		gotoRowCol(0, 0);
		cout << text;
	}*/
	return ED;
}

void Decode(char*& text, int size)
{
	ofstream file("ProcessedFileEcoded.txt");
	ofstream file1("TEXT.txt");
	char ch = 128;
	char n = 0;
	char* temp = new char[size];

	for (int counter = 0; counter < 128; counter++, ch++)
	{
		temp[counter] = ch;
	}
	for (int counter = 0; text[counter] != 0; counter++)
	{
		for (int counter1 = 0; counter1 < 128; counter1++)
		{
			if (text[counter] == temp[counter1])
			{
				n = counter1;
				text[counter] = n;
				file << text[counter];
				file1 << text[counter];
			}
		}
	}
	gotoRowCol(0, 0);
	cout << text;
}

void Paragraphcount(char* text, int& count)
{
	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (text[counter] == '\n' && text[counter + 1] == '\n')
		{
			count++;
			int i = 0;
			for (i = counter; text[i] == '\n'; i++);
			counter += (i - counter);
		}
	}
}

void LargestParagraph(char* text, int& count)
{
	bool check = true;
	int max = 0;
	int j = 0;

	for (int counter = 0; text[counter] != 0 && check == true; counter++, max++)
	{
		if (text[counter] == '\n' && text[counter + 1] == '\n')
		{
			int i = 0;
			for (i = counter; text[i] == '\n'; i++);
			counter += (i - counter);
			check = false;
			j = counter;
			max--;
		}
	}
	for (int counter = j; text[counter] != 0; counter++, count++)
	{
		if (text[counter] == '\n' && text[counter + 1] == '\n' || text[counter + 1] == 0)
		{
			int i = 0;
			for (i = counter; text[i] == '\n'; i++);
			counter += (i - counter);
			if (max < count)
			{
				max = count;
			}
			count = 1;
		}
	}
	count = max;
}

bool serch(char* ch, char* n, int counter)
{
	bool check = true;

	for (int i = 0; n[i] != '\0' && check == true; i++, counter++)
	{
		if (*(ch + counter) != *(n + i))
		{
			check = false;
		}
	}
	return check;
}

void expand(int*& num, int& size, int row, int col)
{
	int* temp = new int[size + 2];

	for (int counter = 0; counter < size; counter++)
	{
		temp[counter] = num[counter];
	}
	temp[size] = row;
	size++;
	temp[size] = col;
	size++;
	delete[] num;
	num = temp;
}

void bold(int* index, int isize, char* substring)
{
	int Ssize = subsize(substring);

	for (int counter = 0; counter < isize; counter += 2)
	{
		gotoRowCol(index[counter], index[counter + 1]);
		for (int counter1 = 0; counter1 < Ssize; counter1++)
		{
			SetConsoleTextAttribute(h, 2);
			cout << substring[counter1];
		}
	}
	while (!_kbhit());
	SetConsoleTextAttribute(h, 7);
}

void output(char* ch)
{
	for (int counter = 0; ch && ch[counter] != 0; counter++)
	{
		cout << ch[counter];
	}
}

void set(char*& ch)
{
	int size = 0;

	for (int counter = 0; ch[counter] != '\0'; counter++)
	{
		size++;
	}
	char* temp = new char[size + 1];
	for (int counter = 0; ch[counter] != '\0'; counter++)
	{
		temp[counter] = ch[counter];
	}
	temp[size] = '\0';
	delete[] ch;
	ch = temp;
}

int subsize(char* n)
{
	int size = 0;

	for (int counter = 0; n[counter] != '\0'; counter++)
	{
		size++;
	}
	return size;
}

void clear(int row, int col)
{
	gotoRowCol(row, col);
	for (int counter = 0; counter < 120; counter++)
	{
		cout << " ";
	}
}

void firstocc(char* text, char* A, int& row, int& col, int& dci)
{
	bool check = true;

	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (serchWord(text, A, counter))
		{
			return;
		}
		else
		{
			col++;
			dci++;
			if (col == 120)
			{
				col = 0;
				row++;
			}
		}
	}
}

void firstocc1(char* text, char* A, int& row, int& col, int& dci)
{
	bool check = true;

	for (int counter = 0; text[counter] != 0; counter++)
	{
		if (serch(text, A, counter))
		{
			return;
		}
		else
		{
			col++;
			dci++;
			if (col == 120)
			{
				col = 0;
				row++;
			}
		}
	}
}

void AllOccs(char*& A, char* B, int& count)
{
	int Asize = subsize(A);
	int Bsize = subsize(B);
	int row = 0;
	int col = 0;
	count = 0;

	for (int counter = 0; counter < Asize - Bsize + 1; counter++, col++)
	{
		if (col == 120)
		{
			col = 0;
			row++;
		}
		if (*(A + counter) == *(B + 0))
		{
			if (serch(A, B, counter) == true)
			{
				count++;
			}
		}
	}
}

void menu()
{
	system("CLS");
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F1";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch a word (Case Sensitive).\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + F1";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch a word (Case Insensitive).\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F2";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch sentence.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F3";
	SetConsoleTextAttribute(h, 7);
	cout << " to Replace the first word only.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F4";
	SetConsoleTextAttribute(h, 7);
	cout << " to Replace the whole file words.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F5";
	SetConsoleTextAttribute(h, 7);
	cout << "  to Add Prefix to Word.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F6";
	SetConsoleTextAttribute(h, 7);
	cout << " to Add Postfix to Word.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F7";
	SetConsoleTextAttribute(h, 7);
	cout << " to find Average Word Length.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F8";
	SetConsoleTextAttribute(h, 7);
	cout << " to find Substring Count.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F9";
	SetConsoleTextAttribute(h, 7);
	cout << " to find Special Characters Count.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "F10";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch Sentences count.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + Q";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch Largest-Word.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + W";
	SetConsoleTextAttribute(h, 7);
	cout << " to serch Smallest-Word.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + E";
	SetConsoleTextAttribute(h, 7);
	cout << " to Encode.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + D";
	SetConsoleTextAttribute(h, 7);
	cout << " to Decode.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + R";
	SetConsoleTextAttribute(h, 7);
	cout << " to find Paragraph Count.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + T";
	SetConsoleTextAttribute(h, 7);
	cout << " to find Largest Paragraph.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + Y";
	SetConsoleTextAttribute(h, 7);
	cout << " to find word that contains the alphabets for highest number of other words.\n";
	cout << "PRESS ";
	SetConsoleTextAttribute(h, 3);
	cout << "ctrl + U";
	SetConsoleTextAttribute(h, 7);
	cout << " to merge files.\n";

	while (!_kbhit());
	while (_kbhit())
	{
		x = _getch();
	}
	system("CLS");
}

char* DECODED(char* ED)
{
	ifstream file("ProcessedFileEcoded.txt");
	char n = 0;
	int size = 0;

	do
	{
		n = file.get();
		if (file)
		{
			insert(ED, n, size);
		}
	} while (file);

	return ED;
}

void resume(char& choice)
{
	gotoRowCol(15, 35);
	cout << "Enter ";
	SetConsoleTextAttribute(h, 4);
	cout << "Y \\ y";
	SetConsoleTextAttribute(h, 7);
	cout << " to run again and ";
	SetConsoleTextAttribute(h, 4);
	cout << "N \\ n";
	SetConsoleTextAttribute(h, 7);
	cout << " to exit:	";
	cin >> choice;
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}