#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;

#define COLUMN 5
//#define ROW 50

int CountLines(string filename)
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename.c_str(),ios::in);//ios::in 表示以只读的方式读取文件
    if(ReadFile.fail())//文件打开失败:返回0
    {
		throw -1;
        return 0;
    }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}
 
template <class Type>  
Type stringToNum(const string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}

void split(const string& s,vector<string>& sv,const char flag = ' ') 
{
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
    return;
}

int main(int argc, char* argv[]) 
{
	//printf("argc:%d", argc);
	if(argc < 4)
	{
		cout << "\033[1;33m";
		printf("Something is not right, input like this: ./Average [dir] [file1] [file2] ... [fileout]\n");
		cout << "\033[0m";
		return 0;
	}
	try
	{
		int input_count = argc - 3;

		if (input_count < 2)
		{
			cout << "\033[1;33m";
			printf("WARNING: Only 1 data file found\n");
			cout << "\033[0m";
		}
		
		//vector<vector<vector<double>>> data;
		vector<vector<double>> output;

		int rows = CountLines(string(argv[1]) + "/" + string(argv[2]));
		int ROW = 0;
		if(rows> 19 && rows <= 49)
			ROW = 20;
		else if(rows > 50 && rows <= 59)
			ROW = 50;
		else if(rows > 60 && rows <= 199)
			ROW = 60;
		else
			ROW = 200;

		output.resize(ROW + 1);
		for(int i = 0;i < ROW + 1; i++)
		{
			output[i].resize(COLUMN);
		}
		output[0][0] = 0.05;
		for(int i = 1;i < COLUMN; i++)
		{
			output[0][i] = 10;
		}

		for(int i = 0;i < input_count;i++)
		{
			int rows_this = CountLines(string(argv[1]) + "/" + string(argv[i+2]));
			string temp;
			fstream file;
			file.open(string(argv[1]) + "/" + string(argv[i+2]),ios::in);
			for(int j = 0; j < rows_this - ROW; j++)
			{
				if(!getline(file,temp,'\n'))
					throw -1;
			}
			for(int j = 0; j < ROW;j++)
			{
				if(!getline(file,temp,'\n'))
					throw -1;
				vector<string> split_string;
				split(temp, split_string, '\t');
				//printf("%s, %s, %s\n", split_string[0].c_str(), split_string[1].c_str(),split_string[2].c_str());
				for(int k = 0; k < COLUMN; k++)
				{
					double data_ = stringToNum<double>(split_string[k]);
					output[j + 1][k] += data_ / input_count;
				}
			}
		}
		//printf("SUC1\n");
		FILE *out = fopen((string(argv[1]) + "/" + string(argv[argc - 1])).c_str(), "w");
		//printf("SUC2\n");
		for(int i = 0; i < output.size(); i++)
		{
			for(int j = 0; j < output[i].size();j++)
			{
				if(j != output[i].size() - 1)
					fprintf(out, "%.6f,", output[i][j]);
				else
					fprintf(out, "%.6f", output[i][j]);
			}
			fprintf(out, "\n");
		}
		fclose(out);
	}
	catch(...)
	{
		cout << "\033[1;31m";
		printf("%s\n", argv[1]);
		printf("输入错误，请确认没有文件/文件夹名字含有空格\n");
		printf("输入错误，请确认文件行数\n");
		cout << "\033[0m";
	}
	return 0;
}