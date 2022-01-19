#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>

using vec = std::vector<std::string>;
using db = std::vector<vec>;

///Printing the database to the screen
inline void print_matrix(const db& v);

///Adding N rows to the database
inline auto add_rows(db& v, const int n) -> void;

///Adding N cols to the database
inline void add_cols(db& v, const int n);

///Inserting N rows before the X row.
inline auto insert_rows(db& v, const int n, const int x) -> void;

///Inserting N cols before the X col.
inline void insert_cols(db& v, const int n, const int x);

///Inserting the value to the IJ cell in the database
inline void edit(db& v, const int i, const int j, const std::string& value);

///Swapping the IJ cell with the XY cell.
inline void swap(db& v, const int i, const int j, const int x, const int y);

///Deleting 'row'th row in the database.
inline void delete_row(db& v, const int row);

///Deleting the  'col'th column in the database
inline auto delete_col(db& v, const int col) -> void;

///Checking if the given row is a valid row of the database.
inline bool validrow(const db& matrix, const char c);

///Checking if the given col is a valid col of the database.
inline bool validcol(const db& matrix, const int i);

///Clearing the IJ-XY range of the database
inline void clear(db& v, int i, const int j, const int x, const int y);

///Saving the database to the given filename
inline void save(const db& v, const std::string f_name, std::string separ);
#endif // FUNCTIONS_H
