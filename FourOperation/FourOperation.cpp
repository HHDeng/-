// FourOperation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"stdlib.h"
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<algorithm>
#include<time.h>
#include<sys/timeb.h>
#include<fstream>
using namespace std;
int languageNum,num_i=4;
string str="";
int random(double start, double end)
{
	return (int)(start + (end - start)*rand() / (RAND_MAX + 1.0));
}   //随机数函数

int gcd(int a, int b)       //定义函数gcd 计算 
{
	if (a%b == 0)
		return b;         
	else
		return gcd(b, a%b);     
}////求最大公约数
void strout1(int fenzi, int fenmu)   //根据分子分母随机生成真分数式子
{
	int f = 1 + random(0, 50);
	if (f < 25) {
		if (num_i > 2)
		{
			num_i--;
			int x = 1;
			int y = 1 + random(fenmu, fenmu+3);
			strout1(x, y);
			int sum1 = fenzi*y - x * fenmu;
			int sum2 = fenmu*y;
			int gcd1 = gcd(sum2, sum1);
			x = sum1 / gcd1; y = sum2 / gcd1;
			str = to_string(x) + "/" + to_string(y) + "+"+str;
		}
		else
		{
			int x = 1;
			int y = 1 + random(fenmu, fenmu +3);
			int sum1 = fenzi*y - x * fenmu;
			int sum2 = fenmu*y;
			int gcd1 = gcd(sum2, sum1);
			int x1 = sum1 / gcd1; int y1 = sum2 / gcd1;
			str =str+ to_string(x) + "/" + to_string(y) + "+"+to_string(x1) + "/" + to_string(y1);
		}
	}
	else if (f >= 25 && f < 50) {
		if (num_i > 2)
		{
			num_i--;
			int x = random(1, 10);
			int y = 1 + random(1, 15);
			strout1(x,y);
			int sum1 = fenzi*y + x*fenmu;
			int sum2 = fenmu*y;
			int gcd1 = gcd(sum2, sum1);
			int x1 = sum1 / gcd1; 
			int y1= sum2 / gcd1;
			str = to_string(x1) + "/" + to_string(y1) + "-" + str ;
		}
		else
		{
			int x = random(1, 10);
			int y = 1 + random(1, 15);
			int sum1 = fenzi*y + x*fenmu;
			int sum2 = fenmu*y;
			int gcd1 = gcd(sum2, sum1);
			int x1 = sum1 / gcd1; 
			int y1 = sum2 / gcd1;
			str = str+to_string(x1) + "/" + to_string(y1) + "-"+to_string(x) + "/" + to_string(y);
		}

	}
	
}    //生成
void strout(int ans)           //根据随机数随机生成整数运算式
{
	int f = 1 + random(0,100);
	if (f < 25) {// +
		if (num_i > 2) {
			num_i--;
			int x = random(1,ans); 
			strout(x);
			int y = ans - x;
			if(y>=0)
			str = to_string(y) + "+" + str;

		}
		else {
			int x =  random(1, ans);
			int y = ans - x;
			if(y>=0)
			str = str + to_string(y) + "+" + to_string(x);
		}
	}
	if (f >= 25 && f < 50) {// -
		if (num_i > 2) {
			num_i--;
			int x = random(1, ans);
			strout(x);
			int y = ans + x;
			str = to_string(y) + "-" + "(" + str + ")";

		}
		else {
			int x = random(1, ans);
			int y = ans + x;
			str = str + to_string(y) + "-" + to_string(x);
		}
	}
	if (f >= 50 && f < 75) {// *
		if (num_i > 2) {
			num_i--;
			int x = 0;
			for (int i = (int)sqrt(ans); i > 0; i++) {
				if (ans%i == 0) {
					x = i;
					break;
				}
			}
			int y = ans / x; 
			strout(x);
			str = to_string(y) + "*" + "(" + str + ")";

		}
		else {
			int x = 0;
			for (int i = (int)sqrt(ans); i > 0; i++) {
				if (ans%i == 0) {
					x = i;
					break;
				}
			}
			int y = ans / x;
			str = str + to_string(y) + "*" + to_string(x);
		}
	}
	if (f >= 75) {// /
		if (num_i > 2) {
			num_i--;
			int x = 1 + random(0,10); 
			strout(x);
			int y = ans * x;
			str = to_string(y) + "÷" + "(" + str + ")";

		}
		else {
			int x = 1 + random(0, 10);
			int y = ans * x;
			str = str + to_string(y) + "÷" + to_string(x);
		}
	}
	//str += "=";
	
}  
 
void run2()                                  //进行分数运算
{
	int n, i;
	int trueCount = 0, errCount = 0,ansCount=1,exeCount=1;
	ofstream fout("FracAnswers.txt");
	ofstream fout1("FracExercises.txt");
	num_i = 2;
	cout << "请输入运算式数量：";
	cin >> n;
	i = n;
	while (n--)
	{
		int fenzi,fenmu,gcd1;
		string get,ans;
		//int num1, num2, a;
		//char signal;
		struct timeb timeSeed;
		ftime(&timeSeed);
		srand(timeSeed.time * 1000 + timeSeed.millitm);
		fenzi = random(1,5);
		fenmu = random(2, 10);
		gcd1 = gcd(fenzi, fenmu);
		fenzi = fenzi / gcd1; fenmu = fenmu / gcd1;
		strout1(fenzi,fenmu);
		cout << str << endl;
		fout1 << ansCount++ << "." << str << endl;
		str = "";
		if (fenzi%fenmu == 0) ans = fenzi / fenmu;
		else ans = to_string(fenzi) + "/" + to_string(fenmu);
		cin >> get;
		fout << exeCount++ << "." << ans << endl;
		if (get == ans) trueCount++;
		else errCount++;
		cout << "你完成了：" << i - n << "道题" << "   正确：" << trueCount << "道" << "   错误：" << errCount << "道" << endl << endl;;
	
		num_i = 2;
	}
	}
	
void run()                     //进行整数运算
{
	int n,i;
	int trueCount=0, errCount = 0,ansCount=1,exeCount=1;
	ofstream fout("IntAnswers.txt");
	ofstream fout1("IntExercises.txt");
	cout << "请输入运算式数量：";
	cin >> n;
	i = n;
	while (n--)
	{
		int get,ans;
		//int num1, num2, a;
		//char signal;
		struct timeb timeSeed;
		ftime(&timeSeed);
		srand(timeSeed.time * 1000 + timeSeed.millitm);
		ans = random(1,50);
		fout << ansCount++ << "." << ans << endl;
		strout(ans);
		cout << str << endl;
		fout1<< exeCount++<<"."<<str << endl;
		str = "";
		num_i = 4;
		cin >> get;
		if (get == ans) trueCount++;
		else errCount++;
		cout << "你完成了：" << i - n << "道题" << "   正确：" << trueCount << "道" << "   错误：" << errCount << "道" << endl;
		
	}
}                  
void mainUI()
{
	int choose;
	if (languageNum == 1)
	{
		cout << "                                       *****************主菜单*********************" << endl;
		cout << "                                                     1.整数运算                       " << endl;
		cout << "                                                     2.真分数运算                       " << endl;
		cout << "                                                     2.语言设置                           " << endl;
		cout << "                                                     3.退出                            " << endl << endl << endl;
		cout << "                          请输入选择：";
	}
	cin >> choose;
	if (choose == 1)
	{
		system("cls");
		run();
	}
	if (choose == 2)
	{
		system("cls");
		run2();
	}
	if (choose == 3) exit(0);
}

int main()
{
	languageNum = 1;
	mainUI();
    return 0;
}

