#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include "pa3-1.h"

using namespace std;

int isKeyword(string x)
{
    string keywords[] = {"BEGIN", "END", "FOR"};
    for(int i = 0; i<3; i++)
    {
        if(strcmp(x.c_str(),keywords[i].c_str()) == 0)
            return 1;
    }
    return 0;
}

int isOperator(string x)
{
    string operators[] = {"+", "-", "*", "/", "++","="};
    for(int i = 0; i<6; i++)
    {
        if(x.compare(operators[i]) == 0)
            return 1;
    }
    return 0;
}
int isConstant(string x)
{
	if(x.compare("0") == 0)
		return 1;
	else
	{
		int a = atoi(x.c_str());
		if(a)
			return 1;
		else
			return 0;
	}
}

int isDelimiter(string x)
{
    if((x.compare(",") == 0) || (x.compare(";") == 0))
        return 1;
    else
        return 0;
}

int isParenthesis(string x)
{
    if((x.compare("(") == 0) || (x.compare(")") == 0))
        return 1;
    else
        return 0;
}

int isIdentifier(string x)
{
    if(isKeyword(x))
        return 0;
    if(isOperator(x))
        return 0;
    if(isParenthesis(x))
        return 0;
    if(isDelimiter(x))
        return 0;
    if(isConstant(x))
        return 0;
    return 1;
}

void eraseSpaces(string& s)
{
    int i = 0;   
    while (s[i] == ' ')
    {
        i++;
    }
    if(i != 0)
        s = s.substr(i,s.length()-1);
}

int goingback = 0;
int poped = 0;
int depted = 0;
Stack<string> real_keywordStack;
int realdepth = 1;
int depth = 0;
Stack<string> keywordStack;
Stack<string> parenthesisStack;

vector<string> keywordVector;
vector<string> identifierVector;
vector<string> constantVector;
vector<char> delimiterVector;
vector<string> operatorVector;
vector<string> errorVector;
int for_flag = 0;
int depth_flag = 0;
int begin_flag = 0;
int end_flag = 1;
int forlocked = 0;
int beginlocked = 0;

void printVector(vector<string> v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
    	cout<< v[i];
    	if(i+1 != v.size())
    		cout << " ";
    }
    cout << endl;
}
void printVector(vector<char> v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout<< v[i];
        if(i+1 != v.size())
            cout << " ";
    }
    cout << endl;
}

int isLowerCase(char c){
    if(c >= 97 && c <= 122)
        return 1;
    else return 0;
}

int isUpperCase(char c){
    if(c >= 65 && c <= 90)
        return 1;
    else return 0;
}


void parser(char delimiters[], string line, vector<string>& wordVector)
{
    size_t pos = 0;
    size_t prev = 0;
    while ((pos = line.find_first_of(delimiters, prev)) != std::string::npos)
    {
        if (pos > prev)
            wordVector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
    }
    if (prev < line.length())
        wordVector.push_back(line.substr(prev, std::string::npos));
    
    for (size_t i = 0; i < wordVector.size(); ++i)
    {
        char* s = new char[wordVector[i].length()];
        strcpy(s,wordVector[i].c_str());
        //eraseSpaces(s);
        wordVector[i] = s;
    }
}

void exp_parser(char delimiters[], string line, vector<string>& wordVector)
{
    size_t pos = 0;
    size_t prev = 0;
    while ((pos = line.find_first_of(delimiters, prev)) != std::string::npos)
    {
        if (pos > prev)
            wordVector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
        if(pos != std::string::npos)
        {
            if(wordVector.size()>1 && wordVector[wordVector.size()-1].compare("+")==0 && line[pos] == '+')
            {//concatanate
                wordVector[wordVector.size()-1].append("+");
                continue;
            }
/*
            else if(wordVector.size()>1 && wordVector[wordVector.size()-1].compare("-")==0 && line[pos] == '-')
            {//concatanate
                wordVector[wordVector.size()-1].append("-");
                continue;
            }
*/
            else
            {
                string delim = string(1,line[pos]);
                if(delim.compare(" ") != 0)
                    wordVector.push_back(delim);
            }
        }
    }
    if (prev < line.length())
        wordVector.push_back(line.substr(prev, std::string::npos));
}


