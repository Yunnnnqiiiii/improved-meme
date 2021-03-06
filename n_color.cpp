#include <string.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
#include<algorithm>
#include <cstdlib> 
#include <ctime> 
using namespace std;
struct node{
	int a[1024];
	int sumNumber;
	int color;
	int c[1024];
	int badColor;
};
struct node2{
	int color;
	vector<int> v;
}; 
struct node2 c[1024];
struct node2 c_copy[1024];
struct node k[1024];
void readData(){
	FILE *fp = fopen("data_500.txt", "r");
    char buf[10000];
    int num=0;
    while(fgets(buf, 10000, fp))
    {
    	int num2=0;
        char *p = strtok(buf, " ");
        p = strtok(NULL, " ");
	    int res = 0;
	    while(p)
	    {
	        
	        k[num].a[num2++]=atoi(p);
	        res++;
	        p = strtok(NULL, " ");
	        
	    }
	    //cout<<num<<":";
	    //for(int i=0;i<num2-1;i++){
	    //	cout<<k[num].a[i]<<" ";
		//}
		k[num].sumNumber=num2-1;
		//cout<<endl;
		num++;
    }

}
void initColor(){
	int s;
	FILE *fp;
	
//	vector<int>::iterator it;
//	unsigned seed;
//	seed = time(0);
//    srand(seed);
//	for(int i=0;i<500;i++){
//		s=rand()%4;
//		k[i].badColor=-1;
//		k[i].color=s;
//		//cout<<k[i].color<<endl;
//		(c[s].v).push_back(i);
//			 
//	}
    fp = fopen("./res_500.txt", "r");//将此文件作为颜色初始化  
	for (int i = 0; i < 500; i++) { 
         fscanf(fp,"%d",&k[i].color);
         s=k[i].color;
         (c[s].v).push_back(i);
         k[i].badColor=-1;
    }
}
void printRes(){
	cout<<"着色结果为："<<endl; 
	vector<int>::iterator it;
	for(int i=0;i<4;i++){
		cout<<i<<" : ";
		for(it=(c[i].v).begin();it!=(c[i].v).end();it++){
			cout<<*it<<" ";
		}
		cout<<endl;
	}
}
int con_num=0;
int conflictNum(){ //计算冲突数 
	int num=0;
	con_num++;
	vector<int>::iterator it,it2;
	for(int i=0;i<500;i++){
		k[i].badColor=-1;
	}
	cout<<"第"<<con_num<<"轮计算冲突为："<<endl; 
	for(int i=0;i<4;i++){
		for(it=(c[i].v).begin();it!=(c[i].v).end();it++){
			for(it2=it+1;it2!=(c[i].v).end();it2++){ 
				for(int j=0;j<k[*it].sumNumber;j++){
					if(k[*it].a[j]==*it2){
						cout<<*it<<" and "<<*it2<<endl;
					    num++;
					    k[*it].badColor=i;
					    
					}
				}
			}
		}
	}
	if(num==0) cout<<"0"<<endl;
	
	//for(int i=1;i<=9;i++){
	//	cout<<k[i].badColor<<" ";
	//}
	//cout<<endl;
	
	return num;
}
int conflictNum2(){ //计算冲突数 
	int num=0;
	vector<int>::iterator it,it2;
	for(int i=0;i<4;i++){
		for(it=(c[i].v).begin();it!=(c[i].v).end();it++){
			for(it2=it+1;it2!=(c[i].v).end();it2++){ 
				for(int j=0;j<k[*it].sumNumber;j++){
					if(k[*it].a[j]==*it2){
						//cout<<"c: "<<*it<<" and "<<*it2<<endl;
					    num++;
					    //k[*it].badColor=i;
					    
					}
				}
			}
		}
	}
	
	
	//if(con_num>=81) cout<<"NUM:"<<num<<endl;
	return num;
}
bool printColor(){
	initColor();
	vector<int>::iterator s;
	int minNum;
	
	while((minNum=conflictNum())!=0){
		//if (con_num>86) break;
		
		//if(con_num>=86){
		//	cout<<"start:"<<endl;
        //    printRes();
		//}
		int sNum=minNum;
		for(int i=0;i<500;i++){
			//if (con_num>=81)cout<<i<<" ";
			if(k[i].badColor==-1) continue;
			int badColor=k[i].badColor;
			for(int j=0;j<4 ;j++){
				if(j==badColor) continue;
				s = find((c[badColor].v).begin(), (c[badColor].v).end(), i);
				(c[badColor].v).erase(s);
				(c[j].v).push_back(i);
				//if(con_num>=86){
				//	cout<<"add:"<<endl;
		        //    printRes();
				//}
				
				conflictNum2();
				
				if(conflictNum2()<=minNum){
					minNum=conflictNum2();
					for(int x=0;x<4;x++){
						vector <int>().swap((c_copy[x].v));
						for(s=(c[x].v).begin();s!=(c[x].v).end();s++){
							(c_copy[x].v).push_back(*s);
						}
					}
					
				}
				(c[badColor].v).push_back(i);
				(c[j].v).pop_back();
				
				
			}
			
		}
		if(sNum!=minNum){
			for(int x=0;x<4;x++){
				vector <int>().swap((c[x].v));
				//(c[x].v).swap(vector<int>());
				for(s=(c_copy[x].v).begin();s!=(c_copy[x].v).end();s++){
					(c[x].v).push_back(*s);
					k[*s].color=x;
				}
			}
			
		}
	}
	return true;
	
}
int main(){
		readData(); 
	if(printColor()) printRes(); 
	return 0;
}
