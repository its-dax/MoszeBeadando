#include <algorithm>
#include <fstream>
#include <sstream>
#include "functions.h"

using namespace std;

int main(const int argc, char** argv)
{
 //Base region
    bool exit = false;      ///< If this is true, exit the application
    string input;           ///< Input string of the method the user want to perform.
    string input_string;    ///< Variable string input
    string output;          ///< Output string for the edit function
    char input_char;        ///< Row of the first input cell
    char input_char2;       ///< Row of the second input cell
    int num;                ///< Col of the first input cell  
    int num2;               ///< Col of the second iunput cell
    db matrix;              ///< The database vector of string vectors
    vec first;              ///< Lines of the database
    first.push_back(" ");
    matrix.push_back(first);
 //Base region end


    if (argc >= 2)
    {
        ifstream file(argv[1]);
        int col_count = 0;
        int row_count = 0;
        string sep = ";";

        if (argc == 4)
        {
            sep = argv[3];
        }

        if (!file.is_open())
        {
            cout << "\n===========================================";
            cout << "\n!! File could not open, loading casually !!\n";
            cout << "===========================================\n";
        }
        while(file.good())
        {
            matrix.pop_back();
            first.pop_back();
            string line;
            
            while (getline(file, line))
            {
                vector<string> row;
                stringstream iss(line);
                string val;
                col_count = 0;
                while (getline(iss, val, sep[0]))
                {
                    row.push_back(val);
                    col_count++;
                }
                matrix.push_back(row);
                row_count++;
            }

            for (int row_p = 0; row_p <= row_count; row_p++)
            {
	            if ((matrix[row_p].size()-1) <= col_count)
	            {
                    int col = matrix[row_p].size();
                    for (col; col < col_count; col++)
                    {
                        
                        matrix[row_p].emplace_back(" ");
                    }
	            }
            }
        }
        file.close();
    }
    

 // manipulation
    while (!exit)
    {
        print_matrix(matrix);
        cout << "What do you want to do? \nYou can do the following operations:\n";
        cout << "--------------------------------------------------------------\n";
        cout << "Increasing methods: addrows, addcols, insertrows, insertcols\n";
        cout << "Decreasing methods: deleterow, deletecol\n";
        cout << "Editing methods:    edit, swap, clear (range)\n";
    	cout << "File methods:       save, exit\n";
        cout << "--------------------------------------------------------------\n\n";

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
            cout << "Which one? (A-Z)\n";
            cin >> input_char;
            input_char = toupper(input_char);
            
            while (!validrow(matrix, input_char))
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid row. Try again.\n";
                cin >> input_char;
            }
            num = static_cast<int>(input_char - 65);
            cout << "Deleting row..\n\n";
            delete_row(matrix, num);

        }
        else if (input == "deletecol")
        {
            cout << "Which one?\n";
            cin >> num;
            while (!validcol(matrix, num))
            {
                cout << "Not a valid col. Try again.\n";
                cin >> num;
            }
            
            cout << "Deleting col..\n\n";
            delete_col(matrix, num);
        }
        else if (input == "edit")
        {
            cout << "Which cell?\n";
            cin >> input_char;
            cin >> num;
            input_char = toupper(input_char);
            while (!validrow(matrix, input_char) || !validcol(matrix, num))
            {   
                cout << "Not a valid cell. Try again.\n";
                cin >> input_char;
                cin >> num;
            }

            cout << "What should the new value be?\n";
            cin >> output;
            cout << "Editing line.." << endl;
            edit(matrix, static_cast<int>(input_char - 65), num, output);
        }
        else if (input == "addrows")
        {
            cout << "How many?\n";
            cin >> num;
            while (!(num > 0 && num < 50) || cin.fail())
            {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Not a valid input. Try again.\n";
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
                cout << "Not a valid input. Try again.\n";
                cin >> num;
            }
            cout << "Adding cols..\n";
            add_cols(matrix, num);
            
        }
        else if (input == "swap")
        {
            cout << "Which cell do you want to swap?\n";
            cin >> input_char;
            cin >> num;
            input_char = toupper(input_char);
            while (!validrow(matrix, input_char) || !validcol(matrix, num))
            {
                cout << "Not a valid cell. Try again.\n";
                cin >> input_char;
                cin >> num;
            }
            
            cout << "Which cell do you want to swap with?\n";
            cin >> input_char2;
            cin >> num2;
            input_char2 = toupper(input_char2);
            while (!validrow(matrix, input_char) || !validcol(matrix, num))
            {
                cout << "Not a valid cell. Try again.\n";
                cin >> input_char;
                cin >> num;
            }
            swap(matrix, static_cast<int>(input_char - 65), num, static_cast<int>(input_char2 - 65), num2);

        }
        else if (input == "sort")
        {   
            cout << "asc or desc?\n";
            cin >> input_string;
            while (!(input_string == "asc") || !(input_string == "desc"))
            {
                cout << "Not a valid input. Try again.\n";
                cin >> input_string;
            }
            if (input_string == "asc")
            {
                sort(matrix.begin(), matrix.end());
            }
            else if (input_string == "desc")
            {
                //sort(matrix.begin(), matrix.end(), mycomp);
            }
        }
        else if (input == "clear")
        {
	        cout << "Whats the first cell of the range?\n";
	        cin >> input_char;
	        cin >> num;
	        input_char = toupper(input_char);
	        while (!validrow(matrix, input_char) || !validcol(matrix, num))
	        {
	            cout << "Not a valid cell. Try again.\n";
	            cin >> input_char;
	            cin >> num;
	        }

	        cout << "Whats the second cell of the range?\n";
	        cin >> input_char2;
	        cin >> num2;
	        input_char2 = toupper(input_char2);
	        while (!validrow(matrix, input_char2) || !validcol(matrix, num2))
	        {
	            cout << "Not a valid cell. Try again.\n";
	            cin >> input_char2;
	            cin >> num2;
	        }
	        const int min_c = (num > num2) ? num2 : num;
	        const int max_c = (num > num2) ? num : num2;

	        const int max_r = (static_cast<int>(input_char - 65) > static_cast<int>(input_char2 - 65))
		                         ? static_cast<int>(input_char - 65)
		                         : static_cast<int>(input_char2 - 65);
	        const int min_r = (static_cast<int>(input_char - 65) > static_cast<int>(input_char2 - 65))
		                         ? static_cast<int>(input_char2 - 65)
		                         : static_cast<int>(input_char - 65);
	        
			clear(matrix, min_r, min_c, max_r, max_c);
        }
        else if (input == "insertrows")
        {
	        cout << "How many?\n";
	        cin >> num;
	        cout << "Before which row?\n";
	        cin >> input_char;
	        while (!validrow(matrix, input_char))
	        {
                cout << "Not a valid row. Try again.\n";
                cin >> input_char;
	        }
            insert_rows(matrix, num, static_cast<int>(input_char - 65));
        }
        else if (input == "insertcols")
        {
	        cout << "How many?\n";
	        cin >> num;
	        cout << "Before which col?\n";
	        cin >> num2;
	        while (!validcol(matrix,num2))
	        {
                cout << "Not a valid col. Try again.\n";
                cin >> num2;
	        }
            insert_cols(matrix, num, num2);
        }
        else if (input == "save")
        {
			cout << "Type in filename please.\n";
            cin >> input_string;
            cout << "Type in the separator of your choosing. For default: type in ';' \n";
            cin >> output;
            cout << "\nSaving..\n";

            save(matrix, input_string, output);
            
        }
        else
        {
            cout << "Not a valid input. Please try again.\n";
        }
        
    }
    cout << "\nExiting program.\n";
}

