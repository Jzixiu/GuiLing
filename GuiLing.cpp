#include <iostream>
#include <vector>
#include <map>
using namespace std;

class card
{
    public:
    int cost;
    int id;
    int type;//spell=0,minion=1,weapon=2
    int standby=0;//法术牌的注能情况/随从牌:1:被幻觉收回来的:hp=1
};

class minion
{
    public:
    bool full_hp;
    int hp;
    int id;
};

class buff
{
    public:
    int val;
    int type;//0:spell,1:minion,2:all
    int duration;//给以下n张减费
};

vector<card> hand;
vector<minion> board;
vector<buff> Buff;
vector<int> damage;
vector<int> avaliable;
map<int,int> library;
map<int,int>::iterator it;
int libnum=0,mana=0;
int FullHpEnemyMinion=0;
bool EnemyHeroFullhp=false;
int CardUsed=0;
int weapon=0;

bool DoubleEffect=false;

const int deck[30]={1,1,2,2,3,3,4,5,6,6,7,7,8,8,9,10,10,11,12,12,13,14,14,15,15,16,16,17,18,19};

card getDefaultCard(int id)
{
    card temp;
    temp.id=id;
    if(id==1)//伪造的幸运币
    {
        temp.cost=0;
        temp.type=0;
    }
    else if(id==2)//伺机待发
    {
        temp.cost=0;
        temp.type=0;
    }
    else if(id==3)//暗影步
    {
        temp.cost=0;
        temp.type=0;
    }
    else if(id==4)//殒命暗影
    {
        temp.cost=0;//存注能
        temp.type=0;
    }
    else if(id==5)//军七要挟
    {
        temp.cost=1;
        temp.type=0;
    }
    else if(id==6)//垂钓时光
    {
        temp.cost=1;
        temp.type=0;
    }
    else if(id==7)//暗影之门
    {
        temp.cost=1;
        temp.type=0;
    }
    else if(id==8)//秘密通道
    {
        temp.cost=1;
        temp.type=0;
    }
    else if(id==9)//鬼魅攻击
    {
        temp.cost=1;
        temp.type=0;
    }
    else if(id==10)//黑水弯刀
    {
        temp.cost=1;
        temp.type=2;
    }
    else if(id==11)//腾武
    {
        temp.cost=2;
        temp.type=1;
    }
    else if(id==12)//行骗
    {
        temp.cost=2;
        temp.type=0;
    }
    else if(id==13)//邮箱舞者
    {
        temp.cost=2;
        temp.type=1;
    }
    else if(id==14)//锯齿骨刺
    {
        temp.cost=2;
        temp.type=0;
    }
    else if(id==15)//潜伏帷幕
    {
        temp.cost=3;
        temp.type=0;
    }
    else if(id==16)//幻觉药水
    {
        temp.cost=4;
        temp.type=0;
    }
    else if(id==17)//刀油
    {
        temp.cost=4;
        temp.type=1;
    }
    else if(id==18)//鲨鱼
    {
        temp.cost=4;
        temp.type=1;
    }
    else if(id==19)//鬼灵
    {
        temp.cost=6;
        temp.type=1;
    }
    return temp;
}

minion getDefaultMinion(int id)
{
    minion temp;
    temp.id=id;
    if(id==11) temp.hp=2;
    else if(id==13) temp.hp=2;
    else if(id==17) temp.hp=3;
    else if(id==18) temp.hp=3;
    else if(id==19) temp.hp=5;
    return temp;
}

inline int getCost(int cost,int type)
{
    if(type==0)//法术
    {
        for(int i=0;i<Buff.size();i++) 
        {
            if(Buff[i].type==0||Buff[i].type==2)cost+=Buff[i].val;
        }
        return cost>0?cost:0;
    }
    if(type==1)
    {
        for(int i=0;i<Buff.size();i++) 
        {
            if(Buff[i].type==1||Buff[i].type==2)cost+=Buff[i].val;
        }
        return cost>0?cost:0;
    }
    if(type==2)
    {
        for(int i=0;i<Buff.size();i++) 
        {
            if(Buff[i].type==2)cost+=Buff[i].val;
        }
        return cost>0?cost:0;
    }
}

void Init_Deck()
{
    for(int i=0;i<30;i++)
    {
        it=library.find(deck[i]);
        if(it==library.end()) library.insert(make_pair(deck[i],1));
        else it->second++;
        libnum++;
    }
}

