// MyString.h
// HW_2
// Created by Liangliang Yang on 06/14/2016

#ifndef MYSTRING_H
#define MYSTRING_H
#define _CRT_SECURE_NO_WARNINGS 

#include <string.h>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class MyString
{
public:
	MyString(); //Construct an empty string
	MyString(const char* str); //Construct a MyString with a  specified string
	MyString(const MyString& mstr); //Copy constructor
	MyString& operator=(const char* str); //overloading of = to assign a char* to a MyString
	MyString& operator=(const MyString& mstr); //overloading of = to assign another MyString to MyString
	~MyString(); //Destructor
	int getLength() const;
	char* getValue() const;
	void set(char* str); // set/initialize the string 
	MyString reverse(); //revese the string
	MyString Substring(int startIndex, int length) const;
	bool AreEqual(const char* str1, const char* str2, int compareSize);
	int indexof(char* substr, unsigned int startindex);
	int* indexTable(char c, unsigned int startindex) const;
	int* bad_char_table();
	int* freqTable(const char* s);
	int* freqTable();
	void Split(char c, vector<MyString>& outputVector) const;
	bool isAnagram(MyString str1, MyString str2);
	void GetAnagrams(vector<MyString>& candidates, vector<MyString>& output);

	void Write(ostream& stream);
	void Display(ostream& stream, char* str);

private:
	char* m_str; //m_str as my_str, to be same as the pdf file in class
	int m_len;

};

MyString::MyString()
{
	m_str = NULL;
	m_len = 0;
}

MyString::MyString(const char* str)
{
	// "Deep" copy the string
	int len = std::strlen(str);
	m_len = len;
	m_str = new char[len + 1]; //Allocate enough space for the char*
	std::strcpy(m_str, str);
}

MyString::MyString(const MyString& mstr)
{
	m_str = new char[mstr.getLength() +1]; //since strlen() can only applied to char*, here we need length() function
	std::strcpy(m_str, mstr.getValue());
	m_len = mstr.getLength();
}

MyString& MyString::operator=(const char* str)
{
	if(m_len !=0)
	{
		delete[] m_str; //delete the current string in MyString
	}
	int len = std::strlen(str);
	m_len = len;
	m_str = new char[len + 1]; //Allocate enough space for the char*
	std::strcpy(m_str, str);
	return *this; //return self
}

MyString& MyString::operator=(const MyString& mstr)
{
	if(m_len !=0)
	{
		delete[] m_str; //delete the current string in MyString
	}
	m_str = new char[mstr.getLength() +1]; //since strlen() can only applied to char*, here we need length() function
	std::strcpy(m_str, mstr.getValue());
	m_len = mstr.getLength();
	return *this;
}
 
MyString::~MyString()
{
	if(m_len !=0)
	{
		delete[] m_str;
	}
}

//define MyString.length()
int MyString::getLength() const
{
	return m_len;
}

char* MyString::getValue() const
{
	return m_str;
}

void MyString::set(char* str)
{
	if(m_len !=0)
	{
		delete[] m_str; //delete the current string in MyString
	}
	int len = std::strlen(str);
	m_len = len;
	m_str = new char[len + 1]; //Allocate enough space for the char*
	std::strcpy(m_str, str);
}

MyString MyString::reverse()
{
	char* s = getValue();
	int len = std::strlen(s);
	int i=0;
	char* temp = new char[len+1];
	for (i=0; i<len; i++)
	{
		temp[i] = s[len-i-1];
	}
	temp[i] = '\0';

	return temp;
}

MyString MyString::Substring(int startIndex, int length) const
{
	char* m_substr = new char[length+1];
	m_substr[length] = '\0';
	int j=0;
	for(int i=startIndex; i<startIndex+length; i++)
	{
		m_substr[j] = m_str[i];
		j++;
	}
	
	return m_substr;
}

bool MyString::AreEqual(const char* str1, const char* str2, int compareSize) 
{
	if (*str1 == '\0' && *str2 == '\0')
	{
		return false;
	}

	while(compareSize--)
	{
		if (*str1 != *str2)
		{
			return false;
		}
		str1++;
		str2++;
	}
	return true;
}


int MyString::indexof(char* substr, unsigned int startindex)
{
	int strLen = getLength();
	int substrLen = std::strlen(substr);
	for(int i = startindex; i <= strLen - substrLen; i++)
	{
		if (AreEqual((m_str+i), substr, substrLen))
		{
			return i;
		}
	}

	return -1;
}

int* MyString::bad_char_table()  
{
	char* s = getValue();
	int* badchar = new int[256];
	int i;

	for (i=0; i<256; i++)
	{
		badchar[i] = -1;
	}

	for (i=0; i<getLength()+1; i++)
	{
		badchar[(int) s[i]] = i;
	}


	return badchar;
	delete[] s;
}

int* MyString::freqTable()
{
	int *table = new int[256];
	char* s = getValue();
	for (int i=0; i<256; i++)
	{
		table[i] = 0 ;
	}
	while (*s)
	{
		table[(unsigned char) *s]++;
		s++;
	}
	return table;
}

int* MyString::freqTable(const char* s)
{
	int *table = new int[256];
	for (int i=0; i<256; i++)
	{
		table[i] = 0 ;
	}
	while (*s)
	{
		table[(unsigned char) *s]++;
		s++;
	}
	return table;
}


void MyString::Split(char c, vector<MyString>& outputVector) const 
{
	int start = 0, end = 0;
	int length = getLength();
	while (start < length)
	{
		while(m_str[end] != c && m_str[end])
		{
			end++;
		}

		MyString strTemp;
		strTemp = Substring(start, end-start);
		outputVector.push_back(strTemp);
		start = end+1;
		while(m_str[start] == c)
		{
			start++;
		}
		end = start;
	}
	
}

bool MyString::isAnagram(MyString str1,MyString str2)
{
    
    if (str1.getLength() != str2.getLength()) 
	{
			return false;
	}

	for (int i=0; i<256; i++)
	{
		if (freqTable(str1.getValue())[i] != freqTable(str2.getValue())[i])
		{
			return false;
		}
	}

	return true;
}


void MyString:: GetAnagrams(vector<MyString>& candidates, vector<MyString>& output)
{
	vector<MyString>::const_iterator iter;
	for(iter = candidates.begin(); iter != candidates.end(); iter++)
	{
		if (isAnagram(m_str, *iter))
		{
			output.push_back(*iter);
		}
	}
}



void MyString::Write(ostream& stream)
{
	stream << m_str;
}

void MyString::Display(ostream& stream, char* str)
{
	stream << str;
	stream << '\n';
}


#endif

