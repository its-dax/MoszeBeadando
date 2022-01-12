#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;
using vec = vector<string>;
using DB = vector<vec>;



void printDB(const DB &v)
{
   for(vec row : v)
   {
      for (string s:row)    cout << setw( 12 ) << left << s << " || ";
      cout << '\n';
   }
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
    string x;
    DB db;
    vec first;
    first.push_back(" ");
    db.push_back(first);
//Base region end


// manipulation

    AddRows(db, 5);
    AddCols(db, 1);
    printDB(db);

    cin >> x;
}

