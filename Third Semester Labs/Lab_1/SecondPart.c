/***
*file: "FirstPart.h"
*synopsis: definitions functions for second part of the first lab
*author: R. Neshta
*written: 01/06/17
*last modified: 01/06/17
****/

#include"SecondPart.h"


/*
The argz_create_sep function converts the null-terminated string into an
argz vector (returned in argz and argz len) by splitting it into elements at every
occurrence of the character sep.
*/
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len){

	int i;
	(*argz_len) = strlen(string);

	if (NULL == (*argz = (char*)malloc((*argz_len + 1) * sizeof(char))))
		exit(1);

	for (i = 0; i <= (*argz_len); i++){

		if (string[i] == sep){

			(*argz)[i] = '\0';

		}
		else{

			(*argz)[i] = string[i];

		}

	}

	return 0;

}

//Returns the number of elements in the argz vector.
size_t argz_count(const char *argz, size_t arg_len){

	int i, n = 0;

	for (i = 1; i <= arg_len; i++){

		if (argz[i] == '\0' && argz[i - 1] != '\0')
			++n;

	}

	return n;

}

//The argz_add function adds the string str to the end of the argz vector // *argz, and updates *argz and *argz_len accordingly.
error_t argz_add(char **argz, size_t *argz_len, const char *str){

	int i, j, len;
	char *s;
	len = strlen(str);

	if (NULL == (s = (char*)malloc(((*argz_len) + len + 2) * sizeof(char))))
		return 1;


	for (i = 0; i <= (*argz_len); i++)
		s[i] = (*argz)[i];

	j = i;
	(*argz_len) += len + 1;

	for (i = 0; i <= len; i++, j++)
		s[j] = str[i];

	free(*argz);
	(*argz) = s;

	return 0;

}


/*If entry points to the beginning of one of the elements in the argz vector *argz, the argz_delete function will remove this entry and reallocate *argz, modifying *argz and *argz_len accordingly. Note that as destructive argz functions usually reallocate their argz argument, pointers into argz vectors such as entry will then become invalid.
*/
void argz_delete(char **argz, size_t *argz_len, char *entry){

	int i = 0, j = 0, len = 0;
	char *str, *p = *argz;

	while (NULL == strstr(p, entry) && i <= (*argz_len)){

		while ((*argz)[i++] != '\0');
		p = &(*argz)[i];
	
	}
	
	if (i > *(argz_len))
		return;
	
	len = strlen(p) + 1;
	if (NULL == (str = (char*)malloc((*argz_len - len + 1) * sizeof(char)))){
	
		printf("Allocation fail\n");
		exit(1);
	
	}
	
	while (j < i){
	
		str[j] = (*argz)[j];
		j++;
	
	}
	
	j += len;
	while (j <= *(argz_len))
		str[i++] = (*argz)[j++];
	
	*(argz_len) -= len;
	
	free(*argz);
	(*argz) = str;
}


/*
The argz_insert function inserts the string entry into the argz vector *argz at a point just before the existing element pointed to by before, reallocating *argz and updating *argz and *argz_len. If before is 0, entry is added to the end instead (as if by argz_add). Since the first element is in fact the same as *argz, passing in *argz as the value of before will result in entry being inserted at the beginning.
*/
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry){
	
	int i, j, k, len;
	char *p, *str;
	
	if (NULL == before){
	
		argz_add(argz, argz_len, entry);
		return 0;
	
	}
	
	len = strlen(entry) + 1;
	if (NULL == (str = (char*)malloc(((*argz_len) + len + 1) * sizeof(char))))
		return 1;
	
	i = 0;
	p = *argz;

	while (NULL == strstr(p, before) && i <= *(argz_len)){
	
		while ((*argz)[i++] != '\0');
		p = &(*argz)[i];
	
	}
	
	j = k = 0;
	if (i <= *argz_len){

		while (j < i){
		
			str[j] = (*argz)[j];
			j++;
		
		}
	
	}
	else
		i = 0;

	while (k < len)
		str[j++] = entry[k++];

	while (i <= *argz_len)
		str[j++] = (*argz)[i++];

	*argz_len += len;

	free(*argz);
	(*argz) = str;

	return 0;

}


/*
The argz_next function provides a convenient way of iterating over the elements in the argz vector argz. It returns a pointer to the next element in argz after the element entry, or 0 if there are no elements following entry. If entry is 0, the first element of argz is returned.
This behavior suggests two styles of iteration:
char *entry = 0;
while ((entry = argz_next (argz, argz_len, entry)))
action;
(the double parentheses are necessary to make some C compilers shut up about what they consider a questionable while-test) and:
char *entry;
for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
action;
Note that the latter depends on argz having a value of 0 if it is empty (rather than a pointer to an empty block of memory); this invariant is maintained for argz vectors created by the functions here.
*/
char * argz_next(char *argz, size_t argz_len, const char *entry){
	
	int i;
	char *p;
	
	if (NULL == entry)
		return argz;
	
	p = argz;
	i = 0;
	
	while (NULL == strstr(p, entry) && i <= argz_len){
	
		while (argz[i++] != '\0');
		p = &argz[i];
	
	}
	
	while (argz[i++] != '\0');
	
	p = &argz[i];
	if (i < argz_len)
		return p;
	
	return NULL;

}

/*
Replace the string str in argz with string with, reallocating argz as
necessary.
*/
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with){
	
	argz_insert(argz, argz_len, str, with);
	argz_delete(argz, argz_len, str);
	
	return 0;

}

/*prints argz vector */
void argz_print(const char *argz, size_t argz_len){
	
	int i;
	for (i = 0; i <= argz_len; i++)
		printf("%c", argz[i]);
	
	printf("\n");

}



