#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <time.h>
using namespace std;
char Title[27][49]//27x49 Map has 48 columns because at the end of each line there is an end character.
{
"                                           _.oo.",
"                   _.u[[/;:,.         .odMMMMMM'",
"                .o888UU[[[/;:-.  .o@P^    MMM^  ",
"               oN88888UU[[[/;::-.        dP^    ",
"              dNMMNN888UU[[[/;:--.   .o@P^      ",
"             ,MMMMMMN888UU[[/;::-. o@^          ",
"             NNMMMNN888UU[[[/~.o@P^             ",
"             888888888UU[[[/o@^-..              ",
"            oI8888UU[[[/o@P^:--..               ",
"         .@^  YUU[[[/o@^;::---..                ",
"       oMP     ^/o@P^;:::---..                  ",
"    .dMMM    .o@^ ^;::---...                    ",
"  dMMMMMMM@^`       `^^^^                       ",
"  YMMMUP^                                       ",
"   ^^                                           ",
"            _____                               ",
"           / ___/ _____ ____ _________          ",
"           \\ __ \\/ __ \ / __ `/ ___/ _ \\     ",
"           ___/ / /_/ / /_/ / /__/  __/         ",
"          /____/ .___/\\__,_/\\___/\\___/       ",
"              /_/                               ",
"                                                ",
"     ____                     __                ",
"    /  _/___ _   ______ _____/ /__  __________  ",
"    / // __ \\ | / / __ `/ __  / _ \\/ ___/ ___/",
"  _/ // / / / |/ / /_/ / /_/ /  __/ /  (__  )   ",
" /___/_/ /_/|___/\\__,_/\\__,_/\\___/_/  /____/ "
};
char Map[20][20] //20x20 Map has 19 columns because at the end of each line there is an end character.
{
    "###################",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#       W         #",
    "###################"
};

class spaceship//spaceship is an abstract base class for player and aliens
{
protected:
    int x;//spaceship's x coordinate on the map
    int y;//spaceship's y coordinate on the map


public:
    int getx(){
        return x;}

    int gety(){
        return y;}

    void setx(int a){
        x=a;}

    void sety(int a){
        y=a;}



    virtual void moveleft()=0;//spaceship moves left

    virtual void moveright()=0;//spaceship moves right

    virtual int getdamage(){
    return 0;}
    virtual void setdamage(int modifier){
    }

};

class player : public spaceship{//player is a class for spaceship that player controls.

    private:

     int damage;//The damage of each shot

    public:
        player()
        {
            sety(18);
            setx(8);
            damage=100;
        }
        void moveleft();
        void moveright();
        int getstate();
        int getdamage();
        void setdamage(int modifier){//damage of player is increased by the modifier
            damage+=modifier;
        }
};




class alien: public spaceship{

    private:


        int ok; //checks if alien is spawned
        int hp; //health points left
        int age;//number of turns that alien took after spawn
        static int globalhp;//maximum hp for aliens to spawn
        static int deathcounter;//total alien kills

    public:

        alien(){

            ok=0;
            hp=1;
            age=0;

        }

        void moveleft();
        void moveright();//alien movement
        void movedown();
        void spawn();//aliens will spawn at Map[3][3]
        void gethit(int damage,class shot &s);//hp reduction or despawn for alien
        int getstate();
        int getok();
        int gethp();
        int getage();
        static int getglobalhp(){
            return globalhp;
        }
        static int getdeathcounter(){
            return deathcounter;
        }
};
class shot
{
    private:
        int state;//state of shot is increased each turn
        int shotx;
        int shoty;//coordinates of shot
    public:
        shot()
        {
            state=0;
        }
        void fire(int x, int y);//function to create the shot
        void ShotMove();//function for shot to continue its movement
        int getstate();
        int getshotx();
        int getshoty();
        void setstate(int s);
        void setshotx(int x);
        void setshoty(int y);

};

