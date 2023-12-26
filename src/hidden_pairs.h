#pragma once

#include "sudoku.h"

typedef struct HiddenPair_impl
{
    Cell *p_cell_1;
    Cell *p_cell_2; 
    int value_1;
    int value_2; 
} HiddenPair;

void find_hidden_pair_values(Cell *p_cell, int hidden_pairs_values[9]); 

int find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter); 

int hidden_pairs(SudokuBoard *p_board);
