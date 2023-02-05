#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#define CardType 20//共有20种牌
using namespace std;

string getName(int id)
{
    if(id==1) return "伪造的幸运币/幸运币";
    if(id==2) return "伺机待发";
    if(id==3) return "暗影步";
    if(id==4) return "殒命暗影";
    if(id==5) return "军七要挟";
    if(id==6) return "垂钓时光";
    if(id==7) return "暗影之门";
    if(id==8) return "秘密通道";
    if(id==9) return "鬼魅攻击";
    if(id==10) return "黑水弯刀";
    if(id==11) return "腾武";
    if(id==12) return "行骗";
    if(id==13) return "邮箱舞者";
    if(id==14) return "锯齿骨刺";
    if(id==15) return "潜伏帷幕";
    if(id==16) return "幻觉药水";
    if(id==17) return "刀油";
    if(id==18) return "鲨鱼";
    if(id==19) return "鬼灵";
    if(id==20) return "已注能的暗影之门";
    return " ";
}

int getDefaultCost(int id)
{
    if(id==1) return 0;
    if(id==2) return 0;
    if(id==3) return 0;
    if(id==4) return 0;
    if(id==5) return 1;
    if(id==6) return 1;
    if(id==7) return 1;
    if(id==8) return 1;
    if(id==9) return 1;
    if(id==10) return 1;
    if(id==11) return 2;
    if(id==12) return 2;
    if(id==13) return 2;
    if(id==14) return 2;
    if(id==15) return 3;
    if(id==16) return 4;
    if(id==17) return 4;
    if(id==18) return 4;
    if(id==19) return 6;
    return -1;
}

int getType(int id)
{
    if(id==1) return 0;
    if(id==2) return 0;
    if(id==3) return 0;
    if(id==4) return 0;
    if(id==5) return 0;
    if(id==6) return 0;
    if(id==7) return 0;
    if(id==8) return 0;
    if(id==9) return 0;
    if(id==10) return 2;
    if(id==11) return 1;
    if(id==12) return 0;
    if(id==13) return 1;
    if(id==14) return 0;
    if(id==15) return 0;
    if(id==16) return 0;
    if(id==17) return 1;
    if(id==18) return 1;
    if(id==19) return 1;
    return -1;
}

int getDefualtHp(int id)
{
    if(id==11) return 2;
    else if(id==13) return 2;
    else if(id==17) return 3;
    else if(id==18) return 3;
    else if(id==19) return 5;
    else return 0;
}

int getId(string name)
{
    if(name=="XingYunBi") return 1;
    if(name=="SiJi") return 2;
    if(name=="AnYingBu") return 3;
    if(name=="AnYing") return 4;
    if(name=="YaoXie") return 5;
    if(name=="ChuiDiao") return 6;
    if(name=="AnYingZhiMen") return 7;
    if(name=="TongDao") return 8;
    if(name=="GuiMei") return 9;
    if(name=="WanDao") return 10;
    if(name=="TengWu") return 11;
    if(name=="XingPian") return 12;
    if(name=="WuZhe") return 13;
    if(name=="GuCi") return 14;
    if(name=="WeiMu") return 15;
    if(name=="HuanJue") return 16;
    if(name=="DaoYou") return 17;
    if(name=="ShaYu") return 18;
    if(name=="GuiLing") return 19;
    return 0;
}

string getPYname(int id)
{
    if(id==1) return "XingYunBi";
    if(id==2) return "SiJi";
    if(id==3) return "AnYingBu";
    if(id==4) return "AnYing";
    if(id==5) return "YaoXie";
    if(id==6) return "ChuiDiao";
    if(id==7) return "AnYingZhiMen";
    if(id==8) return "TongDao";
    if(id==9) return "GuiMei";
    if(id==10) return "WanDao";
    if(id==11) return "TengWu";
    if(id==12) return "XingPian";
    if(id==13) return "WuZhe";
    if(id==14) return "GuCi";
    if(id==15) return "WeiMu";
    if(id==16) return "HuanJue";
    if(id==17) return "DaoYou";
    if(id==18) return "ShaYu";
    if(id==19) return "GuiLing";
    if(id==20) return "Infused_AnYingZhiMen";
    return " ";
}

class Card
{
    public:
    int id;//pos3:5
    string name;
    int Raw_Cost;//pos3:1
    int Buffed_Cost;//pos3:2
    int Type;//0-Spell, 1-Minion, 2-Weapon
    int standby;//pos3:3  注能或暗影变的法术的id 
    double Possibility;//pos3:4
    Card(int id);
    Card()
    {
        id=0;
        name="Undefined";
        Raw_Cost=0;
        Buffed_Cost=0;
        Type=0;
        standby=0;
        Possibility=0;
    }
};

Card::Card(int ID)
{
    id=ID;
    name=getName(ID);
    Raw_Cost=getDefaultCost(ID);
    Buffed_Cost=Raw_Cost;
    Type=getType(ID);
    standby=0;
    Possibility=1;
}

class buff
{
    public:
    int value;
    int duration;
    int type;
    buff(int id);
    buff()
    {
        value=0;
        duration=0;
        type=0;
    }
};

