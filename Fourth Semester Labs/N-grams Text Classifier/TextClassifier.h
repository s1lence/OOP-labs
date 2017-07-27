/*
 * `file` 			TextClassifier.h
 * `written` 		July 27 2017 8:07:53
 * `last modified`	July 27 2017 8:07:53
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		text classifier interface
 *
 *	Description: 	text classifier recognizes text to one of given categories
 *					
 *	`note`			none
 */
 

#ifndef _TEXTCLASSIFIER_H_
#define _TEXTCLASSIFIER_H_

#include<map>

namespace textclassifier{

	/* N-grams frequencies profile */
	typedef std::map<std::string, unsigned long> frequency_map;

	class Text—lassifier {
		
		/* 
		 * `class 			Text—lassifier
		 *
		 * `in 				textclassifier
		 *
		 * `synopsis 		text classifier is simple tool to classify text to one of given categories
		 *
		 * DESCRIPTION: 	class uses n-grams to classify text by calculating distance between texts
		 *
		 * `notes 			none
		 *
		 * `author 			R. Neshta
		 *
		 * `version 		1.0
		 *
		 * `date 			July 27 2017 8:13:15
		 *
		 * Contact: 		Ruslan.Neshta@gmail.com
		 *
		 */
		 
	public:

		/* Name of classification defaults to 'Unknown.' */
		Text—lassifier();

		/*Param classification - name of the classification (e.g., "Spam").    */
		Text—lassifier(const std::string classification);

		/* returns the map N-grams and their frequencies.     */
		frequency_map freqs() { return _freqs; }

		/* returns the name of the classifier.*/
		std::string classification() { return _classification; }

		/*Param classification - name of the classifier.*/
		void setclassification(std::string& classification) { _classification = classification; }

		/*learns the frequencies of N-grams in a corpus.*/
		void Text—lassifier::learn(std::istream& in);

		/*dumps the frequencies of N-grams in a corpus.
		CFile structure is as follows:
		* lines which start with c - comments
		* line which starts with s - classification
		* lines with N-grams start with n  and contain
		* N-gram and its quantity separated with space or tab*/
		void Text—lassifier::dumpprofile(std::ostream& out);

		/*learns the frequencies of N-grams from a file created by.
		* dumpprofile() function */
		void Text—lassifier::learnfromdump(std::istream& in);

		/*returns distance measure between 2 text classifiers*/
		long int Text—lassifier::score(const Text—lassifier &);

	private:
		/*! internal frequency map */
		frequency_map _freqs;
		/*! internal name of classifier */
		std::string _classification;

	};


}

#endif /* _TEXTCLASSIFIER_H_ */