#pragma once

#include "sudoku.h"

typedef struct NakedPairs_impl
{
    Cell *p_cell_1;
    Cell *p_cell_2; 
    int row;
    int col;
    int box;
    int value_1; 
    int value_2; 
} NakedPairs; 

int naked_pairs(SudokuBoard *p_board);