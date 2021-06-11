#include <iostream>
#include <iomanip>
/*
Task: H4
Family Name: Mahfouz
Given Name: Kareem
Matriculation number: 3085597
Uni-Email: kareem.mahfouz@stud.uni-due.de
Course of Studies: ISE CE
*/
using namespace std;

enum Timezone : unsigned int { ACT, CET, CST, EST, GMT, MSK, PST, UTC };
enum State {Arrival=0,Departure};

//™


class LocalTime
{
private:
    int minutes;
    Timezone CurrentTime;
public:
    LocalTime()
    {
        minutes=-1;
        CurrentTime=CET;
    }
    LocalTime(int hour, int mins, Timezone A)
    {

        minutes=(hour*60)+mins;
        A=CET;


    }
    void set_time(int hour, int mins)
    {


        if(((mins || hour) <0) || (hour>23) || (mins>60))
        {
            cerr<<"**ERROR** WRONG TIME"<<endl;
            minutes=-1;

        }
        else
            minutes=(hour*60)+mins;


    }

    int get_minutes()
    {

        return (minutes%60);
    }

    int get_hour()
    {

        return (minutes/60);//No remainder considered;
    }
    bool is_valid()
    {
        if(minutes>=0)
            return true;
        else
            return false;

    }

};

ostream& operator<<(ostream& out,  LocalTime current)
{
    return out <<setw(2)<<setfill('0')<<current.get_hour()<<':'<<setw(2)<<setfill('0')<<current.get_minutes();
}

class Flight
{
private:
    State arrivalOrDeparture;
    string Flightcode,Destination,Gate,CheckIn,Comment;
    LocalTime Expected;
public:
    Flight();
    Flight(State,string,string,string,string);
    ~Flight();
    string get_Flightcode();
    string get_Desttination();
    string get_Gate();
    string get_CheckIn();
    string get_Comment();
    LocalTime get_Expected();
    void set_Expected(LocalTime);
    void set_Comment(string);
    bool is_arrival();
    bool is_departure();
    void print(LocalTime);
};
Flight::Flight()
{
    arrivalOrDeparture;
    Flightcode;
    Destination;
    Gate;
    CheckIn="";

}
Flight::Flight(State ArrOrDep,string code,string Dest,string gate,string check_in)
{
    arrivalOrDeparture=ArrOrDep;
    Flightcode=code;
    Destination=Dest;
    Gate=gate;
    CheckIn=check_in;
    Comment="";

}
Flight::~Flight()
{
    //  cout<<Flightcode;
}

string Flight::get_Flightcode()
{
    return Flightcode;
}
string Flight::get_Desttination()
{
    return Destination;
}
string Flight::get_Gate()
{
    return Gate;
}
string Flight::get_CheckIn()
{
    return CheckIn;
}
string Flight::get_Comment()
{
    return Comment;
}
LocalTime Flight:: get_Expected()
{
    return Expected;
}
void Flight::set_Expected(LocalTime t)
{
    int h=t.get_hour();
    int m=t.get_minutes();
    Expected.set_time(h,m);
}
void Flight::set_Comment(string comm)
{
    Comment=comm;
}
void Flight::print(LocalTime current)
{
    if(Expected.is_valid())
    {
        cout<<Flightcode
            <<"\t"
            <<Destination
            <<"\t \t \t"
            <<current.get_hour()<<':'<<current.get_minutes()
            <<"\b         "

            <<get_Expected()
            <<"\b"

            <<Gate

            <<"\t"
            <<CheckIn
            <<"\t"
            <<Comment
            <<endl;
    }
    else
    {
        cout<<Flightcode
            <<"\t"
            <<Destination
            <<"        "
            <<current.get_hour()<<':'<<current.get_minutes()
            <<"\t"
            <<""
            <<"\t"
            <<Gate
            <<"\t"
            <<CheckIn
            <<"\t"
            <<Comment
            <<endl;
    }
}
bool Flight::is_arrival()
{
    if(arrivalOrDeparture==0)
        return true;
    else
        return false;
}

bool Flight::is_departure()
{
    if(arrivalOrDeparture==1)
        return true;
    else
        return false;
}
class Airport
{


private:
    string AirportName;
    Flight *slot[24][60];
public:

