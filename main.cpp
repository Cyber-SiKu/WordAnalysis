#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>

#include "WrongInfomation.h"
#include "ClassifyValue.h"
#include "Table.h"

using IdTable = Table;
using CostantTable = Table;

std::set<IdTable> id_table;
std::set<CostantTable > constant_table;
/*
 * load key word from file
 * return_value:
 * true ： load successfully
 * false： load failure
 */
bool loadKeyWord(std::string &file_name,std::set<ClassifyValue> & set_key_words);

/*
 * analyse a word from file to id an key_word or constant or symbol
 * if analyse sucess save on the set of CalssValue
 *
 * return value:
 * 1 : analyseword success
 * -1: open source file failure
 * -2: load key word file failure
 */
int analyseWord(const std::string & file_name, std::vector<ClassifyValue> &set_words, std::vector<WrongInfomation> &vector_wrong_infomation);

/*
 * identify id or key word
 */
void idKey_Word(std::ifstream &source_file, ClassifyValue &cv, const std::set<ClassifyValue> KEYWORD);

/*
 * constant include character string and number
 */
void constant(std::ifstream &source_file,ClassifyValue &cv);

/*
 *symbol
 */
void symbol(std::ifstream &source_file,ClassifyValue &cv, std::vector<WrongInfomation> &vector_wrong_infomation);


bool loadKeyWord(std::string &file_name, std::set<ClassifyValue> &set_key_words) {
	bool return_value = false;
	std::ifstream in_file;
	in_file.open(file_name);
	if (!in_file.is_open()) {
		return_value = false;
	} else {
		std::string temp_key_word;
		while(in_file.peek() != EOF){
			in_file>>temp_key_word;
			ClassifyValue temp_classify_value(temp_key_word,temp_key_word);
			set_key_words.insert(temp_classify_value);
		}
		in_file.close();
		return_value = true;
	}
	return return_value;
}


int analyseWord(const std::string &file_name, std::vector<ClassifyValue> &set_words, std::vector<WrongInfomation> &vector_wrong_infomation) {
	int return_value = 0;
	std::ifstream source_file(file_name);
	std::ofstream two_tuples("two_tuples.txt",std::ios::trunc);
	if (!source_file.is_open()) {
		std::cout<<"open source file failure!"<<std::endl;
		return_value = -1;
	}else{
		//load the key words
		std::string file_key_word("./KeyWords.txt");
		std::set<ClassifyValue> KEYWORD;
		if (loadKeyWord(file_key_word,KEYWORD)){
			//load key word sucessfully
			//start to analyses
			char temp;
			ClassifyValue cv;
			while(source_file.peek() != EOF){

				//not in the end of file
				while (source_file.peek() == ' ' || source_file.peek() == '\n' || source_file.peek() == '\r'){
					//delete these character: ' ' '\n' '\r'
					if (source_file.peek() == '\n'){
						++WrongInfomation::lines_;
					}
					source_file.get();
				}
				temp = source_file.peek();
                if (temp == -1){
                    break;
                }

				if ((temp >= 'a' && temp <='z')||(temp >= 'A' && temp <= 'Z') || (temp=='_')){
					//judge the char in the start of word
					//  1. id or key word
					idKey_Word(source_file,cv,KEYWORD);
					IdTable id_temp(cv.getValue(),IdTable::line_type_);
					if (id_table.count(id_temp) == 0 && KEYWORD.count(cv) == 0){
						// the variable has not been declarated
						if (IdTable::line_type_ == "null"){
							// the line of variable is not declarative line;
							//add the wrong infomation
							WrongInfomation wr(WrongInfomation::lines_,WrongInfomation::ERROR1);
							vector_wrong_infomation.push_back(wr);
						} else{
							// the line of variable is declarative line;
							id_table.insert(id_temp);
						}
					}else{

					}
				} else if (temp == '\'' || temp == '\"' || (temp >='0' && temp <='9')){
					//  2. constant (include character string and number)
					constant(source_file,cv);
					CostantTable id_temp(cv.getClassify(),cv.getClassify());
					if (constant_table.count(id_temp) == 0){
						//the constant has not been declarative
						//add it to constant table
						constant_table.insert(id_temp);
					}else{
						//the constant has been in the table
					}
				}else if(temp == ';' || temp == ',' ||
				         temp == '(' || temp == ')' || temp == '[' || temp == ']' || temp == '{' || temp =='}' ||
				         temp == '+' || temp == '-' || temp == '*' || temp == '%' || temp == '/' ||
				         temp == '=' || temp == '<' || temp == '>' || temp == '!' ||
				         temp == '|' || temp == '&') {
					// 3. symbol
					symbol(source_file,cv,vector_wrong_infomation);
//					if (temp != ',' && IdTable::line_type_ != "null") {
//						// the declaration of variable is end
//						IdTable::line_type_ = "null";
//
//					}else{
//
//					}
                    if (cv.getClassify() == "/*" ){
                        ;
                    }else if (cv.getClassify() == "//" ){
                        //the line annotation
                        while (temp != '\n' && temp != '\r'){
                            source_file>>temp;
                            temp = source_file.peek();
                        }
                    }else{}
                }else{
                    //the character which is we can't deal with
                    source_file>>temp;
                    WrongInfomation wr(WrongInfomation::lines_,WrongInfomation::ERROR1);
                    vector_wrong_infomation.push_back(wr);
                    continue;
                }
				two_tuples<<cv<<std::endl;
				set_words.push_back(cv);
			}
			//analyse sucessfully
			return_value = 1;
		}else{
			return_value = -2;
		}
		two_tuples.close();
	}
	source_file.close();
	return  return_value;
}

