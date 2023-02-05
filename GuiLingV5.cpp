#include <iostream>
#include <string.h>
#include <vector>
#include <time.h>
#define CardType 20//最多有20种卡
using namespace std;

//Definition
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

// int PYgetId(string PY)
// {
//     if(PY=="XingYunBi") return 1;
//     if(PY=="SiJi") return 2;
//     if(PY=="AnYingBu") return 3;
//     if(PY=="AnYing") return 4;
//     if(PY=="YaoXie") return 5;
//     if(PY=="ChuiDiao") return 6;
//     if(PY=="AnYingZhiMen") return 7;
//     if(PY=="TongDao") return 8;
//     if(PY=="GuiMei") return 9;
//     if(PY=="WanDao") return 10;
//     if(PY=="TengWu") return 11;
//     if(PY=="XingPian") return 12;
//     if(PY=="WuZhe") return 13;
//     if(PY=="GuCi") return 14;
//     if(PY=="WeiMu") return 15;
//     if(PY=="HuanJue") return 16;
//     if(PY=="DaoYou") return 17;
//     if(PY=="ShaYu") return 18;
//     if(PY=="GuiLing") return 19;
//     return 0;
// }

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
    int id;//pos3:1
    string name;
    int Raw_Cost;//pos3:2
    int Buffed_Cost;//pos3:3
    int Type;//0-Spell, 1-Minion, 2-Weapon
    int standby;//pos3:4  注能或暗影变的法术的id 
    double Possibility;//pos3:5
    Card();
    Card(int id);
};

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
    string name;
    int Hp;//pos3:1
    bool full_Hp;//pos3:2
    Minion();
    Minion(int ID);
};

Card::Card()
{
    id=0;
    name="Place_Holder";
    Raw_Cost=0;
    Buffed_Cost=0;
    Type=0;
    standby=0;
    Possibility=0;
}

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

Minion::Minion()
{
    id=0;
    name="Place_Holder";
    Hp=0;
    full_Hp=true;
}

Minion::Minion(int ID)
{
    id=ID;
    name=getName(ID);
    Hp=getDefualtHp(ID);
    full_Hp=true;
}
//Definition

//Data
Card hand[10];//pos1:1
int handsize=0;
vector<buff> Buff;//pos1:2
int library[CardType+1];//pos1:3
Minion MyBoard[7];//pos1:4
int MyBoardSize=0;
Minion EnemyBoard[7];//pos1:5
int EnemyBoardSize=0;
int mana=0;//pos1:6
int Card_Used=0;//pos1:7
int LibSize=0;//pos1:8
int Lib_Spell=0;//pos1:9
int Lib_Minion=0;//pos1:10
int DoubleEffect=0;//pos1:11,场上鲨鱼的数量
bool MyHeroFullHp=false;//pos1:12
bool EnemyHeroFullHp=false;//pos1:13
double possibility=1;//pos1:14
vector<int> Damage;//pos1:15
//Data

//System
struct diff
{
    int pos1;
    int pos2;
    int pos3;
    int C_D;//Create or Delete: 0, 1-Create, 2-Delete
    double original_value;
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

void Edit(int pos1,int pos2,int pos3,int C_D,double Edit_to);

void update_Buffed_Cost(int position_in_hand)
{
    int temp=hand[position_in_hand].Raw_Cost;
    for(buff tbuff:Buff) if(tbuff.type==hand[position_in_hand].Type||tbuff.type==3) temp+=tbuff.value;
    temp=(temp<0)?0:temp;
    Edit(1,position_in_hand,3,0,temp);
}

void update_All_Buffed_Cost()
{
    for(int i=0;i<handsize;i++) update_Buffed_Cost(i);
}

void Edit(int pos1,int pos2,int pos3,int C_D,double Edit_to)
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
                temp.original_value=hand[pos2].id;
                hand[pos2].id=Edit_to;
            }
            else if(pos3==2)
            {
                temp.original_value=hand[pos2].Raw_Cost;
                hand[pos2].Raw_Cost=Edit_to;
                update_Buffed_Cost(pos2);
            }
            else if(pos3==3)
            {
                temp.original_value=hand[pos2].Buffed_Cost;
                hand[pos2].Buffed_Cost=Edit_to;
            }
            else if(pos3==4)
            {
                temp.original_value=hand[pos2].standby;
                hand[pos2].standby=Edit_to;
            }
            else if(pos3==5)
            {
                temp.original_value=hand[pos2].Possibility;
                hand[pos2].Possibility=Edit_to;
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
            temp.original_value=Lib_Spell;
            Lib_Spell=Edit_to;
        }
        else if(pos1==10)
        {
            temp.original_value=Lib_Minion;
            Lib_Minion=Edit_to;
        }
        else if(pos1==11)
        {
            temp.original_value=DoubleEffect;
            DoubleEffect=Edit_to;
        }
        else if(pos1==12)
        {
            temp.original_value=MyHeroFullHp;
            MyHeroFullHp=Edit_to;
        }
        else if(pos1==13)
        {
            temp.original_value=EnemyHeroFullHp;
            EnemyHeroFullHp=Edit_to;
        }
        else if(pos1==14)
        {
            temp.original_value=possibility;
            possibility=Edit_to;
        }
    }
    else if(C_D==1)
    {
        if(pos1==1)
        {
            hand[handsize++]=Card(Edit_to);
        }
        else if(pos1==2)
        {
            Buff.push_back(buff(Edit_to));
            update_All_Buffed_Cost();
        }
        else if(pos1==4)
        {
            MyBoard[MyBoardSize++]=Minion(Edit_to);
        }
        else if(pos1==5)
        {
            EnemyBoard[EnemyBoardSize++]=Minion();
        }
        else if(pos1==15)
        {
            Damage.push_back(Edit_to);
        }
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
            temp.original_value=Buff[pos2].id;
            Buff.erase(Buff.begin()+pos2);
            update_All_Buffed_Cost();
        }
        else if(pos1==4)
        {
            Minion_Deleted.push_back(MyBoard[pos2]);
            if(MyBoard[pos2].id==18) Edit(11,0,0,0,DoubleEffect-1);//鲨鱼效果
            DelMyMinion(pos2);
        }
        else if(pos1==5)
        {
            Minion_Deleted.push_back(EnemyBoard[pos2]);
            DelEnemyMinion(pos2);
        }
    }
    Tree[Tree.size()-1].push_back(temp);
}