buff::buff(int id)
{
    if(id==2)
    {
        value=-2;
        duration=1;
        type=0;
    }
    else if(id==14)
    {
        value=-2;
        duration=1;
        type=3;
    }
    else if(id==17)
    {
        value=-3;
        duration=2;
        type=3;
    }
}

class Minion
{
    public:
    int id;
    string name;
    int Hp;//pos3:1
    bool full_Hp;//pos3:2
    Minion(int ID);
    Minion()
    {
        id=0;
        name="Undefined";
        Hp=0;
        full_Hp=true;
    }
};

Minion::Minion(int ID)
{
    id=ID;
    name=getName(ID);
    Hp=getDefualtHp(ID);
    full_Hp=true;
}

struct step
{
    short position=-1;
    short mode=0;
    short p1=0,p2=0,p3=0,p4=0;
};


//Data
vector<Card> hand;//pos1:1
vector<buff> Buff;//pos1:2
map<int,int> library;//pos1:3
vector<Minion> MyBoard;//pos1:4
vector<Minion> EnemyBoard;//pos1:5
int mana=0;//pos1:6
int Card_Used=0;//pos1:7
int LibSize=0;//pos1:8
bool DoubleEffect=false;//pos1:9
bool MyHeroFullHp=false;//pos1:10
bool EnemyHeroFullHp=false;//pos1:11
double possibility=1;//pos1:12
vector<int> Damage;//pos1:13
int Lib_Spell=0;//pos1:14
int Lib_Minion=0;//pos1:15
//Data


//System
struct diff
{
    int pos1;//Data中已注明
    int pos2;//hand,Buff,Board中的位置,或library中的id
    int pos3;//各结构中的位置
    double original_value;
    int Create_Delete;//0-否,1-创建,2-删除
    Card original_Card;
    buff original_Buff;
    Minion original_Minion;
};

const int deck[30]={1,1,2,2,3,3,4,5,6,6,7,7,8,8,9,10,10,11,12,12,13,14,14,15,15,16,16,17,18,19};

void InitLib()
{
    for(short i=0;i<30;i++) 
    {
        library[deck[i]]++;
        LibSize++;
        if(getType(deck[i])==0) Lib_Spell++;
        else if(getType(deck[i])==1) Lib_Minion++;
    }
}

struct play
{
    string name;
    int cost;
    int p=0,a=0,b=0,c=0,d=0;
};
vector<play> history;
struct method
{
    vector<play> his;
    vector<int> damage;
    double possibility;
    int sum=0;
};
vector<vector<diff>> Tree;//diff[x][y] x层到x+1层所做的第y个操作
const vector<diff> empty_vec;
method Method;//100%
vector<method> Uncertain_Method;
double Min_Possibility=0;
int Min_Damage=0;

bool cmp(method a,method b)
{
    return a.sum>b.sum;
}

void update_Buffed_cost(int position_in_hand)
{
    hand[position_in_hand].Buffed_Cost=hand[position_in_hand].Raw_Cost;
    for(buff tbuff:Buff) if(tbuff.type==hand[position_in_hand].Type||tbuff.type==3) hand[position_in_hand].Buffed_Cost+=tbuff.value;
    if(hand[position_in_hand].Buffed_Cost<0) hand[position_in_hand].Buffed_Cost=0;
}