void for_parser(char delimiters[], string line, vector<string>& wordVector)
{
    size_t pos = 0;
    size_t prev = 0;

    while ((pos = line.find_first_of(delimiters, prev)) != std::string::npos)
    {
        if (pos > prev)
            wordVector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
        if(pos != std::string::npos)
        {
            string delim = string(1,line[pos]);
            if(delim.compare(" ") != 0)
                wordVector.push_back(delim);
        }
    }
    if (prev < line.length())
        wordVector.push_back(line.substr(prev, std::string::npos));
}

void tokenRecognizer(vector<string> wordVector)
{
    for (size_t i = 1; i < wordVector.size(); ++i)
    {
        if(isKeyword(wordVector[i]))
        {
            if(std::find(keywordVector.begin(),keywordVector.end(),wordVector[i]) != keywordVector.end()){}
            else
                keywordVector.push_back(wordVector[i]);            
        }
        if(isConstant(wordVector[i]))
        {
            if(std::find(constantVector.begin(),constantVector.end(),wordVector[i]) != constantVector.end()){}
            else
                constantVector.push_back(wordVector[i]);
        }
        else if(isOperator(wordVector[i]))
        {
            if(find(operatorVector.begin(),operatorVector.end(),wordVector[i]) != operatorVector.end()){}
            else
                operatorVector.push_back(wordVector[i]);
        }
        else if(isDelimiter(wordVector[i]))
        {
            if(find(delimiterVector.begin(),delimiterVector.end(),wordVector[i][0]) != delimiterVector.end()){}
            else
            {
                char d = wordVector[i][0];
                delimiterVector.push_back(d);
            }
        }
        else if(isParenthesis(wordVector[i]))
        {}
        else
        {
            if(find(identifierVector.begin(),identifierVector.end(),wordVector[i])!= identifierVector.end()){}
            else
                identifierVector.push_back(wordVector[i]);
        }
    }
}

