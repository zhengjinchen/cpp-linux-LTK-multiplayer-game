#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <bits/stdc++.h>
#include "card.h"
using namespace std;
#define TY int
#define MAXN 1005
#define MAXM 200005
#define MAXK 27
#define ll long long
#define ull unsigned long long
#define IL inline
#define pb push_back
#define mod (TY)(998244353)
#define INF (TY)(1e9)
#define For(i,a,b) for(TY i=(a);i<=(b);++i)
#define FOR(i,a,b) for(TY i=(a);i<(b);++i)
#define Rof(i,a,b) for(TY i=(a);i>=(b);--i)
#define ROF(i,a,b) for(TY i=(a);i>(b);--i)
#define Edg(i,a) for(TY i=head[a];i;i=s[i].nex)
IL TY qr(){
    TY u=0,v=1;char ch=getchar();
    while(ch<'0'||ch>'9')v=(ch=='-'?-1:1),ch=getchar();
    while(ch>='0'&&ch<='9')u=u*10+(ch-'0'),ch=getchar();
    return u*v;
}IL void qw(TY now){
    if(now<0){putchar('-');now=-now;}
    if(!now){putchar('0');return;}
    if(now>=10)qw(now/10);putchar(now%10+'0');
}IL void qw(TY now,char op){qw(now);putchar(op);}
IL bool ischar(char u){return (u>='a'&&u<='z')||(u>='A'&&u<='Z');}
IL char getc(){
    char ch=getchar();
    while(!ischar(ch))ch=getchar();
    return ch;
}IL string qs(){
    string lst="";char ch=getchar();
    while(!ischar(ch))ch=getchar();
    while(ischar(ch))lst+=ch,ch=getchar();
    return lst;
}IL void ws(string s){FOR(i,0,s.size())putchar(s[i]);}
IL TY Mod(TY k,TY m=mod){return (k>=m?k-m:k);}
IL TY Ceil(TY x,TY y){return x/y+(x%y!=0);}
IL TY Pow(TY a,TY b){
    TY base=a,ans=1;
    while(b){
        if(b&1)ans=ans*base%mod;
        base=base*base%mod;b>>=1;
    }return ans;
}
#define MAXLINK 2048
#define BUFFSIZE 2048
TY cnt=2048;
mt19937 rnd(time(0));
char buff[BUFFSIZE];

int people,Rpeople;

IL string Cstring(char *a);
IL string Cint(TY now);
IL void Send(TY id,string s);
IL void SendAll(string s);
IL pair<TY,string> ReceiveMessage();
IL void stopServer(TY p);
IL string tostr(TY x);

using namespace std;

bool EndGame=0;

// ▲*●*■*◆
// Black/Red/Mei/Fang 
using namespace CARD;
void card_init(){
	init_card();
	init_Kill();
	init_Shan();
	init_Peach();
	init_Jinnang();
	init_Zhuangbei();
	init_Zuoqi();
	init_Fangju();
	// random_shuffle(a+1,a+110);
}

void Action_Guanshi(int cp6, int val);
void Action_Qinglong(int cp6, int val);
void Action_Weapon(int cp6, int cardnum);
void Action_defend(int cp6, int cardnum);
void Action_jianyi(int cp6, int cardnum);
void Action_jiayi(int cp6, int cardnum);
bool check_alive(int cp6);
void Help(int cp6);
void Next_Shandian(int cp6);
string GetCard(int id);
bool Panduan_Lebu(int val);
void Action_Lebu(int cp6, int val);
void Action_Wugu(int cp6);
void Action_Taoyuan(int cp6);
void Action_Wanjian(int cp6);
void Action_Nanman(int cp6);
void Action_Wuzhong(int cp6);
bool check_Peach(int cp6,int Neednum);
int Ask_Peach(int cp6);
bool check_Wuxie();
int Ask_Wuxie(int cp6);
int GetNumber(int cp6);
int EraseCard(int cp6,int id);
int Ask_Shan(int cp6);
int NumberChosen(int cp6,int CardType);
int check(int cp6,int id);
bool isint(string str);
int toint(string str);
int People_Distance(int x1,int x2);
void Action_Sha(int dmgFrom,int dmgTo,int Dmg); // 可以被闪或桃
void Action_Shan(int Id);
void Action_Tao(int healFrom,int healTo);
void Action_Juedou(int actFrom,int actTo); // 可以无懈 
void Action_Guohe(int actFrom,int actTo); // 可以无懈 
int Action_Wuxie(int cp6); // 无懈
void Action_Shunshou(int cp6,int val);

int m,num_alive; // m 个玩家 

void PutCard(int cp6,int id){
	Send(cp6,"【 "+a[id].name+dick[a[id].number]+a[id].Type+" 】 ");
}
void Panding(int id,bool flag){
	SendAll("判定牌为： 【 "+a[id].name+dick[a[id].number]+a[id].Type+" 】\n\n");
	if(flag) SendAll("，判中！\n\n");
	else SendAll("，不中！\n\n");
}

struct PLAYER{
	sockaddr_in have;
    TY id,sockfd,connfd;
	string name;
	bool is_alive;
	bool Has_Lebu,Has_Shandian;
	bool Is_Lebu,Is_Shandian;
	bool Has_jianyi,Has_Jiayi;
	bool Has_kill;
	int blood,Maxblood,Juese;
	int Reach_dis=1;
	int cp6_player_id;
	int weaponcard, defendcard, jianyicard, jiayicard;
	multiset<int> curCard;

	bool IsChupai=1;
	
	void outCard(){
		Send(cp6_player_id,"你现在的血量: "+tostr(blood)+"\n\n");
		Send(cp6_player_id,"-------------------------\n\n");
		Send(cp6_player_id,"你目前拥有的手牌：\n\n");
		string str="";
		for(auto x:curCard) str=str+GetCard(x);
		Send(cp6_player_id,str+"\n\n");
		Send(cp6_player_id,"-------------------------\n\n");

		Send(cp6_player_id,"你目前拥有的装备牌：\n\n");
		str="";
		if(weaponcard) str=str+GetCard(weaponcard);
		if(defendcard) str=str+GetCard(defendcard);
		if(jianyicard) str=str+GetCard(jianyicard);
		if(jiayicard) str=str+GetCard(jiayicard);
		Send(cp6_player_id,str+"\n\n");
		Send(cp6_player_id,"-------------------------\n\n");
	}
	
