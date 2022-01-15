#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>


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

void edit(db &v, const int i, const int j, string value )
{
    if (i < v.size() && j < v[j].size())
    {
        v[i][j] = std::move(value);
    }
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

int main(const int argc, char** argv)
{
 //Base region
    bool exit = false;
    string input;
    string output;
    string input_string;
    char input_char;
    int num;
    db matrix;
    vec first;
    first.push_back(" ");
    matrix.push_back(first);
 //Base region end

    if (argc >= 2)
    {
        ifstream file(argv[1]);
        if (file.is_open())
        {
            //Loading matrix with file content.
            cout << "File is open.";
            file.close();
        }
        
        //FILE* f = fopen(argv[1], "r");
    }
    

 // manipulation
    while (!exit)
    {
        print_matrix(matrix);
        cout << "What do you want to do? \nYou can do the following operations:\n";
        cout << "Addrows, addcols, deleterow, deletecol, edit, swap, clear, align, save, exit\n" << endl;

        cin >> input;
    	for_each(input.begin(), input.end(), [](char& c)
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
            cin >> input_char;
            input_char = toupper(input_char);
            
            while ((static_cast<int>(input_char) < 65) || (static_cast<int>(input_char) > 90) || ((static_cast<int>(input_char) - 65) > (matrix.size()-1)) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid row. Try again." << endl;
                cin >> input_char;
            }
            num = static_cast<int>(input_char - 65);
            cout << "Deleting row..\n" << endl;
            delete_row(matrix, num);

        }
        else if (input == "deletecol")
        {
            cout << "Which one?" << endl;
            cin >> num;
            while (num < 0 || num > matrix[num].size())
            {
                cout << "Not a valid col. Try again." << endl;
                cin >> num;
            }
            
            cout << "Deleting col..\n" << endl;
            delete_col(matrix, num);
        }
        else if (input == "edit")
        {
            cout << "Which Row (A-Z)?" << endl;
            cin >> input_char;
            input_char = toupper(input_char);
            while (static_cast<int>(input_char) < 65 || static_cast<int>(input_char) > 90  || (static_cast<int>(input_char) - 65) > (matrix.size() -1) || cin.fail())
            {   
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid row. Try again." << endl;
                cin >> input_char;
            }
            
            cout << "Which Col? (0-" << (matrix[0].size()-1) << ")" << endl;
            cin >> num;
            while (num < 0 || (num > (matrix[0].size() - 1)) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid col. Try again." << endl;
                cin >> num;
            }

            cout << "What should the new value be?" << endl;
            cin >> output;
            cout << "Editing line.." << endl;
            edit(matrix, static_cast<int>(input_char - 65), num, output);
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
            add_rows(matrix, num);
            
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
            add_cols(matrix, num);
            
        }
        else if (input == "swap")
        {
            
        }
        else if (input == "clear")
        {
            
        }
        else if (input == "align")
        {
            
        }
        else if (input == "save")
        {
            
        }
        else
        {
            cout << "Not a valid input. Please try again." << endl;
        }
        
    }
    cout << "\nExiting program.\n";
}

