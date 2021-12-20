#include <iostream>
#include <mysql.h>
#include<stdio.h>
#include <sstream>
/*

~~~Movie Ticketing System~~~

~ Created by Asher Yisrael Kutswa (137187).

*/

using namespace std;

//Voids to be used:

void homepage();
void tickets();
void bookticket();
void viewticket();
void deleteticket();
void movie();
void addmovie();
void deletemovie();
void viewmovie();
void seatvoid();
void addseat();
void deleteseat();
void viewseat();
void feedback();
void addfeedback();
void deletefeedback();
void viewfeedback();
void help();
void about();

//Function for changing the Console Text
void consolecolor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
 }

//Global Variable
int query;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

//Database Set-Up and Configuration
class db_response{
public:
    static void ConnectionFunction(){
    conn = mysql_init(0);
    if (conn){
        cout<<"Successful Connection to the Database. "<< conn<< endl;
        system("cls");
    } else{
        cout<<"Failed to Connect to Database. "<<mysql_errno(conn) <<endl;
    }

//Connection to the Database "Movie Ticket System".

conn = mysql_real_connect(conn, "localhost", "root", "", "movie_ticket_system", 3306, NULL, 0);
int cont;

if (conn){
         consolecolor(90) ;
        cout<<"Successful Connection to the Database. "<< conn<< "\n\n";
        cout<<"Press 1 to continue... ";
        consolecolor(7);
        cin>>cont;
        if(cont == 1){
            system("cls");
        }else{
        cout<<"Incorrect value, kindly try again.";
        }
    } else{
        cout<<"Failed to Connect to Database. "<<mysql_errno(conn) <<endl;
    }
    }
};


int main()
{
    //Call the Database Set-Up and Connection Functions

    db_response::ConnectionFunction();

    //Variable for this section

    string name;
    string password;

    //Log In Section

    consolecolor(90);
    cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n";
    cout<<"\n\n";
    consolecolor(36) ;
    cout<<"\t\t Enter Username : ";
    consolecolor(7);
    cin >> name;
    consolecolor(36) ;
    cout<<"\t\t Enter Password : ";
    consolecolor(7);
    cin >> password;
    if(name == "Asher" && password == "1444"){

    homepage();

	}else if(name == "Asher" && password != "1444"){
		cout<<"\n";
		cout<<"Password is not correct, kindly try again.";
	}else if(password == "1444" && name != "Asher"){
		cout<<"\n";
		cout<<"Name is not correct, kindly try again.";
	}else{
		cout<<"\n";
		cout<<"Details are incorrect, kindly try again!";
	}

    return 0;
}

//Homepage

void homepage(){

//New Page
    system("cls");
    consolecolor(90);

    //Variables needed for this section
    int userch;

    //Home Page Section

    cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Home Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t 1 ~ Tickets \n";
        cout<<"\t\t 2 ~ Movies \n";
        cout<<"\t\t 3 ~ Seats \n";
        cout<<"\t\t 4 ~ Feedback \n";
        cout<<"\t\t 5 ~ Help \n";
        cout<<"\t\t 6 ~ About \n";
        cout<<"\t\t 7 ~ Logout \n\n";
        cout<<"\t\t Select one of the following options [1,2,3,4,5,6,7] : ";
        consolecolor(7);
        cin>>userch;
        switch(userch)
        {
            case 1: tickets();
            break;
            case 2: movie();
            break;
            case 3: seatvoid();
            break;
            case 4: feedback();
            break;
            case 5: help();
            break;
            case 6: about();
            break;
            case 7: exit(0);
            break;
        }
}

//Manage Tickets:

void tickets(){

        //New Page
        system("cls");

        //Variables to be used in this section
        int userch;

        consolecolor(90);
        cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Ticket Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t 1 ~ Book Ticket \n";
        cout<<"\t\t 2 ~ View Ticket \n";
        cout<<"\t\t 3 ~ Delete Ticket \n";
        cout<<"\t\t 0 ~ Home Page \n\n";
        cout<<"\t\t Select one of the following options [1,2,3,0] : ";
        consolecolor(7);
        cin>>userch;
        switch(userch)
        {
            case 1: bookticket();
            break;
            case 2: viewticket();
            break;
            case 3: deleteticket();
            break;
            case 0: homepage();
            break;
        }

}