	void Ready(){ // 没想好 
		SendAll("玩家 "+name+" 进入准备阶段\n\n");
	}
	void Check(){
		if(!Is_Lebu && !Is_Shandian){
			SendAll("玩家 "+name+" 不需要判定，跳过判定阶段\n\n");
			return;
		}
		SendAll("玩家 "+name+" 进入判定阶段\n\n");
		if(Is_Lebu){
			SendAll("判定 乐不思蜀:\n\n");
			SendAll("请等待无懈可击！\n\n");
			if(!check_Wuxie()){
				SendAll("操作被无懈可击！\n\n");
				Is_Lebu=0;
			}else{
				int val=Newcard(),falg=1;
				if(a[val].Type=="●") falg=0;
				Panding(val,falg);
				Is_Lebu=0;
				Has_Lebu=falg;
			}
		}
		if(Is_Shandian){
			SendAll("判定 闪电:\n\n");
			SendAll("请等待无懈可击！\n\n");
			if(!check_Wuxie()){
				SendAll("操作被无懈可击！\n\n");
				Is_Shandian=0;
				Next_Shandian(cp6_player_id);
			}else{
				int val=Newcard(),falg=0;
				if(a[val].Type=="▲" && a[val].number>=2 && a[val].number<=9) falg=1;
				Panding(val,falg);
				Is_Shandian=0;
				if (!falg) Next_Shandian(cp6_player_id);
				else {
					blood-=3;
					if(blood<=0) check_Peach(cp6_player_id,1-blood);
				}
				Has_Shandian=!falg;
			}
		}
	}
	void Mopai(const int &Painum=4){
		SendAll("玩家 "+name+" 进入摸牌阶段，摸 "+tostr(Painum)+" 张牌\n\n");
		for(int i=1;i<=Painum;i++) curCard.insert(Newcard());
		outCard();
	}
	void Chupai(){
		if(!is_alive)return;
		Has_kill = false;
		if(Has_Lebu){
			Has_Lebu=0;
			SendAll("玩家 "+name+" 跳过出牌阶段，进入弃牌阶段\n\n");
			return;
		}
		while(1){
			if(!is_alive)return;
			pair<TY,string> tmp=ReceiveMessage();
			if(tmp.second=="Help"){
				Help(tmp.first);
				continue;
			}
			if(tmp.first!=cp6_player_id) continue;
			if(tmp.second=="0") break;
			if(tmp.second=="Sha"){
				if(a[weaponcard].name!="连弩" && Has_kill) {
					Send(cp6_player_id,"你已经出过杀了！\n\n");
					continue;
				}
				Send(cp6_player_id,"请指定杀的目标：\n\n");
				int val;
				while(1){
					val=GetNumber(cp6_player_id);
					if(val==-1) break;
					if(!check_alive(val)) Send(cp6_player_id,"他已经死了！\n\n");
					else if(People_Distance(cp6_player_id,val)>Reach_dis+jianyicard) Send(cp6_player_id,"你无法杀到对方！请重新输入\n\n");
					else break;
				}
				if(val!=-1){
					Send(cp6_player_id,"请选择一张“杀”：\n\n");
					int num=NumberChosen(cp6_player_id,1);
					if(num!=-1){
						aaa[++cur] = EraseCard(cp6_player_id,num);
						Action_Sha(cp6_player_id,val,1);
					}else{
						Send(cp6_player_id,"已放弃出杀!\n\n");
					}
				}
				else{
					Send(cp6_player_id,"已放弃出杀!\n\n");
				}
				continue;
			}
			else if(tmp.second=="Tao"){
				if(blood==Maxblood)	Send(cp6_player_id,"血量已满，不合法的输入！请重新输入\n\n");
				else{
					Send(cp6_player_id,"请选择一张“桃”：\n\n");
					int num=NumberChosen(cp6_player_id,3);
					if(num!=-1){
						blood++;
						aaa[++cur] = EraseCard(cp6_player_id,num);
						SendAll("玩家 "+name+" 使用了“桃”, 恢复 1 点体力!\n\n");
					}
					else{
						Send(cp6_player_id,"已放弃出桃!\n\n");
					}
				}
			}
			else if(tmp.second=="Jue_Dou"){
				Send(cp6_player_id,"请指定决斗的目标：\n\n");
				int val;
				while(1){
					val=GetNumber(cp6_player_id);
					if(val==-1) break;
					if(!check_alive(val)) Send(cp6_player_id,"他已经死了！\n\n");
					else break;
				}
				if(val!=-1){
					Send(cp6_player_id,"请选择一张“决斗”: \n\n");
					int num=NumberChosen(cp6_player_id,4);
					if(num!=-1){
						aaa[++cur2] = EraseCard(cp6_player_id,num);
						Action_Juedou(cp6_player_id,val);
					}
					else{
						Send(cp6_player_id,"已放弃决斗!\n\n");
					}
				}else{
					Send(cp6_player_id,"已放弃决斗!\n\n");
				}
			}
			else if(tmp.second=="Guo_He"){
				Send(cp6_player_id,"请选择拆谁的牌：\n\n");
				int val;
				while(1){
					val=GetNumber(cp6_player_id);
					if(val==-1) break;
					if(!check_alive(val)) Send(cp6_player_id,"他已经死了！\n\n");
					else break;
				}

				if(val!=-1){
					Send(cp6_player_id,"请选择一张“过河拆桥”：\n\n");
					int num=NumberChosen(cp6_player_id,5);
					if(num!=-1){
						aaa[++cur2] = EraseCard(cp6_player_id,num);
						Action_Guohe(cp6_player_id,val);
					}
					else{
						Send(cp6_player_id,"已放弃过河拆桥!\n\n");
					}
				}else{
					Send(cp6_player_id,"已放弃过河拆桥!\n\n");
				}
			}
			else if(tmp.second=="Shun_Shou"){
				Send(cp6_player_id,"请选择顺谁的牌：\n\n");
				int val;
				while(1){
					val=GetNumber(cp6_player_id);
					if(val==-1) break;
					if(!check_alive(val)) Send(cp6_player_id,"他已经死了！\n\n");
					else if(People_Distance(cp6_player_id,val)>1+Has_jianyi) Send(cp6_player_id,"你无法顺到对方！请重新输入\n\n");
					else break;
				}
				if(val!=-1){
					Send(cp6_player_id,"请选择一张“顺手牵羊”：\n\n");
					int num=NumberChosen(cp6_player_id,6);
					if(num!=-1){
						aaa[++cur2] = EraseCard(cp6_player_id,num);
						Action_Shunshou(cp6_player_id,val);
					}else{
						Send(cp6_player_id,"已放弃出顺手牵羊!\n\n");
					}
				}
				else{
					Send(cp6_player_id,"已放弃出顺手牵羊!\n\n");
				}
			}
			else if(tmp.second=="Wu_Zhong"){
				Send(cp6_player_id,"请选择一张“无中生有”: \n\n");
				int num=NumberChosen(cp6_player_id,7);
				if(num!=-1){
					aaa[++cur2] = EraseCard(cp6_player_id,num);
					Action_Wuzhong(cp6_player_id);
				}
				else{
					Send(cp6_player_id,"已放弃出无中生有!\n\n");
				}
			}
				// case "借刀":
					
				// 	break;
			else if(tmp.second=="Nan_Man"){
				Send(cp6_player_id,"请选择一张“南蛮入侵”: \n\n");
				int num=NumberChosen(cp6_player_id,10);
				if(num!=-1){
					aaa[++cur2] = EraseCard(cp6_player_id,num);
					Action_Nanman(cp6_player_id);
				}
				else{
					Send(cp6_player_id,"已放弃出南蛮入侵!\n\n");
				}
			}
			else if(tmp.second=="Wan_Jian"){
				Send(cp6_player_id,"请选择一张“万箭齐发”: \n\n");
				int num=NumberChosen(cp6_player_id,11);
				if(num!=-1){
					aaa[++cur2] = EraseCard(cp6_player_id,num);
					Action_Wanjian(cp6_player_id);
				}
				else{
					Send(cp6_player_id,"已放弃出万箭齐发!\n\n");
				}
			}
			else if(tmp.second=="Tao_Yuan"){
				Send(cp6_player_id,"请选择一张“桃园结义”: \n\n");
				int num=NumberChosen(cp6_player_id,12);
				if(num!=-1){
					aaa[++cur2] = EraseCard(cp6_player_id,num);
					Action_Taoyuan(cp6_player_id);
				}
				else{
					Send(cp6_player_id,"已放弃出桃园结义!\n\n");
				}
			}
			else if(tmp.second=="Wu_Gu"){
				Send(cp6_player_id,"请选择一张“五谷丰登”: \n\n");
				int num=NumberChosen(cp6_player_id,13);
				if(num!=-1){
					aaa[++cur2] = EraseCard(cp6_player_id,num);
					Action_Wugu(cp6_player_id);
				}
				else{
					Send(cp6_player_id,"已放弃出五谷丰登!\n\n");
				}
			}
			else if (tmp.second=="Le_Bu"){
				Send(cp6_player_id,"请选择乐谁：\n\n");
				int val;
				while(1){
					val=GetNumber(cp6_player_id);
					if(val==-1) break;
					if(!check_alive(val)) Send(cp6_player_id,"他已经死了！\n\n");
					if(Panduan_Lebu(val)) Send(cp6_player_id,"他已经被乐了！\n\n");
					else break;
				}
				if(val!=-1){
					Send(cp6_player_id,"请选择一张“乐不思蜀”：\n\n");
					int num=NumberChosen(cp6_player_id,14);
					if(num!=-1){
						aaa[++cur2] = EraseCard(cp6_player_id,num);
						Action_Lebu(cp6_player_id,val);
					}
					else{
						Send(cp6_player_id,"已放弃乐不思蜀!\n\n");
					}
				}else{
					Send(cp6_player_id,"已放弃乐不思蜀!\n\n");
				}
			}
			else if (tmp.second=="Shan_Dian"){
				if (Is_Shandian) {
					Send(cp6_player_id,"该玩家已经挂闪电了！\n\n");
				}
				else {
					Send(cp6_player_id,"请选择一张闪电：\n\n");
					int num = NumberChosen(cp6_player_id,15);
					if (num!=-1){
						SendAll("玩家 "+name+" 使用了“闪电”！\n\n");
						aaa[++cur2] = EraseCard(cp6_player_id,num);
						Is_Shandian=true;
					}
					else {
						Send(cp6_player_id,"已放弃闪电！\n\n");
					}
				}
			}
			else if (tmp.second=="Jie_Dao");
			else if (tmp.second=="Zhu_Ge") {
				Send(cp6_player_id,"请选择一张“诸葛连弩”: \n\n");
				int num=NumberChosen(cp6_player_id,16);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备诸葛连弩!\n\n");
				}
			}
			else if (tmp.second=="Qing_Gang") {
				Send(cp6_player_id,"请选择一张“青釭剑”: \n\n");
				int num=NumberChosen(cp6_player_id,17);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备青釭剑!\n\n");
				}
			}
			else if (tmp.second=="Shuang_Gu") {
				Send(cp6_player_id,"请选择一张“雌雄双股剑”: \n\n");
				int num=NumberChosen(cp6_player_id,18);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备雌雄双股剑!\n\n");
				}
			}
			else if (tmp.second=="Guan_shi") {
				Send(cp6_player_id,"请选择一张“贯石斧”: \n\n");
				int num=NumberChosen(cp6_player_id,19);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备贯石斧!\n\n");
				}
			}
			else if (tmp.second=="Zhang_Ba") {
				Send(cp6_player_id,"请选择一张“丈八蛇矛”: \n\n");
				int num=NumberChosen(cp6_player_id,21);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备丈八蛇矛!\n\n");
				}
			}
			else if (tmp.second=="Qing_Long"){
				Send(cp6_player_id,"请选择一张“青龙偃月刀”: \n\n");
				int num=NumberChosen(cp6_player_id,20);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备青龙偃月刀!\n\n");
				}
			}
			else if (tmp.second=="Fang_Tian"){
				Send(cp6_player_id,"请选择一张“方天画戟”: \n\n");
				int num=NumberChosen(cp6_player_id,22);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备方天画戟!\n\n");
				}
			}
			else if (tmp.second=="Qi_Lin"){
				Send(cp6_player_id,"请选择一张“麒麟弓”: \n\n");
				int num=NumberChosen(cp6_player_id,23);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_Weapon(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备麒麟弓!\n\n");
				}
			}
			else if (tmp.second=="Ba_Gua"){
				Send(cp6_player_id,"请选择一张“八卦阵”: \n\n");
				int num=NumberChosen(cp6_player_id,26);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_defend(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备八卦阵!\n\n");
				}
			}
			else if (tmp.second=="Jia_Yi") {
				Send(cp6_player_id,"请选择一张“+1马”: \n\n");
				int num=NumberChosen(cp6_player_id,25);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_jiayi(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备+1马!\n\n");
				}
			}
			else if (tmp.second=="Jian_Yi") {
				Send(cp6_player_id,"请选择一张“-1马”: \n\n");
				int num=NumberChosen(cp6_player_id,24);
				if(num!=-1){
					int erase_card = EraseCard(cp6_player_id,num);
					Action_jianyi(cp6_player_id,erase_card);
				}
				else{
					Send(cp6_player_id,"已放弃装备-1马!\n\n");
				}
			}
			else{
				Send(cp6_player_id,"无效输入！\n\n");
			}
		}
		SendAll("玩家 "+name+" 结束出牌阶段，进入弃牌阶段\n\n");
	}
	void Qipai(){
		while(curCard.size()>blood){
			Send(cp6_player_id,"请选择一张弃置的牌：\n\n");
			int num=NumberChosen(cp6_player_id,0);
			int erase_card=EraseCard(cp6_player_id,num);
			SendAll("玩家 "+name+" 弃置了 "+GetCard(erase_card)+" ！\n\n");
			aaa[++cur2] = erase_card;
		}
	}
}P[100];

