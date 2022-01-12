#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
using vec = vector<string>;
using DB = vector<vec>;


void printDB(const DB &v)
{
    int i= 65;
    cout << endl;
    cout << "  | ";
    for (int j = 0; j < v[0].size(); j++)
    {   
        cout << setw( 7 ) << right << j << ". col | ";
    }
    cout << endl;

    for(vec row : v)
    {
        cout << char(i) << " | ";
        i++;
        for (string s:row)    cout << setw( 12 ) << left << s << " | ";
        cout << '\n';
    }
    cout << endl;
}

void AddRows(DB &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        vec Add;
        for (int i = 0; i < v[0].size(); i++)
        {
            Add.push_back(" ");
        }
        
        v.push_back(Add);
    }
}

void AddCols(DB &v, int n)
{
    for (int j = 0; j < (v.size()); j++)
    {
        for (int i = 0; i < n; i++)
        {
            v[j].push_back(" ");
        }   
    }
}

void edit(DB &v, int i, int j, string value )
{
    if (i < v.size() && j < v[j].size())
    {
        v[i][j] = value;
    }
}

void deleteRow(DB &v, int row)
{
    if(row < v.size())    
    {
        v.erase( v.begin() + row );
    }
}


void deleteCol(DB &v, int col)
{
    for(vec &row : v)    
    {
        if ( col < row.size() )     
        {
            row.erase( row.begin() + col );
        }
    }
}

int main()
{
    

 //Base region
    bool exit = false;
    string input;
    string output;
    string inputString;
    char inputChar;
    int num;
    DB db;
    vec first;
    first.push_back(" ");
    db.push_back(first);
 //Base region end


 // manipulation
    while (!exit)
    {
        printDB(db);
        cout << "What do you want to do? (addrows, addcols, deleterow, deletecol, edit, exit)" << endl;

        cin >> input;
        for_each(input.begin(), input.end(), [](char & c)
        {
            c = ::tolower(c);
        });

        if (input == "exit")
        {
            exit = true;
        }
        else if (input == "deleterow")
        {
            cout << "Which one? (A-Z)" << endl;
            cin >> inputChar;
            inputChar = toupper(inputChar);
            
            while ((int(inputChar) < 65) || (int(inputChar) > 90) || ((int(inputChar) - 65) > (db.size()-1)) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid row. Try again." << endl;
                cin >> inputChar;
            }
            num = int(inputChar - 65);
            cout << "Deleting row..\n" << endl;
            deleteRow(db, num);

        }
        else if (input == "deletecol")
        {
            cout << "Which one?" << endl;
            cin >> num;
            while (num < 0 || num > db[num].size())
            {
                cout << "Not a valid col. Try again." << endl;
                cin >> num;
            }
            
            cout << "Deleting col..\n" << endl;
            deleteCol(db, num);
        }
        else if (input == "edit")
        {
            cout << "Which Row (A-Z)?" << endl;
            cin >> inputChar;
            inputChar = toupper(inputChar);
            while (int(inputChar) < 65 || int(inputChar) > 90  || (int(inputChar) - 65) > (db.size() -1) || cin.fail())
            {   
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid row. Try again." << endl;
                cin >> inputChar;
            }
            
            cout << "Which Col? (0-" << (db[0].size()-1) << ")" << endl;
            cin >> num;
            while (num < 0 || (num > (db[0].size() - 1)) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid col. Try again." << endl;
                cin >> num;
            }

            cout << "What should the new value be?" << endl;
            cin >> output;
            cout << "Editing line.." << endl;
            edit(db, int(inputChar - 65), num, output);
        }
        else if (input == "addrows")
        {
            cout << "How many?" << endl;
            cin >> num;
            while (!(num > 0 && num < 50) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid input. Try again." << endl;
                cin >> num;
            }
            cout << "Adding rows..\n" << endl;
            AddRows(db, num);
            
        }
        else if (input == "addcols")
        {
            cout << "How many?" << endl;
            cin >> num;
            while (num < 1 || num > 50 || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid input. Try again." << endl;
                cin >> num;
            }
            cout << "Adding cols..\n";
            AddCols(db, num);
            
        }
        else
        {
            cout << "Not a valid input. Please try again." << endl;
        }
        
    }
}

