/*
 * `file`           TextClassifier.cpp
 * `written`        July 28 2017 10:28:21
 * `last modified`  August 04 2017 22:00:59
 *
 * Author:          R. Neshta
 * Contact:         Ruslan.Neshta@gmail.com
 *
 * `synopsis`       implementation of text classifier class
 *
 * Description:     heavy function of text classifier class realized here
 *					
 * `note`           none
 */
 
#include "TextClassifier.h"


namespace textclassifier{

	int compare(const void * p2f, const void * p2s){
		pair_type *first = (pair_type*)p2f;
		pair_type *second = (pair_type*)p2s;
		
		return first->second<second->second ? 1 : first->second>second->second ? -1 : 0;
	}

	void TextClassifier::process(const std::string &word, frequency_map &buffer)
	{
		for (unsigned required = min; required <= max; ++required){
			std::string n_gram("_");

			int length = word.size();
			for (int i = 0; i <= length; ++i){
			
				int j = i ? i - 1 : i;
				while (n_gram.size() < required && j < length)
					n_gram += word[j++];

				while (n_gram.size() < required)
					n_gram += '_';

				++buffer[n_gram];
				n_gram.clear();
			}
		}
	}

	void TextClassifier::learn(std::istream& in)
	{
		char symbol;
		std::string word;

		in.unsetf(std::ios_base::skipws);
		while (!(in.eof() || in.fail())){
			in >> symbol;

			if ('a' <= symbol && 'z' >= symbol || 'A' <= symbol && 'Z' >= symbol
				|| '\'' == symbol){

				word += symbol;
			}
			
			if (!word.empty()){
				process(word, _freqs);
				word.clear();
			}
		}

		std::vector<pair_type> values;
		for (auto it : _freqs)
			values.emplace_back(it);
		
		std::qsort(&*values.begin(), values.size(), sizeof(pair_type), compare);

		for (unsigned i = 0; i < values.size(); ++i)
			_freqs[values[i].first] = i;
	}

	void TextClassifier::dumpprofile(std::ostream& out)
	{
		out << R"(c This file contains dump from ")" << _classification << R"(" classification.)" << std::endl;
		out << "s" << _classification << std::endl;
		for (auto &i : _freqs)
			out << "n" << i.first << " " << i.second << std::endl;
	}

	void TextClassifier::learnfromdump(std::istream& in)
	{
		char symbol;
		std::string buffer, freq;

		while (!(in.eof() || in.fail())){
			in >> symbol;
			switch(symbol){

			case 's':
				buffer.clear();
				while(symbol!='\0'){
					buffer += symbol;
					in >> symbol;
				}
				_classification = buffer;
				break;

			case 'n':
				buffer.clear();
				while (symbol != ' ' && symbol != '\t'){
					buffer += symbol;
					in >> symbol;
				}

				freq.clear();
				in >> symbol;
				
				while (symbol != '\0'){
					freq += symbol;
					in >> symbol;
				}
				_freqs.emplace(buffer, atol(freq.c_str()));
				break;

			default:
				continue;
			}
		}
	}

	long int TextClassifier::score(const TextClassifier &tc)
	{
		long int distance = 0;
		maximiser maximum;

		for (auto &my : _freqs){
			auto got = tc._freqs.find(my.first);
			
			if (got != tc._freqs.end())
				distance += my.second > got->second ? my.second - got->second : got->second - my.second;
			else
				distance += maximum(_freqs.size());
		}

		return distance;
	}

}

