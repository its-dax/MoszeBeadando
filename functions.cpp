///Header file for all functions

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "functions.h"

using namespace std;
using vec = vector<string>;
using db = vector<vec>;

///Printing the database to the screen
inline void print_matrix(const db& v)
{
    int i = 65;
    cout << endl;
    cout << "  | ";
    for (int j = 0; j < v[0].size(); j++)
    {
        cout << setw(7) << right << j << "      | ";
    }
    cout << endl;

    for (const vec& row : v)
    {
        int row_count = 0;
        for (string s : row)
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
        for (const string& s : row)
        {
            cout << setw(12) << left << s << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

///Adding N rows to the database
inline auto add_rows(db& v, const int n) -> void
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

///Adding N cols to the database
inline void add_cols(db& v, const int n)
{
    for (auto& j : v)
    {
        for (int i = 0; i < n; i++)
        {
            j.emplace_back(" ");
        }
    }
}

///Inserting N rows before the X row.
inline auto insert_rows(db& v, const int n, const int x) -> void
{
    for (int i = 0; i < n; i++)
    {
        vec add;
        for (int i = 0; i < v[0].size(); i++)
        {
            add.push_back(" ");
        }

        v.emplace(v.begin() + x, add);
    }
}

///Inserting N cols before the X col.
inline void insert_cols(db& v, const int n, const int x)
{
    for (auto& j : v)
    {
        for (int i = 0; i < n; i++)
        {
            j.emplace(j.begin() + x, " ");
        }
    }
}

///Inserting the value to the IJ cell in the database
inline void edit(db& v, const int i, const int j, const string& value)
{
    if (i < v.size() && j < v[j].size())
    {
        v[i][j] = value;
    }
}

///Swapping the IJ cell with the XY cell.
inline void swap(db& v, const int i, const int j, const int x, const int y)
{
    const string temp = v[i][j];
    v[i][j] = v[x][y];
    v[x][y] = temp;
}

///Deleting 'row'th row in the database.
inline void delete_row(db& v, const int row)
{
    if (row < v.size())
    {
        v.erase(v.begin() + row);
    }
}

///Deleting the  'col'th column in the database
inline auto delete_col(db& v, const int col) -> void
{
    for (vec& row : v)
    {
        if (col < row.size())
        {
            row.erase(row.begin() + col);
        }
    }
}

///Checking if the given row is a valid row of the database.
inline bool validrow(const db& matrix, const char c)
{
    if ((static_cast<int>(c) < 65) || (static_cast<int>(c) > 90) || ((static_cast<int>(c) - 65) > (matrix.size() - 1)) || cin.fail())
    {
        return false;
    }
    else
    {
        return true;
    }
}

///Checking if the given col is a valid col of the database.
inline bool validcol(const db& matrix, const int i)
{
    if ((i >= 0) && (i <= (matrix[i].size() - 1)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

///Clearing the IJ-XY range of the database
inline void clear(db& v, int i, const int j, const int x, const int y)
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

///Saving the database to the given filename
inline void save(const db& v, const string f_name, string separ)
{
    ofstream outfile;
    outfile.open(f_name, ios_base::out); // append instead of overwrite

    for (const auto& a : v)
    {
        string f_line;
        for (const auto& b : a)
        {
            f_line = f_line + b + separ[0];
        }
        outfile << f_line << "\n";
    }
    outfile.close();
}