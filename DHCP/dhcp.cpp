#include<iostream>
#include<algorithm>
#include<cstring>

const int N=10010;
using namespace std;

struct mesg{
	int ti;
	string sender,getter,type;
	int ip,outime;
}msg[N];

//sever
int n,t_def,t_max,t_min;
string h;
int st[N];   // 0 未分配 1 待分配 2 占用 3 过期 
int outime[N];
string owner[N];

/*
DIS： Discover 
OFR： Offer 
REQ： Request 
ACK： Ack 
NAK：Nak 
*/

int n_msg;


void init(){
	memset(st,0,sizeof st);
	for(int i=1;i<=n;i++) owner[i]="-1";
	memset(outime,0,sizeof outime);
}
void reqpro(mesg&t){
	if(t.getter!=h){
		for(int i=1;i<=n;i++){
			if(owner[i]==t.sender){
				if(st[i]==1){
					st[i]=0;
					owner[i]="-1";
					outime[i]=0;
					return;
				}
			}
		}
	}
	else if(t.ip>=1&&t.ip<=n&&owner[t.ip]==t.sender){
		st[t.ip]=2;
		if(t.outime==0){
			outime[t.ip]=t.ti+t_def;
		}
		else if(t.outime-t.ti>=t_min&&t.outime-t.ti<=t_max){
			outime[t.ip]=t.outime;
		}
		else if(t.outime-t.ti<t_min){
			outime[t.ip]=t_min+t.ti;
		}
		else outime[t.ip]=t_max+t.ti;
		cout<<h<<" "<<t.sender<<" "<<"ACK"<<" "<<t.ip<<" "<<outime[t.ip]<<endl;
	}
	else{
		cout<<h<<" "<<t.sender<<" "<<"NAK"<<" "<<t.ip<<" "<<0<<endl;
	}
}
void dispro(mesg&t){
	int ip=-1,i;
	for(i=1;i<=n;i++){
		if(owner[i]==t.sender){
			ip=i;
			break;
		}
	}
	if(i==n+1){
		for(i=1;i<=n;i++){
			if(st[i]==0){
				ip=i;
				break;
			}
		}
		if(i==n+1){
			for(i=1;i<=n;i++){
				if(st[i]==3){
					ip=i;
					break; 
				}	
			}
			if(i==n+1) return;
		}
	
	}
	st[ip]=1;
	owner[ip]=t.sender;
	if(t.outime==0){
		outime[ip]=t.ti+t_def;
	}
	else if(t.outime-t.ti>=t_min&&t.outime-t.ti<=t_max){
		outime[ip]=t.outime;
	}
	else if(t.outime-t.ti<t_min){
		outime[ip]=t_min+t.ti;
	}
	else outime[ip]=t_max+t.ti;
	cout<<h<<" "<<t.sender<<" "<<"OFR"<<" "<<ip<<" "<<outime[ip]<<endl;
	return;
	
}







void judge(mesg&t){
	if(t.type!="DIS"&&t.type!="REQ") return;
	if(t.getter=="*"&&t.type!="DIS"){
		return;
	}
	else if(t.getter==h&&t.type=="DIS"){
		return;
	}
	if(t.getter!="*"&&t.type=="REQ"){
		reqpro(t);
	}
	else if(t.getter=="*"&&t.type=="DIS") dispro(t);
}


int main(){
	ios::sync_with_stdio(false);
	cin>>n>>t_def>>t_max>>t_min>>h;
	init();
	cin>>n_msg;
	for(int i=1;i<=n_msg;i++){
		cin>>msg[i].ti>>msg[i].sender>>msg[i].getter>>msg[i].type>>msg[i].ip>>msg[i].outime;
		for(int j=1;j<=n;j++){
			if(st[j]==2&&msg[i].ti>=outime[j]){
				st[j]=3;
				outime[j]=0;
			}
			else if(st[j]==1&&msg[i].ti>=outime[j]){
				st[j]=0;
				owner[j]="-1";
				outime[j]=0;
			}
		}
		judge(msg[i]);
	}

	return 0;
}
