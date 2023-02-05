#include <iostream>
#include <string.h>
#include <vector>
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

int PYgetId(string PY)
{
    if(PY=="xyb") return 1;
    if(PY=="sj") return 2;
    if(PY=="ayb") return 3;
    if(PY=="ay") return 4;
    if(PY=="yx") return 5;
    if(PY=="cd") return 6;
    if(PY=="ayzm") return 7;
    if(PY=="td") return 8;
    if(PY=="gm") return 9;
    if(PY=="wd") return 10;
    if(PY=="tw") return 11;
    if(PY=="xp") return 12;
    if(PY=="wz") return 13;
    if(PY=="gc") return 14;
    if(PY=="wm") return 15;
    if(PY=="hj") return 16;
    if(PY=="dy") return 17;
    if(PY=="sy") return 18;
    if(PY=="gl") return 19;
    return 0;
}

class Card
{
    public:
    int id;
    int Raw_Cost;//pos3:1
    int Buffed_Cost;//pos3:2
    int Type;
    int standby;//pos3:3  注能或暗影变的法术的id 
    Card();
    Card(int id);
};

Card::Card()
{
    id=0;
    Raw_Cost=0;
    Buffed_Cost=0;
    Type=0;
    standby=0;
}

Card::Card(int ID)
{
    id=ID;
    Raw_Cost=getDefaultCost(ID);
    Buffed_Cost=Raw_Cost;
    Type=getType(ID);
    standby=0;
}

class buff
{
    public:
    int id;
    int value;
    int duration;
    int type;
    buff();
    buff(int id);
};

buff::buff()
{
    id=0;
    value=0;
    duration=0;
    type=0;
}

buff::buff(int ID)
{
    id=ID;
    if(ID==2)
    {
        value=-2;
        duration=1;
        type=0;
    }
    else if(ID==14)
    {
        value=-2;
        duration=1;
        type=3;
    }
    else if(ID==17)
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
    int Hp;//pos3:1
    bool full_Hp;//pos3:2
    Minion();
    Minion(int ID);
};

Minion::Minion()
{
    id=0;
    Hp=0;
    full_Hp=true;
}

Minion::Minion(int ID)
{
    id=ID;
    Hp=getDefualtHp(ID);
    full_Hp=true;
}

//Data
Card hand[10];//pos1:1
int handsize=0;

vector<buff> Buff;//pos1:2

Minion MyBoard[7];//pos1:3
int MyBoardSize=0;

Minion EnemyBoard[7];//pos1:4
int EnemyBoardSize=0;

int mana=0;//pos1:5

int Card_Used=0;//pos1:6

bool MyHeroFullHp=false;//pos1:7

int EnemyHeroFullHp=0;

int EnemyHeroCurHp=0;//pos1:8

vector<string> history;
//Data

//System
struct diff
{
    int pos1;
    int pos2;
    int pos3;
    int C_D;
    double ov;
};
vector<Card> Card_Deleted;
vector<Minion> Minion_Deleted;
vector< vector<diff> > Tree;
const vector<diff> empty_vec;

void DelHand(int p)
{
    for(int i=p;i<handsize&&i<9;i++)
    {
        hand[i]=hand[i+1];
    }
    handsize--;
    hand[9]=Card();
}

void DelMyMinion(int p)
{
    for(int i=p;i<MyBoardSize&&i<6;i++)
    {
        MyBoard[i]=MyBoard[i+1];
    }
    MyBoardSize--;
    MyBoard[6]=Minion();
}

void DelEnemyMinion(int p)
{
    for(int i=p;i<EnemyBoardSize&&i<6;i++)
    {
        EnemyBoard[i]=EnemyBoard[i+1];
    }
    EnemyBoardSize--;
    EnemyBoard[6]=Minion();
}

void Edit(int pos1,int pos2,int pos3,int C_D,double val);

void update_Buffed_Cost(int p)
{
    int temp=hand[p].Raw_Cost;
    for(buff t:Buff) if(t.type==hand[p].Type||t.type==3) temp+=t.value;
    if(temp<0) temp=0;
    Edit(1,p,2,0,temp);
}

void update_All_Buffed_Cost()
{
    for(int i=0;i<handsize;i++) update_Buffed_Cost(i);
}

