#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct card
{
    short id;
    short type;//0-法术, 1-随从, 2-武器
    short cost;
    short True_Cost;
    short standby=0;//注能、变形
};

struct minion
{
    short id;
    short hp;
    bool full_hp;
};

struct buff
{
    short val;
    short type;
    short duration;
};

struct Log
{
    card hand[11];
    map<short,short> library;//卡牌id -- 数量
    minion MyBoard[8],EnemyBoard[8];
    vector<buff> Buff;
    vector<short> Damage;
    short handsize=0,MyBoardSize=0,EnemyBoardSize=0,LibSize=0,mana=0,Card_Used=0;
    bool DoubleEffect;
};

card hand[11];
map<short,short> library;//卡牌id -- 数量
minion MyBoard[8],EnemyBoard[8];
vector<buff> Buff;
vector<short> Damage;
short handsize=0,MyBoardSize=0,EnemyBoardSize=0,LibSize=0,mana=0,Card_Used=0;
bool DoubleEffect;

const short deck[30]={1,1,2,2,3,3,4,5,6,6,7,7,8,8,9,10,10,11,12,12,13,14,14,15,15,16,16,17,18,19};

void InitLib()
{
    for(short i=0;i<30;i++) 
    {
        library[deck[i]]++;
        LibSize++;
    }
}

card getDefaultCard(short id)
{
    card temp;
    temp.id=id;
    if(id==1)//伪造的幸运币
    {
        temp.cost=0;
        temp.type=0;
    }
    if(id==2)//伺机待发
    {
        temp.cost=0;
        temp.type=0;
    }
    if(id==3)//暗影步
    {
        temp.cost=0;
        temp.type=0;
    }
    if(id==4)//殒命暗影
    {
        temp.cost=0;//存注能
        temp.type=0;
    }
    if(id==5)//军七要挟
    {
        temp.cost=1;
        temp.type=0;
    }
    if(id==6)//垂钓时光
    {
        temp.cost=1;
        temp.type=0;
    }
    if(id==7)//暗影之门
    {
        temp.cost=1;
        temp.type=0;
    }
    if(id==8)//秘密通道
    {
        temp.cost=1;
        temp.type=0;
    }
    if(id==9)//鬼魅攻击
    {
        temp.cost=1;
        temp.type=0;
    }
    if(id==10)//黑水弯刀
    {
        temp.cost=1;
        temp.type=2;
    }
    if(id==11)//腾武
    {
        temp.cost=2;
        temp.type=1;
    }
    if(id==12)//行骗
    {
        temp.cost=2;
        temp.type=0;
    }
    if(id==13)//邮箱舞者
    {
        temp.cost=2;
        temp.type=1;
    }
    if(id==14)//锯齿骨刺
    {
        temp.cost=2;
        temp.type=0;
    }
    if(id==15)//潜伏帷幕
    {
        temp.cost=3;
        temp.type=0;
    }
    if(id==16)//幻觉药水
    {
        temp.cost=4;
        temp.type=0;
    }
    if(id==17)//刀油
    {
        temp.cost=4;
        temp.type=1;
    }
    if(id==18)//鲨鱼
    {
        temp.cost=4;
        temp.type=1;
    }
    if(id==19)//鬼灵
    {
        temp.cost=6;
        temp.type=1;
    }
    return temp;
}

minion getDefaultMinion(short id)
{
    minion temp;
    temp.id=id;
    temp.full_hp=true;
    if(id==11) temp.hp=2;
    else if(id==13) temp.hp=2;
    else if(id==17) temp.hp=3;
    else if(id==18) temp.hp=3;
    else if(id==19) temp.hp=5;
    return temp;
}

string Id2Name(short id)
{
    if(id==1) return "伪造的/幸运币";
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

    return 0;
}

short Name2Id(string name)
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

void UpdateHand()
{
    for(short i=0;i<handsize;i++)
    {
        hand[i].True_Cost=hand[i].cost;
        for(short j=0;j<Buff.size();j++)
        {
            if(hand[i].type==Buff[j].type||Buff[j].type==3) hand[i].True_Cost+=Buff[j].val;
        }
        if(hand[i].True_Cost<0) hand[i].True_Cost=0;
        if(hand[i].id==7&&hand[i].standby>=2) hand[i].id=20;
    }
}

