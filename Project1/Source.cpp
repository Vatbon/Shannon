/*Вычисление кол-ва информации по формуле Шеннона*/

#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#define POSITION_OF_STRING 1 
#define BUFF_SIZE 1024 

int main(int argc, char *argv[]) {
	char* FileName = argv[POSITION_OF_STRING];
	FILE* InputFile;
	fopen_s(&InputFile, FileName, "rb");
	if (!InputFile) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	double Alphabet[256];
	size_t i;
	size_t InputLength;
	size_t count = 0;
	double Resultf = 0;
	size_t Result;
	double chance;
	unsigned char InputString[BUFF_SIZE];

	for (i = 0; i < 256; i++)
		Alphabet[i] = 0;
	do {
		InputLength = fread(InputString, sizeof InputString[0], BUFF_SIZE, InputFile);
		for (i = 0; i < InputLength; i++) {
			Alphabet[InputString[i]] += 1;
			count++;
		}
	} while (InputLength == 1024);

	for (i = 0; i < 256; i++) {
		if (Alphabet[i]) {
			chance = Alphabet[i] / count;
			Resultf = Resultf + chance * log2(chance);
		}
	}

	Result = (size_t)ceil(-(Resultf * count));
	printf("%d\n", Result);

	fclose(InputFile);
	return 0;
}