void Edit(int pos1,int pos2,int pos3,int C_D,double val)
{
    diff temp;
    temp.pos1=pos1;
    temp.pos2=pos2;
    temp.pos3=pos3;
    temp.C_D=C_D;
    if(C_D==0)
    {
        if(pos1==1)
        {
            if(pos3==1)
            {
                temp.ov=hand[pos2].Raw_Cost;
                hand[pos2].Raw_Cost=val;
            }
            else if(pos3==2)
            {
                temp.ov=hand[pos2].Buffed_Cost;
                hand[pos2].Buffed_Cost=val;
            }
            else if(pos3==3)
            {
                temp.ov=hand[pos2].standby;
                hand[pos2].standby=val;
            }
        }
        else if(pos1==2)
        {
            temp.ov=Buff[pos2].duration;
            Buff[pos2].duration=val;
        }
        else if(pos1==3)
        {
            if(pos3==1)
            {
                temp.ov=MyBoard[pos2].Hp;
                MyBoard[pos2].Hp=val;
            }
            else if(pos3==2)
            {
                temp.ov=MyBoard[pos2].full_Hp;
                MyBoard[pos2].full_Hp=val;
            }
        }
        else if(pos1==4)
        {
            if(pos3==1)
            {
                temp.ov=EnemyBoard[pos2].Hp;
                EnemyBoard[pos2].Hp=val;
            }
            else if(pos3==2)
            {
                temp.ov=EnemyBoard[pos2].full_Hp;
                EnemyBoard[pos2].full_Hp=val;
            }
        }
        else if(pos1==5)
        {
            temp.ov=mana;
            mana=val;
        }
        else if(pos1==6)
        {
            temp.ov=Card_Used;
            Card_Used=val;
        }
        else if(pos1==7)
        {
            temp.ov=MyHeroFullHp;
            MyHeroFullHp=val;
        }
        else if(pos1==8)
        {
            temp.ov=EnemyHeroCurHp;
            EnemyHeroCurHp=val;
        }
    }
    else if(C_D==1)
    {
        if(pos1==1)
        {
            hand[handsize++]=Card(val);
            update_Buffed_Cost(handsize-1);
        }
        else if(pos1==2)
        {
            Buff.push_back(buff(val));
            update_All_Buffed_Cost();
        }
        else if(pos1==3) MyBoard[MyBoardSize++]=Minion(val);
        else if(pos1==4) EnemyBoard[EnemyBoardSize++]=Minion();
    }
    else if(C_D==2)
    {
        if(pos1==1)
        {
            Card_Deleted.push_back(hand[pos2]);
            DelHand(pos2);
        }
        else if(pos1==2)
        {
            temp.ov=Buff[pos2].id;
            Buff.pop_back();
            update_All_Buffed_Cost();
        }
        else if(pos1==3)
        {
            Minion_Deleted.push_back(MyBoard[pos2]);
            DelMyMinion(pos2);
        }
        else if(pos1==4)
        {
            Minion_Deleted.push_back(EnemyBoard[pos2]);
            DelEnemyMinion(pos2);
        }
    }
    Tree[Tree.size()-1].push_back(temp);
}

