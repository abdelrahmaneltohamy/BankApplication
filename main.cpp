#include <iostream>
#include <fstream>
#include<string>
using namespace std;
class BankAccount
{
private:

    string AccountID;
    float Balance;
public:

    BankAccount(int balance)
    {
        setAccountID();
        Balance=balance;
    }

    BankAccount()
    {
        setAccountID();
        Balance=0;
    }

     virtual bool withdraw(int withdrawAmount)
    {
        if(withdrawAmount>Balance)
            return false;
        else
            Balance-=withdrawAmount;
        return true;
    }
     virtual bool deposit(int depositAmount)
    {
        Balance+=depositAmount;
        return true;
    }
    void setBalance(float balance)
    {
        Balance=balance;
    }
    void setAccountID()
    {
        static int ID=0;
        AccountID="";
        AccountID+="FCI-";
        ID++;
        if(ID/10==0)
        {
            AccountID=AccountID+"00";
            AccountID+=to_string(ID);
        }else if(ID/100==0)
        {
            AccountID+=("0"+to_string(ID));
        }else if(ID/1000==0)
        {
            AccountID+=to_string(ID);
        }else{AccountID+=to_string(ID);}
    }
    float getBalance()
    {
        return Balance;
    }
    string getAccountID()
    {
        return AccountID;
    }
};
class SavingsBankAccount :public BankAccount
{
private:
    const int minimumBalance=1000;
public:
    SavingsBankAccount(int balance):BankAccount(getBalance())
    {
        if (balance>=minimumBalance)
        {
            setBalance(balance);
        }
    }
    SavingsBankAccount(){};
    bool withdraw(int withdrawAmount)
    {
        if((getBalance()-withdrawAmount)>minimumBalance)
        {
            setBalance(getBalance()-withdrawAmount);
            return true;
        }
        else
            return false;
    }
    bool deposit(int depositAmount)
    {
        if (depositAmount<100)
            return false;
        else
        {
            setBalance(getBalance()+depositAmount);
            return true;
        }
    }

};
class CertificateOfDeposit :public BankAccount
{
private:
    const int minimumBalance=20000;
public:
    CertificateOfDeposit(int initialBalance):BankAccount(initialBalance)
    {
        if(initialBalance%20000==0)
        {
            setBalance(initialBalance);
        }
    }
    CertificateOfDeposit(){};
    float withdrawPenaltyPercent(int withdrawAmount)
    {
           return withdrawAmount/100.0;
    }
    bool withdraw(int withdrawAmount)
    {
        float totalwithdrawAmount=withdrawAmount+withdrawPenaltyPercent(withdrawAmount);
        if(totalwithdrawAmount<getBalance())
            return false;
        else
        {
            setBalance(getBalance()-totalwithdrawAmount);
            return true;
        }
    }
    bool deposit(int depositAmount)
    {
        if(depositAmount%20000==0)
        {
            setBalance(getBalance()+depositAmount);
            return true;
        }
        else
            return false;
    }
};
class client
{
private:
    string Name;
    string Address;
    string Phonenumber;
    BankAccount* myAccount;
    string acounttype;
public:
    client()
    {
        Name="";
        Address="";
        Phonenumber="";
        acounttype="";
    }
    client(string name,string address, string phonenumber)
    {
        Name=name;
        Address=address;
        Phonenumber=phonenumber;
    }
    void setName(string name)
    {
        Name=name;
    }
    string getName()
    {
        return Name;
    }
    void setAddress(string address)
    {
        Address=address;
    }
    string getAddress()
    {
        return Address;
    }
    void setPhonenumber(string phonenumber)
    {
        Phonenumber=phonenumber;
    }
    string getPhonenumber()
    {
        return Phonenumber;
    }
    void setMyAccount(string type)
    {
     if(type=="Basic")
     {
          myAccount = new BankAccount;
          acounttype="Basic";
     }
     else if(type=="Savings")
     {
         myAccount = new SavingsBankAccount;
         acounttype="Savings";
     }
     else if(type=="Certificate")
     {
         myAccount = new CertificateOfDeposit;
         acounttype="Certificate";
     }
    }
    string getAcounttype()
    {
        return acounttype;
    }
    void fillmyAccount(float balance)
    {
        myAccount->setBalance(balance);
    }
    float getMyBalance()
    {
        return myAccount->getBalance();
    }
    string getMyID()
    {
        return myAccount->getAccountID();
    }
};
class BankingApplication
{
public:
    client* ListOfClients=new client[1000];
    int numberofclients=0;
    BankingApplication(fstream& file)
    {
        int i=0;
        while(!file.eof())
        {
                ListOfClients[i].setName(getinformationfromline(file));
                ListOfClients[i].setAddress(getinformationfromline(file));
                ListOfClients[i].setPhonenumber(getinformationfromline(file));
                ListOfClients[i].setMyAccount(getinformationfromline(file));
                ListOfClients[i].fillmyAccount(stoi(getinformationfromline(file)));
                i++;
                numberofclients++;
        }
    }
    string getinformationfromline(fstream& file)
    {
        char x[100];
        file.getline(x,100,'\t');
        file.getline(x,100);
        return x;
    }
     bool writeALine(fstream& file,string information,int typeofinformation)
    {
        if(typeofinformation==1)
        {
            file<<"Name:\t"<<information<<endl;
            return true;
        }
        if(typeofinformation==2)
        {
            file<<"Address:\t"<<information<<endl;
            return true;
        }
        if(typeofinformation==3)
        {
            file<<"Phone number:\t"<<information<<endl;
            return true;
        }
        if(typeofinformation==4)
        {
            file<<information<<endl;
            return true;
        }
        if(typeofinformation==5)
        {
            file<<"Balance:\t"<<information<<endl;
            return true;
        }
        if(typeofinformation==6)
        {
            file<<"Balance:\t"<<information;
            return true;
        }
        return false;
    }
    void writeinfile(fstream& file)
    {

        for(int i=0;i<numberofclients;i++)
        {
                writeALine(file,ListOfClients[i].getName(),1);
                writeALine(file,ListOfClients[i].getAddress(),2);
                writeALine(file,ListOfClients[i].getPhonenumber(),3);
                file<<ListOfClients[i].getMyID()<<"\t";
                writeALine(file,ListOfClients[i].getAcounttype(),4);
                if(i==numberofclients-1)
                {
                    writeALine(file,to_string(ListOfClients[i].getMyBalance()),6);
                }else
                {
                    writeALine(file,to_string(ListOfClients[i].getMyBalance()),5);
                }
        }
    }