void player::moveleft()
{
    Map[y][x-1]='W';
    Map[y][x]=' ';
    --x;
}
void player::moveright()
{
    Map[y][x+1]='W';
    Map[y][x]=' ';
    ++x;
}

void shot::fire(int y, int x)
{
       shotx=x;
       shoty=y-3;
       ++state;
}
void shot::ShotMove()
{
    if(state==7)//maximum hight for the shot is reached, shot gets killed
    {
        shoty=0;
        shotx=0;
        state=0;
    }
    if(state==6)
    {
        Map[shoty][shotx]=' ';
        shoty=shoty-3;
        ++state;
    }
    if(state==5||state==4||state==3||state==2)
    {

        shoty=shoty-3;
        Map[shoty][shotx]='^';
        ++state;
        Map[shoty+3][shotx]=' ';
    }
    if(state==1)
    {

        Map[shoty][shotx]='^';
        ++state;
    }

}
int shot::getstate()
{
    return state;
}

int shot::getshotx()
{
    return shotx;
}

int shot::getshoty()
{
    return shoty;
}

void shot::setstate(int s)
{
    state=s;
}

void shot::setshotx(int x)
{
    shotx=x;
}

void shot::setshoty(int y)
{
    shoty=y;
}


int alien::gethp()
{
    return hp;
}

void alien::moveleft()
{
    --x;
    Map[y][x]='O';
    Map[y][x+1]=' ';
    age++;
}

void alien::moveright()
{
    ++x;
    Map[y][x]='O';
    Map[y][x-1]=' ';
    age++;
}

void alien::movedown()
{

    y+=3;
    Map[y][x]='O';
    Map[y-3][x]=' ';
    age++;
}

void alien::spawn()
{
    x=3;
    y=3;
    ok=1;
    hp=globalhp;

}

int alien::getok()
{
    return ok;
}

void alien::gethit(int damage, shot &s)
{
    hp-=damage;//alien gets damage
    s.setstate(0);
    s.setshotx(1);
    s.setshoty(1);
    if(hp<=0)//alien is killed
    {
    Map[y][x]=' ';
    ok=0;
    x=0;
    age=0;
    ++deathcounter;
    if(deathcounter%5==0)//max hp of aliens will increase by 600 every 5 kills
    globalhp+=600;
    }
}

int alien::getage()
{
    return age;
}
int player::getdamage()
{
    return damage;
}

int alien::globalhp=300;

int alien::deathcounter=0;



