//
// Created by siku on 3/16/17.
//

#ifndef WORDANALYSIS_TABLE_H
#define WORDANALYSIS_TABLE_H

#include <string>
#include <iostream>

class Table {
private:
	std::string name_;
	std::string type_;
	std::string & value_ = type_;
//	int address_;
public:
	static std::string line_type_ ;
	Table(const std::string &name,const std::string &type);
	friend bool operator < (const Table &t1,const Table &t2);
	friend std::ostream &operator<<(std::ostream & out,const Table &t);
};

bool operator<(const Table &t1, const Table &t2);
std::ostream &operator<<(std::ostream & out,const Table &t);

#endif //WORDANALYSIS_TABLE_H