void bookticket(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch, seat;
     string id, name, format, gerne, date, time, price, seatno;
     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Book A Ticket ~~ \n\n\n";
        consolecolor(36);

        cout<<"\t\t Enter Movie ID : ";
        cin>>id;
        string select = "SELECT * FROM `movies` WHERE `Movie_ID` = '" + id + "'";

        //This is required for c_str to convert string to constant char.
        const char* s = select.c_str();

        query = mysql_query(conn, s);

        if(!query){
            res =mysql_store_result(conn);
            while ((row = mysql_fetch_row(res))){
                cout<<"\t\t Movie Name : "<<row[1]<<endl;
                cout<<"\t\t Format : "<<row[2]<<endl;
                cout<<"\t\t Genre : "<<row[3]<<endl;
                cout<<"\t\t Show Date : "<<row[4]<<endl;
                cout<<"\t\t Show Time : "<<row[5]<<endl;
                cout<<"\t\t Price : "<<row[6]<<endl;
                cout<<"\t\t Enter Seat ID : ";
                consolecolor(36);
                cin>>seat;
                cout<<"\t\t Enter Seat Number : ";
                consolecolor(36);
                cin>>seatno;
                cout<<"\n\n";
                if(seat > 10){
                    cout<<"\n\n";
                    cout<<"\t\t Invalid Seat ID, Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: bookticket();
                    break;
                    }
                }else{

                 //Reserve Seat
                 string b = "Booked";
                 string updateseats = "UPDATE `seats` SET `Movie_ID`= '" + id + "',`Status` = 'Booked' WHERE `Seat_No` = '"+ seatno +"'";
                 const char* sseats = updateseats.c_str();
                 query = mysql_query(conn, sseats);

        if(!query){
            cout<<"\t\t Seat has been reserved. \n";

                   //Book Ticket
                 string book = "INSERT INTO `tickets`(`Seat_No`, `Movie_ID`) VALUES ('" + seatno + "','" + id + "')";
                 const char* bs = book.c_str();
                 query = mysql_query(conn, bs);

        if(!query){
            cout<<"\t\t Ticket has been booked. \n";
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: bookticket();
                    break;
        }}
        else{
        cout<<"\t\t Error Occurred, Ticket has not been booked. \n\n";
        }

        }else{
        cout<<"\t\t Error Occurred, Seat has not been reserved. \n\n";
        cout<<"\t\t Error Occurred, Ticket has not been booked. \n\n";
        }

                }
                }
                }
        else{
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
        }


}

void viewticket(){

        //New Page
     system("cls");

     //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ View Tickets ~~ \n\n\n";
        consolecolor(36);
        query = mysql_query(conn, "SELECT * FROM `tickets`");
        if(!query){
            res = mysql_store_result(conn);
            printf("\t\t -----------------------------------------\n");
            printf("\t\t |           List of All Tickets         |\n");
            printf("\t\t -----------------------------------------\n");
            printf("\t\t | %-5s | %-10s | %-25s \n", "Ticket ID", "Seat Number", "Movie ID");
            printf("\t\t -----------------------------------------\n");
            while((row = mysql_fetch_row(res))){
            printf("\t\t | %-5s | %-10s | %-25s  \n", row[0], row[1], row[2]);
            }
            printf("\t\t -----------------------------------------\n");
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to refresh or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: viewticket();
                    break;
        }
        }else{

        cout<<"Query Execution Problem! "<<mysql_errno(conn)<<endl;

        }


}

void deleteticket(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string id, sid;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Delete A Ticket ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Kindly input a Ticket ID : ";
        cin>>id;
        cout<<"\t\t Kindly input the corresponding Seat ID : ";
        cin>>sid;
        string delt = "DELETE FROM `tickets` WHERE `Ticket_ID` = '"+ id +"'";
        const char* dt = delt.c_str();

        query = mysql_query(conn, dt);

        if(!query){
                string delst =  "UPDATE `seats` SET `Status` = 'Not Booked' WHERE `Seat_ID` = '"+ sid +"'";
                const char* ds = delst.c_str();

                query = mysql_query(conn, ds);
                if(!query){
                    cout<<"\t\t Ticket Deleted Successfully!!!\n";
                    cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deleteticket();
                    break;
                }}else{
                cout<<"\t\t Error Occurred unable to reset seat."<<mysql_errno(conn)<<"\n";
                cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deleteticket();
                    break;
                }
        }}else{
                cout<<"\t\t Error Occurred unable to delete ticket."<<mysql_errno(conn)<<"\n";
                cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deleteticket();
                    break;
                }

}

}