int main()
{
    srand(time(NULL));
    char entry='n';//entry character is used to choose the action that player commands
    bool printed [20][20]={false};//printed array of booleans is used for checking if the character on the map is already printed
    bool PowerupSpawned=false;//boolean of PowerupSpawned is true if a powerup is already on the map
     spaceship *user; //spaceship pointer user is created
    user = new player; //player size of area is allocated for user
     shot shots[7];//array of shot objects are created
     alien aliens[40];//array of aliens are created
    int gamespeed=20;//system will be frozen for gamespeed-time to balance game speed
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b); //system color change into light blue
    for(;;)//Opening screen disappears when player presses space bar
    {
        for(int titlecntry=0;titlecntry<27;titlecntry++)
        {
            for(int titlecntrx=0;titlecntrx<49;titlecntrx++)
            {
                cout<<Title[titlecntry][titlecntrx];
                if(titlecntrx==48)
                {
                    cout<<endl;
                }
            }
        }
        if(GetAsyncKeyState(VK_SPACE)!=0)
        {
            break;
        }
        Sleep(2000);
        system("cls");
    }

    for(int turn=1;;turn++)//turns will increase until the end of the game
    {
        system("cls");//clearing screen for a new frame

        for(int cntry=0;cntry<20;cntry++)//loops for drawing the frame
        {
            for(int cntrx=0;cntrx<20;cntrx++)
            {
                for(int cntr6=40;cntr6>-1;cntr6--)
                {       //Temporarily changing color for special characters and aliens for their remaining health

                    if(Map[cntry][cntrx]=='O'&&aliens[cntr6].getx()==cntrx&&aliens[cntr6].gety()==cntry&&aliens[cntr6].getok()==1&&aliens[cntr6].gethp()<=300)
                    {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0f);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                     break;
                    }
                    else if(Map[cntry][cntrx]=='O'&&aliens[cntr6].getx()==cntrx&&aliens[cntr6].gety()==cntry&&aliens[cntr6].getok()==1&&aliens[cntr6].gethp()<=900)
                    {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                    break;
                    }
                    else if(Map[cntry][cntrx]=='O'&&aliens[cntr6].getx()==cntrx&&aliens[cntr6].gety()==cntry&&aliens[cntr6].getok()==1&&aliens[cntr6].gethp()<=1800)
                    {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                     break;
                    }
                    else if(Map[cntry][cntrx]=='O'&&aliens[cntr6].getx()==cntrx&&aliens[cntr6].gety()==cntry&&aliens[cntr6].getok()==1&&aliens[cntr6].gethp()<=3600)
                    {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0c);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                    break;
                    }
                    else if(Map[cntry][cntrx]=='O'&&aliens[cntr6].getx()==cntrx&&aliens[cntr6].gety()==cntry&&aliens[cntr6].getok()==1&&aliens[cntr6].gethp()<=4800)
                    {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0d);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                    break;
                    }
                }
                if(Map[cntry][cntrx]=='W')
                {
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                }
                else if(Map[cntry][cntrx]=='^')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0e);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                }
                else if(Map[cntry][cntrx]=='+')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0c);
                     cout << Map[cntry][cntrx];
                     printed[cntry][cntrx]=true;
                     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0b);
                }
                else if(printed[cntry][cntrx]==false)
                cout << Map[cntry][cntrx];

                if (cntrx==19)
                    cout<<endl;
            }
        }
        cout<<"Kills: "<<alien::getdeathcounter()<<endl;//Scoreboard
        cout<<"Alien Max Hp: "<<alien::getglobalhp()<<endl;
        cout<<"Player Damage: "<<user->getdamage()<<endl;
        Sleep(gamespeed);//game is paused for gamespeed-time for each turn
        for(int cntr7=0;cntr7<20;cntr7++)
        {
            for(int cntr8=0;cntr8<20;cntr8++)
            {
                printed[cntr7][cntr8]=false;//printed array of booleans are reset to false for repetitive uses.
            }
        }
        if(turn/300+1>user->getdamage()/100)//powerups will begin to spawn every 300 turns and in every 300 turns player is allowed to collect up to 5 powerups
        {
            PowerupSpawned=false;
            for(int cntr8=0;cntr8<20;cntr8++)
            {
                if(Map[18][cntr8]=='+')//checking if powerup is already spawned
                {
                    PowerupSpawned=true;
                    break;
                }
            }
            if(PowerupSpawned==false)
            {
                int Powerupx=rand()%16+2;
                Map[18][Powerupx]='+';//powerup is represented with + character at a random location
            }
        }
        for(;;)//user input
        {
            if(GetAsyncKeyState(VK_LEFT)!=0)
            {
                entry='a';//this method is used to negate more than one entries for each turn
                break;
            }
            if(GetAsyncKeyState(VK_RIGHT)!=0)
            {
                entry='d';
                break;
            }
            if(GetAsyncKeyState(VK_UP)!=0)
            {
                entry='w';
                break;
            }
            else
            {
                entry='0';
                break;
            }
        }

        if(entry=='a')
            {
                if(user->getx()!=1)
                {
                   if(Map[18][user->getx()-1]=='+')//player collects the powerup if possible
                   {
                       user->setdamage(20);
                   }
                   user->moveleft();//player moves left
                }

            }

        if(entry=='d')
            {
                if(user->getx()!=17)
                {
                   if(Map[18][user->getx()+1]=='+')//player collects the powerup if possible
                   {
                       user->setdamage(20);
                   }
                   user->moveright();//player moves right
                }
            }

        if(entry=='w')
            {
                shots[6].fire(user->gety(), user->getx());//spaceship fires

            }

        for(int cntr2=7;cntr2>0;cntr2--){//shots are ordered to become last to first

            for(int cntr3=0;cntr3<6;cntr3++){

                if(shots[cntr3].getstate()<shots[cntr3+1].getstate())
                {
                     shot swop=shots[cntr3+1];
                    shots[cntr3+1]=shots[cntr3];
                    shots[cntr3]=swop;
                }
            }
        }

        for(int cntr3=0;cntr3<7;cntr3++){
            shots[cntr3].ShotMove();//shots make their next move
        }

        for(int cntr2=7;cntr2>0;cntr2--){//shots are ordered to become last to first

            for(int cntr3=0;cntr3<6;cntr3++){

                if(shots[cntr3].getstate()<shots[cntr3+1].getstate()){

                     shot swop=shots[cntr3+1];
                    shots[cntr3+1]=shots[cntr3];
                    shots[cntr3]=swop;
                }
            }
        }

        if(turn%21==0)//a new alien is spawned every 21 turns
        {
            aliens[0].spawn();
        }

        for(int cntr2=40;cntr2>0;cntr2--)//aliens are ordered to become first to last
        {
            for(int cntr3=0;cntr3<40;cntr3++)
            {
                if(aliens[cntr3].getok()>aliens[cntr3+1].getok())
                {
                     alien swop=aliens[cntr3+1];
                    aliens[cntr3+1]=aliens[cntr3];
                aliens[cntr3]=swop;
                }
            }
        }

        for(int cntr2=40;cntr2>0;cntr2--)
        {
            for(int cntr3=0;cntr3<40;cntr3++)
            {
                if(aliens[cntr3].getage()>aliens[cntr3+1].getage())
                {
                     alien swop=aliens[cntr3+1];
                    aliens[cntr3+1]=aliens[cntr3];
                    aliens[cntr3]=swop;
                }
            }
        }

        if(turn%3==2)//aliens move every 3 turns
        {
            for(int cntr2=40;cntr2>0;cntr2--)
            {
                if(aliens[cntr2].gety()%6==3&&aliens[cntr2].getok()==1)
                {
                    aliens[cntr2].moveright();
                }
                if(aliens[cntr2].gety()%6==0&&aliens[cntr2].getok()==1)
                {
                    aliens[cntr2].moveleft();
                }
                if(aliens[cntr2].gety()%6==0&&aliens[cntr2].getx()==1&&aliens[cntr2].getok()==1)
                {
                    aliens[cntr2].movedown();
                }
                else if(aliens[cntr2].gety()%6==3&&aliens[cntr2].getx()==17&&aliens[cntr2].getok()==1)
                {
                    aliens[cntr2].movedown();
                }
            }
        }
        for(int cntr2=0;cntr2<40;cntr2++)//if a shot and an alien collides, this part will call gethit function
        {
            for(int cntr3=0;cntr3<7;cntr3++)
            {
                if(aliens[cntr2].getok()==1&&aliens[cntr2].gety()==shots[cntr3].getshoty()&&aliens[cntr2].getx()==shots[cntr3].getshotx())
                {
                    aliens[cntr2].gethit(user->getdamage(),shots[cntr3]);
                }
            }
        }
        for(int cntr2=40;cntr2>0;cntr2--)//aliens are ordered to become first to last
        {
            for(int cntr3=0;cntr3<40;cntr3++)
            {
                if(aliens[cntr3].getage()>aliens[cntr3+1].getage())
                {
                     alien swop=aliens[cntr3+1];
                    aliens[cntr3+1]=aliens[cntr3];
                    aliens[cntr3]=swop;
                }
            }
        }
        for(int cntr2=40;cntr2>=0;cntr2--)//game continues until an alien touches the player
        {
            if(aliens[cntr2].getx()==user->getx()&&aliens[cntr2].gety()==user->gety())
            {
                cout<<"   YOU LOST" << endl;
                Sleep(6000);
                return 0;
            }
        }

    }

    return 0;
}