void Edit(int pos1, int pos2, int pos3, int C_D, double Edit_to)
{
    diff temp;
    temp.pos1=pos1;
    temp.pos2=pos2;
    temp.pos3=pos3;
    temp.Create_Delete=C_D;
    temp.original_value=-1;
    if(C_D==1)
    {
        if(pos1==1)
        {
            hand.push_back(Card(Edit_to));
        }
        else if(pos1==2)
        {
            Buff.push_back(buff(Edit_to));
            for(int i=0;i<hand.size();i++) update_Buffed_cost(i);
        }
        else if(pos1==4)
        {
            MyBoard.push_back(Minion(Edit_to));
        }
        else if(pos1==5)
        {
            EnemyBoard.push_back(Minion(0));
        }
        else if(pos1==13)
        {
            Damage.push_back(Edit_to);
        }
    }
    else if(C_D==2)
    {
        if(pos1==1)
        {
            temp.original_Card=hand[pos2];
            hand.erase(hand.begin()+pos2);
        } 
        else if(pos1==2)
        {
            temp.original_Buff=Buff[pos2];
            Buff.erase(Buff.begin()+pos2);
            for(int i=0;i<hand.size();i++) update_Buffed_cost(i);
        }
        else if(pos1==4)
        {
            temp.original_Minion=MyBoard[pos2];
            MyBoard.erase(MyBoard.begin()+pos2);
        }
        else if(pos1==5)
        {
            temp.original_Minion=EnemyBoard[pos2];
            EnemyBoard.erase(EnemyBoard.begin()+pos2);
        }
    }
    else
    {
        if(pos1==1)
        {
            if(pos3==1) 
            {
                temp.original_value=hand[pos2].Raw_Cost;
                hand[pos2].Raw_Cost=Edit_to;
                update_Buffed_cost(pos2);
            }
            else if(pos3==2) 
            {
                temp.original_value=hand[pos2].Buffed_Cost;
                hand[pos2].Buffed_Cost=Edit_to;
            }
            else if(pos3==3) 
            {
                temp.original_value=hand[pos2].standby;
                hand[pos2].standby=Edit_to;
            }
            else if(pos3==4) 
            {
                temp.original_value=hand[pos2].Possibility;
                hand[pos2].Possibility=Edit_to;
            }
            else if(pos3==5)
            {
                temp.original_value=hand[pos2].id;
                hand[pos2].id=Edit_to;
            }
        }
        else if(pos1==2)
        {
            temp.original_value=Buff[pos2].duration;
            Buff[pos2].duration=Edit_to;
        }
        else if(pos1==3)
        {
            temp.original_value=library[pos2];
            library[pos2]=Edit_to;
        }
        else if(pos1==4)
        {
            if(pos3==1)
            {
                temp.original_value=MyBoard[pos2].Hp;
                MyBoard[pos2].Hp=Edit_to;
            }
            else if(pos3==2)
            {
                temp.original_value=MyBoard[pos2].full_Hp;
                MyBoard[pos2].full_Hp=Edit_to;
            }
        }
        else if(pos1==5)
        {
            if(pos3==1)
            {
                temp.original_value=EnemyBoard[pos2].Hp;
                EnemyBoard[pos2].Hp=Edit_to;
            }
            else if(pos3==2)
            {
                temp.original_value=EnemyBoard[pos2].full_Hp;
                EnemyBoard[pos2].full_Hp=Edit_to;
            }
        }
        else if(pos1==6)
        {
            temp.original_value=mana;
            mana=Edit_to;
        }
        else if(pos1==7)
        {
            temp.original_value=Card_Used;
            Card_Used=Edit_to;
        }
        else if(pos1==8)
        {
            temp.original_value=LibSize;
            LibSize=Edit_to;
        }
        else if(pos1==9)
        {
            temp.original_value=DoubleEffect;
            DoubleEffect=Edit_to;
        }
        else if(pos1==10)
        {
            temp.original_value=MyHeroFullHp;
            MyHeroFullHp=Edit_to;
        }
        else if(pos1==11)
        {
            temp.original_value=EnemyHeroFullHp;
            EnemyHeroFullHp=Edit_to;
        }
        else if(pos1==12)
        {
            temp.original_value=possibility;
            possibility=Edit_to;
        }
        else if(pos1==14)
        {
            temp.original_value=Lib_Spell;
            Lib_Spell=Edit_to;
        }
        else if(pos1==15)
        {
            temp.original_value=Lib_Minion;
            Lib_Minion=Edit_to;
        }
    }
    Tree[Tree.size()-1].push_back(temp);
}

void Undo(diff temp)
{
    if(temp.Create_Delete==1)
    {
        if(temp.pos1==1)
        {
            hand.erase(hand.end()-1);
        }
        else if(temp.pos1==2)
        {
            Buff.erase(Buff.end()-1);
            for(int i=0;i<hand.size();i++) update_Buffed_cost(i);
        }
        else if(temp.pos1==4)
        {
            MyBoard.erase(MyBoard.end()-1);
        }
        else if(temp.pos1==5)
        {
            EnemyBoard.erase(EnemyBoard.end()-1);
        }
        else if(temp.pos1==13)
        {
            Damage.erase(Damage.end()-1);
        }
    }
    else if(temp.Create_Delete==2)
    {
        if(temp.pos1==1)
        {
            hand.push_back(Card(0));
            for(int i=hand.size()-1;i>temp.pos2;i--) hand[i]=hand[i-1];
            hand[temp.pos2]=temp.original_Card;
        }
        else if(temp.pos1==2)
        {
            Buff.push_back(buff(0));
            for(int i=Buff.size()-1;i>temp.pos2;i--) Buff[i]=Buff[i-1];
            Buff[temp.pos2]=temp.original_Buff;
            for(int i=0;i<hand.size();i++) update_Buffed_cost(i);
        }
        else if(temp.pos1==4)
        {
            MyBoard.push_back(Minion(0));
            for(int i=MyBoard.size()-1;i>temp.pos2;i--) MyBoard[i]=MyBoard[i-1];
            MyBoard[temp.pos2]=temp.original_Minion;
        }
        else if(temp.pos1==5)
        {
            EnemyBoard.push_back(Minion(0));
            for(int i=EnemyBoard.size()-1;i>temp.pos2;i--) EnemyBoard[i]=EnemyBoard[i-1];
            EnemyBoard[temp.pos2]=temp.original_Minion;
        }
    }
    else
    {
        if(temp.pos1==1)
        {
            if(temp.pos3==1)
            {
                hand[temp.pos2].Raw_Cost=temp.original_value;
                update_Buffed_cost(temp.pos2);
            }
            else if(temp.pos3==2)
            {
                hand[temp.pos2].Buffed_Cost=temp.original_value;
            }
            else if(temp.pos3==3)
            {
                hand[temp.pos2].standby=temp.original_value;
            }
            else if(temp.pos3==4)
            {
                hand[temp.pos2].Possibility=temp.original_value;
            }
            else if(temp.pos3==5)
            {
                hand[temp.pos2].id=temp.original_value;
            }
        }
        else if(temp.pos1==2)
        {
            Buff[temp.pos2].duration=temp.original_value;
        }
        else if(temp.pos1==3)
        {
            library[temp.pos2]=temp.original_value;
        }
        else if(temp.pos1==4)
        {
            if(temp.pos3==1)
            {
                MyBoard[temp.pos2].Hp=temp.original_value;
            }
            else if(temp.pos3==2)
            {
                MyBoard[temp.pos2].full_Hp=temp.original_value;
            }
        }
        else if(temp.pos1==5)
        {
            if(temp.pos3==1)
            {
                EnemyBoard[temp.pos2].Hp=temp.original_value;
            }
            else if(temp.pos3==2)
            {
                EnemyBoard[temp.pos2].full_Hp=temp.original_value;
            }
        }
        else if(temp.pos1==6)
        {
            mana=temp.original_value;
        }
        else if(temp.pos1==7)
        {
            Card_Used=temp.original_value;
        }
        else if(temp.pos1==8)
        {
            LibSize=temp.original_value;
        }
        else if(temp.pos1==9)
        {
            DoubleEffect=temp.original_value;
        }
        else if(temp.pos1==10)
        {
            MyHeroFullHp=temp.original_value;
        }
        else if(temp.pos1==11)
        {
            EnemyHeroFullHp=temp.original_value;
        }
        else if(temp.pos1==12)
        {
            possibility=temp.original_value;
        }
        else if(temp.pos1==14)
        {
            Lib_Spell=temp.original_value;
        }
        else if(temp.pos1==15)
        {
            Lib_Minion=temp.original_value;
        }
    }
}