//Manage Movies

void movie(){

        //New Page
        system("cls");

        //Variables to be used in this section
        int userch;

        consolecolor(90);
        cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Movie Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t 1 ~ Add Movie \n";
        cout<<"\t\t 2 ~ View Movies \n";
        cout<<"\t\t 3 ~ Delete Movie \n";
        cout<<"\t\t 0 ~ Home Page \n\n";
        cout<<"\t\t Select one of the following options [1,2,3,0] : ";
        consolecolor(7);
        cin>>userch;
        switch(userch)
        {
            case 1: addmovie();
            break;
            case 2: viewmovie();
            break;
            case 3: deletemovie();
            break;
            case 0: homepage();
            break;
        }

}

void addmovie(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string id, name, format, gerne, date, time, price;
     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Add A Movie ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Movie Name : ";
        consolecolor(7);
        cin>>name;
        consolecolor(36);
        cout<<"\t\t Format (2D, 3D or 4D) : ";
        consolecolor(7);
        cin>>format;
        consolecolor(36);
        cout<<"\t\t Genre : ";
        consolecolor(7);
        cin>>gerne;
        consolecolor(36);
        cout<<"\t\t Show Date (dd/MM/YYYY) : ";
        consolecolor(7);
        cin>>date;
        consolecolor(36);
        cout<<"\t\t Show Time (24hrs) : ";
        consolecolor(7);
        cin>>time;
        consolecolor(36);
        cout<<"\t\t Price : ";
        consolecolor(7);
        cin>>price;
        consolecolor(36);

                   //Add Movie
                 string addm = "INSERT INTO `movies`(`Name`, `Format`, `Genre`, `Show Date`, `Show Time`, `Price`) VALUES ('"+ name +"','"+ format +"','"+ gerne +"','"+ date +"','"+ time +"','"+ price +"')";
                 const char* adm = addm.c_str();
                 query = mysql_query(conn, adm);

        if(!query){
            cout<<"\t\t Movie has been added. \n";
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: addmovie();
                    break;
        }

                }

        else{
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
        }


}

void viewmovie(){

        //New Page
     system("cls");

     //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ View Movies ~~ \n\n\n";
        consolecolor(36);
        query = mysql_query(conn, "SELECT * FROM `movies`");
        if(!query){
            res = mysql_store_result(conn);
            printf("\t\t ----------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t |           List of All Movies         |\n");
            printf("\t\t ----------------------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t | %-5s | %-10s | %-15s | %-20s | %-25s | %-30s | %-40s \n", "Movie ID", "Name", "Format", "Genre", "Show Date", "Show Time", "Price(shs)");
            printf("\t\t ----------------------------------------------------------------------------------------------------------------------------\n");
            while((row = mysql_fetch_row(res))){
            printf("\t\t | %-5s | %-10s | %-15s | %-20s | %-25s | %-30s | %-40s  \n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            }
            printf("\t\t -----------------------------------------------------------------------------------------------------------------------------\n");
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to refresh or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: viewmovie();
                    break;
        }
        }else{

        cout<<"Query Execution Problem! "<<mysql_errno(conn)<<endl;

        }


}

void deletemovie(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string id;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Delete A Movie ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Kindly input a Movie ID : ";
        cin>>id;
        string delt = "DELETE FROM `movies` WHERE `Movie_ID` = '"+ id +"'";
        const char* dt = delt.c_str();

        query = mysql_query(conn, dt);

                if(!query){
                    cout<<"\t\t Movie Deleted Successfully!!!\n";
                    cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deletemovie();
                    break;
                }}else{
                cout<<"\t\t Error Occurred unable to delete movie. "<<mysql_error(conn)<<"\n";
                cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deletemovie();
                    break;
                }
        }

}

//Manage Seats

void seatvoid(){

        //New Page
        system("cls");

        //Variables to be used in this section
        int userch;

        consolecolor(90);
        cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Seats Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t 1 ~ Add Seat \n";
        cout<<"\t\t 2 ~ View Seats \n";
        cout<<"\t\t 3 ~ Delete Seats \n";
        cout<<"\t\t 0 ~ Home Page \n\n";
        cout<<"\t\t Select one of the following options [1,2,3,0] : ";
        consolecolor(7);
        cin>>userch;
        switch(userch)
        {
            case 1: addseat();
            break;
            case 2: viewseat();
            break;
            case 3: deleteseat();
            break;
            case 0: homepage();
            break;
        }

}

