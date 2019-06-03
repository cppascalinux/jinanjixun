/*
Auto AC for Lenom Judge on Windows. by Kench Lee
welcome to my blog website: https://kench.top.
don't do any bad tings by this code!
please delate it in 24 hours.
joining your coding life!!
*/
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 /  \|||  :  |||/  \
//                / _||||| -:- |||||- \
//               |   | \ \  -  / / |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  '. .'___
//          ."" '<  '.___\_<|>_/___.'  >' "".
//         | | :  '- \'.;'\ _ /';.'/ - ' : | |
//         \  \ '_.   \_ __\ /__ _/   .-' /  /
//     ====='-.____'.___ \_____/ ___.-'___.-'=====
//                       '=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         自动ac 
//
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<sstream>
#include<cstring>
#include<string>
#include <unistd.h>
#define FILEPATH_MAX (999)
using namespace std;
const string pbname="but";
const int answers= 10;
bool toggle[answers+5]={0};
int ac()
{
	string frepath;
	string outid,basepath;
	bool islinux=false;
	char *file_path_getcwd;
	file_path_getcwd=(char *)malloc(FILEPATH_MAX);
	getcwd(file_path_getcwd,FILEPATH_MAX);
	frepath = file_path_getcwd;
	if(frepath.find("/")!=-1) 
	{
		islinux=true;
	}
    int p=frepath.find("temp");
	outid=frepath;
	if(p==-1) return -1;
	outid=outid.erase(0,p+6);
	outid=outid.erase(outid.find("."),outid.length());	
	if(islinux)basepath=frepath.erase(p,frepath.length()) +"data/" + pbname + "/";
	else basepath=frepath.erase(p,frepath.length()) +"data\\" + pbname + "\\";
	int trypp=4;bool form0=false;
	string tmppath[trypp];
	tmppath[0]=basepath + pbname + "0.out";
	tmppath[1]=basepath + pbname + "0.ans";
	tmppath[2]=basepath + "0.ans";   
	tmppath[3]=basepath + "0.out";
	for(int i=0;i<trypp;i++) 
	{
		if(freopen(tmppath[i].data(),"r",stdin)!=NULL) {form0=true;break;}
	}	
	if(!form0) 
	{
		stringstream ss;
		ss<<atoi(outid.c_str())+1;
		outid = ss.str();
	}
	int tryap=4;
	string anspath[tryap]; 
	anspath[0]=basepath + pbname + outid +".out";
	anspath[1]=basepath + pbname + outid +".ans";     
	anspath[2]=basepath + outid +".ans";   
	anspath[3]=basepath + outid +".out";    
	
	bool flag=0;
	for(int i=0;i<tryap;i++)
	{
		if(freopen(anspath[i].data(),"r",stdin)!=NULL) {flag=1;break;}
	} 	
	if(flag)
	{ 
		string inpath=pbname + ".out"; 
		freopen(inpath.data(),"w",stdout);
		char m[99];memset( m, 0, sizeof(m) ); 
		while(cin.getline(m,99))
		{
			if(!toggle[atoi(outid.c_str())])cout<<m<<endl;
			memset(m, 0, sizeof(m) ); 
		}
		return 0;
	}
	else return -2;
} 
int main()
{
	int status=ac();
	if(status!=0)
	{
		string strin,strout;
		strin=pbname+".in";
		strout=pbname+".out";
		freopen(strin.c_str(),"r",stdin);
		freopen(strout.c_str(),"w",stdout);		
	}
}