void L2H(int id)
{
    library[id]--;
    if(hand.size()<10) hand.push_back(getDefaultCard(id));
    libnum--;
}

void L2H1(int id)
{
    library[id]--;
    card temp;
    hand.push_back(temp);
    for(int i=hand.size()-1;i>0;i++)
    {
        hand[i]=hand[i-1];
    }
    hand[0]=getDefaultCard(id);
    libnum--;
}

void H2B(int position)
{
    minion temp=getDefaultMinion(hand[position].id);
    temp.full_hp=true;
    if(hand[position].standby==1) temp.hp=1;
    board.push_back(temp);
    hand.erase(hand.begin()+position);
}

void dellib(int id)
{
    library[id]--;
    libnum--;
}


void ZhuNeng(int x)
{
    for(int j=0;j<hand.size();j++)
    {
        if(hand[j].id==7) hand[j].standby+=x;//注能
    }
}

bool Death_acc()
{
    bool flag=false;
    for(int i=0;i<board.size();i++)
    {
        if(board[i].hp<=0)
        {
            if(board[i].id==18) DoubleEffect=false;
            board.erase(board.begin()+i);
            ZhuNeng(1);
            flag=true;
        }
    }
    return flag;
}

void DeleteHand(int temp)
{
    hand.erase(hand.begin()+temp);
}

string getIdName(int id)
{
    if(id==1) return "伪造的/幸运币";
    else if(id==2) return "伺机待发";
    else if(id==3) return "暗影步";
    else if(id==4) return "殒命暗影";
    else if(id==5) return "军七要挟";
    else if(id==6) return "垂钓时光";
    else if(id==7) return "暗影之门";
    else if(id==8) return "秘密通道";
    else if(id==9) return "鬼魅攻击";
    else if(id==10) return "黑水弯刀";
    else if(id==11) return "腾武";
    else if(id==12) return "行骗";
    else if(id==13) return "邮箱舞者";
    else if(id==14) return "锯齿骨刺";
    else if(id==15) return "潜伏帷幕";
    else if(id==16) return "幻觉药水";
    else if(id==17) return "刀油";
    else if(id==18) return "鲨鱼";
    else if(id==19) return "鬼灵";
}


void showBoard()
{
    cout<<"当前战场:"<<endl;
    for(int i=0;i<board.size();i++)
    {
        cout<<i<<":"<<getIdName(board[i].id)<<"(hp:"<<board[i].hp<<") "<<endl;
    }
    cout<<endl;
}

void showHand()
{
    cout<<"当前手牌:"<<endl;
    for(int i=0;i<hand.size();i++)
    {
        cout<<i<<":"<<getIdName(hand[i].id)<<"(cost:"<<hand[i].cost<<",type:"<<hand[i].type<<",standby:"<<hand[i].standby<<") "<<endl;
    }
    cout<<endl;
}

void showBuff()
{
    cout<<"当前Buff:"<<endl;
    for(int i=0;i<Buff.size();i++)
    {
        cout<<"Value:"<<Buff[i].val<<",Type:"<<Buff[i].type<<",Duration:"<<Buff[i].duration<<endl;
    }
    cout<<endl;
}