    BankingApplication(){}
    string mainMenu()
    {
        cout<<"Welcome to FCI Banking Application"<<endl<<"1. Create a New Account"<<endl<<"2. List Clients and Accounts"<<endl<<"3. Withdraw Money"<<endl<<"4. Deposit Money"<<endl;
        string x;
        cin>>x;
        if(x=="1")
            CreateNewAccount();
         else if(x=="2")
            ListClients();
        else if(x=="3"){
            cout<<"please enter the account ID"<<endl;
            string id;
            cin>>id;
            cout<<"Please enter the withdraw amount"<<endl;
            int withdrawAmount;
            cin>>withdrawAmount;
            withdrawMoney(id,withdrawAmount);
            cout<<"withdraw is done successfully"<<endl;}
        else if(x=="4")
        {
            cout<<"please enter the account ID"<<endl;
            string id;
            cin>>id;
            cout<<"Please enter the deposit amount"<<endl;
            int depositAmount;
            cin>>depositAmount;
            DepositeMoney(id,depositAmount);
            cout<<"Deposit is done successfully"<<endl;

        }
        else
            cout<<"Invalid input"<<endl;
        return x;

    }
    void CreateNewAccount()
    {
        string x;
        cout<<"Please enter your name"<<endl;
        getline(cin,x);getline(cin,x);
        ListOfClients[numberofclients].setName(x);
        cout<<"Please enter your address"<<endl;
        getline(cin,x);
        ListOfClients[numberofclients].setAddress(x);
        cout<<"Please enter your phone number"<<endl;
        getline(cin,x);
        ListOfClients[numberofclients].setPhonenumber(x);
        cout<<"Please enter your account type"<<endl<<"1)Basic"<<endl<<"2)Saving"<<endl<<"3)Certificate"<<endl;
        string acctype;
        cin>>acctype;
        if(acctype=="3")
            x="Certificate";
        else if(acctype=="2")
            x="Savings";
        else
            x="Basic";
        ListOfClients[numberofclients].setMyAccount(x);
        cout<<"Please enter your starting balance"<<endl;
        bool validBalance=false;
        while(!validBalance)
        {
            cin>>x;
            if(acctype=="3"&&stoi(x)<20000)
                cout<<"In certificate accounts the minimum balance needs to exceed 20000"<<endl;
            if(acctype=="2"&&stoi(x)<1000)
                cout<<"In Saving accounts the minimum balance needs to exceed 1000"<<endl;
            else
                validBalance =true;
        }
        ListOfClients[numberofclients].fillmyAccount(stoi(x));
        cout<<"your account's id is: "<<ListOfClients[numberofclients].getMyID();
        numberofclients++;
    }
    void ListClients()
    {
        for(int i=0;i<numberofclients;i++)
        {
                cout<<"Name:\t"<<ListOfClients[i].getName()<<endl;
                cout<<"Address:\t"<<ListOfClients[i].getAddress()<<endl;
                cout<<"Phone number:\t"<<ListOfClients[i].getPhonenumber()<<endl;
                cout<<ListOfClients[i].getMyID()<<"\t"<<ListOfClients[i].getAcounttype()<<endl;
                cout<<"Balance:\t"<<ListOfClients[i].getMyBalance()<<endl;
        }
    }
    void withdrawMoney(string ID,int amount)
    {
        for(int i=0;i<numberofclients;i++)
        if(ListOfClients[i].getMyID()==ID){
                float oldBalance=ListOfClients[i].getMyBalance();
                if(oldBalance<amount)
                    cout<<"Insufficient balance"<<endl;
                float newBalance=oldBalance-amount;
                ListOfClients[i].fillmyAccount(newBalance);
                break;}
    }
    void DepositeMoney(string ID,int amount)
    {
        for(int i=0;i<numberofclients;i++)
        {
            if(ListOfClients[i].getMyID()==ID)
            {
                string x=ListOfClients[i].getAcounttype();
                if(x=="Basic")
                {
                    float oldBalance=ListOfClients[i].getMyBalance();
                    float newBalance=oldBalance+amount;
                    ListOfClients[i].fillmyAccount(newBalance);
                    break;
                }
                if(x=="Savings")
                {
                    if(amount<100)
                        cout<<"Less than minimum deposit amount"<<endl;
                    else{
                        float oldBalance=ListOfClients[i].getMyBalance();
                        float newBalance=oldBalance+amount;
                        ListOfClients[i].fillmyAccount(newBalance);
                        break;}
                }
                if(x=="Certificate")
                {
                    if(amount%20000!=0)
                        cout<<"Not from the duplicates of 20000"<<endl;
                    else
                    {
                        float oldBalance=ListOfClients[i].getMyBalance();
                        float newBalance=oldBalance+amount;
                        ListOfClients[i].fillmyAccount(newBalance);
                        break;

                    }
                }

            }
        }
    }

};
int main()
{
    fstream databasein,databaseout;
    databasein.open("demo.txt",ios::in);
    BankingApplication acc1(databasein);
    databasein.close();
    acc1.mainMenu();
    databaseout.open("demo.txt",ios::out);
    acc1.writeinfile(databaseout);
    databaseout.close();
    return 0;
}