void idKey_Word(std::ifstream &source_file, ClassifyValue &cv, const std::set<ClassifyValue> KEYWORD) {
	std::string word;
	char temp;
	temp = source_file.peek();
	//we have judge the first char so + (temp >='0' && temp <='9')
	while ((temp >= 'a' && temp <='z')||(temp >= 'A' && temp <= 'Z')||(temp >='0' && temp <='9')||temp=='_'){
		source_file>>temp;
		word.push_back(temp);
		temp = source_file.peek();
	}
	//when we get the key_word or id we left the char which not belong to this word in the stream of source_file
	cv.setSelf(word,word);
	//the word is key_word or id
	if (KEYWORD.count(cv)){
		//key_word
		IdTable ::line_type_ = cv.getClassify();
	} else{
		//id
		cv.setClassify("id");
	}
}

void constant(std::ifstream &source_file, ClassifyValue &cv) {
	std::string word;
	char temp;
	temp = source_file.peek();
	//we have know the first char is ' or " so to find next
	if (temp == '\'' || temp == '\"'){
		//the constant of character or string or number
		source_file>>temp;
		temp = source_file.peek();
		while(temp != '\'' && temp != '\"'){
			source_file>>temp;
			word.push_back(temp);
			temp = source_file.peek();
			temp;
		}
		//delete the unnecessary ' or "
		source_file>>temp;
	} else {
		//constant number
		temp = source_file.peek();
		while(temp >='0' && temp <='9'){
			source_file>>temp;
			word.push_back(temp);
			temp = source_file.peek();
		}
		if (temp == '.'){
			source_file>>temp;
			word.push_back(temp);
			temp = source_file.peek();
			while(temp >='0' && temp <='9'){
				source_file>>temp;
				word.push_back(temp);
				temp = source_file.peek();
			}
		}else{}
	}
	cv.setSelf(word,word);
}

void symbol(std::ifstream &source_file,ClassifyValue &cv, std::vector<WrongInfomation> &vector_wrong_infomation) {
	std::string word;
	char temp;
	source_file>>temp;
	word.push_back(temp);
	if (temp == '+' || temp == '-' || temp == '%' ||
			temp == '=' || temp == '<' || temp == '>' || temp == '!' || temp == '*' || temp == '!'){
		temp = source_file.peek();
		if (temp == '='){
			source_file>>temp;
			word.push_back(temp);
		}else{}
	}else if(temp == '|' || temp == '&'){
		if (temp == source_file.peek()){
			source_file>>temp;
			word.push_back(temp);
		}
	}else if (temp == '/'){
		// divide or annotation;
		temp = source_file.peek();
		if (temp == '='){
			source_file>>temp;
			word.push_back(temp);
		}else if (temp == '*'){
			//annotation
			source_file>>temp;
			word.push_back(temp);
			temp = source_file.peek();
			while (!source_file.eof()){
				if (temp == '*'){
                    source_file>>temp;
                    temp = source_file.peek();
					if (temp == '/'){
						source_file>>temp;
						goto tt;
					}else{}
				}else{}
				temp = source_file.get();
				temp = source_file.peek();
			}
			if (source_file.eof() && word =="/*"){
				WrongInfomation wr(WrongInfomation::lines_,WrongInfomation::ERROR2);
				vector_wrong_infomation.push_back(wr);
			}else{}
		} else if (temp == '/'){
            source_file>>temp;
            word.push_back(temp);
        } else {}
	}else{}
	tt:	cv.setSelf(word,word);
	if (word == "<" || word == "<=" || word == ">" || word == ">=" || word == "=="||word == "!="){
		//relation operator
		cv.setClassify("rlop");
	}else{}
}

int main(int argc,char *argv[]) {
	std::string file_name = "./1.cpp";
//	std::string file_name(argv[1]);
	std::vector<ClassifyValue> set_words;
	std::vector<WrongInfomation> set_wrong_infomation;
	analyseWord(file_name, set_words, set_wrong_infomation);
	for (std::vector<ClassifyValue>::iterator i = set_words.begin(); i != set_words.end(); ++i) {
		std::cout<<*i<<std::endl;
	}

	std::cout<<"id table:"<<std::endl;
	for (std::set<Table>::iterator i = id_table.begin(); i != id_table.end(); ++i) {
		std::cout<<*i<<std::endl;
	}

	std::cout<<"constant table:"<<std::endl;
	for (std::set<Table>::iterator i = constant_table.begin(); i != constant_table.end(); ++i) {
		std::cout<<*i<<std::endl;
	}

	std::cout<<"wrong infomation:"<<std::endl;
	for (std::vector<WrongInfomation>::iterator i = set_wrong_infomation.begin(); i != set_wrong_infomation.end(); ++i) {
		std::cout<<*i<<std::endl;
	}
	return 0;
}