void Undo(int pos1, int pos2, int pos3, int C_D, double original_value)
{
    if(C_D==0)
    {
        if(pos1==1)
        {
            if(pos3==1)
            {
                hand[pos2].id=original_value;
            }
            else if(pos3==2)
            {
                hand[pos2].Raw_Cost=original_value;
            }
            else if(pos3==3)
            {
                hand[pos2].Buffed_Cost=original_value;
            }
            else if(pos3==4)
            {
                hand[pos2].standby=original_value;
            }
            else if(pos3==5)
            {
                hand[pos2].Possibility=original_value;
            }
        }
        else if(pos1==2)
        {
            Buff[pos2].duration=original_value;
        }
        else if(pos1==3)
        {
            library[pos2]=original_value;
        }
        else if(pos1==4)
        {
            if(pos3==1)
            {
                MyBoard[pos2].Hp=original_value;
            }
            else if(pos3==2)
            {
                MyBoard[pos2].full_Hp=original_value;
            }
        }
        else if(pos1==5)
        {
            if(pos3==1)
            {
                EnemyBoard[pos2].Hp=original_value;
            }
            else if(pos3==2)
            {
                EnemyBoard[pos2].full_Hp=original_value;
            }
        }
        else if(pos1==6)
        {
            mana=original_value;
        }
        else if(pos1==7)
        {
            Card_Used=original_value;
        }
        else if(pos1==8)
        {
            LibSize=original_value;
        }
        else if(pos1==9)
        {
            Lib_Spell=original_value;
        }
        else if(pos1==10)
        {
            Lib_Minion=original_value;
        }
        else if(pos1==11)
        {
            DoubleEffect=original_value;
        }
        else if(pos1==12)
        {
            MyHeroFullHp=original_value;
        }
        else if(pos1==13)
        {
            EnemyHeroFullHp=original_value;
        }
        else if(pos1==14)
        {
            possibility=original_value;
        }
    }
    else if(C_D==1)
    {
        if(pos1==1)
        {
            hand[--handsize]=Card();
        }
        else if(pos1==2)
        {
            Buff.erase(Buff.end()-1);
        }
        else if(pos1==4)
        {
            MyBoard[--MyBoardSize]=Minion();
        }
        else if(pos1==5)
        {
            EnemyBoard[--EnemyBoardSize]=Minion();
        }
        else if(pos1==15)
        {
            Damage.erase(Damage.end()-1);
        }
    }
    else if(C_D==2)
    {
        if(pos1==1)
        {
            for(int i=handsize;i>pos2;i--) hand[i]=hand[i-1];
            handsize++;
            hand[pos2]=Card_Deleted[Card_Deleted.size()-1];
            Card_Deleted.erase(Card_Deleted.end()-1);
        }
        else if(pos1==2)
        {
            Buff.push_back(buff());
            for(int i=Buff.size()-1;i>pos2;i--) Buff[i]=Buff[i-1];
            Buff[pos2]=buff(original_value);
            Buff[pos2].duration=0;
        }
        else if(pos1==4)
        {
            for(int i=MyBoardSize;i>pos2;i--) MyBoard[i]=MyBoard[i-1];
            MyBoardSize++;
            MyBoard[pos2]=Minion_Deleted[Minion_Deleted.size()-1];
            Minion_Deleted.erase(Minion_Deleted.end()-1);
        }
        else if(pos1==5)
        {
            for(int i=EnemyBoardSize;i>pos2;i--) EnemyBoard[i]=EnemyBoard[i-1];
            EnemyBoardSize++;
            EnemyBoard[pos2]=Minion_Deleted[Minion_Deleted.size()-1];
            Minion_Deleted.erase(Minion_Deleted.end()-1);
        }
    }
}