void UseBuff(int type)//0-spell, 1-minion, 3-All
{
    for(short i=Buff.size()-1;i>=0;i--)
    {
        if(Buff[i].type==type||Buff[i].type==3) Edit(2,i,0,0,Buff[i].duration-1);
        if(Buff[i].duration==0) Edit(2,i,0,2,0);
    }
}

void draw(int id)
{
    if(id)
    {
        double chance=(double)library[id]/LibSize;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        if(getType(id)==0) Edit(14,0,0,0,Lib_Spell-1);
        else if(getType(id)==1) Edit(15,0,0,0,Lib_Minion-1);
        Edit(1,0,0,1,id);
        Edit(1,hand.size()-1,4,0,chance);
        update_Buffed_cost(hand.size()-1);
    }
}

void draw_spell(int id)
{
    if(id)
    {
        double chance=(double)library[id]/Lib_Spell;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        Edit(14,0,0,0,Lib_Spell-1);
        Edit(1,0,0,1,id);
        Edit(1,hand.size()-1,4,0,chance);
    }
}

void draw_minion(int id)
{
    if(id)
    {
        double chance=(double)library[id]/Lib_Minion;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        Edit(15,0,0,0,Lib_Minion-1);
        Edit(1,0,0,1,id);
        Edit(1,hand.size()-1,4,0,chance);
    }
}

void infuse()//注能
{
    for(int i=0;i<hand.size();i++)
    {
        if(hand[i].id==7)
        {
            Edit(1,i,3,0,hand[i].standby+1);
            if(hand[i].standby==2) Edit(1,i,5,0,20);
        }
    }
}

bool check_death(int position_on_board)
{
    if(position_on_board>=0&&position_on_board<=6)
    {
        if(MyBoard[position_on_board].Hp<=0)
        {
            if(MyBoard[position_on_board].id==18) Edit(9,0,0,0,0);//鲨鱼效果
            Edit(4,position_on_board,0,2,0);//删除随从
            infuse();
            return true;
        }
        return false;
    }
    else if(position_on_board>=7&&position_on_board<=13)
    {
        if(EnemyBoard[position_on_board-7].Hp<=0)
        {
            Edit(5,position_on_board-7,0,2,0);
            return true;
        }
        return false;
    }
}

