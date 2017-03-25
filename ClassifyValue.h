//
// Created by siku on 2/28/17.
//

#ifndef EXICALANALYSIS_CLASSIFYVALUE_H
#define EXICALANALYSIS_CLASSIFYVALUE_H

#include <string>
#include <set>
#include <iostream>

class ClassifyValue {
public:
	ClassifyValue();

	ClassifyValue(const std::string &classify,const std::string &value);
	friend bool operator < (const ClassifyValue & cf1,const ClassifyValue & cf2);
	void setClassify(const std::string & classify);
	friend std::ostream &operator <<(std::ostream &out,const ClassifyValue & cf);
	void setSelf(const std::string & classify,const std::string & value);
	std::string getClassify();
	std::string getValue();

private:
    std::string classify_;
    std::string value_;
};

std::ostream &operator <<(std::ostream &out,const ClassifyValue & cf);
bool operator<(const ClassifyValue &cf1, const ClassifyValue & cf2);

#endif //EXICALANALYSIS_CLASSIFYVALUE_H