void Undo_This_Floor()
{
    for(int i=Tree[Tree.size()-1].size()-1;i>=0;i--) 
    {
        Undo(Tree[Tree.size()-1][i].pos1,Tree[Tree.size()-1][i].pos2,Tree[Tree.size()-1][i].pos3,Tree[Tree.size()-1][i].C_D,Tree[Tree.size()-1][i].original_value);
    }
    Tree[Tree.size()-1].clear();
}

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

void UseBuff(int type)//0-spell, 1-minion, 3-All
{
    for(short i=Buff.size()-1;i>=0;i--)
    {
        if(Buff[i].type==type||Buff[i].type==3) Edit(2,i,0,0,Buff[i].duration-1);
        if(Buff[i].duration==0) Edit(2,i,0,2,0);
    }
}

bool draw(int id)
{
    if(id)
    {
        double chance=(double)library[id]/LibSize;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        if(getType(id)==0) Edit(9,0,0,0,Lib_Spell-1);
        else if(getType(id)==1) Edit(10,0,0,0,Lib_Minion-1);
        if(handsize<10)
        {
            Edit(1,0,0,1,id);
            Edit(1,handsize-1,5,0,chance);
            update_Buffed_Cost(handsize-1);
            return true;
        }
        
    }
    return false;
}

bool draw_spell(int id)
{
    if(id)
    {
        double chance=(double)library[id]/Lib_Spell;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        Edit(9,0,0,0,Lib_Spell-1);
        if(handsize<10)
        {
            Edit(1,0,0,1,id);
            Edit(1,handsize-1,5,0,chance);
            update_Buffed_Cost(handsize-1);
            return true;
        }
    }
    return false;
}

bool draw_minion(int id)
{
    if(id)
    {
        double chance=(double)library[id]/Lib_Minion;
        Edit(3,id,0,0,library[id]-1);
        Edit(8,0,0,0,LibSize-1);
        Edit(10,0,0,0,Lib_Minion-1);
        if(handsize<10)
        {
            Edit(1,0,0,1,id);
            Edit(1,handsize-1,5,0,chance);
            update_Buffed_Cost(handsize-1);
            return true;
        }
    }
    return false;
}

void infuse()//注能
{
    for(int i=0;i<handsize;i++)
    {
        if(hand[i].id==7)
        {
            Edit(1,i,4,0,hand[i].standby+1);
            if(hand[i].standby==2) Edit(1,i,1,0,20);
        }
    }
}

