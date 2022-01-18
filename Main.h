#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
using vec = vector<string>;
using db = vector<vec>;


void print_matrix(const db &v)
{
    int i= 65;
    cout << endl;
    cout << "  | ";
    for (int j = 0; j < v[0].size(); j++)
    {   
        cout << setw( 7 ) << right << j << ". col | ";
    }
    cout << endl;

    for(const vec& row : v)
    {
        int row_count = 0;
        for (string s:row)
        {
            if (row_count == 0)
            {
                cout << "------------------";
            }
            else
            {
                cout << "---------------"; 
            }
            row_count++;
        }
        cout << endl;
        cout << static_cast<char>(i) << " | ";
        i++;
        for (const string& s:row)
        {
            cout << setw( 12 ) << left << s << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

auto add_rows(db& v, const int n) -> void
{
    for (int i = 0; i < n; i++)
    {
        vec add;
        for (int i = 0; i < v[0].size(); i++)
        {
            add.push_back(" ");
        }
        
        v.push_back(add);
    }
}

void add_cols(db &v, const int n)
{
    for (auto& j : v)
    {
        for (int i = 0; i < n; i++)
        {
	        j.emplace_back(" ");
        }   
    }
}

void edit(db &v, const int i, const int j, const string& value )
{
    if (i < v.size() && j < v[j].size())
    {
        v[i][j] = value;
    }
}

void swap(db& v, const int i, const int j, const int x, const int y)
{
    const string temp = v[i][j];
    v[i][j] = v[x][y];
    v[x][y] = temp;
}

void delete_row(db &v, const int row)
{
    if(row < v.size())    
    {
        v.erase( v.begin() + row );
    }
}


auto delete_col(db& v, const int col) -> void
{
    for(vec &row : v)    
    {
        if ( col < row.size() )     
        {
            row.erase( row.begin() + col );
        }
    }
}

bool mycomp(const string a, const string b)
{
	return a<b;
}

bool validrow(const db& matrix, const char c)
{
    if ((static_cast<int>(c) < 65) || (static_cast<int>(c) > 90) || ((static_cast<int>(c) - 65) > (matrix.size()-1)) || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
    
} 

bool validcol(const db& matrix, const int i)
{
    if ((i >= 0) && (i <= (matrix[i].size()-1)))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void clear(db& v,  int i, const int j, const int x, const int y)
{
	for (i; i <= x; i++)
	{
        int n = j;
        for (n; n <= y; n++)
        {
            v[i][n] = " ";
        }
	}
}

void save(const db& v, const string f_name)
{

    ofstream outfile;
    outfile.open(f_name, ios_base::out); // append instead of overwrite

    for (const auto& a : v)
    {
        string f_line;
        for (int b = 0; b < a.size(); b++)
        {
            f_line = f_line + a[b] + ";";
        }
        outfile << f_line << "\n";
	    
    }
    outfile.close();

}