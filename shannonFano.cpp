#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

using namespace std;

struct CharacterT {
	char c;
	int freq;
	string code;
};

void ShannonFano(CharacterT *chars, int end, int start = 0, const string &branch = "", const string &fullBranch = "") {
	string code = fullBranch + branch;

	// если дошли до одного символа какого-то, то выводим значения
	if (start == end) {
		chars[start].code = code;
	    return;
	}

	int sum = 0; // сумма частот
	// считаем сумму частот от начала до конца
	for (int i = start; i <= end; i++)
	    sum += chars[i].freq;

	sum /= 2; // делим пополам, чтобы получить идеал равных частот
	int i, sum2 = chars[start].freq;

	// ищем границу раздела массива частот для наиболее равномерного разделения
	for (i = start + 1; abs(sum - (sum2 + chars[i].freq)) < abs(sum - sum2) && i < end; i++)
	    sum2 += chars[i].freq;

	ShannonFano(chars, i - 1, start, "0", code);
	ShannonFano(chars, end, i, "1", code);
}

int main() {
	string s;
	cout << "Enter string: ";
	getline(cin, s);

	CharacterT *chars = new CharacterT[s.length()]; // массив символов и частот строки
	int size = 0; // размер массива

	// обрабатываем всю строку
	for (int i = 0; i < s.length(); i++) {
		int j = 0;

		// ищем в массиве текущий символ
		while (j < size && chars[j].c != s[i])
			j++;

		// если не нашли (j = size), то добавляем этот символ и учитываем, что частота его равна 1
		if (j == size) {
			chars[size].c = s[i];
			chars[size++].freq = 1;
		} else
			chars[j].freq++; // если нашли, увеличиваем значение частоты
	}

	bool isSorted = false;
	while (!isSorted) {
		isSorted = true;

		for (int i = 0; i < size - 1; i++) {
			if (chars[i].freq < chars[i + 1].freq) {
				CharacterT tmp = chars[i];
				chars[i] = chars[i + 1];
				chars[i + 1] = tmp;
				isSorted = false;
			}
		}
	}

	ShannonFano(chars, size - 1);

	cout << "+-------------------+" << endl;
	cout << "| c | freq |  code  |" << endl;
	cout << "+---+------+--------+" << endl;
	for (int i = 0; i < size; i++)
		printf("| %c | %4d | %6s |\n", chars[i].c, chars[i].freq, chars[i].code.c_str());
	cout << "+-------------------+" << endl;

	delete[] chars;
}