bool check_death(int position_on_board)
{
    if(position_on_board>=0&&position_on_board<=6)
    {
        if(MyBoard[position_on_board].Hp<=0)
        {
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
    return false;
}

struct play
{
    int id;
    int cost;
    int p,a,b,c,d;
};
vector<play> history;

void Use(int p,int a,int b,int c,int d)
{
    play temp;
    temp.p=p;
    temp.a=a;
    temp.b=b;
    temp.c=c;
    temp.d=d;
    temp.id=hand[p].id;
    temp.cost=hand[p].Buffed_Cost;
    if(hand[p].id==4) temp.d=hand[p].standby;

    Edit(14,0,0,0,possibility*hand[p].Possibility);
    int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
    int cost=((id==5||id==10)&&(a==1))?1:hand[p].Buffed_Cost;
    Edit(6,0,0,0,mana-cost);//扣除费用
    UseBuff(hand[p].Type);
    if(hand[p].Type==0)//法术入场
    {
        for(int i=0;i<handsize;i++) 
        {
            if(hand[i].id==4) 
            {
                Edit(1,i,4,0,id);//变形殒命暗影
                Edit(1,i,2,0,getDefaultCost(id));//改费用
                update_Buffed_Cost(i);
            }
        }
    }
    else if(hand[p].Type==1)//随从入场
    {
        Edit(4,0,0,1,id);
        if(hand[p].standby==1) Edit(4,MyBoardSize-1,1,0,1);//幻觉药水hp为1
    }
    Edit(1,p,0,2,0);//删除该牌

    if(id==1)
    {
        Edit(6,0,0,0,mana+1);
    }
    else if(id==2)
    {
        Edit(2,0,0,1,2);
    }
    else if(id==3)
    {
        temp.b=MyBoard[a].id;

        Edit(1,0,0,1,MyBoard[a].id);
        Edit(1,handsize-1,2,0,hand[handsize-1].Raw_Cost-2);
        Edit(4,a,0,2,0);
        
    }
    else if(id==4)
    {
        ;
    }
    else if(id==5)
    {
        if(a==0)
        {
            if(b>=0&&b<=6)
            {
                temp.c=MyBoard[b].id;
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
                Edit(12,0,0,0,0);
            }
            else if(b==15)
            {
                Edit(13,0,0,0,0);
                Edit(15,0,0,1,3);
            }
        }
        else if(a==1)
        {
            Edit(3,5,0,0,library[5]+1);
            draw(b);
        }
    }
    else if(id==6)
    {
        if(Card_Used&&a)
        {
            double chance=1;
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
            Edit(1,handsize-1,5,0,chance);
        }
    }
    else if(id==7)
    {
        if(a) draw_spell(a);
    }
    else if(id==8)
    {
        // while(handsize) Edit(1,handsize-1,0,2,0);//删光手牌
        // if(a) draw(a);
        // if(b) draw(b);
        // if(c) draw(c);
        // if(d) draw(d);
    }
    else if(id==9)
    {
        if(a>=0&&a<=6)
        {
            temp.c=MyBoard[a].id;
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
            Edit(12,0,0,0,0);
        }
        else if(a==15)
        {
            Edit(13,0,0,0,0);
            Edit(15,0,0,1,1);
        }
        if(Card_Used) draw(b);
    }
    else if(id==10)
    {
        if(a==0)
        {
            Edit(15,0,0,1,2);
        }
        else if(a==1)
        {
            Edit(3,10,0,0,library[10]+1);
            draw(b);
            Edit(1,c,2,0,hand[c].Raw_Cost-1);
            Edit(1,c,5,0,hand[c].Possibility/handsize);
        }
    }
    else if(id==11)
    {
        temp.b=MyBoard[a].id;
        Edit(1,0,0,1,MyBoard[a].id);
        Edit(1,handsize-1,2,0,1);
        Edit(4,a,0,2,0);
    }
    else if(id==12)
    {
        if(a) draw_spell(a);
        if(b&&(handsize<10)) draw_minion(b);
    }
    else if(id==13)
    {
        Edit(1,0,0,1,1);
        if(DoubleEffect) if(handsize<10) Edit(1,0,0,1,1);
    }
    else if(id==14)
    {
        if(a>=0&&a<=6)
        {
            temp.b=MyBoard[a].id;
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
    else if(id==15)
    {
        bool flag1,flag2;
        flag1=draw_minion(a);
        flag2=draw_minion(b);
        if(flag1&&flag2)
        {
            double chance=(hand[handsize-1].Possibility)*(hand[handsize-2].Possibility)*2;
            Edit(1,handsize-1,5,0,chance);
            Edit(1,handsize-2,5,0,chance);
        }
    }
    else if(id==16)
    {
        for(int i=0;i<MyBoardSize;i++)
        {
            if(handsize<10)
            {
                Edit(1,0,0,1,MyBoard[i].id);
                Edit(1,handsize-1,2,0,1);
                Edit(1,handsize-1,4,0,1);
            }
        }
    }
    else if(id==17)
    {
        if(Card_Used)
        {
            Edit(2,0,0,1,17);
            if(DoubleEffect) Edit(2,0,0,1,17);
        }
    }
    else if(id==18)
    {
        Edit(11,0,0,0,DoubleEffect+1);
    }
    else if(id==19)
    {
        Edit(15,0,0,1,Card_Used);
        if(DoubleEffect) Edit(15,0,0,1,Card_Used);
    }
    else if(id==20)
    {
        if(a)
        {
            draw_spell(a);
            if(handsize<10) Edit(1,0,0,1,a);
        }
    }
    history.push_back(temp);
    if(!((id==5||id==10)&&(a==1))) Edit(7,0,0,0,Card_Used+1);
}

double Min_Possibility=0;
int Min_Damage=0;
struct Method
{
    vector<int> Damage_;
    vector<play> his;
    double Possibility;
    int Sum_Damage=0;
};
Method Certain;
vector<Method> Uncertain;

bool satisfied;

long long t_dfs=0;

void dfs(int fl)
{
    t_dfs++;
    if(satisfied) return;
    Tree.push_back(empty_vec);
    int son[10];
    int sonsize=0;

    bool GuiLing=false;
    bool HuiShou=false;
    bool chouPai=false;
    bool BoardGuiLing=false;
    int coin=-1;
    for(int p=0;p<handsize;p++)
    {
        if(hand[p].id==1&&hand[p].Raw_Cost==0) coin=p;
        int id=(hand[p].id==4)?hand[p].standby:hand[p].id;
        if(id==19) GuiLing=true;
        else if(id==3||id==11||id==16) HuiShou=true;
        else if(id==5||id==6||id==7||id==9||id==10||id==12||id==15) chouPai=true;
    }
    for(int i=0;i<MyBoardSize;i++)
    {
        if(MyBoard[i].id==19)
        {
            BoardGuiLing=true;
            break;
        }
    }

    if(coin>=0&&Buff.size()==0&&mana<10)
    {
        son[sonsize++]=coin;
    }
    else
    {
        for(int p=0;p<handsize;p++)
        {
            if(hand[p].Buffed_Cost<=mana)
            {
                if(getType(hand[p].id)==1)
                {
                    if(MyBoardSize<7) son[sonsize++]=p;
                }
                else son[sonsize++]=p;
            }
        }
    }
    if((GuiLing||(HuiShou&&BoardGuiLing)||(chouPai&&library[19]))&&(sonsize))
    {
        for(int i=0;i<sonsize;i++)
        {
            if(hand[son[i]].Possibility*possibility>=Min_Possibility)
            {
                int id=(hand[son[i]].id==4)?hand[son[i]].standby:hand[son[i]].id;
                int p=son[i];
                if(id==1)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==2)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==3)
                {
                    for(int a=0;a<MyBoardSize;a++)
                    {
                        Use(p,a,0,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                }
                else if(id==5)
                {
                    int a,b;
                    a=0;
                    for(b=0;b<MyBoardSize;b++)
                    {
                        Use(p,a,b,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                    for(b=0;b<EnemyBoardSize;b++)
                    {
                        Use(p,a,b+7,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                    if(MyHeroFullHp)
                    {
                        Use(p,a,14,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                    if(EnemyHeroFullHp)
                    {
                        Use(p,a,15,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                    a=1;
                    if(LibSize)
                    {
                        for(int b=1;b<CardType;b++)
                        {
                            if(library[b])
                            {
                                Use(p,a,b,0,0);
                                dfs(fl+1);
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
                                    Use(p,a,0,0,0);
                                    dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                    }
                    else
                    {
                        Use(p,0,0,0,0);
                        dfs(fl+1);
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
                                Use(p,a,0,0,0);
                                dfs(fl+1);
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
                    for(int a=0;a<MyBoardSize;a++)
                    {
                        if(LibSize)
                        {
                            for(int b=1;b<CardType;b++)
                            {
                                if(library[b])
                                {
                                    Use(p,a,b,0,0);
                                    dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                        else 
                        {
                            Use(p,a,0,0,0);
                            dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                    for(int a=0;a<EnemyBoardSize;a++)
                    {
                        if(LibSize)
                        {
                            for(int b=1;b<CardType;b++)
                            {
                                if(library[b])
                                {
                                    Use(p,a+7,b,0,0);
                                    dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                        else 
                        {
                            Use(p,a+7,0,0,0);
                            dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                    for(int a=14;a<=15;a++)
                    {
                        if(LibSize)
                        {
                            for(int b=1;b<CardType;b++)
                            {
                                if(library[b])
                                {
                                    Use(p,a,b,0,0);
                                    dfs(fl+1);
                                    history.erase(history.end()-1);
                                    Undo_This_Floor();
                                }
                            }
                        }
                        else
                        {
                            Use(p,a,0,0,0);
                            dfs(fl+1);
                            history.erase(history.end()-1);
                            Undo_This_Floor();
                        }
                    }
                }
                else if(id==10)
                {
                    int a;
                    a=0;
                    Use(p,a,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();

                    if(LibSize)
                    {
                        a=1;
                        for(int b=1;b<CardType;b++)
                        {
                            if(library[b])
                            {
                                for(int c=0;c<handsize;c++)
                                {
                                    if(hand[c].Type==0)
                                    {
                                        Use(p,a,b,c,0);
                                        dfs(fl+1);
                                        history.erase(history.end()-1);
                                        Undo_This_Floor();
                                    }
                                }
                            }
                        }
                    }
                }
                else if(id==11)
                {
                    for(int a=0;a<MyBoardSize;a++)
                    {
                        Use(p,a,0,0,0);
                        dfs(fl+1);
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
                                        Use(p,a,b,0,0);
                                        dfs(fl+1);
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
                                Use(p,a,0,0,0);
                                dfs(fl+1);
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
                                Use(p,0,b,0,0);
                                dfs(fl+1);
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
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==14)
                {
                    for(int a=0;a<MyBoardSize;a++)
                    {
                        Use(p,a,0,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                    for(int a=0;a<EnemyBoardSize;a++)
                    {
                        Use(p,a+7,0,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                }
                else if(id==15)
                {
                    const int Minion_id_list[5]={11,13,17,18,19};
                    if(Lib_Minion>=2)
                    {
                        for(int a=0;a<5;a++)
                        {
                            if(library[Minion_id_list[a]])
                            {
                                for(int b=0;b<5;b++)
                                {
                                    if((a!=b)&&library[Minion_id_list[b]])
                                    {
                                        Use(p,Minion_id_list[a],Minion_id_list[b],0,0);
                                        dfs(fl+1);
                                        history.erase(history.end()-1);
                                        Undo_This_Floor();
                                    }
                                }
                            }
                        }
                    }
                    else if(Lib_Minion==1)
                    {
                        for(int a=0;a<5;a++)
                        {
                            if(library[Minion_id_list[a]])
                            {
                                Use(p,Minion_id_list[a],0,0,0);
                                dfs(fl+1);
                                history.erase(history.end()-1);
                                Undo_This_Floor();
                            }
                        }
                    }
                    else if(Lib_Minion==0)
                    {
                        Use(p,0,0,0,0);
                        dfs(fl+1);
                        history.erase(history.end()-1);
                        Undo_This_Floor();
                    }
                }
                else if(id==16)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==17)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==18)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
                else if(id==19)
                {
                    Use(p,0,0,0,0);
                    dfs(fl+1);
                    history.erase(history.end()-1);
                    Undo_This_Floor();
                }
            }
        }
    }
    else
    {
        int sum=0;
        for(int i:Damage) sum+=i;
        if(possibility==1&&sum>Certain.Sum_Damage)
        {
            cout<<"第"<<t_dfs<<"次的结果:"<<endl;
            Method tMethod;
            tMethod.Damage_=Damage;
            tMethod.his=history;
            tMethod.Possibility=possibility;
            tMethod.Sum_Damage=sum;
            Certain=tMethod;
            cout<<endl<<endl;
            for(int i=0;i<Certain.his.size();i++)
            {
                cout<<"第"<<i+1<<"步:"<<endl;
                cout<<"["<<Certain.his[i].p+1<<"]:"<<Certain.his[i].cost<<"费卡牌\""<<getName(Certain.his[i].id)<<"\"";
                if(Certain.his[i].id==4)
                {
                    cout<<"变为\""<<Certain.his[i].d<<"\"";
                    Certain.his[i].id=Certain.his[i].d;
                }
                if(Certain.his[i].id==3)
                {
                    cout<<"->我方["<<Certain.his[i].a+1<<"]:\""<<getName(Certain.his[i].b)<<"\"";
                }
                else if(Certain.his[i].id==5)
                {
                    if(Certain.his[i].a==0)
                    {
                        cout<<" 模式:打 目标:";
                        if(Certain.his[i].b<=6)
                        {
                            cout<<"我方["<<Certain.his[i].b+1<<"]:"<<getName(Certain.his[i].c);
                        }
                        else if(Certain.his[i].b<=13)
                        {
                            cout<<"敌方["<<Certain.his[i].b-7+1<<"]";
                        }
                        else if(Certain.his[i].b==14)
                        {
                            cout<<"我方英雄";
                        }
                        else if(Certain.his[i].b==15)
                        {
                            cout<<"敌方英雄";
                        }
                    }
                    else
                    {
                        cout<<" 模式:交易 抽牌:"<<getName(Certain.his[i].b);
                    }
                }
                else if(Certain.his[i].id==6)
                {
                    cout<<"->"<<getName(Certain.his[i].a);
                }
                else if(Certain.his[i].id==7||Certain.his[i].id==20)
                {
                    cout<<"->"<<getName(Certain.his[i].a);
                }
                else if(Certain.his[i].id==9)
                {
                    cout<<"->";
                    if(Certain.his[i].a<=6)
                    {
                        cout<<"我方["<<Certain.his[i].a+1<<"]:"<<getName(Certain.his[i].c);
                    }
                    else if(Certain.his[i].a<=13)
                    {
                        cout<<"敌方["<<Certain.his[i].a-7+1<<"]";
                    }
                    else if(Certain.his[i].a==14)
                    {
                        cout<<"我方英雄";
                    }
                    else if(Certain.his[i].a==15)
                    {
                        cout<<"敌方英雄";
                    }
                    cout<<"抽牌:"<<getName(Certain.his[i].b);
                }
                else if(Certain.his[i].id==10)
                {
                    if(Certain.his[i].a==0)
                    {
                        cout<<" 模式:装备";
                    }
                    else if(Certain.his[i].a==1)
                    {
                        cout<<" 模式:交易 抽牌:"<<getName(Certain.his[i].b)<<" 减费位置:"<<Certain.his[i].c+1;
                    }
                }
                else if(Certain.his[i].id==11)
                {
                    cout<<"->["<<Certain.his[i].a+1<<"]:"<<getName(Certain.his[i].b);
                }
                else if(Certain.his[i].id==12)
                {
                    cout<<"->"<<getName(Certain.his[i].a)<<"&"<<getName(Certain.his[i].b);
                }
                else if(Certain.his[i].id==14)
                {
                    if(Certain.his[i].a<=6)
                    {
                        cout<<"->我方["<<Certain.his[i].a+1<<"]:"<<getName(Certain.his[i].b);
                    }
                    else if(Certain.his[i].a<=13)
                    {
                        cout<<"->敌方["<<Certain.his[i].a-7+1<<"]";
                    }
                }
                else if(Certain.his[i].id==15)
                {
                    cout<<"->"<<getName(Certain.his[i].a)<<"&"<<getName(Certain.his[i].b);
                }
                cout<<endl<<endl;
            }
            cout<<endl;
            cout<<"伤害结算:";
            if(Certain.Damage_.size()) cout<<Certain.Damage_[0];
            for(int i=1;i<Certain.Damage_.size();i++) cout<<" + "<<Certain.Damage_[i];
            cout<<" = "<<Certain.Sum_Damage<<endl;
            cout<<endl<<endl;
            if(sum>=Min_Damage)
            {
                cout<<"已达到伤害";
                satisfied=true;
            }
        }
        else if(sum>Certain.Sum_Damage&&possibility>=Min_Possibility) 
        {
            Method tMethod;
            tMethod.Damage_=Damage;
            tMethod.his=history;
            tMethod.Possibility=possibility;
            tMethod.Sum_Damage=sum;
            Uncertain.push_back(tMethod);
        }
    }
    Tree.erase(Tree.end()-1);
}

void show()
{
    cout<<"当前法力水晶:"<<mana<<endl;
    cout<<"当前用牌次数:"<<Card_Used<<endl;
    cout<<"当前Buff:"<<endl;
    for(short i=0;i<Buff.size();i++)
    {
        cout<<"Value:"<<Buff[i].value<<",Type:"<<Buff[i].type<<",Duration:"<<Buff[i].duration<<endl;
    }
    cout<<endl;
    cout<<"敌方英雄满血:"<<(EnemyHeroFullHp?"是":"否")<<endl;
    cout<<"我方英雄满血:"<<(MyHeroFullHp?"是":"否")<<endl;
    cout<<"当前敌方战场:"<<endl;
    for(short i=0;i<EnemyBoardSize;i++)
    {
        cout<<i<<":"<<"(hp:"<<EnemyBoard[i].Hp<<",满血:"<<((EnemyBoard[i].full_Hp)?"是":"否")<<") "<<endl;
    }
    cout<<endl;
    cout<<"当前我方战场:"<<endl;
    for(short i=0;i<MyBoardSize;i++)
    {
        cout<<i<<":"<<MyBoard[i].name<<"(hp:"<<MyBoard[i].Hp<<",满血:"<<((MyBoard[i].full_Hp)?"是":"否")<<")"<<endl;
    }
    cout<<endl;

    cout<<"当前手牌:"<<endl;
    for(short i=0;i<handsize;i++)
    {
        cout<<i+1<<":"<<hand[i].name<<"(cost:"<<hand[i].Buffed_Cost<<",type:"<<hand[i].Type<<",standby:"<<hand[i].standby<<") "<<endl;
    }
    cout<<endl;

    cout<<"当前伤害序列:"<<endl;
    if(Damage.size()>0)
    {
        short sum=Damage[0];
        cout<<sum;
        for(short i=1;i<Damage.size();i++)
        {
            cout<<" + "<<Damage[i];
            sum+=Damage[i];
        }
        cout<<" = "<<sum;
    }
    cout<<endl<<endl;
}

//System


int main()
{
    system("chcp 65001");
    memset(library,0,sizeof library);
    InitLib();
    Tree.push_back(empty_vec);
    string command;
    while(1)
    {
        cin>>command;
        if(command=="d")
        {
            string temp;
            cout<<"输入抽到的牌:";
            cin>>temp;
            while(!PYgetId(temp))
            {
                cout<<"重新输入:";
                cin>>temp;
            }
            draw(PYgetId(temp));
        }
        else if(command=="u")
        {
            int p,a=0,b=0,c=0,d=0;
            cout<<"输入使用的牌的位置:";
            cin>>p;
            p-=1;
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
                cout<<"输入要回手的随从位置:";
                cin>>a;
                a-=1;
                Use(p,a,b,c,d);
            }
            else if(id==5)
            {
                cout<<"模式(0:打,1:交易):";
                cin>>a;
                if(a==0)
                {
                    cout<<"输入目标(1~7为己方随从,8-14为敌方随从,15为己方英雄,16为敌方英雄):";
                    cin>>b;
                    b-=1;
                    Use(p,a,b,c,d);
                }
                else if(a==1)
                {
                    cout<<"输入抽到的牌:";
                    cin>>command;
                    b=PYgetId(command);
                    if(b) Use(p,a,b,c,d);
                }
            }
            else if(id==6)
            {
                if(Card_Used&&LibSize)
                {
                    cout<<"输入抽到的牌";
                    cin>>command;
                    a=PYgetId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==7)
            {
                if(LibSize)
                {
                    cout<<"输入抽到的牌";
                    cin>>command;
                    a=PYgetId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==8)
            {
                // cout<<"输入抽到的第1张牌(0-不抽):";
                // cin>>command;
                // a=PYgetId(command);
                // if(a)
                // {
                //     cout<<"输入抽到的第2张牌(0-不抽):";
                //     cin>>command;
                //     b=PYgetId(command);
                //     if(b)
                //     {
                //         cout<<"输入抽到的第3张牌(0-不抽):";
                //         cin>>command;
                //         c=PYgetId(command);
                //         if(c)
                //         {
                //             cout<<"输入抽到的第4张牌(0-不抽):";
                //             cin>>command;
                //             PYgetId(command);
                //         }
                //     }
                // }
                Use(p,a,b,c,d);
            }
            else if(id==9)
            {
                cout<<"输入目标(1~7为己方随从,8-14为敌方随从,15为己方英雄,16为敌方英雄):";
                cin>>a;
                a-=1;
                if(Card_Used)
                {
                    cout<<"输入抽到的牌:";
                    cin>>command;
                    b=PYgetId(command);
                    if(b) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
            else if(id==10)
            {
                cout<<"输入模式(0:装备,1:交易):";
                cin>>a;
                if(a==0)
                {
                    Use(p,a,b,c,d);
                }
                else if(a==1)
                {
                    cout<<"输入抽到的牌:";
                    cin>>command;
                    b=PYgetId(command);
                    cout<<"输入减费的位置:";
                    cin>>c;
                    c-=1;
                    if(b) Use(p,a,b,c,d);
                }
            }
            else if(id==11)
            {
                cout<<"输入要回手的随从位置:";
                cin>>a;
                a-=1;
                Use(p,a,b,c,d);
            }
            else if(id==12)
            {
                cout<<"输入抽到的法术牌:";
                cin>>command;
                a=PYgetId(command);
                cout<<"输入抽到的随从牌:";
                cin>>command;
                b=PYgetId(command);
                Use(p,a,b,c,d);
            }
            else if(id==13)
            {
                Use(p,a,b,c,d);
            }
            else if(id==14)
            {
                cout<<"输入攻击目标的位置(1~7为己方随从,8~14为敌方随从):";
                cin>>a;
                a-=1;
                Use(p,a,b,c,d);
            }
            else if(id==15)
            {
                cout<<"输入抽到的第一张随从牌:";
                cin>>command;
                a=PYgetId(command);
                cout<<"输入抽到的第二章随从牌:";
                cin>>command;
                b=PYgetId(command);
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
                    cout<<"输入抽到的牌";
                    cin>>command;
                    a=PYgetId(command);
                    if(a) Use(p,a,b,c,d);
                }
                else Use(p,a,b,c,d);
            }
        }
        if(command=="show")
        {
            show();
        }
        else if(command=="delHand")
        {
            int temp;
            cout<<"被删除手牌的位置:";
            cin>>temp;
            temp-=1;
            DelHand(temp);
        }
        else if(command=="coin")
        {
            Edit(1,0,0,1,1);
        }
        else if(command=="setmana")
        {
            cout<<"将水晶设置为:";
            cin>>mana;
        }
        else if(command=="addEM")
        {
            int temp;
            Edit(5,0,0,1,0);
            cout<<"输入血量:";
            cin>>temp;
            Edit(5,EnemyBoardSize-1,1,0,temp);
            cout<<"是否满血:";
            cin>>temp;
            Edit(5,EnemyBoardSize-1,2,0,temp);
        }
        else if(command=="setUsed")
        {
            cout<<"将已用牌数设置为:";
            cin>>Card_Used;
        }
        else if(command=="setHero")
        {
            cout<<"敌方英雄是否满血(0/1):";
            cin>>EnemyHeroFullHp;
            cout<<"我方英雄是否满血(0/1):";
            cin>>MyHeroFullHp;
        }
        else if(command=="dfs")
        {
            cout<<"最小概率(0~1,忽略任何该值以下的情况):";
            cin>>Min_Possibility;
            cout<<"最小伤害:";
            cin>>Min_Damage;
            cout<<"当前水晶:";
            cin>>mana;
            cout<<"已用的牌数量:";
            cin>>Card_Used;
            cout<<"敌方英雄是否满血(0/1):";
            cin>>EnemyHeroFullHp;
            cout<<"我方英雄是否满血(0/1):";
            cin>>MyHeroFullHp;
            clock_t start=clock();
            satisfied=false;
            possibility=1;
            for(int i=0;i<handsize;i++) hand[i].Possibility=1;
            Tree[0].clear();
            history.clear();
            dfs(1);
            cout<<endl<<"time elapsed:"<<double(clock()-start)/CLOCKS_PER_SEC<<"s";
            cout<<endl;
        }
        else if(command=="pause")
        {
            cout<<endl;
        }
        if(command!="dfs") show();
    }
    cout<<"end";
    return 0;
}