#include<windows.h>
#include<iostream>
#include<conio.h>
#include<fstream>
#include<random>
#include<vector>
#include<ctime>
using namespace std;
const string aname[5]={"ľ","ʯ","��","��","��"},bname[5]={"��","��","��","��","��"},cname[10]={"����","����","С��","���","����","����","ú̿","����","���","���ؿ���"};
long long matter[50],level,money,healthy;
const long long thingtime[5]={10,20,50,100,5},need[5][2]={{2,3},{1,2},{2,3},{2,1},{2,2}};
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
HWND hWnd=GetConsoleWindow();
string user,file;
bool have;
int Rand(){
	std::mt19937 mt(rand());
	return mt()%RAND_MAX;
}
void color(int f,int b){
	SetConsoleTextAttribute(hOut,f*16+b);
}
string ll2str(long long x){
	string ans="";
	while(x){
		ans=(char)(x%10+'0')+ans;
		x/=10;
	}
	return ans;
}
void out(string wd){
	for(long long i=0;i<wd.size();i++){
		putchar(wd[i]);
		Sleep(Rand()%60+20);
	}
}
void say(string name,string wd){
	cout<<"��"<<name<<"����";
	out(wd);
}
void lb(long long tot){
	for(long long i=0;i<tot;i++)putchar(' ');
}
void wline(){
	color(0,8);
	for(long long i=0;i<41;i++)putchar('-');
}
string randword(const vector<string>&wdlist){
	return wdlist[Rand()%wdlist.size()];
}
string itemname(long long code){
	if(code<5)return aname[code];
	if(code>29)return cname[code-30];
	return aname[code%5]+bname[code/5-1];
}
long long priceof(long long k){
	if(k<5||k>29)switch(k){
		case 0:return 10;
		case 1:return 20;
		case 2:return 75;
		case 3:return 150;
		case 4:return 175;
		case 30:return 3;
		case 31:return 7;
		case 32:return 10;
		case 33:return 15;
		case 34:return 10;
		case 35:return 20;
		case 36:return 25;
		case 37:return 50;
		case 38:return 125;
		case 39:return 500;
	}
	return 10*need[k/5-1][0]+priceof(k%5)*need[k/5-1][0];
}
void setwindow(short r,short c){
	COORD size={c,100};
	SMALL_RECT rc;
	RECT rc2;
	rc.Right=c-1;
	rc.Bottom=r-1;
	rc.Left=rc.Top=0;
	SetConsoleTitle("ToLive");
	SetConsoleWindowInfo(hOut,true,&rc);
	SetConsoleScreenBufferSize(hOut,size);
    GetWindowRect(hWnd, &rc2);
    SetWindowLongPtr(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE)&~WS_THICKFRAME&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
    SetWindowPos(hWnd,NULL,rc2.left,rc2.top,rc2.right-rc2.left,rc2.bottom-rc2.top,NULL);
}
void HideCursor(){
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=false;
	SetConsoleCursorInfo(hOut,&cci);
}
bool SetCursorPosition(short x,short y){
    return SetConsoleCursorPosition(hOut,(COORD){y,x});
}
COORD GetCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo(hOut,&sbi);
    return sbi.dwCursorPosition;
}
void _set(int id,int line,int col1,int col2,string st){
    SetCursorPosition(line,0);
    color(col1/16,col1%16);
    cout<<id<<". "<<st<<endl;
    color(col2/16,col2%16);
}
int choose(const vector<string>&op,int co=240,int uc=15,int sel=0){
	COORD cpos=GetCursorPosition();
	int len=op.size(),s1=cpos.Y,s2=s1,cur=sel;
	vector<int>pos;
	char ch;
	for(int i=0;i<len;i++){
		pos.push_back(s1);
		if(i==sel)SetConsoleTextAttribute(hOut,co);
		cout<<i<<". "<<op[i]<<endl;
		if(i==sel)SetConsoleTextAttribute(hOut,uc);
		s1++;
	}
	while((ch=_getch())!='\r'){
		if(ch==72||ch=='W'||ch=='w'){
			_set(cur,s2+cur,uc,co,op[cur]);
			if(!cur)cur=len-1;
			else cur--;
			_set(cur,s2+cur,co,uc,op[cur]);
		}else if(ch==80||ch=='S'||ch=='s'){
			_set(cur,s2+cur,uc,co,op[cur]);
			if(cur==len-1)cur=0;
			else cur++;
			_set(cur,s2+cur,co,uc,op[cur]);
		}else if(isdigit(ch)){
			int x=ch-'0';
			if(x>=len)continue;
			if(x!=cur){
				_set(cur,s2+cur,uc,co,op[cur]);
				cur=x;
				_set(cur,s2+cur,co,uc,op[cur]);
			}
		}
	}
	SetCursorPosition(cpos.Y+len,0);
	return cur;
}
int main(){
	srand(time(NULL));
	HideCursor();
	setwindow(27,41);
	SetConsoleOutputCP(936);
	color(0,15);
	puts("������......");
	ifstream in("data.sgr");
	if(!in.is_open()){
		out("�Բ���,����ʱ��������,��ȷ����Ĵ浵����");
		getch();
		in.close();
		return 0;
	}
	getline(in,file);
	in>>level>>money>>healthy;
	for(long long i=0;i<40;i++)in>>matter[i];
	system("cls");
	lb(15);
	out("ToLive v1.0.2\n");
	wline();
	color(0,15);
	say("YHX","�Һ��������������...\n");
	say("YHX","�Ҹ���ô�ƺ���?\n");
	cout<<"���㡿��";
	getline(cin,user);
	system("cls");
	if(user!=file){
		say("YHX","ԭ�����ǵ�һ��������!\n");
		level=0;
		money=1000;
		healthy=100;
		memset(matter,0,sizeof(matter));
	}else say("YHX","��,���㰡!\n");
	say("YHX","����,����ǰ��!\n");
	getch();
	while(healthy>0){
		level++;
		system("cls");
		color(0,12);
		lb(15);
		puts("ToLive v1.0.2");
		wline();
		color(0,14);
		cout<<user<<"\n��ң�"<<money<<"\n������"<<healthy<<"\n";
		wline();
		color(0,11);
		cout<<"��"<<level<<"��\n";
		puts("��ı�����");
		have=0;
		for(long long i=0;i<5;i++)if(matter[i]){
			cout<<aname[i]<<"  x"<<matter[i]<<endl;
			have=1;
		}
		for(long long i=5;i<30;i++)if(matter[i]){
			cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
			have=1;
		}
		for(long long i=30;i<40;i++)if(matter[i]){
			cout<<cname[i-30]<<'x'<<matter[i]<<endl;
			have=1;
		}
		if(!have)puts("��");
		wline();
		vector<string>act={"����","��ľ","��ʯ","�ڿ�","����","����","���","�ֵ�","���","����"};
		switch(choose(act)){
			case 0:{
				say("YHX","�����ɹ�!�ظ�1������\n");
				say("��",randword(vector<string>({"...","��...","��˵�������гɹ����ɹ���?"})));
				healthy++;
				getch();
				break;
			}
			case 1:{
				say("YHX","��Ҫ��ʲô�ɼ�ľͷ?\n");
				long long cut=choose(vector<string>({"��!","ľ��","ʯ��","����","�긫","��"}));
				if(!cut){
					say("YHX","�ܺ�!��ɵ���3��ľͷ!���е�ʹ...");
					healthy-=3;
					matter[0]+=3;
				}else{
					if(matter[14+cut]){
						say("YHX","�治��,���ø�ͷ�ɵ���ľͷ!");
						matter[14+cut]--;
						matter[0]+=thingtime[cut-1];
					}else{
						say("YHX","�ǳ��ź�.��û�����ָ�ͷ.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}
				}
				getch();
				break;
			}
			case 2:{
				say("YHX","��Ҫ��ʲô�ɼ�ʯͷ?\n");
				long long cut=choose(vector<string>({"ľ��","ʯ��","����","���","���"}));
				if(matter[5+cut]){
					say("YHX","�治��,���ø��Ӳɵ���ʯͷ!");
					matter[5+cut]--;
					matter[1]+=thingtime[cut];
				}else{
					say("YHX","�ǳ��ź�.��û�����ָ���.\n");
					say("��",randword(vector<string>({"What?","What!","��!","..."})));
				}
				getch();
				break;
			}
			case 3:{
				if(Rand()%2){
					if(Rand()%2){
						say("YHX","�治��!��ֻ�ҵ���ʯͷ.\n");
						say("YHX","��Ҫ��ʲô�ɼ�ʯͷ?\n");
						long long cut=choose(vector<string>({"ľ��","ʯ��","����","���","���"}));
						if(matter[5+cut]){
							say("YHX","���ø��Ӳɵ���ʯͷ!");
							matter[5+cut]--;
							matter[1]+=thingtime[cut];
						}else{
							say("YHX","�ǳ��ź�.��û�����ָ���.\n");
							say("��",randword(vector<string>({"What?","What!","��!","..."})));
						}
					}else{
						if(Rand()%2){
							say("YHX","���ҵ���ú��!\n");
							say("YHX","��Ҫ��ʲô�ɼ�ú��?\n");
							long long cut=choose(vector<string>({"ľ��","ʯ��","����","���","���"}));
							if(matter[5+cut]){
								say("YHX","���ø��Ӳɵ���ú��!");
								matter[5+cut]--;
								matter[36]+=thingtime[cut];
							}else{
								say("YHX","�ǳ��ź�.��û�����ָ���.\n");
								say("��",randword(vector<string>({"What?","What!","��!","..."})));
							}
						}else if(Rand()%2){
							say("YHX","���ҵ�������!\n");
							say("YHX","��Ҫ��ʲô�ɼ�����?\n");
							long long cut=choose(vector<string>({"ʯ��","����","���","���"}));
							if(matter[6+cut]){
								say("YHX","���ø��Ӳɵ�������!");
								matter[6+cut]--;
								matter[37]+=thingtime[cut]/2;
							}else{
								say("YHX","�ǳ��ź�.��û�����ָ���.\n");
								say("��",randword(vector<string>({"What?","What!","��!","..."})));
							}
						}else{
							if(!Rand()%3){
								say("YHX","���ҵ�����ʯ!\n");
								say("YHX","��Ҫ��ʲô�ɼ���ʯ?\n");
								long long cut=choose(vector<string>({"����","���"}));
								if(matter[7+cut]){
									say("YHX","���ø��Ӳɵ�����ʯ!");
									matter[7+cut]--;
									matter[3]+=thingtime[cut]/5;
								}else{
									say("YHX","�ǳ��ź�.��û�����ָ���.\n");
									say("��",randword(vector<string>({"What?","What!","��!","..."})));
								}
							}else if(Rand()%2){
								say("YHX","���ҵ��˻ƽ�!\n");
								say("YHX","��Ҫ��ʲô�ɼ��ƽ�?\n");
								long long cut=choose(vector<string>({"����","���","���"}));
								if(matter[7+cut]){
									say("YHX","���ø��Ӳɵ��˻ƽ�!");
									matter[7+cut]--;
									matter[38]+=thingtime[cut]/5;
								}else{
									say("YHX","�ǳ��ź�.��û�����ָ���.\n");
									say("��",randword(vector<string>({"What?","What!","��!","..."})));
								}
							}else{
								say("YHX","���ҵ������ؿ���!\n");
								if(matter[8]){
									say("YHX","�������ɵ������ؿ���!");
									matter[8]--;
									matter[39]+=1;
								}else{
									say("YHX","�ǳ��ź�.��û�����.\n");
									say("��",randword(vector<string>({"What?","What!","��!","..."})));
								}
							}
						}
					}
				}else{
					long long hurt;
					say("YHX","�������˹���!\n");
					if(choose(vector<string>({"ս��","����"}))){
						hurt=5+Rand()%10;
						healthy-=hurt;
						say("YHX","��������,�������ܵ���");
						cout<<hurt;
						out("���˺�!");
					}else{
						say("YHX","��Ҫ��ʲô��������?\n");
						long long kind=choose(vector<string>({"��!","ľ��","ʯ��","����","�꽣","��"}));
						if(!kind){
							hurt=50+Rand()%10;
							healthy-=hurt;
							matter[34]++;
							say("YHX","����˹���,���ܵ���");
							cout<<hurt;
							out("���˺�!\n");
							say("YHX","����������");
						}else{
							if(matter[kind+9]){
								hurt=100/thingtime[kind-1]+Rand()%10;
								matter[kind+9]--;
								healthy-=hurt;
								matter[34]++;
								say("YHX","����˹���,���ܵ���");
								cout<<hurt;
								out("���˺�,\n");
								say("YHX","����������");
							}else{
								hurt=50+Rand()%10;
								healthy-=hurt;
								say("YHX","�ǳ��ź�.��û�����ֽ�.\n");
								say("YHX","���ܵ���");
								cout<<hurt;
								out("���˺�!\n");
								say("��",randword(vector<string>({"What?","What!","��!","..."})));
							}
						}
					}
				}
				getch();
				break;
			}
			case 4:{
				long long from,to;
				say("YHX","��Ҫ��ʲô����?\n");
				from=choose(vector<string>({"ľ","ʯ","��","��","��"}));
				say("YHX","��Ҫ��ʲô����?\n");
				to=choose(vector<string>({"��","��","��","��","��"}));
				if(from){
					if(matter[0]<need[to][0]||matter[from]<need[to][1]){
						say("YHX","�ǳ��ź�.��û���㹻�Ĳ���.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}else{
						matter[0]-=need[to][0];
						matter[from]-=need[to][1];
						matter[to*5+from+5]++;
						say("YHX","�ɹ����!");
					}
				}else{
					if(matter[0]<need[to][0]+need[to][1]){
						say("YHX","�ǳ��ź�.��û���㹻�Ĳ���.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}else{
						matter[0]-=need[to][0]+need[to][1];
						matter[to*5+5]++;
						say("YHX","�ɹ����!");
					}
				}
				getch();
				break;
			}
			case 5:{
				vector<string>itemnames;
				long long prices[10],codes[10];
				for(long long i=0;i<10;i++){
					codes[i]=Rand()%40;
					prices[i]=priceof(codes[i])+Rand()%20;
					itemnames.push_back(itemname(codes[i])+" "+ll2str(prices[i]));
				}
				say("YHX","��Ҫ����Ʒ��������Ʒ?\n");
				long long ti=choose(vector<string>({"��","��"}));
				if(ti){
					say("YHX","��Ҫ��ʲô?\n");
					long long w=choose(itemnames);
					if(matter[codes[w]]){
						matter[codes[w]]--;
						money+=prices[w];
						say("YHX","�����ɹ�!");
					}else{
						say("YHX","�ǳ��ź�.��û��������Ʒ.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}
				}else{
					say("YHX","��Ҫ��ʲô?\n");
					long long w=choose(itemnames);
					if(prices[w]<=money){
						matter[codes[w]]++;
						money-=prices[w];
						say("YHX","�����ɹ�!");
					}else{
						say("YHX","�ǳ��ź�.��û���㹻��Ǯ.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}
				}
				getch();
				break;
			}
			case 6:{
				long long hurt;
				say("YHX","�������˹���!\n");
				if(choose(vector<string>({"ս��","����"}))){
					hurt=5+Rand()%10;
					healthy-=hurt;
					say("YHX","��������,�������ܵ���");
					cout<<hurt;
					out("���˺�!");
				}else{
					say("YHX","��Ҫ��ʲô��������?\n");
					long long kind=choose(vector<string>({"��!","ľ��","ʯ��","����","�꽣","��"}));
					if(!kind){
						hurt=50+Rand()%10;
						healthy-=hurt;
						matter[34]++;
						say("YHX","����˹���,���ܵ���");
						cout<<hurt;
						out("���˺�!\n");
						say("YHX","����������");
					}else{
						if(matter[kind+9]){
							hurt=100/thingtime[kind-1]+Rand()%10;
							matter[kind+9]--;
							healthy-=hurt;
							matter[34]++;
							say("YHX","����˹���,���ܵ���");
							cout<<hurt;
							out("���˺�,\n");
							say("YHX","����������");
						}else{
							hurt=50+Rand()%10;
							healthy-=hurt;
							say("YHX","�ǳ��ź�.��û�����ֽ�.\n");
							say("YHX","���ܵ���");
							cout<<hurt;
							out("���˺�!\n");
							say("��",randword(vector<string>({"What?","What!","��!","..."})));
					 	}
					}
				}
				break;
			}
			case 7:{
				say("YHX","��Ҫ��ʲô?\n");
				long long cho=choose(vector<string>({"����","����","��С��"}));
				if(!cho){
					say("YHX","��Ҫ��ʲô����?\n");
					long long cut=choose(vector<string>({"��!","ľ��","ʯ��","����","���","���"}));
					if(!cut){
						say("YHX","�ܺ�!��ɵ���3������!���е�ʹ...");
						matter[30]+=3;
						healthy-=3;
					}else{
						if(matter[19+cut]){
							say("YHX","�治��,���ò��Ӳɵ�������!");
							matter[30]+=thingtime[cut-1];
							matter[19+cut]--;
						}else{
							say("YHX","�ǳ��ź�.��û�����ֲ���.\n");
							say("��",randword(vector<string>({"What?","What!","��!","..."})));
						}
					}
				}else if(cho==1){
					say("YHX","��Ҫ��ʲô����?\n");
					long long cut=choose(vector<string>({"ľ��","ʯ��","����","���","���"}));
					if(matter[25+cut]){
						say("YHX","�治��,���ó�ͷ�����˸���!");
						matter[31]+=min(thingtime[cut],matter[30]);
						matter[30]-=min(thingtime[cut],matter[30]);
						matter[25+cut]--;
					}else{
						say("YHX","�ǳ��ź�.��û�����ֳ�ͷ.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}
				}else{
					long long num;
					say("YHX","��Ҫ�ֶ���С��?\n");
					cin>>num;
					if(matter[32]<num){
						say("YHX","�ǳ��ź�,��û����ô��С��.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}else if(matter[31]<num){
						say("YHX","�ǳ��ź�,��û����ô�����.\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
					}else{
						matter[32]+=2*num;
						matter[31]-=num;
						say("YHX","��С��ɹ�!");
					}
				}
				getch();
				break;
			}
			case 8:{
				say("YHX","��ԵĻ��ǳ�!\n");
				if(choose(vector<string>({"��","��"}))){
					say("YHX","����ܳԵ�ȫ����!");
					healthy+=30*matter[33]+50*matter[35];
					matter[35]=0;
					matter[33]=0;
				}else{
					say("YHX","�������Ķ�����!");
					matter[35]+=matter[34]/3;
					matter[33]+=matter[32]/3;
					matter[32]%=3;
					matter[34]%=3;
				}
				getch();
				break;
			}
			case 9:{
				say("YHX","������ʼ!\n");
				long long needed=matter[37]+matter[38]*2+matter[39]*5;
				if(matter[36]>=needed){
					matter[36]-=needed;
					matter[2]+=matter[37];
					matter[4]+=matter[38];
					switch(Rand()%4){
						case 0:{
							matter[36]+=matter[39]*10;
							break;
						}
						case 1:{
							matter[2]+=matter[39]*8;
							break;
						}
						case 2:{
							matter[3]+=matter[39]*6;
							break;
						}
						case 3:{
							matter[4]+=matter[39]*4;
							break;
						}
					}
					matter[37]=0;
					matter[38]=0;
					matter[39]=0;
					say("YHX","Ү,�����ɹ�!");
				}else{
					matter[36]=0;
					say("YHX","��ѽ,������,����ʧ��!");
				}
				getch();
				break;
			}
		}
		ofstream kout("data.sgr");
		kout<<user<<endl<<level<<' '<<money<<' '<<healthy<<endl;
		for(long long i=0;i<40;i++)kout<<matter[i]<<' ';
		kout.close();
		if(level%365==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n��ң�"<<money<<"\n������"<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"��"<<level<<"��\n";
			puts("��ı�����");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("��");
			wline();
			color(0,15);
			int get=Rand()%1000;
			money+=get;
			say("YHX","�������������!\n");
			say("YHX","���յ��˵�һ������.\n");
			say("YHX","��õ���");
			cout<<get;
			out("�����!\n");
			say("��",randword(vector<string>({"��!","�治��!","��ϲ��!"})));
			getch();
		}
		if(level%50==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n��ң�"<<money<<"\n������"<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"��"<<level<<"��\n";
			puts("��ı�����");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("��");
			wline();
			long long hurt;
			color(0,15);
			say("YHX","������Ϯ!��ô��?\n");
			if(choose(vector<string>({"ս��","����"}))){
				hurt=level+Rand()%10;
				healthy-=hurt;
				say("YHX","��������,�������ܵ���");
				cout<<hurt;
				out("���˺�!");
				getch();
			}else{
				say("YHX","��Ҫ��ʲô��������?\n");
				long long kind=choose(vector<string>({"��!","ľ��","ʯ��","����","�꽣","��"}));
				if(!kind){
					hurt=level*8/5+Rand()%10;
					healthy-=hurt;
					matter[34]+=3;
					say("YHX","����˹���,���ܵ���");
					cout<<hurt;
					out("���˺�!\n");
					say("YHX","����������!");
					getch();
				}else{
					if(matter[kind+9]){
						hurt=level*20/thingtime[kind-1]+Rand()%10;
						matter[kind+9]--;
						healthy-=hurt;
						matter[34]++;
						say("YHX","����˹���,���ܵ���");
						cout<<hurt;
						out("���˺�,\n");
						say("YHX","����������");
						getch();
					}else{
						hurt=level*7/5+Rand()%10;
						healthy-=hurt;
						say("YHX","�ǳ��ź�.��û�����ֽ�.\n");
						say("YHX","���ܵ���");
						cout<<hurt;
						out("���˺�!\n");
						say("��",randword(vector<string>({"What?","What!","��!","..."})));
						getch();
					}
				}
			}
			if(healthy<=0)break;
		}
		if(level%4050==0){
			system("cls");
			color(0,12);
			lb(15);
			puts("ToLive v1.0.2");
			wline();
			color(0,14);
			cout<<user<<"\n��ң�"<<money<<"\n������"<<healthy<<"\n";
			wline();
			color(0,11);
			cout<<"��"<<level<<"��\n";
			puts("��ı�����");
			have=0;
			for(long long i=0;i<5;i++)if(matter[i]){
				cout<<aname[i]<<"  x"<<matter[i]<<endl;
				have=1;
			}
			for(long long i=5;i<30;i++)if(matter[i]){
				cout<<aname[i%5]<<bname[i/5-1]<<'x'<<matter[i]<<endl;
				have=1;
			}
			for(long long i=30;i<36;i++)if(matter[i]){
				cout<<cname[i-30]<<'x'<<matter[i]<<endl;
				have=1;
			}
			if(!have)puts("��");
			wline();
			say("YHX","������,\n");
			say("YHX","�㾭����81��ϴ�ٶ��Ҵ�.\n");
			say("YHX","��һ���ǳ�ǿ��.\n");
			say("YHX","��ʱ����ܿ�����.\n");
			say("��","ʲô����?\n");
			say("YHX","�����,��Ϳ����뿪,\n");
			say("YHX","��Ȼ�ͳ�˯�������!\n");
			say("��","ʲô?�㲻������?\n");
			say("YHX","������!\n");
			say("��","������!\n");
			getch();
			for(int i=0;i<10;i++){
				system("color f0");
				Sleep(50);
				system("color 0f");
				Sleep(50);
			}
			system("cls");
			say("��","��?\n");
			say("��","��������?\n");
			say("İ����","���!\n");
			say("��","����˭?\n");
			say("İ����","�ҽ�YHX.\n");
			say("��","YHX?!?!\n");
			say("İ����","����,���Ǻ�YHX.\n");
			say("İ����","�Ҵ���˻�YHX,\n");
			say("İ����","�Ҵ���������������,\n");
			say("��","Ϊʲô��ôҪ��\"��\"...\n");
			say("İ����","����һ�д��¿�ʼ!\n");
			say("İ����","ӭ��ȫ�µ������!\n");
			say("��","������!\n");
			getch();
			money=1000;
			healthy=100;
			memset(matter,0,sizeof(matter));
		}
		kout<<user<<endl<<level<<' '<<money<<' '<<healthy<<endl;
		for(long long i=0;i<40;i++)kout<<matter[i]<<' ';
		kout.close();
	}
	system("cls");
	say("YHX","�治��,��һ���������뿪������.\n");
	getch();
	ofstream kout("data.sgr");
	kout<<"MCH\n0 1000 100\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
	kout.close();
	return 0;
}
