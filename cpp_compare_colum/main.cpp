#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;


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
	if(argc < 3)
	{
		cout << "\033[1;33m";
		printf("Input like this: ./Compare [file1] [file2] ... [fileout_prefix]\n");
		cout << "\033[0m";
		return 0;
	}
	try
	{
		vector<vector<vector<string>>> reshape_datas;
		int file_count = argc - 2;
		int max_row = 0;
		string tmp;
		vector<string> tmp_split;
		ifstream tmpFile;
		tmpFile.open(argv[1],ios::in);
		if(!getline(tmpFile,tmp,'\n'))
			throw -1;
		split(tmp, tmp_split, ',');
		int column_count = tmp_split.size();
		reshape_datas.resize(column_count);
		for(int i = 0;i < column_count;i++)
			reshape_datas[i].resize(file_count);
		
		for(int i = 0;i < file_count; i++)
		{
			ifstream thisFile;
			thisFile.open(argv[i+1],ios::in);
			int rowCount = CountLines(argv[i+1]);
			for (int j =0;j < rowCount;j++)
			{
				string temp;
				vector<string> split_string;
				if(!getline(thisFile,temp))
					throw -1;
				split(temp, split_string, ',');
				for(int k = 0; k < split_string.size();k++)
				{
					reshape_datas[k][i].push_back(split_string[k]);
				}
			}
			if(rowCount > max_row)
				max_row = rowCount;
		}
		//printf("HERE!\n");
		for(int i = 0;i < reshape_datas.size(); i++)
		{
			FILE *out = fopen((string(argv[argc - 1]) + to_string(i+1) + ".csv").c_str(), "w");
			for(int j = 0; j < max_row; j++)
			{
				for(int k = 0; k < file_count; k++)
				{
					if(reshape_datas[i][k].size() > j)
						fprintf(out, "%s,", reshape_datas[i][k][j].c_str());
					else
						fprintf(out, ",");
				}
				fprintf(out, "\n");
			}
			fclose(out);
		}


		
	}
	catch(...)
	{
		cout << "\033[1;31m";
		printf("%s\n", argv[argc - 1]);
		printf("输入错误，请确认没有文件/文件夹名字含有空格\n");
		cout << "\033[0m";
	}
	return 0;
}