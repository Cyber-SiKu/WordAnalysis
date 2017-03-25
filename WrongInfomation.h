//
// Created by siku on 3/14/17.
//

#ifndef WORDANALYSIS_WRONGINFOMATION_H
#define WORDANALYSIS_WRONGINFOMATION_H

#include <iostream>
#include <string>

#define MAXSIZE 2

class WrongInfomation {
public:
	WrongInfomation(int line,int number_class);
	friend std::ostream & operator << (std::ostream & out,const WrongInfomation &wi);
	void setSelf(int line,int number_classify);
	static const int ERROR1;    //the character not allow
	static const int ERROR2;    //the source file has been end but the annotation been not
//	static const int ERROR3;
	static const std::string ERRORHIT[MAXSIZE];
	static int lines_;
private:
	int line_;
	int number_classify_;
};

std::ostream &operator<<(std::ostream &out, const WrongInfomation &wi);

#endif //WORDANALYSIS_WRONGINFOMATION_H
