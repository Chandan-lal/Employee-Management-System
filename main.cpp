#include <iostream>
#include<windows.h>
#include<winsock.h>
#include<mysql.h>
#include <sstream>
#include<stdio.h>

using namespace std;

// Global Variable
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class employee
{
public:
    employee();
    void show();
    void add();
    void editemployee();
    void deleteemployee();
    void searchid();
}s;


employee::employee()
{
   conn = mysql_init(0);
    if (conn)
    {
        cout << "Database Connected" << endl;


    }
    else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "", "employee", 0, NULL, 0);
    if (conn)
    {
        cout << "Database Connected To MySql" << conn << endl;

    }
    else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
}


void employee::add()
{


        string eid;
        string name;
	    string phno;
        float salary;
        string desig;

        cout << "Enter name of Employee: ";
        cin >> name;

        cout << "Enter Employee ID : ";
        cin >> eid;

        cout << "Enter Employee Contact number: ";
        cin >> phno;

        cout<<"Enter Employee Salary : ";
        cin >> salary;

        cout << " Enter Employee Designation : ";
        cin >> desig;


        stringstream ss;
        ss << "INSERT INTO details(name, eid, phno, salary, desig) VALUES('" << name <<"','"<< eid <<"','"<< phno <<"'," << salary <<",'"<< desig <<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if(qstate == 0){
            cout << "Record Inserted" << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

        system("pause");
        system("cls");

}


void employee::editemployee()
{
        string eid;
        float salary;
        cout << "Enter EmployeeID : ";
        cin >> eid;
        cout << "Enter Employee Salary : ";
        cin >> salary;

        stringstream ss;
        ss << "UPDATE details SET salary = salary +" << salary << " WHERE eid = '" << eid << "'";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

         if(qstate == 0){
            cout << "Record Updated" << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

        system("pause");
        system("cls");

}

void employee :: searchid()
{
        string eid;
        cout << "Enter Employee ID : ";
        cin >> eid;

        stringstream ss;
        ss << "select * from details  WHERE eid = '" << eid << "'";

        string query = ss.str();

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(!qstate){
            res = mysql_store_result(conn);

            cout<<" Name\t |\tEID\t |\tPhone Number\t |\tSalary\t |\tDesignation\n";
            while(row = mysql_fetch_row(res)){

                 cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t\t | \t" << row[3] <<"\t | \t" << row[4]  <<endl << endl;
             }
        }


    system("pause");
    system("cls");



}
void employee::show()
{
    qstate = mysql_query(conn, "SELECT name, eid, phno, salary , desig FROM details");

    if(!qstate){
            res = mysql_store_result(conn);
            cout<<" Name\t |\tEmployeeID\t |\tPhNo\t |\tSalary\t |\tDesignation\n";
            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t\t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t" << row[4]  <<endl << endl;
             }
        }


}


void employee::deleteemployee()

{
    string id;
    cout<<"Enter Employee Id to delete: ";
    cin>>id;



    string query = "SELECT eid FROM details;";




        query = "delete from details where eid = '"+id+"';";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << "Successfully Deleted From Item Record." << endl;
        }
        else
        {
            cout << "Failed To Delete!" << endl;
        }

}

void user()
{
	int ch;
	do
	{
		system("cls");
		cout<<"...............EMPLOYEE MANAGEMENT SYSTEM..............\n";
		cout<<"======================================================\n";
		cout<<"0. Exit from Program\n";
		cout<<"1. ENTER NEW EMPLOYEE\n";
		cout<<"2. EDIT EMPLOYEE SALARY\n";
		cout<<"3. DELETE EMPLOYEE RECORD\n";
		cout<<"4. DISPLAY EMPLOYEE RECORD\n";
		cout<<"5. SEARCH BY EMPLOYEE ID\n";
		cout<<"Enter your choice  : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case 1: s.add(); break;
			case 2: s.editemployee(); break;
			case 3: s.deleteemployee(); break;
			case 4: s.show(); break;
			case 5: s.searchid(); break;
		}
		system("pause");
	}while(ch);
}


int main()
{
      user();
      return 0;
}
