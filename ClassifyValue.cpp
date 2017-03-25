//
// Created by siku on 3/2/17.
//

#include "ClassifyValue.h"

ClassifyValue::ClassifyValue(const std::string &classify,const std::string &value) : classify_(classify),value_(value){}
ClassifyValue::ClassifyValue(){}
bool operator<(const ClassifyValue & cf1, const ClassifyValue & cf2) {
	bool return_value = false;
	if (cf1.classify_ > cf2.classify_){
		return_value = true;
	}
	return return_value;
}

void ClassifyValue::setClassify(const std::string &classify) {
	this->classify_ = classify;
}

std::ostream &operator<<(std::ostream &out, const ClassifyValue &cf) {
	out<<"<"<<cf.classify_<<","<<cf.value_<<">";
	return out;
}

void ClassifyValue::setSelf(const std::string &classify, const std::string &value) {
	this->classify_ = classify;
	this->value_ = value;
}

std::string ClassifyValue::getClassify() {
	return this->classify_;
}

std::string ClassifyValue::getValue() {
	return this->value_;
}