int People_Distance(int x1,int x2){
	int cnt1=0,cnt2=0;
	int num1=x1;
	while (num1 != x2) {
		num1=(num1%m)+1;
		if (P[num1].is_alive) cnt1++;
	}
	while (num1 != x1) {
		num1=(num1%m)+1;
		if (P[num1].is_alive) cnt2++;
	}
	cnt1 = min(cnt1, cnt2);
	if (P[x1].jianyicard) cnt1--;
	if (P[x2].jiayicard) cnt1++;
	return max(cnt1, 1);
}

void Game(){
	for(int i=1;i<=m;i++) P[i].Mopai();
	while(!EndGame){
		for(int i=1;i<=m;i++){
			if(!P[i].is_alive) continue;
			P[i].Ready();
			P[i].Check();
			P[i].Mopai(2);
			P[i].Chupai();
			P[i].Qipai();
		}
	}
}
void Player_init(){
	m=people;
	num_alive=m;
	for(int i=1;i<=m;i++){
		P[i].is_alive=1;
		P[i].Has_Lebu=P[i].Has_Shandian=0;
		P[i].Is_Lebu=P[i].Is_Shandian=0;
		P[i].Has_jianyi=P[i].Has_Jiayi=0;
		P[i].blood=4;
		P[i].Maxblood=4;
		P[i].Juese=114514;
		P[i].Reach_dis=1;
		P[i].cp6_player_id=i;
		P[i].curCard.clear();
		P[i].weaponcard=P[i].defendcard=P[i].jianyicard=P[i].jiayicard;
	}
}