int main()
{
    //patched
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    ifstream file(file_name.c_str());
    string line;
    
    Stack<string> s;
    string token;
    vector<string> lineVector;
    Stack<string> ps;
    int endneed = 0;
    if(file.is_open())
    {
        while(getline(file, line))
        {
            eraseSpaces(line);
            lineVector.push_back(line);
        }
        file.close();
    }
    else
    {
       cout << "Failed to open file: " + file_name << endl;
        return 0;
    }
    vector<string> wordVector;
    char for_delimiter[] = "(), ";
    for (size_t i = 0; i < lineVector.size(); ++i)
    {
        if(isUpperCase(lineVector[i][0]))
        {
            for_parser(for_delimiter,lineVector[i],wordVector);
            if(wordVector.size()>1)
            { //for
                int for_validation = 1; 
                if(!for_flag)
                {
                    for_flag = 1;
                    end_flag = 0;
                    begin_flag = 0;
                    //cout << "for flag" << endl;
                    if(depth_flag && !beginlocked && !forlocked)
                    {
                        depth++;
                        endneed++;
                    }
                    if(wordVector[0].compare("FOR") != 0)
                    {
                        for_validation = 0;
                        errorVector.push_back(wordVector[0]);
                        //cout << "wrong for" << endl;
                    }
                    else
                    {
                        if(std::find(keywordVector.begin(),keywordVector.end(),wordVector[0]) != keywordVector.end()){}
                        else
                            keywordVector.push_back(wordVector[0]);                        
                    }
                    for (size_t i = 1; i < wordVector.size(); ++i)
                    {
                        if(isConstant(wordVector[i]))
                        {
                            if(std::find(constantVector.begin(),constantVector.end(),wordVector[i]) != constantVector.end()){}
                            else
                                constantVector.push_back(wordVector[i]);
                        }
                        else if(isOperator(wordVector[i]))
                        {
                            if(find(operatorVector.begin(),operatorVector.end(),wordVector[i]) != operatorVector.end()){}
                            else
                                operatorVector.push_back(wordVector[i]);
                        }

                        else if(isParenthesis(wordVector[i])) {}

                        else if(isDelimiter(wordVector[i]))
                        {
                            if(wordVector[i].compare(",") == 0)
                            {
                                if(find(delimiterVector.begin(),delimiterVector.end(),wordVector[i][0]) != delimiterVector.end()){}
                                else
                                {
                                    char d = wordVector[i][0];
                                    delimiterVector.push_back(d);
                                }
                            }
                            else
                            {
                                for_validation = 0;
                                errorVector.push_back(";");
                            }
                        }
                        else
                        {
                            if(find(identifierVector.begin(),identifierVector.end(),wordVector[i])!= identifierVector.end()){}
                            else
                                identifierVector.push_back(wordVector[i]);
                        }
                    }
                    for (size_t i = 0; i < wordVector.size(); ++i)
                    {

                        if(isParenthesis(wordVector[i]))
                        {
                            if(wordVector[i].compare(")") == 0)
                            {
                                if(!parenthesisStack.isEmpty() && parenthesisStack.top().compare("(") == 0)
                                    parenthesisStack.pop();
                                else
                                    parenthesisStack.push(wordVector[i]);
                            }
                            else
                                parenthesisStack.push(wordVector[i]);
                        }
                    }
                    if(!parenthesisStack.isEmpty())
                    {
                        for_validation = 0;
                        while(!parenthesisStack.isEmpty())
                        {
                            errorVector.push_back(parenthesisStack.pop());
                        }
                    }
                }
                else
                {
                    errorVector.push_back(lineVector[i]);
                    //cout << "invalid for or line" << endl;
                    for_validation = 0;
                }
                if(for_validation){
                    keywordStack.push("FOR");
                    if(!real_keywordStack.isEmpty() && real_keywordStack.top().compare("BEGIN") == 0)
                    {
                        real_keywordStack.push("FOR");
                        
                        if(!goingback)
                        {
                            realdepth++;
                            depted = 1;
                        }
                    }
                    else
                        real_keywordStack.push("FOR");

                }
                else
                {
                    keywordStack.push("X");
                    forlocked++;    
                }
            }
            else if(wordVector.size() == 1)
            { //begin or end

                if(end_flag && keywordStack.isEmpty())
                {
                    errorVector.push_back(wordVector[0]);
                    //cout << "end_flag enable" << endl;
                }
                else
                {
                    keywordStack.push(wordVector[0]);
                    for_flag = 0;
                    if(!begin_flag)
                    {
                        begin_flag = 1;
                        depth_flag = 1;
                        //cout << "begin_flag" << endl;
                        end_flag = 0;
                        if(wordVector[0].compare("BEGIN") !=0 )
                        {
                            errorVector.push_back(wordVector[0]);

                            //cout << "not begin" << endl;
                            
                            beginlocked++;
                            if(!real_keywordStack.isEmpty() && real_keywordStack.top().compare("FOR") == 0)
                            {
                                real_keywordStack.pop();
                                if(depted)
                                    realdepth--;
                            }
                        }
                        else
                        {
                            if(std::find(keywordVector.begin(),keywordVector.end(),wordVector[0]) != keywordVector.end()){}
                            else
                                keywordVector.push_back(wordVector[0]);
                            
                            if(!real_keywordStack.isEmpty() && real_keywordStack.top().compare("FOR") == 0)
                            {
                                real_keywordStack.push(wordVector[0]);
                            }
                        }
                    }
                    else
                    {
                        //cout << "end_flag" << endl;
                        if(keywordStack.pop().compare("END") == 0){}

                        if(keywordStack.pop().compare("BEGIN") != 0)
                            beginlocked--;
                        if(keywordStack.pop().compare("FOR") != 0)
                            forlocked --;

                        depth_flag = 0;
                        end_flag = 1;


                        if(wordVector[0].compare("END") != 0)
                        {
                            errorVector.push_back(wordVector[0]);
                            //cout << "not end" << endl;
                        }
                        else
                        {
                            if(std::find(keywordVector.begin(),keywordVector.end(),wordVector[0]) != keywordVector.end()){}
                            else
                                keywordVector.push_back(wordVector[0]);
                            if(!real_keywordStack.isEmpty() && real_keywordStack.top().compare("BEGIN") == 0)
                            {
                                poped = 1;
                                depted = 0;
                                real_keywordStack.pop();
                                real_keywordStack.pop();
                                if(!real_keywordStack.isEmpty() && real_keywordStack.top().compare("BEGIN") == 0)
                                    goingback = 1;
                            }
                        }
                    }
                }   
            }
            /*cout << "----" << endl;
            keywordStack.print();
            cout << "----" << endl;*/
        }
        else
        {

            if(for_flag && !begin_flag)
            {
                errorVector.push_back(lineVector[i]);
            }
            else
            {
                char exp_delim[] = "=+-*/;() ";
                exp_parser(exp_delim,lineVector[i],wordVector);
                
                tokenRecognizer(wordVector);

                int size = wordVector.size();                        
                        if(wordVector[size-1].compare(";") != 0)
                            errorVector.push_back(";");


                for (int i = 0; i < size; ++i)
                {
                    if(isIdentifier(wordVector[i]) || isConstant(wordVector[i]))
                    {
                        if(!s.isEmpty() && isOperator(s.top()))
                        {
                            s.pop();
                            s.pop();
                            s.push("res");
                        }
                        else
                            s.push(wordVector[i]);

                    }
                    if(isOperator(wordVector[i]))
                    {
                        if(!s.isEmpty() && isIdentifier(s.top()))
                            s.push(wordVector[i]);
                        else if(s.isEmpty() && wordVector[i].compare("++") == 0)
                            s.push(wordVector[i]);
                        else
                            errorVector.push_back(wordVector[i]);
                    }
                    else if(isDelimiter(wordVector[i]))
                    {
                        if(wordVector[i].compare(",") == 0)
                            errorVector.push_back(",");
                        if(wordVector[i].compare(";") == 0)
                        {
                            if(i != size-1)
                                errorVector.push_back(wordVector[i]);
                            else
                                s.pop();
                        }
                    }
                }
            }
        }
	    wordVector.clear();
    }
    /*cout << "====" << endl;
    keywordStack.print();
    cout << "====" << endl;*/

    if(!s.isEmpty())
    {
        while(!s.isEmpty())
        {
            if(s.top().compare("res") != 0)
                errorVector.push_back(s.pop());
            else
                s.pop();
        }
    }
    while(!real_keywordStack.isEmpty())
    {
        string s = real_keywordStack.pop();
        if(s.compare("BEGIN") == 0)
        {
            realdepth--;
            errorVector.push_back("END");
        }
    }
    if(!poped)
        realdepth = 0;
    //output
    cout << "The depth of nested loop(s) is " << realdepth << endl;
    cout << "Keywords: ";
        printVector(keywordVector);
    cout << "Identifier: ";
        printVector(identifierVector);
    cout << "Constant: ";
        printVector(constantVector);
    cout << "Operators: ";
        printVector(operatorVector);
    cout << "Delimiter: ";
        printVector(delimiterVector);
    cout << "Syntax Error(s): ";
    if(errorVector.empty())
        cout << "NA" << endl;
    else
        printVector(errorVector);
    
    return 0;
}


