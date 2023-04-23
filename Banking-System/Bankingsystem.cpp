#include <iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include <map>
using namespace std;

#define MIN_BALANCE 500
class InsufficientFunds
{
};

class Account
{
private:
  long accountNumber;
  string firstname;
  string lastname;
  float balance;
  static long nextaccountnumber;

public:
  Account() {}
  Account(string fname, string lname, float balance);
  long getAccno() { return accountNumber; }
  string getfname() { return firstname; }
  string getlname() { return lastname; }
  float getbalance() { return balance; }

  void deposit(float amount);
  void withdraw(float amount);
  static void setlastaccountnumber(long accountNumber);
  static void getlastaccountnumber();
};
long Account::nextaccountnumber = 0;

class Bank
{
private:
  map<long, Account> accounts;

public:
  Bank();
  Account openaccount(string fname, string lname, float balance);
  Account BalanceEnquiry(long accountnumber);
  Account deposit(long accountnumber, float amount);
  Account withdraw(long accountNumber, float amount);
  void closeaccount(long accountnumber);
  void showallaccounts();
  ~Bank();
};

int main()
{
  Bank b;
  Account acc;
  int choice;
  string fname, lname;
  long accountNumber;
  float balance;
  float amount;

  cout << "****Banking System****" << endl;

  do
  {
    cout << "\n\tselect one option below";
    cout << "\n\t1 create an account";
    cout << "\n\t2 balance enquiry";
    cout << "\n\t3 Deposit";
    cout << "\n\t4 withdrawal";
    cout << "\n\t5 close an account";
    cout << "\n\t6 show all accounts";
    cout << "\n\t7 Quit";
    cout << "\nenter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      cout << "enter your first name";
      cin >> fname;
      cout << "enter your last name";
      cin >> lname;
      cout << "enter initial balance";
      cin >> balance;
      acc = b.openaccount(fname, lname, balance);
      cout << endl
           << "Congratulations your account is created" << endl;
      cout << acc;
      break;
    case 2:
      cout << "enter your account number" << endl;
      cin >> accountNumber;
      acc = b.BalanceEnquiry(accountNumber);
      cout << endl
           << "your account details" << endl;
      cout << acc;
      break;
    case 3:
      cout << "Enter Account Number:";
      cin >> accountNumber;
      cout << "Enter Balance:";
      cin >> amount;
      acc = b.deposit(accountNumber, amount);
      cout << endl
           << "Amount is Deposited" << endl;
      cout << acc;
      break;
    case 4:
      cout << "Enter Account Number:";
      cin >> accountNumber;
      cout << "Enter Balance:";
      cin >> amount;
      acc = b.withdraw(accountNumber, amount);
      cout << endl
           << "Amount Withdrawn" << endl;
      cout << acc;
      break;
    case 5:
      cout << "Enter Account Number:";
      cin >> accountNumber;
      b.closeaccount(accountNumber);
      cout << endl
           << "Account is Closed" << endl;
      cout << acc;
    case 6:
      b.showallaccounts();
      break;
    case 7:
      break;
    default:
      cout << "enter correct choice" << endl;
      exit(0);
    }

  } while (choice != 7);
  return 0;
}
Account::Account(string fname, string lname, float balance)
{
  nextaccountnumber++;
  accountNumber = nextaccountnumber;
  firstname = fname;
  lastname = lname;
  this->balance = balance;
}

void Account::deposit(float amount)
{
  balance += amount;
}
void Account::withdraw(float amount)
{
  if (balance - amount < MIN_BALANCE)
    throw InsufficientFunds();
  balance -= amount;
}
void Account::setlastaccountnumber(long accountNumber);
{
  nextaccountnumber = accountnumber;
}
long Account::getLastAccountNumber()
{
  return nextaccountnumber;
}
ofstream & operator<<(ofstream &ofs,Account &acc)
{
 ofs<<acc.accountNumber<<endl;
 ofs<<acc.firstName<<endl;
 ofs<<acc.lastName<<endl;
 ofs<<acc.balance<<endl;
 return ofs;
}
ifstream & operator>>(ifstream &ifs,Account &acc)
{
 ifs>>acc.accountNumber;
 ifs>>acc.firstName;
 ifs>>acc.lastName;
 ifs>>acc.balance;
 return ifs;
 
}
ostream & operator<<(ostream &os,Account &acc)
{
 os<<"First Name:"<<acc.getFirstName()<<endl;
 os<<"Last Name:"<<acc.getLastName()<<endl;
 os<<"Account Number:"<<acc.getAccNo()<<endl;
 os<<"Balance:"<<acc.getBalance()<<endl;
 return os;
}
Bank::Bank()
{
 
 Account account;
 ifstream infile;
 infile.open("Bank.data");
 if(!infile)
 {
 //cout<<"Error in Opening! File Not Found!!"<<endl;
 return;
 }
 while(!infile.eof())
 {
 infile>>account;
 accounts.insert(pair<long,Account>(account.getAccNo(),account));
 }
 Account::setLastAccountNumber(account.getAccNo());
 
 infile.close();
 
}
Account Bank::OpenAccount(string fname,string lname,float balance)
{
 ofstream outfile;
 Account account(fname,lname,balance);
 accounts.insert(pair<long,Account>(account.getAccNo(),account));
 
 outfile.open("Bank.data", ios::trunc);
 
 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
 return account;
}
Account Bank::BalanceEnquiry(long accountNumber)
{
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 return itr->second;
}
Account Bank::Deposit(long accountNumber,float amount)
{
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Deposit(amount);
 return itr->second;
}
Account Bank::Withdraw(long accountNumber,float amount)
{
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Withdraw(amount);
 return itr->second;
}
void Bank::CloseAccount(long accountNumber)
{
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 cout<<"Account Deleted"<<itr->second;
 accounts.erase(accountNumber);
}
void Bank::ShowAllAccounts()
{
 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
 }
}
Bank::~Bank()
{
 ofstream outfile;
 outfile.open("Bank.data", ios::trunc);
 
 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
}