void Undo(diff temp)
{
    if(temp.C_D==0)
    {
        if(temp.pos1==1)
        {
            if(temp.pos3==1) hand[temp.pos2].Raw_Cost=temp.ov;
            else if(temp.pos3==2) hand[temp.pos2].Buffed_Cost=temp.ov;
            else if(temp.pos3==3) hand[temp.pos2].standby=temp.ov;
        }
        else if(temp.pos1==2) Buff[temp.pos2].duration=temp.ov;
        else if(temp.pos1==3)
        {
            if(temp.pos3==1) MyBoard[temp.pos2].Hp=temp.ov;
            else if(temp.pos3==2) MyBoard[temp.pos2].full_Hp=temp.ov;
        }
        else if(temp.pos1==4)
        {
            if(temp.pos3==1) EnemyBoard[temp.pos2].Hp=temp.ov;
            else if(temp.pos3==2) EnemyBoard[temp.pos2].full_Hp=temp.ov;
        }
        else if(temp.pos1==5) mana=temp.ov;
        else if(temp.pos1==6) Card_Used=temp.ov;
        else if(temp.pos1==7) MyHeroFullHp=temp.ov;
        else if(temp.pos1==8) EnemyHeroCurHp=temp.ov;
    }
    else if(temp.C_D==1)
    {
        if(temp.pos1==1) hand[--handsize]=Card();
        else if(temp.pos1==2) Buff.pop_back();
        else if(temp.pos1==3) MyBoard[--MyBoardSize]=Minion();
        else if(temp.pos1==4) EnemyBoard[--EnemyBoardSize]=Minion();
    }
    else if(temp.C_D==2)
    {
        if(temp.pos1==1)
        {
            for(int i=handsize;i>temp.pos2;i--) hand[i]=hand[i-1];
            handsize++;
            hand[temp.pos2]=Card_Deleted[Card_Deleted.size()-1];
            Card_Deleted.pop_back();
        }
        else if(temp.pos1==2)
        {
            Buff.push_back(buff());
            for(int i=Buff.size()-1;i>temp.pos2;i--) Buff[i]=Buff[i-1];
            Buff[temp.pos2]=buff(temp.ov);
            Buff[temp.pos2].duration=0;
        }
        else if(temp.pos1==3)
        {
            for(int i=MyBoardSize;i>temp.pos2;i--) MyBoard[i]=MyBoard[i-1];
            MyBoardSize++;
            MyBoard[temp.pos2]=Minion_Deleted[Minion_Deleted.size()-1];
            Minion_Deleted.pop_back();
        }
        else if(temp.pos1==4)
        {
            for(int i=EnemyBoardSize;i>temp.pos2;i--) EnemyBoard[i]=EnemyBoard[i-1];
            EnemyBoardSize++;
            EnemyBoard[temp.pos2]=Minion_Deleted[Minion_Deleted.size()-1];
            Minion_Deleted.pop_back();
        }
    }
}

void Undo_Floor()
{
    for(int i=Tree[Tree.size()-1].size()-1;i>=0;i--) Undo(Tree[Tree.size()-1][i]);
    Tree[Tree.size()-1].clear();
    history.pop_back();
}

void UseBuff(int type)
{
    for(int i=Buff.size()-1;i>=0;i--)
    {
        if(Buff[i].type==type||Buff[i].type==3)
        {
            if(Buff[i].duration==1) Edit(2,i,0,2,0);
            else Edit(2,i,0,0,Buff[i].duration-1);
        }
    }
}

void infuse()
{
    for(int i=0;i<handsize;i++) if(hand[i].id==7) Edit(1,i,3,0,hand[i].standby+1);
}

bool check_death(int p)
{
    if(p<=6)
    {
        if(MyBoard[p].Hp<=0)
        {
            Edit(3,p,0,2,0);
            infuse();
            return true;
        }
        return false;
    }
    else
    {
        if(EnemyBoard[p].Hp<=0)
        {
            Edit(4,p,0,2,0);
            return true;
        }
        return false;
    }
}

void Use(int p,int a,int b,int c,int d)
{
    string temp="";
    temp+="[";
    temp+=p;
    temp+="]:";
    if(hand[p].id==4) temp+="殒命暗影 变为 ";
    int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
    temp+=getName(id);
    Edit(5,0,0,0,mana-hand[p].Buffed_Cost);
    UseBuff(hand[p].Type);
    if(hand[p].Type==0)
    {
        for(int i=0;i<handsize;i++)
        {
            if(hand[i].id==4)
            {
                Edit(1,i,3,0,id);
                Edit(1,i,1,0,getDefaultCost(id));
                update_Buffed_Cost(i);
            }
        }
    }
    else if(hand[p].Type==1)
    {
        Edit(3,0,0,1,id);
        if(hand[p].standby==1) Edit(3,MyBoardSize-1,1,0,1);
    }
    Edit(1,p,0,2,0);

    if(id==1)
    {
        Edit(5,0,0,0,mana+1);
    }
    else if(id==2)
    {
        Edit(2,0,0,1,2);
    }
    else if(id==3)
    {
        
    }
    else if(id==5)
    {

    }
}

int main()
{
    const vector<diff> empty_vec;
    Tree.push_back(empty_vec);
    return 0;
}