void UseBuff(short type)//0-法术,1-随从,3-全部
{
    for(short i=0;i<Buff.size();i++)
    {
        if(Buff[i].type==type||Buff[i].type==3) Buff[i].duration--;
        if(Buff[i].duration==0) Buff.erase(Buff.begin()+i);
    }
}

void draw(short id,bool position)//0-left 1-right
{
    if(id)
    {
        library[id]--;
        if(handsize<10) 
        {
            if(position==1)
            {
                hand[handsize++]=getDefaultCard(id);
            }
            else
            {
                for(short i=handsize-1;i>0;i++)
                {
                    hand[i]=hand[i-1];
                }
                hand[0]=getDefaultCard(id);
            }
        }
        UpdateHand();
    }
}

void DelHand(short position)
{
    for(short i=position;i<10;i++)
    {
        hand[i]=hand[i+1];
    }
    handsize--;
}

void DelMyBoard(short position)
{
    for(short i=position;i<7;i++)
    {
        MyBoard[i]=MyBoard[i+1];
    }
    MyBoardSize--;
}

void DelEnemyBoard(short position)
{
    for(short i=position;i<7;i++)
    {
        EnemyBoard[i]=EnemyBoard[i+1];
    }
    EnemyBoardSize--;
}

void Minion_Enter(short position_in_hand)
{
    MyBoard[MyBoardSize]=getDefaultMinion(hand[position_in_hand].id);
    if(hand[position_in_hand].standby==1) MyBoard[MyBoardSize].hp=1;
    MyBoardSize++;
    DelHand(position_in_hand);
}

void ZhuNeng(short x)
{
    for(short j=0;j<handsize;j++)
    {
        if(hand[j].id==7) hand[j].standby+=x;//注能
    }
}

bool Death_acc()
{
    bool flag=false;
    for(short i=0;i<MyBoardSize;i++)
    {
        if(MyBoard[i].hp<=0)
        {
            if(MyBoard[i].id==18) DoubleEffect=false;
            DelMyBoard(i);
            ZhuNeng(1);
            flag=true;
        }
    }
    for(short i=0;i<EnemyBoardSize;i++)
    {
        if(EnemyBoard[i].hp<=0)
        {
            DelEnemyBoard(i);
            flag=true;
        }
    }
    return flag;
}

void showBoard()
{
    cout<<"当前我方战场:"<<endl;
    for(short i=0;i<MyBoardSize;i++)
    {
        cout<<i<<":"<<Id2Name(MyBoard[i].id)<<"(hp:"<<MyBoard[i].hp<<") "<<endl;
    }
    cout<<endl;
}

void showHand()
{
    cout<<"当前手牌:"<<endl;
    for(short i=0;i<handsize;i++)
    {
        cout<<i<<":"<<Id2Name(hand[i].id)<<"(cost:"<<hand[i].True_Cost<<",type:"<<hand[i].type<<",standby:"<<hand[i].standby<<") "<<endl;
    }
    cout<<endl;
}

void showBuff()
{
    cout<<"当前Buff:"<<endl;
    for(short i=0;i<Buff.size();i++)
    {
        cout<<"Value:"<<Buff[i].val<<",Type:"<<Buff[i].type<<",Duration:"<<Buff[i].duration<<endl;
    }
    cout<<endl;
}

