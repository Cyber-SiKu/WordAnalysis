//
// Created by siku on 3/14/17.
//


#include "WrongInfomation.h"

std::ostream &operator<<(std::ostream &out, const WrongInfomation &wi) {
	out<<"the "<<wi.line_+1<<"st line: "<<WrongInfomation::ERRORHIT[wi.number_classify_];
	return out;
}

WrongInfomation::WrongInfomation(int line, int number_class) {
	this->line_ = line;
	this->number_classify_ = number_class;
}

void WrongInfomation::setSelf(int line, int number_classify) {
	this->line_ = line;
	this->number_classify_ = number_classify;
}
const std::string WrongInfomation::ERRORHIT[MAXSIZE]={
/*0*/	std::string("the character is not allow"),
/*1*/	std::string("the source has end but the annotation not been")
};

int WrongInfomation::lines_=0;
// the error : find the character which is not allow
const int WrongInfomation::ERROR1 = 0;
// the file has end but the annotation been not
const int WrongInfomation::ERROR2 = 1;