bool Use(int p,int a,int b,int c,int d)
{
    play temp;
    temp.name=getPYname(hand[p].id);
    temp.cost=hand[p].Buffed_Cost;
    temp.p=p;temp.a=a;temp.b=b;temp.c=c;temp.d=d;
    history.push_back(temp);
    if(possibility*hand[p].Possibility<Min_Possibility) return false;
    else Edit(12,0,0,0,possibility*hand[p].Possibility);
    int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
    int cost;
    if((id==5||id==10)&&a==1) cost=1;
    else cost=hand[p].Buffed_Cost;
    Edit(6,0,0,0,mana-cost);//扣除费用
    UseBuff(hand[p].Type);//扣除buff
    if(hand[p].Type==0)
    {
        for(int i=0;i<hand.size();i++) 
        {
            if(hand[i].id==4) 
            {
                Edit(1,i,3,0,id);//变形殒命暗影
                Edit(1,i,1,0,getDefaultCost(id));//改费用
                update_Buffed_cost(i);//更新费用
            }
        }
    }
    if(hand[p].Type==1)
    {
        Edit(4,0,0,1,id);
        if(hand[p].standby==1) Edit(4,hand.size()-1,1,0,1);//幻觉药水hp为1
    }
    Edit(1,p,0,2,0);//删除使用的牌
    if(id==1)
    {
        Edit(6,0,0,0,mana+1);
    }
    else if(id==2)
    {
        Edit(2,0,0,1,2);
    }
    else if(id==3)//a:场上位置
    {
        Edit(1,0,0,1,MyBoard[a].id);
        Edit(1,hand.size()-1,1,0,hand[hand.size()-1].Raw_Cost-2);
        Edit(4,a,0,2,0);
    }
    else if(id==4)
    {
        ;
    }
    else if(id==5)//a:0-打(b:目标:0~6为己方随从,7-13为敌方随从,14为己方英雄,15为敌方英雄),1-交易(b:抽牌id)
    {
        if(a==0)
        {
            if(b>=0&&b<=6)
            {
                Edit(4,b,1,0,MyBoard[b].Hp-3);
                Edit(4,b,2,0,0);
                check_death(b);
            }
            else if(b>=7&&b<=13)
            {
                Edit(5,b-7,1,0,EnemyBoard[b-7].Hp-3);
                Edit(5,b-7,2,0,0);
                check_death(b);
            }
            else if(b==14)
            {
                Edit(10,0,0,0,0);
            }
            else if(b==15)
            {
                Edit(11,0,0,0,0);
                Edit(13,0,0,1,3);
            }
        }
        else if(a==1)
        {
            Edit(3,5,0,0,library[5]+1);
            draw(b);
        }
    }
    else if(id==6)//a-抽牌id
    {
        if(Card_Used&&a)
        {
            double chance;
            if(LibSize<=3) chance=1;
            else
            {
                for(int k=0;k<3;k++)
                {
                    chance*=(LibSize-library[a]-k);
                    chance/=(LibSize-k);
                }
                chance=1-chance;
            }
            draw(a);
            Edit(1,hand.size()-1,4,0,chance);
        }
    }
    else if(id==7)//a-抽牌id
    {
        if(a) draw_spell(a);
    }
    else if(id==8)//a,b,c,d-抽牌id
    {
        while(hand.size()) Edit(1,hand.size()-1,0,2,0);//删光手牌
        if(a) draw(a);
        if(b) draw(b);
        if(c) draw(c);
        if(d) draw(d);
    }
    else if(id==9)//a-目标(0~6为己方随从,7-13为敌方随从,14为己方英雄,15为敌方英雄),b-抽牌id
    {
        if(a>=0&&a<=6)
        {
            Edit(4,a,1,0,MyBoard[a].Hp-1);
            Edit(4,a,2,0,0);
            check_death(a);
        }
        else if(a>=7&&a<=13)
        {
            Edit(5,a-7,1,0,EnemyBoard[a-7].Hp-1);
            Edit(5,a-7,2,0,0);
            check_death(a);
        }
        else if(a==14)
        {
            Edit(10,0,0,0,0);
        }
        else if(a==15)
        {
            Edit(11,0,0,0,0);
            Edit(13,0,0,1,1);
        }
        if(Card_Used) draw(b);
    }
    else if(id==10)//a:0-装备,1-交易,b-抽到的牌的id,c-减费的位置
    {
        if(a==0)
        {
            Edit(13,0,0,1,2);
        }
        else if(a==1)
        {
            Edit(3,10,0,0,library[10]+1);
            draw(b);
            Edit(1,c,1,0,hand[c].Raw_Cost-1);
            Edit(1,c,4,0,hand[c].Possibility/hand.size());
            update_Buffed_cost(c);
        }
    }
    else if(id==11)//a-目标
    {
        Edit(1,0,0,1,MyBoard[a].id);
        Edit(1,hand.size()-1,1,0,1);
        update_Buffed_cost(hand.size()-1);
        Edit(4,a,0,2,0);
    }
    else if(id==12)//a-法术id,b-随从id
    {
        if(a) draw_spell(a);
        if(b&&hand.size()<10) draw_minion(b);
    }
    else if(id==13)
    {
        Edit(1,0,0,1,1);
        if(DoubleEffect) if(hand.size()<10) Edit(1,0,0,1,1);
    }
    else if(id==14)//a-目标(0~6为我方随从,7~13为敌方随从)
    {
        if(a>=0&&a<=6)
        {
            Edit(4,a,1,0,MyBoard[a].Hp-3);
            Edit(4,a,2,0,0);
            if(check_death(a)) Edit(2,0,0,1,14);
        }
        else if(a>=7&&a<=13)
        {
            Edit(5,a-7,1,0,EnemyBoard[a-7].Hp-3);
            Edit(5,a-7,2,0,0);
            if(check_death(a)) Edit(2,0,0,1,14);
        }
    }
    else if(id==15)//a-第一个随从,b-第二个随从
    {
        if(a) draw_minion(a);
        if(b&&hand.size()<10) draw_minion(b);
    }
    else if(id==16)
    {
        for(int i=0;i<MyBoard.size();i++)
        {
            if(hand.size()<10)
            {
                Edit(1,0,0,1,MyBoard[i].id);
                Edit(1,hand.size()-1,1,0,1);
                Edit(1,hand.size()-1,3,0,1);
            }
        }
    }
    else if(id==17)
    {
        Edit(2,0,0,1,17);
        if(DoubleEffect) Edit(2,0,0,1,17);
    }
    else if(id==18)
    {
        Edit(9,0,0,0,1);
    }
    else if(id==19)
    {
        Edit(13,0,0,1,Card_Used);
        if(DoubleEffect) Edit(13,0,0,1,Card_Used);
    }
    else if(id==20)//a-抽牌id
    {
        if(a)
        {
            draw_spell(a);
            if(hand.size()<10) Edit(1,0,0,1,a);
        }
        
    }
    Edit(7,0,0,0,Card_Used+1);//Card_Used++
    return true;
}

