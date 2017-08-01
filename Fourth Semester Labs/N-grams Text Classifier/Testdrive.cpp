/*
 * `file` 			Testdrive.cpp
 * `written` 		July 27 2017 8:03:21
 * `last modified`	August 01 2017 17:05:56
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		testing text classifier
 *
 *	Description: 	text classifier used to classify text to one of given categories
 *					
 *	`note`			none
 */

#include<iostream>
#include<fstream>

#include "TextClassifier.h"

using namespace textclassifier;


int main(){
	const int n = 3;
	const char* prefix = R"(..\N-grams Text Classifier\)";
	if(n==3)
		std::cout << "3" << std::endl;
	else{
		if (n == 3)
			std::cout << "3" << std::endl;
	}
	std::string categories[n] = { "spam", "programming", "finance" };
	TextÑlassifier classifiers[n];

	std::string catfound;
	int i;

	for (i = 0; i < n; i++){
		classifiers[i].setclassification(categories[i]);
		std::string file_name = prefix + categories[i] + ".txt";
		std::ifstream in(file_name);
		classifiers[i].learn(in);
	}

	TextÑlassifier* minscore = &classifiers[0];
	TextÑlassifier text2classify;

	std::string file_name = "toclassify.txt";
	std::ifstream in(file_name);	
	text2classify.learn(in);

	for (i = 1; i < n; i++){

		if (text2classify.score(classifiers[i]) < text2classify.score(*minscore))
			minscore = &classifiers[i];
	}

	catfound = minscore->classification();
	
	return 0;
}