void addseat(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string seatno;
     string status = "Not Booked";
     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Add A Seat ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Seat Number : ";
        consolecolor(7);
        cin>>seatno;

                   //Add Seat
                 string adds = "INSERT INTO `seats`(`Seat_No`, `Status`) VALUES ('"+ seatno +"','"+ status +"')";
                 const char* ads = adds.c_str();
                 query = mysql_query(conn, ads);

        if(!query){
            consolecolor(36);
            cout<<"\t\t Seat has been added. \n";
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: addseat();
                    break;
        }

                }

        else{
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
        }


}

void viewseat(){

        //New Page
     system("cls");

     //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ View Seats ~~ \n\n\n";
        consolecolor(36);
        query = mysql_query(conn, "SELECT * FROM `seats`");
        if(!query){
            res = mysql_store_result(conn);
            printf("\t\t ------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t |           List of All Seats         |\n");
            printf("\t\t ------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t | %-5s | %-10s | %-15s | %-20s \n", "Seat ID", "Seat Number", "Movie ID", "Status");
            printf("\t\t -------------------------------------------------------------------------------------------------------------\n");
            while((row = mysql_fetch_row(res))){
            printf("\t\t | %-5s | %-10s | %-15s | %-20s \n", row[0], row[2], row[1], row[3]);
            }
            printf("\t\t -------------------------------------------------------------------------------------------------------------\n");
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to refresh or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: viewseat();
                    break;
        }
        }else{

        cout<<"Query Execution Problem! "<<mysql_errno(conn)<<endl;

        }


}

void deleteseat(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string id;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Delete A Seat ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Kindly input a Seat ID : ";
        cin>>id;
        string delts = "DELETE FROM `seats` WHERE `Seat_ID` = '"+ id +"'";
        const char* dts = delts.c_str();

        query = mysql_query(conn, dts);

                if(!query){
                    consolecolor(36);
                    cout<<"\t\t Seat Deleted Successfully!!!\n";
                    cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deleteseat();
                    break;
                }}else{
                cout<<"\t\t Error Occurred unable to delete movie. "<<mysql_error(conn)<<"\n";
                cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deleteseat();
                    break;
                }
        }

}

//Manage Feedback

void feedback(){

        //New Page
        system("cls");

        //Variables to be used in this section
        int userch;

        consolecolor(90);
        cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Feedback Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t 1 ~ Add Feedback \n";
        cout<<"\t\t 2 ~ View Feedback \n";
        cout<<"\t\t 3 ~ Delete Feedback \n";
        cout<<"\t\t 0 ~ Home Page \n\n";
        cout<<"\t\t Select one of the following options [1,2,3,0] : ";
        consolecolor(7);
        cin>>userch;
        switch(userch)
        {
            case 1: addfeedback();
            break;
            case 2: viewfeedback();
            break;
            case 3: deletefeedback();
            break;
            case 0: homepage();
            break;
        }

}

void addfeedback(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string feed, name, id;
     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Add Feedback ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Enter your name : ";
        consolecolor(7);
        cin>>name;
        consolecolor(36);
        cout<<"\t\t Enter Movie ID : ";
        consolecolor(7);
        cin>>id;
        cout<<"\n\n";
        consolecolor(36);
        cout<<"\t\t ~ Feedback Guide : \n\n";
        cout<<"\t\t A = Great Service, Quality and Quick Performance. \n";
        cout<<"\t\t B = Average Service, Average and Average Performance. \n";
        cout<<"\t\t C = Poor Service, Quality and Slow Performance. \n\n";
        cout<<"\t\t Kindly input Feedback value (A, B, or C) : ";
        consolecolor(7);
        cin>>feed;

                   //Add Seat
                 string addf = "INSERT INTO `feedback`(`Name`, `Movie_ID`, `Feedback`) VALUES ('"+ name +"','"+ id +"','"+ feed +"')";
                 const char* adf = addf.c_str();
                 query = mysql_query(conn, adf);

        if(!query){
                consolecolor(36);
            cout<<"\t\t Feedback has been saved. \n";
            cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: addfeedback();
                    break;
        }

                }

        else{
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
        }


}

