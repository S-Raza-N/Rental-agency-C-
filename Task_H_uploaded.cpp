#include <iostream>
#include <string>
//Matr number:3090802
//Name: Syed Raza Nasir
using namespace std;

class DayOfYear
{
private:
    unsigned short int dayOfYear, year;
    static const int days[];
public:
    DayOfYear(int d=1,int y=365)
    {
        dayOfYear=d;
        year=y;
    }


    DayOfYear(int d, int m, int y)
    {

           dayOfYear = d + days[m];
    }

    int get_dayOfYear(){return dayOfYear;}

     void operator ++()
    {

        if((dayOfYear+1)==365)
        {
            dayOfYear=1;
        }else{
            dayOfYear+1;
        }
        dayOfYear;
    }
    friend istream& operator>>(istream& in, DayOfYear &v )
    {
        int month;

        return in >> v.year >> month >> v.dayOfYear;



    }

    friend ostream& operator<<(ostream& o,  DayOfYear d)
   {
      return o << d.year << "-" << d.days << "-" << d.dayOfYear;
   }
   friend class Rental;
};
const int DayOfYear::days[]={0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

class Vehicle
{
    public:

       Vehicle(int number,string v_model,float priceh)
{
        no=number;
        model=v_model;
        price24h=priceh;
    //ctor
}
        //virtual ~Vehicle();
        int get_no(){return no;}
        string get_model(){return model;}
        float get_price(int x=0)
{
        price24h*=x;
        return price24h;
}
        virtual void print()=0;

    protected:
        int no;
       string model;
       float price24h;

};

class Bike : public Vehicle
{
    public:
       Bike(int number, string v_model, float priceh=9.99):Vehicle(number, v_model,priceh)
       {

       }


        void print()
{
    cout<< model << "(Bike)" << endl;
}

};
class EMotorVehicle : public  Vehicle
{
      public:
       EMotorVehicle(int number, string v_model, float priceh): Vehicle(number, v_model,priceh)
{

}

        virtual bool is_streetLegal()=0;
        virtual void print()
{
    if (is_streetLegal()==true)
    {
        cout << no << " " << model << endl;

    }else if(is_streetLegal()==false)
    {
         cout << no << " " << model <<  "(not street legal)"<< endl;

    }

}

};

class EBike : public EMotorVehicle
{
       public:
          EBike(int number, string v_model, float priceh=29.99): EMotorVehicle(number, v_model,priceh)
{

}
           virtual bool is_streetLegal(){return true;}
           virtual void print()
{
    EMotorVehicle::print();
    cout <<  "(EBike)"<< endl;
}

};

class EScooter : public EMotorVehicle
{
     private:
         bool streetlegal;
     public:
  EScooter(int number, string v_model, float priceh=19.99, bool s=false): EMotorVehicle(number, v_model,priceh)
{
    streetlegal=s;
}

         virtual bool is_streetLegal(){return streetlegal;}
         virtual void print()
{
    EMotorVehicle::print();
    cout<< "(EScooter)"<< endl;
}


};

class Rental
{
    friend class Schedule;
     private:
        int no;
        DayOfYear from;
        int days;
        string customer;
        static int last_no;
     public:
        Rental(string x, DayOfYear d,int y=1)
        {
            customer=x;
            from=d;
            days=y;
            no = last_no;
            last_no++;

        }
        int get_days(){return days;}
        DayOfYear get_from(){return from;}
        DayOfYear get_untill()
        {
            DayOfYear untill;
            untill=from;
            for(int i=1; i<=days; i++)
            {
                ++untill;
            }
            return untill;
        }
        void print()
        {
            cout<< get_from() << " to "<< get_untill()<< " rental no " << no << " for "<<customer <<endl;
        }
};

int Rental::last_no=1;

class Schedule
{

private:
    Vehicle *vehicle;
    Rental *year[365];
    Schedule *next;
public:
    Schedule(Vehicle *p)
    {
        vehicle=p;
        for(int i=0; i<365; i++)
        {
            year[i]=nullptr;
            next=NULL;
        }
    }
    Vehicle* get_vehicle()
    {
        return vehicle;
    }
    Schedule* get_next()
    {
        return next;
    }
    void set_next(Schedule* x)
    {
        next=x;
    }
    bool isFree(DayOfYear d, int no_days){

        for(int i= d.get_dayOfYear(); i< d.get_dayOfYear() + no_days; i++){

        if(year[i]== NULL){
            return true;
       }else{
            return false;

        }
        }
    }

    float book(string x,DayOfYear d, int n_days)
        {
            Rental *temp = new Rental(x,d,n_days);
            //customer = x;
            for(int i=d.get_dayOfYear(); i<= n_days + d.get_dayOfYear()-1; i++)
            {
                year[i]=temp;
            }
            Vehicle *v;
            return v->get_price(n_days);
        }
    void print(DayOfYear d)
        {
            vehicle->print();
            if(year[d.get_dayOfYear()]!=nullptr)
            {
                    year[d.get_dayOfYear()]->print();
            }

        }
        void print()
        {
            cout<<"Schedule for:"<<endl;
            Vehicle* v;
            v->print();
            int i=0;
            while(i<sizeof(year)/sizeof(year[0]))
            {

                if(year[i]!=nullptr)
                {
                    int x;
                    while(x<i)
                    {
                        if(year[i]==year[x])
                        {
                            i++;
                            break;
                        }
                        if(i==x)
                        {
                            year[i]->print();
                            cout<<endl;
                            i++;
                        }
                    }
                }

            }


        }
};

class Agency
{
private:
    float profitPercent, profit;
    Schedule *head;
    Schedule *last;
protected:
    Schedule* searchFor(int f)
    {
        Schedule* curr = head;
        while(curr!=nullptr)
        {
            if(curr->get_vehicle()->get_no()==f)
            {
                return curr;
            }
            curr->get_next();
        }
    }
public:

    Agency()
    {
        profitPercent=0.20;
        profit=0.00;
        head = nullptr;
        last= nullptr;
    }
    float get_profit()
    {
        return profit;
    }
    void set_profitPercent(float y)
    {
        profitPercent=y;
    }
    void add(Vehicle *v)
    {
        Schedule* next=new Schedule(v);
        if(head==nullptr)
        {
            head=next;
        }else
        {
            Schedule *trav;
            trav=head;
            while(trav->get_next()!=nullptr)
            {
                trav=trav->get_next();
            }
            trav->get_next();
        }

    }

    bool isFree(int v_no, DayOfYear d, int no_days)
    {
        Schedule *s=searchFor(v_no);
        return s->isFree(d, no_days);
    }
    float book(int v_no, string c, DayOfYear d, int no_days)
    {
        Schedule *s= searchFor(v_no);
        profit=s->book(c, d , no_days);
        profit= profit+profitPercent;
        return profit;
    }
    int choose_Vehicle()
    {
       Schedule* next=head;
        while(next!=nullptr)
        {
            next->print();
            next= next->get_next();
        }
        int j;
        cin>>j;
        return j;
    }
    void print(DayOfYear d)
    {
        Schedule* next=head;
        while(next!=nullptr)
        {
            next->print(d);
           next->get_next();
        }
    }

    void print()
    {
        Schedule* next=head;
        while(next!=nullptr)
        {
            next->print();
            next=next->get_next();
        }
        cout<< "profit: "<< get_profit()<< "euros"<<endl;
    }


};

int main()

{
    DayOfYear today(03, 01, 2021), tomorrow(04,01,2021);
    Agency a;
    //Rental obj_agency=new Rental('xyz', today, 1);
    //Rental obj_rental=new Rental('xyz', today, 1);

    char choice;
    do{
         cout<< "MENUE"<<endl;
         cout<< "A end of simulation"<<endl;
         cout<< "B set new simulation date"<<endl;
         cout<< "C new rental manually"<<endl;
         cout<< "D print rental of today 2021-01-03 "<<endl;
         cout<< "E print rental of tomorrow 2021-01-04"<<endl;
         cout<< "F print all rentals"<<endl;
         cout<< "G print agency profit"<<endl;
         cout<< "H set agency profit percent"<<endl;
         cout<< "I add bikes"<<endl;
         cout<< "J add E-bikes"<<endl;
         cout<< "K add E-scooters"<<endl;
         cout<<"Your choice: ";
         cin>> choice;

         switch(choice)
         {
            case 'a':
              {
               break;
              }
            case 'b':
                {
                cout<< "Input date of today: ";
                cin>>today;
                 break;
                }
            case 'c':
                {
                 break;
                }
            case 'd':
                {
                 a.print(today);
                 break;
                }
            case 'e':
                {
                 a.print(tomorrow);
                 break;
                }
            case 'f':
                {
                a.print();
                 break;

                }
            case 'g':
                {
                cout<< a.get_profit();
                cout<<" Euros"<<endl;
                 break;
                }
            case 'h':
                {
                 float temp;
                cout<< "your agency profit percent: ";
                cin >> temp;
                 a.set_profitPercent(temp);
                 break;
                }
            case 'i':
                {
                int x;
                cout<< "how many bikes in this simulation? ";
                cin>>x;
                int i=1;
                while(i<=x)
                {
                    Vehicle *b;
                    b=new Bike(i, "City" + i);
                    a.add(b);
                    i++;
                }
                 break;
                }
            case 'j':
                {
                int o;
                cout<< "how many Ebikes in this simulation? ";
                cin>>o;
                int u=1;
                while(u<=o)
                {
                    Vehicle *eb;
                    eb=new EBike(u, "Trekky" + u);
                    a.add(eb);
                    u++;
                }
                 break;
                }
            case 'k':
                {
                 int w;
                cout<< "how many Escooters in this simulation? ";
                cin>>w;
                int y=1;
                while(y<=w)
                {
                    Vehicle *es;
                    es=new EScooter(y, "Scooty" + y);
                   a.add(es);
                    y++;
                }
                 break;
                }
         }

    }while(choice!='a');
}