void Undo_This_Floor()
{
    for(int i=Tree[Tree.size()-1].size()-1;i>=0;i--) Undo(Tree[Tree.size()-1][i]);
    Tree[Tree.size()-1].clear();
}

void dfs(int fl)
{
    Tree.push_back(empty_vec);
    int son[10];
    int sonsize=0;
    bool GuiLing=false;
    bool HuiShou=false;
    bool chouPai=false;
    int p=0;
    for(p=0;p<hand.size();p++)
    {
        if(hand[p].Buffed_Cost<=mana) 
        {
            son[sonsize++]=p;
        }
        int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
        if(id==19) GuiLing=true;
        else if(id==3||id==11||id==16) HuiShou=true;
        else if(id==5||id==6||id==7||id==9||id==10||id==12||id==15) chouPai=true;
    }

    bool BoardGuiLing=false;
    for(int i=0;i<MyBoard.size();i++)
    {
        if(MyBoard[i].id==19)
        {
            BoardGuiLing=true;
            break;
        }
    }
    if((GuiLing||(HuiShou&&BoardGuiLing)||(chouPai&&library[19]))&&(sonsize))
    {
        for(int i=0;i<sonsize;i++)
        {
            int p=son[i];
            bool flag=true;
            int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
            if(id==1)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==2)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==3)
            {
                for(int a=0;a<MyBoard.size();a++)
                {
                    flag=Use(p,a,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
            else if(id==4)
            {
                ;
            }
            else if(id==5)
            {
                int a,b;
                a=0;
                for(b=0;b<MyBoard.size();b++)
                {
                    flag=Use(p,a,b,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                for(b=0;b<EnemyBoard.size();b++)
                {
                    flag=Use(p,a,b+7,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                flag=Use(p,a,14,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
                flag=Use(p,a,15,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
                a=1;
                if(LibSize)
                {
                    for(int b=1;b<CardType;b++)
                    {
                        if(library[b])
                        {
                            flag=Use(p,a,b,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
            }
            else if(id==6)
            {
                if(Card_Used)
                {
                    if(LibSize)
                    {
                        for(int a=1;a<CardType;a++)
                        {
                            if(library[a])
                            {
                                flag=Use(p,a,0,0,0);
                                if(flag) dfs(fl+1);
                                history.erase(history.end()-1);
                                Undo_This_Floor();
                            }
                        }
                    }
                }
                else
                {
                    flag=Use(p,0,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
            else if(id==7||id==20)
            {
                if(LibSize)
                {
                    for(int a=1;a<CardType;a++)
                    {
                        if(getType(a)==0&&library[a])
                        {
                            flag=Use(p,a,0,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                
            }
            else if(id==8)
            {
                ;
            }
            else if(id==9)
            {
                for(int a=0;a<MyBoard.size();a++)
                {
                    if(LibSize)
                    {
                        for(int b=1;b<CardType;b++)
                        {
                            if(library[b])
                            {
                                flag=Use(p,a,b,0,0);
                                if(flag) dfs(fl+1);
                                history.erase(history.end()-1);
                                Undo_This_Floor();
                            }
                        }
                    }
                }
                for(int a=0;a<EnemyBoard.size();a++)
                {
                    if(LibSize)
                    {
                        for(int b=1;b<CardType;b++)
                        {
                            if(library[b])
                            {
                                flag=Use(p,a+7,b,0,0);
                                if(flag) dfs(fl+1);
                                history.erase(history.end()-1);
                                Undo_This_Floor();
                            }
                        }
                    }
                }
                if(LibSize)
                {
                    int a=14;
                    for(int b=1;b<CardType;b++)
                    {
                        if(library[b])
                        {
                            flag=Use(p,a,b,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                if(LibSize)
                {
                    int a=15;
                    for(int b=1;b<CardType;b++)
                    {
                        if(library[b])
                        {
                            flag=Use(p,a,b,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                
            }
            else if(id==10)
            {
                int a;
                a=0;
                flag=Use(p,a,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();

                if(LibSize)
                {
                    a=1;
                    for(int b=1;b<CardType;b++)
                    {
                        if(library[b])
                        {
                            for(int c=0;c<hand.size();c++)
                            {
                                flag=Use(p,a,b,c,0);
                                if(flag) dfs(fl+1);
                                history.erase(history.end()-1);
                                Undo_This_Floor();
                            }
                        }
                    }
                }
                
            }
            else if(id==11)
            {
                for(int a=0;a<MyBoard.size();a++)
                {
                    flag=Use(p,a,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
            else if(id==12)
            {
                if(Lib_Spell&&Lib_Minion)
                {
                    for(int a=1;a<CardType;a++)
                    {
                        if(getType(a)==0)
                        {
                            for(int b=1;b<CardType;b++)
                            {
                                if(getType(b)==1)
                                {
                                    flag=Use(p,a,b,0,0);
                                    if(flag) dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                    }
                }
                else if(Lib_Spell)
                {
                    for(int a=1;a<CardType;a++)
                    {
                        if(getType(a)==0)
                        {
                            flag=Use(p,a,0,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                else if(Lib_Minion)
                {
                    for(int b=1;b<CardType;b++)
                    {
                        if(getType(b)==0)
                        {
                            flag=Use(p,0,b,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                else
                {
                    Use(p,0,0,0,0);
                }
            }
            else if(id==13)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==14)
            {
                for(int a=0;a<MyBoard.size();a++)
                {
                    flag=Use(p,a,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                for(int a=0;a<EnemyBoard.size();a++)
                {
                    flag=Use(p,a+7,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
            else if(id==15)
            {
                if(Lib_Minion>=2)
                {
                    for(int a=10;a<CardType;a++)
                    {
                        if(getType(a)==1)
                        {
                            for(int b=10;a<CardType;b++)
                            {
                                if(getType(b)==1)
                                {
                                    flag=Use(p,a,b,0,0);
                                    if(flag) dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                    }
                }
                else if(Lib_Minion==1)
                {
                    for(int a=10;a<CardType;a++)
                    {
                        if(getType(a)==1)
                        {
                            flag=Use(p,a,0,0,0);
                            if(flag) dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                else
                {
                    flag=Use(p,0,0,0,0);
                    if(flag) dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
            else if(id==16)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==17)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==18)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
            else if(id==19)
            {
                flag=Use(p,0,0,0,0);
                if(flag) dfs(fl+1);
                history.erase(history.end()-1);
                Undo_This_Floor();
            }
        }
    }
    else
    {
        int sum=0;
        for(int i:Damage) sum+=i;
        if(sum>Min_Damage)
        {
            method temp;
            temp.damage=Damage;
            temp.his=history;
            temp.possibility=possibility;
            temp.sum=sum;
            if(temp.possibility==1)
            {
                if(temp.sum>Method.sum) Method=temp;
            }
            else Uncertain_Method.push_back(temp);
        }
    }
    Tree.erase(Tree.end()-1);
}

void show()
{
    std::cout<<"当前法力水晶:"<<mana<<endl;
    std::cout<<"当前用牌次数:"<<Card_Used<<endl;
    std::cout<<"当前Buff:"<<endl;
    for(short i=0;i<Buff.size();i++)
    {
        std::cout<<"Value:"<<Buff[i].value<<",Type:"<<Buff[i].type<<",Duration:"<<Buff[i].duration<<endl;
    }
    std::cout<<endl;
    std::cout<<"敌方英雄满血:"<<(EnemyHeroFullHp?"是":"否")<<endl;
    std::cout<<"我方英雄满血:"<<(MyHeroFullHp?"是":"否")<<endl;
    std::cout<<"当前敌方战场:"<<endl;
    for(short i=0;i<EnemyBoard.size();i++)
    {
        std::cout<<i<<":"<<"(hp:"<<EnemyBoard[i].Hp<<",满血:"<<((EnemyBoard[i].full_Hp)?"是":"否")<<") "<<endl;
    }
    std::cout<<endl;
    std::cout<<"当前我方战场:"<<endl;
    for(short i=0;i<MyBoard.size();i++)
    {
        std::cout<<i<<":"<<MyBoard[i].name<<"(hp:"<<MyBoard[i].Hp<<",满血:"<<((MyBoard[i].full_Hp)?"是":"否")<<")"<<endl;
    }
    std::cout<<endl;

    std::cout<<"当前手牌:"<<endl;
    for(short i=0;i<hand.size();i++)
    {
        std::cout<<i<<":"<<hand[i].name<<"(cost:"<<hand[i].Buffed_Cost<<",type:"<<hand[i].Type<<",standby:"<<hand[i].standby<<") "<<endl;
    }
    std::cout<<endl;

    std::cout<<"当前伤害序列:"<<endl;
    if(Damage.size()>0)
    {
        short sum=Damage[0];
        std::cout<<sum;
        for(short i=1;i<Damage.size();i++)
        {
            std::cout<<" + "<<Damage[i];
            sum+=Damage[i];
        }
        std::cout<<" = "<<sum;
    }
    std::cout<<endl<<endl;
}

//System




int main()
{
    system("chcp 65001");
    InitLib();
    Tree.push_back(empty_vec);
    string command;
    // draw(11);
    draw(16);
    draw(13);
    // draw(8);
    draw(14);
    draw(1);
    draw(19);
    
    // draw(18);
    
    
    // draw(17);
    // draw(10);
    mana=5;
    while(1)
    {
        std::cin>>command;
        if(command=="draw")
        {
            string temp;
            std::cout<<"输入抽到的牌:";
            std::cin>>temp;
            while(!getId(temp))
            {
                std::cout<<"重新输入:";
                std::cin>>temp;
            }
            draw(getId(temp));
        }
        else if(command=="use")
        {
            int p,a=0,b=0,c=0,d=0;
            std::cout<<"输入使用的牌的位置:";
            std::cin>>p;
            int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
            if(id==1)
            {
                Use(p,a,b,c,d);
            }
            else if(id==2)
            {
                Use(p,a,b,c,d);
            }
            else if(id==3)
            {
                std::cout<<"输入要回手的随从位置:";
                std::cin>>a;
                Use(p,a,b,c,d);
            }
            else if(id==5)
            {
                std::cout<<"模式(0:交易,1:打):";
                std::cin>>a;
                if(a==0)
                {
                    std::cout<<"输入目标(0~6为己方随从,7-13为敌方随从,14为己方英雄,15为敌方英雄):";
                    std::cin>>b;
                    Use(p,a,b,c,d);
                }
                else if(a==1)
                {
                    std::cout<<"输入抽到的牌:";
                    std::cin>>command;
                    b=getId(command);
                    if(b) Use(p,a,b,c,d);
                }
            }
            else if(id==6)
            {
                if(Card_Used&&LibSize)
                {
                    std::cout<<"输入抽到的牌";
                    std::cin>>command;
                    a=getId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==7)
            {
                if(LibSize)
                {
                    std::cout<<"输入抽到的牌";
                    std::cin>>command;
                    a=getId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==8)
            {
                std::cout<<"输入抽到的第1张牌(0-不抽):";
                std::cin>>command;
                a=getId(command);
                if(a)
                {
                    std::cout<<"输入抽到的第2张牌(0-不抽):";
                    std::cin>>command;
                    b=getId(command);
                    if(b)
                    {
                        std::cout<<"输入抽到的第3张牌(0-不抽):";
                        std::cin>>command;
                        c=getId(command);
                        if(c)
                        {
                            std::cout<<"输入抽到的第4张牌(0-不抽):";
                            std::cin>>command;
                            getId(command);
                        }
                    }
                }
                Use(p,a,b,c,d);
            }
            else if(id==9)
            {
                std::cout<<"输入目标(0~6为己方随从,7-13为敌方随从,14为己方英雄,15为敌方英雄):";
                std::cin>>a;
                if(Card_Used)
                {
                    std::cout<<"输入抽到的牌:";
                    std::cin>>command;
                    b=getId(command);
                    if(b) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==10)
            {
                std::cout<<"输入模式(0:交易,1:装备):";
                std::cin>>a;
                if(a==0)
                {
                    Use(p,a,b,c,d);
                }
                else if(a==1)
                {
                    std::cout<<"输入抽到的牌:";
                    std::cin>>command;
                    b=getId(command);
                    std::cout<<"输入减费的位置:";
                    std::cin>>c;
                    if(b) Use(p,a,b,c,d);
                }
            }
            else if(id==11)
            {
                std::cout<<"输入要回手的随从位置:";
                std::cin>>a;
                Use(p,a,b,c,d);
            }
            else if(id==12)
            {
                std::cout<<"输入抽到的法术牌:";
                std::cin>>command;
                a=getId(command);
                std::cout<<"输入抽到的随从牌:";
                std::cin>>command;
                b=getId(command);
                Use(p,a,b,c,d);
            }
            else if(id==13)
            {
                Use(p,a,b,c,d);
            }
            else if(id==14)
            {
                std::cout<<"输入攻击目标的位置(0~6为己方随从,7~13为敌方随从):";
                std::cin>>a;
                Use(p,a,b,c,d);
            }
            else if(id==15)
            {
                std::cout<<"输入抽到的第一张随从牌:";
                std::cin>>command;
                a=getId(command);
                std::cout<<"输入抽到的第二章随从牌:";
                std::cin>>command;
                b=getId(command);
                Use(p,a,b,c,d);
            }
            else if(id==16)
            {
                Use(p,a,b,c,d);    
            }
            else if(id==17)
            {
                Use(p,a,b,c,d); 
            }
            else if(id==18)
            {
                Use(p,a,b,c,d); 
            }
            else if(id==19)
            {
                Use(p,a,b,c,d); 
            }
            else if(id==20)
            {
                if(LibSize)
                {
                    std::cout<<"输入抽到的牌";
                    std::cin>>command;
                    a=getId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
        }
        else if(command=="show")
        {
            show();
        }
        else if(command=="delHand")
        {
            int temp;
            std::cout<<"被删除手牌的位置:";
            std::cin>>temp;
            hand.erase(hand.begin()+temp);
        }
        else if(command=="coin")
        {
            Edit(1,0,0,1,1);
        }
        else if(command=="setmana")
        {
            std::cout<<"将水晶设置为:";
            std::cin>>mana;
        }
        else if(command=="addEM")
        {
            int temp;
            Edit(5,0,0,1,0);
            std::cout<<"输入血量:";
            std::cin>>temp;
            Edit(5,EnemyBoard.size()-1,1,0,temp);
            std::cout<<"是否满血:";
            std::cin>>temp;
            Edit(5,EnemyBoard.size()-1,2,0,temp);
        }
        else if(command=="clearUsed")
        {
            Card_Used=0;
        }
        else if(command=="dfs")
        {
            cout<<"最小概率:";
            cin>>Min_Possibility;
            cout<<"最小伤害:";
            cin>>Min_Damage;
            for(int i=0;i<hand.size();i++) hand[i].Possibility=1;
            dfs(1);
            // sort(Uncertain_Method.begin(),Uncertain_Method.end(),cmp);
            cout<<Method.sum+1;
        }
    }
    return 0;
}