void viewfeedback(){

        //New Page
     system("cls");

     //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ View Feedback ~~ \n\n\n";
        consolecolor(36);
        query = mysql_query(conn, "SELECT * FROM `feedback`");
        if(!query){
            res = mysql_store_result(conn);
            printf("\t\t ------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t |           List of All Feedback         |\n");
            printf("\t\t ------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t | %-5s | %-10s | %-15s | %-20s \n", "Feedback ID", "Name", "Movie ID", "Feedback");
            printf("\t\t -------------------------------------------------------------------------------------------------------------\n");
            while((row = mysql_fetch_row(res))){
            printf("\t\t | %-5s | %-10s | %-15s | %-20s \n", row[0], row[1], row[2], row[3]);
            }
            printf("\t\t -------------------------------------------------------------------------------------------------------------\n");
            cout<<"\n\n";
             consolecolor(36);
        cout<<"\t\t ~ Feedback Guide : \n\n";
        cout<<"\t\t A = Great Service, Quality and Quick Performance. \n";
        cout<<"\t\t B = Average Service, Average and Average Performance. \n";
        cout<<"\t\t C = Poor Service, Quality and Slow Performance. \n\n";
                    cout<<"\t\t Input 1 to refresh or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: viewfeedback();
                    break;
        }
        }else{

        cout<<"Query Execution Problem! "<<mysql_errno(conn)<<endl;

        }


}

void deletefeedback(){

     //New Page
     system("cls");

     //Variables to be used in this section
     int userch;
     string id;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Delete Feedback ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t Kindly input a Feedback ID : ";
        cin>>id;
        string deltf = "DELETE FROM `feedback` WHERE `Feedback_ID` = '"+ id +"'";
        const char* dtf = deltf.c_str();

        query = mysql_query(conn, dtf);

                if(!query){
                        consolecolor(36);
                    cout<<"\t\t Feedback Deleted Successfully!!!\n";
                    cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deletefeedback();
                    break;
                }}else{
                cout<<"\t\t Error Occurred unable to delete movie. "<<mysql_error(conn)<<"\n";
                cout<<"\n\n";
                    cout<<"\t\t Input 1 to try again or 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                    case 1: deletefeedback();
                    break;
                }
        }

}

void help(){

       //New Page
     system("cls");

    //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ Help Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t The purpose of this system is to : \n\n";
        cout<<"\t\t i. To manage the ticket bookings.\n";
        cout<<"\t\t ii. To view movie schedule.\n";
        cout<<"\t\t iii. To manipulate movie schedule this includes adding, deleting, and editing movies and their details.\n";
        cout<<"\t\t v. To manage seats in the theater.\n";
        cout<<"\t\t vi. To allow users to record customer feedback.\n\n";
        cout<<"\t\t This system was Created by Asher Yisrael Kutswa (137187).";
                    cout<<"\t\t Input 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                }

}

void about(){

       //New Page
     system("cls");

    //Variables to be used in this section
     int userch;

     consolecolor(90);
     cout<<"\n\t\t\t\t ~~~ Movie Ticketing System ~~~ \n\n";
        consolecolor(90);
        cout<<"\t\t ~~ About Page ~~ \n\n\n";
        consolecolor(36);
        cout<<"\t\t A conventional paper-based system is used by many theaters and cinemas to manage their tickets, timetables, and movie schedules. Although it is a less expensive option to an electronically based system, its mobility is restricted, and it is susceptible to physical harm. It is also more difficult to find certain files since one must search through several physical documents and updating linked files can be time consuming and complicated because one record does not instantly reflect in the other.\n\n";
        cout<<"By allowing users to purchase tickets, see different tickets, check seats, search for data with more convenience, amend movie schedules, and read movie schedules, the Movie Ticket Booking System will assist to solve challenges created by traditional paper-based systems used in cinemas, as indicated above.\n\n";
        cout<<"\t\t This system was Created by Asher Yisrael Kutswa (137187).";
                    cout<<"\t\t Input 0 to go to Home Page : ";
                    cin>>userch;
                    switch(userch){
                    case 0: homepage();
                    break;
                }

}

/*

~~~Movie Ticketing System~~~

~ Created by Asher Yisrael Kutswa (137187).

~Thank you for your time :)
*/

