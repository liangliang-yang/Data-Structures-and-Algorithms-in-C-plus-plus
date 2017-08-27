// Student.h
// HW_6
// Created by Liangliang Yang on 07/02/2016

#ifndef STUDENT_H  // without these, will cause  error as "error C2011: 'Student' : 'class' type redefinition"
#define STUDENT_H

//#pragma once  // also can use this one

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Student
{

private:
	int stu_id;
	string stu_name;

public:
	Student();
	Student(char* studentName, int studentID);
	Student(string& studentName, int studentID);
	//~Student();

	int getID();
	int GetKey();
	string getName();
	//string ToString();
	void write();

};

Student::Student(char* studentName, int studentID)
{
	stu_name = studentName;
	stu_id = studentID;
}

Student::Student(string& studentName, int studentID)
{
	stu_name = studentName;
	stu_id = studentID;
}

int Student::getID()
{
	return stu_id;
}

int Student::GetKey()
{
	return stu_id;
}

string Student::getName()
{
	return stu_name;
}

void Student::write()
{
	cout << stu_name << "," << stu_id << ";" ;
}

#endif
