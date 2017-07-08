/***
*file: "FirstPart.c"
*synopsis: definitions functions for first part of the first lab
*author: R. Neshta
*written: 30/06/17
*last modified: 30/06/17
****/

#include"FirstPart.h"


int substr(const char* first, const char* second){

	int lengthFirst = strlen(first);
	int lengthSecond = strlen(second);

	int i, j;
	for (i = 0, j = 0; i < lengthFirst && j < lengthSecond; ++i, ++j){

		if (first[i] != second[j]){

			i -= j;
			j = -1;

		}

	}

	if (j == lengthSecond)
		return i - j;

	return -1;

}

int subseq(const char* first, const char* second){

	int longest = 0;
	int current = 0;
	int lengthFirst = strlen(first);
	int lengthSecond = strlen(second);

	int i;
	for (i = 0; i < lengthFirst; ++i){

		int iCopy = i;
		int j = 0;

		while (j <= lengthSecond){

			if (first[iCopy] == second[j] && j < lengthSecond){

				++current;
				++iCopy;
				++j;

			}
			else{

				if (current > longest)
					longest = current;

				if (iCopy == i){

					++j;

				}
				else{

					current = 0;
					iCopy = i;

				}

			}

		}

	}

	return longest;

}

char ispal(const char* string){

	int length = strlen(string);
	int i = 0;

	for (; i < length / 2 + 1; ++i){

		if (string[i] != string[length - i - 1])
			return '0';

	}

	return '1';

}

char* makepal(const char* string){

	int length = strlen(string);
	int leftBorder = 0, rightBorder = length - 1, count = 0, tmpCount;

	while (leftBorder < rightBorder){

		while (string[leftBorder] != string[rightBorder]){

			leftBorder++; count++;

		}

		tmpCount = 0;

		while (string[leftBorder] == string[rightBorder]){

			leftBorder++; rightBorder--; tmpCount++;

		}

		if (leftBorder < rightBorder){

			rightBorder = length - 1;
			leftBorder -= tmpCount - 1;
			count += tmpCount;

		}

	}

	char* pal = (char*)malloc((length + count + 1) * sizeof(char));

	int i, j;
	for (i = 0; i < length; i++)
		pal[i] = string[i];

	for (j = 0; j < count; j++, i++)
		pal[i] = string[count - j - 1];

	pal[i] = '\0';

	return pal;

}

double* txt2double(const char* string, int* size){

	int k = strlen(string), n = 0, max = 0, num = 0, j, i, chk = 12;
	char *check = { ";.0123456789" };
	double *arr;
	char *s;

	(*size) = 0;
	for (i = 0; i < k; i++){

		if (string[i] == ';'){

			if (string[i + 1] == ';')
				continue;

			n++;

			if (num > max)
				max = num;

			num = 0;

		}
		else{

			num++;

			if (string[i + 1] == '\0'){

				n++;

				if (num > max)
					max = num;

			}

		}

		for (j = 0; j < chk; j++){

			if (string[i] == check[j])
				break;

		}

		if (j == chk)
			return NULL;

	}

	if (NULL == (s = (char*)malloc((max + 1)*sizeof(char))) || NULL == (arr = (double*)malloc(n*sizeof(double)))){
	
		printf("Allocation fail\n");
		exit(1);
	
	}
	
	
	for (i = 0, j = 0, num = 0; i <= k; i++){

		if (string[i] != ';' && string[i] != '\0'){
		
			s[j] = string[i];
			j++;
		
		}
		else{
		
			if (string[i + 1] == ';')
				continue;
			
			s[j] = '\0';
			arr[num++] = atof(s);
			
			(*size) += 1;
			j = 0;
			
			while (s[j] != '\0'){
			
				s[j] = '\0';
				j++;
			
			}
			
			j = 0;
		
		}
	
	}
	
	free(s);
	
	return arr;

}
