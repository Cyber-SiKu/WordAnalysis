//
// Created by siku on 3/16/17.
//

#include "Table.h"

Table::Table(const std::string &name, const std::string &type) {
	this->name_ = name;
	this->type_ = type;
}

bool operator<(const Table &t1, const Table &t2) {
	return t1.name_>t2.name_;
}

std::string Table::line_type_ = "null";

std::ostream &operator<<(std::ostream &out,const Table & t) {
	out<<"name: "<<t.name_<<" value(type): "<<t.type_;
	return out;
}