int main(){
	srand(time(0));
   	printf("Please input number of people: \n");
   	Rpeople=qr(),people=Rpeople;
	card_init(); Player_init();
   	For(i,1,people){
   	    if(i!=people+1)printf("Run At %d\n\n",i);
   	    else printf("Init root\n\n");
   	    P[i].sockfd=socket(AF_INET, SOCK_STREAM, 0);
   	    bzero(&P[i].have,sizeof(P[i].have));
  	     P[i].have.sin_family = AF_INET;
   	    P[i].have.sin_addr.s_addr = htonl(INADDR_ANY);
       cerr<<"cnt "<<cnt<<endl;
   	    P[i].have.sin_port = htons(++cnt);
   	    cerr<<"debug "<<P[i].name<<' '<<P[i].sockfd<<endl;
   	    if(-1==bind(P[i].sockfd,(struct sockaddr*)&P[i].have,sizeof(P[i].have))){
   	        printf("Bind error(%d): %s\n", errno, strerror(errno));
  	         For(i,1,people)stopServer(i);
   	        return -1;
   	    }if(-1==listen(P[i].sockfd,MAXLINK)){
   	        printf("Listen error(%d): %s\n", errno, strerror(errno));
           return -1;
   	    }printf("Listening...\n");
       P[i].connfd=accept(P[i].sockfd,NULL,NULL);
       printf("ok\n");
       close(P[i].sockfd);
   }printf("Everyone link ok!\n");
   TY cnt=people;bool ok[32];
   memset(ok,0,sizeof(ok));
   while(cnt){
       bzero(buff,sizeof(buff));
       For(i,1,people+1){
           TY len_recv=recv(P[i].connfd,buff,sizeof(buff),MSG_DONTWAIT);
           if(len_recv==-1){
               if(errno==EAGAIN||errno==EWOULDBLOCK)continue;
           }else if(len_recv>0){
               if(!ok[i]){
                   ok[i]=1;--cnt;
                   P[i].name=Cstring(buff);
                   cerr<<"recieve "<<P[i].name<<endl;
               }break;
           }else if(len_recv == 0){
               printf("client closed\n");
               exit(0);
           }
       }
   }
   while(1) Game();
   For(i,1,people)stopServer(P[i].sockfd);
   printf("Close");
   exit(0);
}
IL string Cstring(char *a){
    string lst="";TY len=strlen(a);
    FOR(i,0,len)lst+=a[i];
    return lst;
}IL string Cint(TY now){
    string lst="";
    while(now)lst+=char(now%10+'0'),now/=10;
    reverse(lst.begin(),lst.end());
    return lst;
}IL pair<TY,string> ReceiveMessage(){
    bzero(buff,sizeof(buff));
    For(i,1,people)if(1){
        TY len_recv=recv(P[i].connfd,buff,sizeof(buff),MSG_DONTWAIT);
        if(len_recv==-1){
            if(errno==EAGAIN||errno==EWOULDBLOCK)continue;
        }else if(len_recv>0){
            return {i,Cstring(buff)};
        }else if(len_recv == 0){
            printf("client closed\n");
            exit(0);
        }
    }return {-1,""};
}IL void Send(TY id,string s){
	// s+="\n";
    send(P[id].connfd,s.c_str(),strlen(s.c_str()),0);
}IL void SendAll(string s){
    For(i,1,people)Send(i,s);
}IL bool CheckMessage(string s){
    FOR(i,0,s.size())if(s[i]=='['||s[i]==']'||s[i]==':')return false;
    return true;
}IL TY IsInt(string s){
    TY sum=0;
    FOR(i,0,s.size()){
        if(s[i]==' '||s[i]=='\0'||s[i]=='\b'||s[i]=='\n'||(s[i]>='0'&&s[i]<='9')){
            if(s[i]>='0'&&s[i]<='9')sum=sum*10+(s[i]-'0');
            if(sum>1000)return -1;
        }else{
            return -1;
        }
    }if(sum>Rpeople)return -1;
    return sum;
}IL void stopServer(TY p){
    close(p);
    printf("%d's server is close\n",p);
}IL string tostr(TY x){
	string s="";
	while(x) s+=(char)(x%10+48),x/=10;
	reverse(s.begin(),s.end());
	return s;
}
bool isint(string str){
	for(int i=0;i<str.size();i++) if(!isdigit(str[i]) && str[i]!='\n' && str[i]!='\b' && str[i]!=' ' && str[i]!='\r') return 0;
	return 1;
}
int toint(string str){
	int val=0;
	for(int i=0;i<str.size();i++) val=val*10+str[i]-'0';
	if(val<0) return 0;
	return val;
}
int check(int cp6,int id){
	if(P[cp6].curCard.size()<id) return 0;
	auto it=P[cp6].curCard.begin();
	while(id--) it++;
	return a[*it].id;
}
int NumberChosen(int cp6,int CardType){
	int numberChosen;
	pair<TY,string> Goal;
	while(1){
		do{
			Goal=ReceiveMessage();
		}while(Goal.first!=cp6);
		if(isint(Goal.second)){
			numberChosen=toint(Goal.second);
			int Id=check(cp6,numberChosen);
			if(Id==CardType || !CardType) return numberChosen;
		}
		else if(Goal.second=="No" && CardType) return -1;
		Send(cp6,"不合法的输入！请重新输入\n\n");
	}
}