void showDamage()
{
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

void coin()//幸运币
{
    mana++;
}

void Si_Ji()//伺机待发
{
    buff temp;
    temp.val=-2;
    temp.type=0;
    temp.duration=1;
    Buff.push_back(temp);
}

void An_Ying_Bu(short position_on_board)//暗影步
{
    card temp=getDefaultCard(MyBoard[position_on_board].id);
    temp.cost-=2;
    hand[handsize++]=temp;
    DelMyBoard(position_on_board);
}

void Yao_Xie(short mode,short target)//军七要挟
{
    if(mode==0)//交易
    {
        draw(target,1);
    }
    else//打
    {
        if(target<=6)
        {
            MyBoard[target].hp-=3;
            MyBoard[target].full_hp=false;
            Death_acc();
        }
        else if(target==14)
        {
            Damage.push_back(3);
        }
        else if(target==15)
        {

        }
        else
        {
            EnemyBoard[target-7].hp-=3;
            EnemyBoard[target-7].full_hp=false;
            Death_acc();
        }
    }
    
}

void Chui_Diao(short id)//垂钓时光
{
    if(id) draw(id,1);
}

void An_Ying_Zhi_Men(short id)//暗影之门
{
    if(id) draw(id,1);
}

void Tong_Dao(short id1,short id2,short id3,short id4)
{
    if(id1) draw(id1,1);
    if(id2) draw(id2,1);
    if(id3) draw(id3,1);
    if(id4) draw(id4,1);
}

void Gui_Mei(short id,short target)//鬼魅攻击
{
    if(id) draw(id,1);
    if(target==7) Damage.push_back(1);
    else if(target==8)
    {

    }
    else
    {
        MyBoard[target].hp--;
        MyBoard[target].full_hp=false;
        Death_acc();
    }
}

void Wan_Dao(short mode,short id,short p)//黑水弯刀
{
    if(mode==0)//交易
    {
        library[10]++;
        draw(id,1);
        hand[p].cost--;
    }
    else if(mode==1)
    {
        Damage.push_back(2);
    }
}

void Teng_Wu(short target)//腾武
{
    card temp;
    temp=getDefaultCard(MyBoard[target].id);
    temp.cost=1;
    hand[handsize++]=temp;
    DelMyBoard(target);
}

void Xing_Pian(short spell_id,short minion_id)//行骗
{
    if(spell_id) draw(spell_id,1);
    if(minion_id) draw(minion_id,1);
}

void Wu_Zhe()//邮箱舞者
{
    if(handsize<10) hand[handsize++]=getDefaultCard(1);
    if(DoubleEffect) if(handsize<10) hand[handsize++]=getDefaultCard(1);
}

void Gu_Ci(short target)
{
    if(target<=6)
    {
        MyBoard[target].hp-=3;
        MyBoard[target].full_hp=false;
    }
    else
    {
        EnemyBoard[target-7].hp-=3;
        EnemyBoard[target-7].full_hp=false;
    }
    if(Death_acc())
    {
        buff temp;
        temp.val=-2;
        temp.type=3;
        temp.duration=1;
        Buff.push_back(temp);
    }
}

void Wei_Mu(short id1,short id2)
{
    if(id1) draw(id1,1);
    if(id2) draw(id2,1);
}

void Huan_Jue()//幻觉药水
{
    for(short i=0;i<MyBoardSize;i++)
    {
        card temp=getDefaultCard(MyBoard[i].id);
        temp.cost=1;
        temp.standby=1;
        if(handsize<10) hand[handsize++]=temp;
    }
}

void Dao_You()//刀油
{
    if(Card_Used)
    {
        buff temp;
        temp.val=DoubleEffect?-6:-3;
        temp.type=3;
        temp.duration=2;
        Buff.push_back(temp);
    }
}

void Sha_Yu()//鲨鱼
{
    DoubleEffect=true;
}

void Gui_Ling()//鬼灵
{
    Damage.push_back(Card_Used);
    if(DoubleEffect) Damage.push_back(Card_Used);
}

void Zhu_Neng_An_Ying_Men(short id)
{
    if(id)
    {
        draw(id,1);
        if(handsize<10) hand[handsize++]=getDefaultCard(id);
    }
}

void Use(short position_in_hand,short mode,short p1,short p2,short p3,short p4)
{
    if(hand[position_in_hand].type==0)//法术
    {
        short id=hand[position_in_hand].id;
        if(id==5&&mode==1) 
        {
            mana--;
        }
        else if(id==4)
        {
            id=hand[position_in_hand].standby;
            UseBuff(0);
            mana-=hand[position_in_hand].True_Cost;
        }
        else 
        {
            UseBuff(0);
            mana-=hand[position_in_hand].True_Cost;
        }
        DelHand(position_in_hand);
        for(short i=0;i<handsize;i++) if(hand[i].id==4) hand[i].standby=id;

        if(id==1) coin();
        else if(id==2) Si_Ji();
        else if(id==3) An_Ying_Bu(p1);//我方场上的编号
        else if(id==5) Yao_Xie(mode,p1);//mode:0:交易(p1为抽的牌的id),1:打(p1为打的随从的id,我方为0~6,敌方为7~13,14为敌方英雄,15为自己英雄)
        else if(id==6) Chui_Diao(p1);//p1:0:不抽牌,1:抽的牌的id
        else if(id==7) An_Ying_Zhi_Men(p1);//p1:抽牌的id
        else if(id==8) Tong_Dao(p1,p2,p3,p4);//抽的四张牌,0代表抽不到
        else if(id==9) Gui_Mei(p1,p2);//p1:0:不抽牌,>0则为抽牌的id/p2:攻击对象,0~6为己方随从,7为敌方英雄,8为己方英雄
        else if(id==12) Xing_Pian(p1,p2);//p1,p2:0:不抽牌,>0:抽的随从或法术牌的id
        else if(id==14) Gu_Ci(p1);//刺的随从的位置:0~6为己方随从,7~13为敌方随从
        else if(id==15) Wei_Mu(p1,p2);//抽的两张随从牌的id,0为抽不到
        else if(id==16) Huan_Jue();
        else if(id==20) Zhu_Neng_An_Ying_Men(p1);//p1:抽牌的id
    }
    else if(hand[position_in_hand].type==1)//随从
    {
        UseBuff(1);
        short id=hand[position_in_hand].id;
        mana-=hand[position_in_hand].True_Cost;
        Minion_Enter(position_in_hand);
        if(id==11) Teng_Wu(p1);//p1:回手的随从在场上的位置
        else if(id==13) Wu_Zhe();
        else if(id==17) Dao_You();
        else if(id==18) Sha_Yu();
        else if(id==19) Gui_Ling();
    }
    else if(hand[position_in_hand].type==2)//武器
    {
        DelHand(position_in_hand);
        if(mode==0)
        {
            mana--;
            Card_Used--;
        }
        else
        {
            mana-=hand[position_in_hand].True_Cost;
            UseBuff(2);
        }
        Wan_Dao(mode,p1,p2);//mode:0:交易,1:装备,/p1:抽牌id/p2:减费的位置
    }
    Card_Used++;
    UpdateHand();
}

void AddEnemyMinion(short hp,bool full_hp)
{
    minion temp;
    temp.id=-1;
    temp.hp=hp;
    temp.full_hp=full_hp;
    EnemyBoard[EnemyBoardSize++]=temp;
}

void dfs()
{

}

int main()
{
    system("chcp 65001");
    string command,temp;
    short p1,p2,p3,p4,p5,p6;
    while(1)
    {
        p1=0,p2=0,p3=0,p4=0,p5=0,p6=0;
        cin>>command;
        if(command=="draw")
        {
            cout<<"输入抽到的牌:";
            cin>>temp;
            while(!Name2Id(temp))
            {
                cout<<"重新输入:";
                cin>>temp;
            }
            draw(Name2Id(temp),1);
        }
        if(command=="setmana")
        {
            cout<<"将法力水晶设置为:";
            cin>>p1;
            mana=p1;
        }
        if(command=="setUsed")
        {
            cout<<"设置用牌次数为:";
            cin>>p1;
            Card_Used=p1;
        }
        if(command=="Use")
        {
            cout<<"输入使用的牌的位置:";
            cin>>p1;
            short id=hand[p1].id;
            if(id==4) id=hand[p1].standby;

            if(id==1) Use(p1,0,0,0,0,0);
            else if(id==2) Use(p1,0,0,0,0,0);
            else if(id==3)
            {
                cout<<"输入要回手的随从位置:";
                cin>>p2;
                Use(p1,0,p2,0,0,0);
            }
            else if(id==5)
            {
                cout<<"模式(0:交易,1:打):";
                cin>>p2;
                if(p2==0)
                {
                    cout<<"输入抽到的牌:";
                    cin>>temp;
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    Use(p1,p2,Name2Id(temp),0,0,0);
                }
                else
                {
                    cout<<"输入攻击目标(我方为0~6,敌方为7~13,14为敌方英雄,15为自己英雄):";
                    cin>>p3;
                    Use(p1,p2,p3,0,0,0);
                }
            }
            else if(id==6)
            {
                cout<<"输入抽到的牌:";
                cin>>temp;
                if(temp=="0") Use(p1,0,0,0,0,0);
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    Use(p1,0,Name2Id(temp),0,0,0);
                }
            }
            else if(id==7)
            {
                cout<<"输入抽到的法术牌:";
                cin>>temp;
                if(temp=="0") Use(p1,0,0,0,0,0);
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    Use(p1,0,Name2Id(temp),0,0,0);
                }
            }
            else if(id==8)
            {
                short tp[4]={0,0,0,0};
                for(short i=0;i<4;i++)
                {
                    cout<<"输入抽到的第"<<i+1<<"张牌(0为不抽牌):";
                    cin>>temp;
                    if(temp=="0") break;
                    else
                    {
                        while(!Name2Id(temp))
                        {
                            cout<<"重新输入:";
                            cin>>temp;
                        }
                        tp[i]=Name2Id(temp);
                    }
                }
                Use(p1,0,tp[0],tp[1],tp[2],tp[3]);
            }
            else if(id==9)
            {
                cout<<"输入抽到的牌(0为不抽牌):";
                cin>>temp;
                if(temp=="0") p2=0;
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    p2=Name2Id(temp);
                }
                cout<<"输入攻击对象(0~6为己方随从,7为敌方英雄,8为己方英雄):";
                cin>>p3;
                Use(p1,0,p2,p3,0,0);
            }
            else if(id==10)
            {
                cout<<"输入模式(0:交易,1:装备):";
                cin>>p2;
                if(p2==0)
                {
                    cout<<"输入抽到的牌:";
                    cin>>temp;
                    if(temp=="0") p3=0;
                    else
                    {
                        while(!Name2Id(temp))
                        {
                            cout<<"重新输入:";
                            cin>>temp;
                        }
                        p3=Name2Id(temp);
                    }
                    cout<<"输入减费的位置:";
                    cin>>p4;
                    Use(p1,p2,p3,p4,0,0);
                }
                else
                {
                    Use(p1,p2,0,0,0,0);
                }
            }
            else if(id==11)
            {
                cout<<"输入要回手的随从位置:";
                cin>>p2;
                Use(p1,0,p2,0,0,0);
            }
            else if(id==12)
            {
                cout<<"输入抽到的法术牌:";
                cin>>temp;
                if(temp=="0") p2=0;
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    p2=Name2Id(temp);
                }
                cout<<"输入抽到的随从牌:";
                cin>>temp;
                if(temp=="0") p3=0;
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    p3=Name2Id(temp);
                }
                Use(p1,0,p2,p3,0,0);
            }
            else if(id==13)
            {
                Use(p1,0,0,0,0,0);
            }
            else if(id==14)
            {
                cout<<"输入攻击目标的位置(0~6为己方随从,7~13为敌方随从):";
                cin>>p2;
                Use(p1,0,p2,0,0,0);
            }
            else if(id==15)
            {
                cout<<"输入抽到的第一张随从牌:";
                cin>>temp;
                if(temp=="0") p2=0;
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    p2=Name2Id(temp);
                }
                cout<<"输入抽到的第二章随从牌:";
                cin>>temp;
                if(temp=="0") p3=0;
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    p3=Name2Id(temp);
                }
                Use(p1,0,p2,p3,0,0);
            }
            else if(id==16)
            {
                Use(p1,0,0,0,0,0);
            }
            else if(id==17)
            {
                Use(p1,Card_Used,0,0,0,0);
            }
            else if(id==18)
            {
                Use(p1,0,0,0,0,0);
            }
            else if(id==19)
            {
                Use(p1,0,0,0,0,0);
            }
            else if(id==20)
            {
                cout<<"输入抽到的法术牌:";
                cin>>temp;
                if(temp=="0") Use(p1,0,0,0,0,0);
                else
                {
                    while(!Name2Id(temp))
                    {
                        cout<<"重新输入:";
                        cin>>temp;
                    }
                    Use(p1,0,Name2Id(temp),0,0,0);
                }
            }
        }
        if(command=="show")
        {
            cout<<"当前法力水晶:"<<mana<<endl;
            cout<<"当前用牌次数:"<<Card_Used<<endl;
            showBuff();
            showBoard();
            showHand();
            showDamage();
        }
        if(command=="DelHand")
        {
            cout<<"删除的手牌的位置:";
            cin>>p1;
            DelHand(p1);
        }
        if(command=="AddEnemy")
        {
            cout<<"输入敌方随从的生命值:"<<endl;
            cin>>p1;
            cout<<"是否为满血(0-否,1-是):";
            cin>>p2;
            AddEnemyMinion(p1,p2);
        }
    }

    return 0;
}