    Airport(string name)
    {
        AirportName=name;
        for (int i =0 ; i<24 ; i++)
        {
            for(int j=0 ; j<60 ; j++)
                slot[i][j]=NULL;
        }
    }
    ~Airport()
    {
        cout<<endl;
        for(int i=0; i<24; i++)
        {
            for(int j=0; j<60; j++)
            {
                if(slot[i][j])
                {
                    cout<<"Flight "<<slot[i][j]->get_Flightcode()<<" deleted"<<endl;
                    delete [] slot;
                }

            }
        }

    }


    void schedule(LocalTime current, Flight *x)
    {

        slot[current.get_hour()][current.get_minutes()]=x;

    }

    void comment(LocalTime current, string x)
    {

        slot[current.get_hour()][current.get_minutes()]->set_Comment(x);


    }
    void delay(LocalTime current, LocalTime delayed)
    {
        int NewMin,NewHour,currentHour,curretMin;
        NewMin= delayed.get_minutes();
        NewHour =delayed.get_hour();
        currentHour= current.get_hour();
        curretMin= current.get_minutes();
        slot[currentHour][curretMin]->set_Expected(delayed);

    }
    void print(State ArrOrDep)
    {
        LocalTime temp;

        if(ArrOrDep==0)
        {
            cout<<" ™ ARRIVALS ™ "
                <<endl
                <<"==========================="
                <<endl
                <<"Flight \t From"
                << "                "
                <<"Scheduled \t Expected \t Gate \t Check-in \t Comments"
                <<endl;


            for(int i=0 ; i<24 ; i++)
            {
                for(int j=0 ; j<60 ; j++)
                {

                    if(slot[i][j]!=NULL)
                    {
                        if(slot[i][j]->is_arrival()==true)
                        {
                            temp.set_time(i,j);
                            slot[i][j]->print(temp);
                        }

                    }

                }
            }

        }

        else if (ArrOrDep==1)
        {
            cout<<endl;
            cout<<"™ DEPARTURES ™"
                <<endl
                <<"==========================="
                <<endl
                <<"Flight \t To"
                << "                  "
                <<"Scheduled \t Expected \t Gate \t Check-in \t Comments"
                <<endl;

            for(int i=0 ; i<24 ; i++)
            {
                for(int j=0 ; j<60 ; j++)
                {

                    if(slot[i][j]!=NULL)
                    {
                        if(slot[i][j]->is_departure()==true)
                        {
                            temp.set_time(i,j);
                            slot[i][j]->print(temp);
                        }

                    }

                }
            }

        }



    }




};

int main()
{

    cout<<setw(60)<<setfill(' ')<<right<<"WELCOME TO DUSSELDORF AIRPORT"<<endl;
    Airport D1("DUSSELDORF AIRPORT");
    Flight f1(Arrival,"LH 2010","Munich","         A04","");
    LocalTime t1(12,41,CET);
    LocalTime t1delayed(13,05,CET);
    D1.schedule(t1,&f1);
    D1.delay(t1,t1delayed);

    Flight f2(Arrival,"EW 9347","Manchester      ","          B04","");
    LocalTime t2(14,50,CET);
    D1.schedule(t2,&f2);

    Flight f3(Departure,"AF 1307","Paris          ","         B51"," 192-194");
    LocalTime t3(9,10,CET);
    D1.schedule(t3,&f3);
    D1.comment(t3,"Departed");


    Flight f4(Departure,"SU 2537","Moscow         ","         C31"," 252-255");
    LocalTime t4(10,40,CET);
    D1.schedule(t4,&f4);
    D1.comment(t4,"Boarding");

    Flight f5(Departure,"EW 9466","London-Heathrow","         B35"," 151-170");
    LocalTime t5(11,15,CET);
    D1.schedule(t5,&f5);

    Flight f6(Departure,"LH 2011","Munich","           A40","   115-120");
    LocalTime t6(13,25,CET);
    D1.schedule(t6,&f6);
    D1.comment(t6,"Code Sharing");

    Flight f7(Departure,"XQ 959","Izmir ","        C45"," 240-242");
    LocalTime t7(13,25,CET);
    D1.schedule(t7,&f7);
    LocalTime t7delayed(15,20,CET);
    D1.delay(t7,t7delayed);

    D1.print(Arrival);
    D1.print(Departure);


    return 0;
}