void Action_Sha(int dmgFrom,int dmgTo,int Dmg){
	P[dmgFrom].Has_kill=true;
	SendAll("玩家 "+P[dmgFrom].name+" 对 "+P[dmgTo].name+"出杀!\n\n");
	if (P[dmgTo].defendcard && P[dmgFrom].weaponcard!=95){
		SendAll("玩家 "+P[dmgTo].name+" 使用了八卦阵\n\n");
		int val=Newcard(),falg=0;
		if(a[val].Type=="●"||a[val].Type=="◆") falg=1;
		Panding(val,falg);
		if (falg) {
			SendAll("玩家 "+P[dmgTo].name+" 视为使用了一张闪\n\n");
			if (P[dmgFrom].weaponcard==98) Action_Qinglong(dmgFrom, dmgTo);
			if (P[dmgFrom].weaponcard==97) Action_Guanshi(dmgFrom,dmgTo);
			return;
		}
		else SendAll("玩家 "+P[dmgTo].name+" 仍需打出闪！\n\n");
	}
	int num=Ask_Shan(dmgTo);
	if(num!=-1){
		aaa[++cur2] = EraseCard(dmgTo,num);
		SendAll("玩家 "+P[dmgTo].name+" 出闪, 不受伤害!\n\n");
		if (P[dmgFrom].weaponcard==98) Action_Qinglong(dmgFrom, dmgTo);
		if (P[dmgFrom].weaponcard==97) Action_Guanshi(dmgFrom,dmgTo);
		return;
	}
	SendAll("玩家 "+P[dmgTo].name+" 受到伤害!\n\n");
	P[dmgFrom].outCard();
	P[dmgTo].blood--;
	if(P[dmgTo].blood<=0) check_Peach(dmgTo,1-P[dmgTo].blood);
}
int GetNumber(int cp6){
	pair<TY,string> Goal;
	while(1){
		do{
			Goal=ReceiveMessage();
		}while(Goal.first!=cp6);
		if(isint(Goal.second)){
			int val=toint(Goal.second); 
			if(val>=1 && val<=m && val!=cp6) return val;
		}
		else if(Goal.second=="No") return -1;
		Send(cp6,"不合法的输入！请重新输入\n\n");
	}
}
int Ask_Shan(int cp6) {
	Send(cp6,"请出一张闪,输入 No 放弃出闪,否则输入你要出的编号\n\n");
	int num=NumberChosen(cp6,2);
	return num;
}
bool Ask_Sha(int cp6) {
	Send(cp6,"请出一张杀\n\n");
	if (P[cp6].weaponcard==99) {
		Send(cp6,"你是否想要使用丈八蛇矛？\n\n");
		int num=NumberChosen(cp6,0);
		if (num!=-1) {
			aaa[++cur2]=NumberChosen(cp6,0);
			aaa[++cur2]=NumberChosen(cp6,0);
			return true;
		}
	}
	Send(cp6,"请选择一张杀\n\n");
	int num=NumberChosen(cp6,1);
	if (num==-1)return false;
	aaa[++cur2]=num;
}
int EraseCard(int cp6,int id){
	auto it=P[cp6].curCard.begin();
	while(id--) it++;
	int erase_card = (*it);
	P[cp6].curCard.erase(it);
	P[cp6].outCard();
	return erase_card;
}
void Action_Juedou(int cp6,int val){
	SendAll("玩家 "+P[cp6].name+" 对 "+P[val].name+" 使用了“决斗”！\n\n");
	SendAll("请等待无懈可击！\n\n");
	if(!check_Wuxie()){
		SendAll("操作被无懈可击！\n\n");
		return;
	}
	for(int cur=val;;cur^=(val^cp6)){
		SendAll("轮到 "+P[cur].name+" 出杀!\n\n");
		Send(cur,"请你出杀,否则受到伤害. 如果不出杀, 输入 No!\n\n");
		int num=NumberChosen(cur,1);
		if(num==-1){
			SendAll("玩家 "+P[cur].name+" 不出杀,受到伤害!\n\n");
			P[cur].blood--;
			if(P[cur].blood<=0) check_Peach(cur,1-P[cur].blood);
			break;
		}else{
			SendAll("玩家 "+P[cur].name+" 出杀!\n\n");
			aaa[++cur2] = EraseCard(cur,num);
		}
	}
}
void Action_Guohe(int cp6,int val){
	SendAll("玩家 "+P[cp6].name+" 对 "+P[val].name+" 使用了“过河拆桥”！\n\n");
	SendAll("请等待无懈可击！\n\n");
	if(!check_Wuxie()){
		SendAll("操作被无懈可击！\n\n");
		return;
	}
	SendAll("操作没有被无懈！正常执行！\n\n");
	Send(cp6,"请选择拆他的哪张牌！\n\n");
	Send(cp6,"手牌编号在 0 至 "+tostr(P[val].curCard.size()-1)+" 之间!\n\n");
	Send(cp6,"装备牌编号在 101 至 104 之间!\n\n");
	pair<TY,string> Goal; int num;
	while(1){
		do{
			Goal=ReceiveMessage();
		}while(Goal.first!=cp6);
		if(isint(Goal.second)){
			int tmp=toint(Goal.second);
			if((tmp>=0 && tmp<P[val].curCard.size())||(tmp>=101&&tmp<=104)){
				num=tmp;
				break;
			}
		}
		Send(cp6,"不合法的输入！请重新输入\n\n");
	}
	if(num<P[val].curCard.size()){
		num=rnd()%P[val].curCard.size();
		int erase_card=EraseCard(val,num);
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“过河拆桥”，拆掉了其 "+GetCard(erase_card)+"\n\n");
		aaa[++cur2] = erase_card;
	}
	else{
		if(num==101){
			SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“过河拆桥”，拆掉了其 "+GetCard(P[val].weaponcard)+"\n\n");
			aaa[++cur2] = P[val].weaponcard;
			P[val].weaponcard=0; P[val].Reach_dis=1;
		}
		else if (num==102){
			SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“过河拆桥”，拆掉了其 "+GetCard(P[val].defendcard)+"\n\n");
			aaa[++cur2] = P[val].defendcard;
			P[val].defendcard=0;
		}
		else if (num==103){
			SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“过河拆桥”，拆掉了其 "+GetCard(P[val].jianyicard)+"\n\n");
			aaa[++cur2] = P[val].jianyicard;
			P[val].jianyicard=0;
		}
		else if (num==104){
			SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“过河拆桥”，拆掉了其 "+GetCard(P[val].jiayicard)+"\n\n");
			aaa[++cur2] = P[val].jiayicard;
			P[val].jiayicard=0;
		}
	}
}
void Action_Shunshou(int cp6,int val){
	SendAll("玩家 "+P[cp6].name+" 对 "+P[val].name+" 使用了“顺手牵羊”！\n\n");
	SendAll("请等待无懈可击！\n\n");
	if(!check_Wuxie()){
		SendAll("操作被无懈可击！\n\n");
		return;
	}
	SendAll("操作没有被无懈！正常执行！\n\n");
	Send(cp6,"请选择顺他的哪张牌！\n\n");
	Send(cp6,"手牌编号在 0 至 "+tostr(P[val].curCard.size()-1)+" 之间!\n\n");
	Send(cp6,"装备牌编号在 101 至 104 之间!\n\n");
	pair<TY,string> Goal; int num;
	while(1){
		do{
			Goal=ReceiveMessage();
		}while(Goal.first!=cp6);
		if(isint(Goal.second)){
			int tmp=toint(Goal.second);
			if((tmp>=0 && tmp<P[val].curCard.size())||(tmp>=101&&tmp<=104)){
				num=tmp;
				break;
			}
		}
		Send(cp6,"不合法的输入！请重新输入\n\n");
	}
	if(num<P[val].curCard.size()){
		num=rnd()%P[val].curCard.size();
		// auto it=P[val].curCard.begin();
		// int dk=num; while(dk--) it++;
		int erase_card = EraseCard(val, num);
		P[cp6].curCard.insert(erase_card);
		P[cp6].outCard();
	}
	else{
		if (num==101) {
			P[cp6].curCard.insert(P[val].weaponcard);
			P[cp6].outCard();
			P[val].weaponcard=0;P[val].Reach_dis=1;
		}
		else if (num==102){
			P[cp6].curCard.insert(P[val].defendcard);
			P[cp6].outCard();
			P[val].defendcard=0;
		}
		else if (num==103){
			P[cp6].curCard.insert(P[val].jianyicard);
			P[cp6].outCard();
			P[val].jianyicard=0;
		}
		else if (num==104){
			P[cp6].curCard.insert(P[val].jiayicard);
			P[cp6].outCard();
			P[val].jiayicard=0;
		}
	}
	SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了“顺手牵羊”！\n\n");
}
bool check_Wuxie(){
	int flag=1; // 1 生效
	while(1){
		bool Changed=0;
		for(int i=1;i<=m;i++){
			if(!P[i].is_alive) continue;
			int num=Ask_Wuxie(i);
			if(num==-1) continue;
			SendAll("玩家 "+P[i].name+" 使用了“无懈可击”！\n\n");
			aaa[++cur2] = EraseCard(i,num);
			flag^=1; Changed=1; break;
		}
		if(!Changed) break;
	}
	return flag;
}
int Ask_Wuxie(int cp6){
	Send(cp6,"请出一张无懈可击！如果不出请输入 No.\n\n");
	int num=NumberChosen(cp6,9);
	return num;
}
bool check_Peach(int cp6,int Neednum){
	for(int i=1;i<=m;i++){
		if (!P[i].is_alive) continue;
		while(Neednum){
			int num=Ask_Peach(i);
			if(num==-1) break;
			SendAll("玩家 "+P[i].name+" 使用了“桃”！\n\n");
			P[cp6].blood++; Neednum--;
			aaa[++cur2] = EraseCard(i,num);
		}
	}
	if(Neednum){
		SendAll("玩家 "+P[cp6].name+" 死了！\n\n");
		P[cp6].is_alive=false;
		num_alive--;
		return 0;
	}
	return 1;
}
int Ask_Peach(int cp6){
	Send(cp6,"请出一张桃！如果不出请输入 No.\n\n");
	int num=NumberChosen(cp6,3);
	return num;
}
void Action_Wuzhong(int cp6){
	SendAll("玩家 "+P[cp6].name+" 使用了“无中生有”！\n\n");
	SendAll("请等待无懈可击！\n\n");
	if(!check_Wuxie()){
		SendAll("操作被无懈可击！\n\n");
		return;
	}
	SendAll("操作没有被无懈！正常执行！\n\n");
	int cur=Newcard(); P[cp6].curCard.insert(cur);
	cur=Newcard(); P[cp6].curCard.insert(cur);
	P[cp6].outCard();
}
void Action_Nanman(int cp6){
	SendAll("玩家 "+P[cp6].name+" 使用了“南蛮入侵”！\n\n");
	for(int i=1;i<=m;i++){
		if (!P[i].is_alive) continue;
		if(i==cp6) continue;
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[i].name+" 使用了南蛮入侵！\n\n");
		SendAll("请等待无懈可击！\n\n");
		if(!check_Wuxie()){
			SendAll("操作被无懈可击！\n\n");
			continue;
		}
		SendAll("操作没有被无懈！正常执行！\n\n");
		Send(i,"请你出一张“杀”，否则减少一点体力！\n\n");
		int num=NumberChosen(i,1);
		if(num==-1){
			SendAll("玩家 "+P[i].name+" 不出杀，受到伤害！\n\n");
			P[i].blood--;
			if(P[i].blood<=0){
				check_Peach(i,1-P[i].blood);
				// if(!check_Peach(i,1-P[i].blood)) i--;
			}
		}else{
			SendAll("玩家 "+P[i].name+" 出杀，不受伤害！\n\n");
		}
	}
	SendAll("南蛮入侵结束！\n\n");
}
void Action_Wanjian(int cp6){
	SendAll("玩家 "+P[cp6].name+" 使用了“万箭齐发”！\n\n");
	for(int i=1;i<=m;i++){
		if (!P[i].is_alive) continue;
		if(i==cp6) continue;
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[i].name+" 使用了万箭齐发！\n\n");
		SendAll("请等待无懈可击！\n\n");
		if(!check_Wuxie()){
			SendAll("操作被无懈可击！\n\n");
			continue;
		}
		SendAll("操作没有被无懈！正常执行！\n\n");
		Send(i,"请你出一张“闪”，否则减少一点体力！\n\n");
		int num=NumberChosen(i,2);
		if(num==-1){
			SendAll("玩家 "+P[i].name+" 不出闪，受到伤害！\n\n");
			P[i].blood--;
			if(P[i].blood<=0){
				check_Peach(i,1-P[i].blood);
				// if(!check_Peach(i,1-P[i].blood)) i--;
			}
		}else{
			SendAll("玩家 "+P[i].name+" 出闪，不受伤害！\n\n");
		}
	}
	SendAll("万箭齐发结束！\n\n");
}
void Action_Taoyuan(int cp6){
	SendAll("玩家 "+P[cp6].name+" 使用了“桃园结义”！\n\n");
	for(int i=1;i<=m;i++){
		if (!P[i].is_alive) continue;
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[i].name+" 使用了桃园结义！\n\n");
		SendAll("请等待无懈可击！\n\n");
		if(!check_Wuxie()){
			SendAll("操作被无懈可击！\n\n");
			continue;
		}
		SendAll("操作没有被无懈！正常执行！\n\n");
		if(P[i].blood<P[i].Maxblood) SendAll("玩家 "+P[i].name+" 恢复一点体力！\n\n"),P[i].blood++;
		else SendAll("玩家 "+P[i].name+" 血量已满，不恢复体力！\n\n");
	}
	SendAll("桃园结义结束！\n\n");
}
void Action_Wugu(int cp6) {
	SendAll("玩家 "+P[cp6].name+"使用了“五谷丰登”！\n\n");

	vector<int> vec;
	for(int i=1;i<=num_alive;i++) vec.push_back(Newcard());
	for(int t=cp6;t<=m;t++){
		if(!P[t].is_alive)continue;
		string str="";
		for(int i=0;i<vec.size();i++) str+=GetCard(vec[i]);
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[t].name+" 使用了五谷丰登！\n\n");
		SendAll("目前卡牌： "+str+"\n\n");
		SendAll("请等待无懈可击！\n\n");
		if(!check_Wuxie()){
			SendAll("操作被无懈可击！\n\n");
			continue;
		}
		SendAll("操作没有被无懈！正常执行！\n\n");
		Send(t,"请选择一张牌：\n\n");
		int num; pair<TY,string> Goal;
		while(1){
			do{
				Goal=ReceiveMessage();
			}while(Goal.first!=t);
			if(isint(Goal.second)){
				num=toint(Goal.second);
				if(num<vec.size()) break;
			}
			Send(t,"不合法的输入！请重新输入\n\n");
		}
		SendAll("玩家 "+P[t].name+" 选择了 "+GetCard(vec[num])+"！\n\n");
		P[t].curCard.insert(vec[num]); P[t].outCard();
		auto it=vec.begin();
		while(num--) it++;
		vec.erase(it);
	}
	for(int t=1;t<cp6;t++){
		if(!P[t].is_alive)continue;
		string str="";
		for(int i=0;i<vec.size();i++) str+=GetCard(vec[i]);
		SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[t].name+" 使用了五谷丰登！\n\n");
		SendAll("目前卡牌： "+str+"\n\n");
		SendAll("请等待无懈可击！\n\n");
		if(!check_Wuxie()){
			SendAll("操作被无懈可击！\n\n");
			continue;
		}
		SendAll("操作没有被无懈！正常执行！\n\n");
		Send(t,"请选择一张牌：\n\n");
		int num; pair<TY,string> Goal;
		while(1){
			do{
				Goal=ReceiveMessage();
			}while(Goal.first!=t);
			if(isint(Goal.second)){
				num=toint(Goal.second);
				if(num<vec.size()) break;
			}
			Send(t,"不合法的输入！请重新输入\n\n");
		}
		SendAll("玩家 "+P[t].name+" 选择了 "+GetCard(vec[num])+"！\n\n");
		P[t].curCard.insert(vec[num]); P[t].outCard();
		auto it=vec.begin();
		while(num--) it++;
		vec.erase(it);
	}
	for(int x:vec) aaa[++cur2]=x; vec.clear();
}
string GetCard(int id){return " 【 "+a[id].name+dick[a[id].number]+a[id].Type+" 】 ";}
bool Panduan_Lebu(int val) {
	return P[val].Is_Lebu;
}
void Action_Lebu(int cp6, int val) {
	SendAll("玩家 "+P[cp6].name+" 对玩家 "+P[val].name+" 使用了乐不思蜀！\n\n");
	P[val].Is_Lebu=true;
}
void Next_Shandian(int cp6) {
	int cur=cp6%m+1;
	if(P[cur].is_alive&&!P[cur].Is_Shandian) {
		P[cur].Is_Shandian=true;
	}
	else Next_Shandian(cur);
}
void Help(int cp6){
	Send(cp6,"你的编号是："+tostr(P[cp6].cp6_player_id)+"\n\n");
	for(int i=1;i<=m;i++){
		if(!P[i].is_alive){
			Send(cp6,"玩家 "+P[i].name+" 死了！\n\n");
			continue;
		}
		else if(i==cp6){
			Send(cp6,"你的血量为："+tostr(P[cp6].blood)+"\n\n");
			string str=""; for(int x:P[i].curCard) str+=GetCard(x);
			Send(cp6,"你的手牌有："+str+"\n\n");
			str=""; if(P[i].weaponcard) str=str+GetCard(P[i].weaponcard); if(P[i].defendcard) str=str+GetCard(P[i].defendcard);	if(P[i].jianyicard) str=str+GetCard(P[i].jianyicard);	if(P[i].jiayicard) str=str+GetCard(P[i].jiayicard);
			string STR1=(P[i].Is_Lebu?"有":"没有");
			string STR2=(P[i].Is_Shandian?"有":"没有");
			Send(cp6,"你的装备牌有： "+str+"，"+STR1+"乐不思蜀，"+STR2+"闪电. \n\n");
			continue;
		}
		Send(cp6,"玩家 "+P[i].name+" ，编号为 "+tostr(P[i].cp6_player_id)+" ，手牌数为："+tostr(P[i].curCard.size())+" 血量为："+tostr(P[i].blood)+"\n\n");
		string str=""; if(P[i].weaponcard) str=str+GetCard(P[i].weaponcard); if(P[i].defendcard) str=str+GetCard(P[i].defendcard);	if(P[i].jianyicard) str=str+GetCard(P[i].jianyicard);	if(P[i].jiayicard) str=str+GetCard(P[i].jiayicard);
		string STR1=(P[i].Is_Lebu?"有":"没有");
		string STR2=(P[i].Is_Shandian?"有":"没有");
		Send(cp6,"玩家 "+P[i].name+" 的装备牌有： "+str+"，"+STR1+"乐不思蜀，"+STR2+"闪电. \n\n");
	}
}
bool check_alive(int cp6) {
	return P[cp6].is_alive;
}
void Action_Weapon(int cp6, int cardnum) {
	SendAll("玩家 "+P[cp6].name+" 装备了 "+GetCard(cardnum)+"\n\n");
	if (P[cp6].weaponcard != 0) {
		SendAll("玩家 "+P[cp6].name+" 卸下了 "+GetCard(P[cp6].weaponcard)+"\n\n");
		aaa[++cur2] = P[cp6].weaponcard;
	}
	P[cp6].weaponcard = cardnum;
	if (cardnum==16) P[cp6].Reach_dis=1;
	else if (cardnum==17||cardnum==18) P[cp6].Reach_dis=2;
	else if (cardnum==19||cardnum==20||cardnum==21) P[cp6].Reach_dis=3;
	else if (cardnum==22) P[cp6].Reach_dis=4;
	else if (cardnum==23) P[cp6].Reach_dis=5;
}
void Action_defend(int cp6,int cardnum) {
	SendAll("玩家 "+P[cp6].name+" 装备了 "+GetCard(cardnum)+"\n\n");
	if (P[cp6].defendcard != 0) {
		SendAll("玩家 "+P[cp6].name+" 卸下了 "+GetCard(P[cp6].defendcard)+"\n\n");
		aaa[++cur2] = P[cp6].defendcard;
	}
	P[cp6].defendcard = cardnum;
}
void Action_jianyi(int cp6,int cardnum) {
	SendAll("玩家 "+P[cp6].name+" 装备了 "+GetCard(cardnum)+"\n\n");
	if (P[cp6].jianyicard != 0) {
		SendAll("玩家 "+P[cp6].name+" 卸下了 "+GetCard(P[cp6].jianyicard)+"\n\n");
		aaa[++cur2] = P[cp6].jianyicard;
	}
	P[cp6].jianyicard = cardnum;
}
void Action_jiayi(int cp6,int cardnum) {
	SendAll("玩家 "+P[cp6].name+" 装备了 "+GetCard(cardnum)+"\n\n");
	if (P[cp6].jiayicard != 0) {
		SendAll("玩家 "+P[cp6].name+" 卸下了 "+GetCard(P[cp6].jiayicard)+"\n\n");
		aaa[++cur2] = P[cp6].jiayicard;
	}
	P[cp6].jiayicard = cardnum;
}
void Action_Qinglong(int cp6, int val) {
	Send(cp6,"是否继续出杀？是则选择一张杀，否则输出No\n\n");
	int num=NumberChosen(cp6,1);
	if(num!=-1){
		aaa[++cur] = EraseCard(cp6,num);
		Action_Sha(cp6,val,1);
	}else{
		Send(cp6,"已放弃出杀!\n\n");
		return;
	}
}
void Action_Guanshi(int cp6,int val){
	if (P[cp6].curCard.size()>=2){
		Send(cp6,"是否弃置两张牌，仍造成伤害？是则输出1，否则输出No\n\n");
		int num = NumberChosen(cp6,0);
		if (num==-1) {
			Send(cp6,"已放弃发动贯石斧！\n\n");
			return;
		}
		else {
			SendAll("玩家 "+P[cp6].name+" 发动了贯石斧！\n\n");
			for (int i = 0; i < 2; i++) {
				if (num == 102) {
					SendAll("玩家 "+P[cp6].name+" 弃置了 "+GetCard(P[cp6].defendcard)+"\n\n");
					aaa[++cur2] = P[cp6].defendcard;
					P[cp6].defendcard=0;
				}
				else if (num == 103) {
					SendAll("玩家 "+P[cp6].name+" 弃置了 "+GetCard(P[cp6].jianyicard)+"\n\n");
					aaa[++cur2] = P[cp6].jianyicard;
					P[cp6].jianyicard=0;
				}
				else if (num == 104) {
					SendAll("玩家 "+P[cp6].name+" 弃置了 "+GetCard(P[cp6].jiayicard)+"\n\n");
					aaa[++cur2] = P[cp6].jiayicard;
					P[cp6].jiayicard=0;
				}
				else {
					int erase_card = EraseCard(cp6,num);
					aaa[++cur2] = erase_card;
					SendAll("玩家 "+P[cp6].name+" 弃置了 "+GetCard(erase_card)+"！\n\n");
				}
			}
		}
	}
}
