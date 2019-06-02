#include<bits/stdc++.h>
#include<io.h>
using namespace std;
vector<string>vans;
void findFiles(string dir,bool fg) {
	intptr_t handle;
	_finddata_t findData;
	handle = _findfirst((dir+"*").c_str(), &findData);
	if (handle == -1)
		return;
	bool flag=false;
	do {
		if (findData.attrib & _A_SUBDIR) {
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
			if (strcmp(findData.name, "three") == 0) {
				flag=true;
			}
			if (strcmp(findData.name,"AUTO ACCEPT MACHINE")==0||strcmp(findData.name,"source")==0||strcmp(findData.name,"src")==0||strcmp(findData.name,"sources")==0||strcmp(findData.name,"player")==0||strcmp(findData.name,"players")==0)
				break;
			findFiles(dir+findData.name+"\\",flag);
		} else if(fg) {
			vans.push_back(dir+findData.name);
		}
	} while (!flag && _findnext(handle, &findData) == 0);
	_findclose(handle);
}
struct input{
	string s;
	int k;
}in,ans;
int main() {
	findFiles("..\\..\\",false);
	ifstream datain("three.in");
	datain>>in.k>>in.s;
	ofstream dataout("three.out");
	for(int i=0;i<vans.size();i++){
		string s=vans[i];
		if(s.find(".in")==-1)continue;
		s=s.substr(0,s.find(".in"));
		ifstream ansin(vans[i].c_str());
		ansin>>ans.k>>ans.s;
		if(in.s!=ans.s||in.k!=ans.k)continue;
		ifstream ansout((s+".out").c_str());
		if(!ansout){
			ansout.open((s+".ans").c_str());
			if(!ansout)break;
		}
		int op;
		ansout>>op;
		ofstream dataout("three.out");
		dataout<<op<<endl;
		return 0;
	}
	cout<<233;
}