void showDamage()
{
    cout<<"当前伤害序列:"<<endl;
    if(damage.size()>0)
    {
        int sum=damage[0];
        cout<<sum;
        for(int i=1;i<damage.size();i++)
        {
            cout<<" + "<<damage[i];
            sum+=damage[i];
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

void An_Ying_Bu(int position_on_board)//暗影步
{
    card temp=getDefaultCard(board[position_on_board].id);
    temp.cost-=2;
    hand.push_back(temp);
    board.erase(board.begin()+position_on_board);
}

void Yao_Xie(int position_on_board,int mode,int id)//军七要挟
{
    if(mode==1)
    {
        if(position_on_board==-1)//敌方随从
        {
            
        }
        else if(position_on_board==-2)//敌方英雄
        {
            damage.push_back(3);
        }
        else
        {
            board[position_on_board].hp-=3;
            board[position_on_board].full_hp=false;
            Death_acc();
        }
    }
    else if(mode==0)
    {
        L2H(id);
    }
    
}

void Chui_Diao(int target)//垂钓时光
{
    if(target) L2H(target);
}

void An_Ying_Zhi_Men(int target,int x)//暗影之门
{
    if(x>=2) hand.push_back(getDefaultCard(target));
    L2H(target);
}

void Tong_Dao(int a,int b,int c,int d)//秘密通道
{
    hand.clear();
    L2H(a);
    L2H(b);
    L2H(c);
    L2H(d);
}

void Gui_Mei(int target,int id)//鬼魅攻击
{
    if(target==-1)
    {
        damage.push_back(1);
    }
    else
    {
        board[target].hp--;
        Death_acc();
    }
    if(id!=0) L2H(id);
}

void Wan_Dao(int mode,int id,int p)//黑水弯刀
{
    if(mode==0)
    {
        library[10]++;
        L2H(id);
        hand[p].cost--;
    }
    else if(mode==1)
    {
        weapon=2;
    }
}

void Teng_Wu(int target)//腾武
{
    card temp;
    temp=getDefaultCard(board[target].id);
    temp.cost=1;
    hand.push_back(temp);
    board.erase(board.begin()+target);
}

void Xing_Pian(int spell_id,int minion_id)//行骗
{
    if(spell_id) L2H(spell_id);
    if(minion_id) L2H(minion_id);
}

void Wu_Zhe()//邮箱舞者
{
    if(hand.size()<10) hand.push_back(getDefaultCard(1));
    if(DoubleEffect) if(hand.size()<10) hand.push_back(getDefaultCard(1));
}

void Gu_Ci(int target)//骨刺
{
    if(target==-2)
    {
        buff temp;
        temp.val=-2;
        temp.type=2;
        temp.duration=1;
        Buff.push_back(temp);
    }
    else if(target==-1)
    {

    }
    else
    {
        board[target].hp-=3;
        if(Death_acc())
        {
            buff temp;
            temp.val=-2;
            temp.type=2;
            temp.duration=1;
            Buff.push_back(temp);
        }
    }
    
}

void Wei_Mu(int id1,int id2)//潜伏帷幕
{
    L2H(id1);
    L2H(id2);
}

void Huan_Jue()//幻觉药水
{
    for(int i=0;i<board.size();i++)
    {
        card temp=getDefaultCard(board[i].id);
        temp.cost=1;
        temp.standby=1;
        if(hand.size()<10) hand.push_back(temp);
    }
}

void Dao_You(int LianJi)//刀油
{
    if(LianJi)
    {
        buff temp;
        temp.val=DoubleEffect?-6:-3;
        temp.type=2;
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
    damage.push_back(CardUsed);
    if(DoubleEffect) damage.push_back(CardUsed);
}


void Use(int position_in_hand, int target,int a,int b,int c)
{    
    if(hand[position_in_hand].type==0)//法术
    {
        int cost,id,sdb;
        if(hand[position_in_hand].id==4)
        {
            id=hand[position_in_hand].standby;
            cost=getCost(getDefaultCard(id).cost,0);
            sdb=hand[position_in_hand].cost;
            for(vector<buff>::iterator bf=Buff.begin();bf<Buff.end();bf++)
            {
            if(bf->type==2||bf->type==0) bf->duration--;
            if(bf->duration==0) Buff.erase(bf);
            }
        }
        else if(hand[position_in_hand].id==5)
        {
            if(a==0)
            {
                id=5;
                cost=1;
            }
            else if(a==1)
            {
                id=5;
                cost=getCost(hand[position_in_hand].cost,0);
                for(vector<buff>::iterator bf=Buff.begin();bf<Buff.end();bf++)
                {
                    if(bf->type==2||bf->type==0) bf->duration--;
                    if(bf->duration==0) Buff.erase(bf);
                }
            }
        }
        else
        {
            cost=getCost(hand[position_in_hand].cost,0);
            id=hand[position_in_hand].id;
            sdb=hand[position_in_hand].standby;
            for(vector<buff>::iterator bf=Buff.begin();bf<Buff.end();bf++)
            {
            if(bf->type==2||bf->type==0) bf->duration--;
            if(bf->duration==0) Buff.erase(bf);
            }
        }
        
        mana-=cost;
        hand.erase(hand.begin()+position_in_hand);
        for(int i=0;i<hand.size();i++) 
        {
            if(hand[i].id==4) 
            {
                hand[i].standby=id;//存储使用过的法术
                if(id==7)
                {
                    hand[i].cost=sdb;
                }
            }
        }
        if(id==1) coin();
        else if(id==2) Si_Ji();
        else if(id==3) An_Ying_Bu(target);//target:暗影步收的随从在board中的编号
        else if(id==4) cout<<"见鬼了";//额
        else if(id==5) Yao_Xie(target,a,b);//target:-2:敌方英雄,-1:敌方随从,>=0:board中编号/a:0:交易,1:打/b:抽牌id
        else if(id==6) Chui_Diao(target);//target:从牌库中抽的牌的id
        else if(id==7) An_Ying_Zhi_Men(target,sdb);//target:抽的牌,sdb:注能情况
        else if(id==8) Tong_Dao(target,a,b,c);//抽的四张
        else if(id==9) Gui_Mei(target,a);//target:-1:敌方英雄,>=0:board中的编号/id:0:不构成连击,>0:所抽的牌的id
        else if(id==12) Xing_Pian(target,a);//target:抽的法术牌的id/a:抽的随从牌的id
        else if(id==14) Gu_Ci(target);//target:-2:敌方某能打死的随从,-1:敌方某不能打死的随从,>=0:board上的编号
        else if(id==15) Wei_Mu(target,a);//抽的两个随从的id
        else if(id==16) Huan_Jue();
        CardUsed++;
    }
    else if(hand[position_in_hand].type==1)//随从
    {
        int id=hand[position_in_hand].id;
        int cost=getCost(hand[position_in_hand].cost,1);
        for(vector<buff>::iterator bf=Buff.begin();bf<Buff.end();bf++)
        {
        if(bf->type==2||bf->type==1) bf->duration--;
        if(bf->duration==0) Buff.erase(bf);
        }  
        mana-=cost;
        H2B(position_in_hand);
        if(id==11) Teng_Wu(target);//Board上的位置
        else if(id==13) Wu_Zhe();
        else if(id==17) Dao_You(target);//0:不连击,1:连击
        else if(id==18) Sha_Yu();
        else if(id==19) Gui_Ling();
        CardUsed++;
    }
    else if(hand[position_in_hand].type==2)
    {
        int cost;
        if(target==0) 
        {
            cost=1;
        }
        else
        {
            cost=getCost(hand[position_in_hand].cost,2);
            for(vector<buff>::iterator bf=Buff.begin();bf<Buff.end();bf++)
            {
                if(bf->type==2) bf->duration--;
                if(bf->duration==0) Buff.erase(bf);
            }
            CardUsed++;
        }
        mana-=cost;
        hand.erase(hand.begin()+position_in_hand);
        Wan_Dao(target,a,b);//交易0,挂刀1/抽取的卡牌/减费的卡牌的位置
    }
    
}






int main()
{
    system("chcp 65001");
    Init_Deck();
    string command;
    int p1,p2,p3,p4,p5;

    



    
    while(1)
    {
        cin>>command>>p1;
        if(command=="draw") 
        {
            L2H(p1);//抽id为x的牌
        }
        if(command=="Use") 
        {
            cin>>p2>>p3>>p4>>p5;
            Use(p1,p2,p3,p4,p5);
        }
        else if(command=="setmana") 
        {
            mana=p1;//设置当前法力水晶
        }
        else if(command=="H2B") 
        {
            H2B(p1);//手上第x张被脏鼠拉到场上
        }
        else if(command=="draw1")
        {
            L2H1(p1);
        }
        else if(command=="dellib")
        {
            dellib(p1);
        }
        else if(command=="setuse")
        {
            CardUsed==p1;
        }
        // else if(command=="FullHpEnemyMinion") FullHpEnemyMinion=p1;//是否存在满血敌方随从可以要挟
        // else if(command=="EnemyHeroFullhp") EnemyHeroFullhp=p1;//敌方英雄是否满血用以要挟
        // else if(command=="DeleteHand") DeleteHand(p1);//删除手牌
        // else if(command=="ZhuNeng") ZhuNeng(p1);//给手牌注能
        cout<<endl<<"当前法力值:"<<mana<<endl<<endl;
        cout<<"当前已用"<<CardUsed<<"张牌"<<endl<<endl;
        showBuff();
        showBoard();
        showHand();
        showDamage();
    }
    

    return 0;
}