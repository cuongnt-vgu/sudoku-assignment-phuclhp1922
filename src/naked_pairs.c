#include "naked_pairs.h"
#include <string.h>
#include <stdlib.h>

int find_naked_pairs(Cell **p_cells, NakedPairs *p_naked_pairs, int *p_counter)
{
    // Loop 
    for (int i = 0; i <= 7; i++)
    {
        if (p_cells[i]->num_candidates != 1)
        {
            for (int j = i + 1; j <= 8; j++)
            {
                if ( (p_cells[i]->num_candidates == 2) && (p_cells[i]->num_candidates == p_cells[j]->num_candidates) && (memcmp(get_candidates(p_cells[i]), get_candidates(p_cells[j]), 2 * sizeof(int))) )
                {
                    // Update cells 
                    NakedPairs new_naked_pairs; 
                    new_naked_pairs.p_cell_1 = p_cells[i]; 
                    new_naked_pairs.p_cell_2 = p_cells[j]; 
                    
                    // Check if the pair belongs to the row, the column, or the box
                    if (p_cells[i]->row_index == p_cells[j]->row_index)
                    {
                        new_naked_pairs.row = p_cells[i]->row_index;
                    }
                    else if (p_cells[i]->col_index == p_cells[j]->col_index)
                    {
                        new_naked_pairs.col = p_cells[i]->col_index;
                    }
                    else if (p_cells[i]->box_index == p_cells[j]->box_index)
                    {
                        new_naked_pairs.box = p_cells[i]->box_index;
                    }
                    
                    // Update both value
                    int *candidates = get_candidates(p_cells[i]); 
                    new_naked_pairs.value_1 = candidates[0]; 
                    new_naked_pairs.value_2 = candidates[1]; 
                    free(candidates); 

                    // Update the storing array and increment the counter 
                    p_naked_pairs[*p_counter] = new_naked_pairs; 
                    *p_counter += 1; 
                }
            }
        }
    }

    return *p_counter; 
}

int naked_pairs(SudokuBoard *p_board)
{
    // To find all the naked pairs in the board and return the number of them 

    // param *p_board: the pointer to the sudoku board. 

    NakedPairs naked_pairs[BOARD_SIZE * BOARD_SIZE]; 

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        naked_pairs[i].row = 9; 
        naked_pairs[i].col = 9; 
        naked_pairs[i].box = 9; 
    }

    int counter = 0; 

    // Loop 
    for (int i = 0; i <= 8; i++)
    {
        // Find naked pairs 
        find_naked_pairs(p_board->p_rows[i], naked_pairs, &counter); 
        find_naked_pairs(p_board->p_cols[i], naked_pairs, &counter);
        find_naked_pairs(p_board->p_boxes[i], naked_pairs, &counter);  
    }

    // Loop 
    for (int i = 0; i < counter; i++)
    {
        if (naked_pairs[i].row != 9)
        {
            for (int j = 0; j <= 8; j++)
            {
                if ((p_board->p_rows[naked_pairs[i].row][j] != naked_pairs[i].p_cell_1) && (p_board->p_rows[naked_pairs[i].row][j] != naked_pairs[i].p_cell_2) && (p_board->p_rows[naked_pairs[i].row][j]->num_candidates != 1) )
                {
                    for (int value = 0; value <= 8; value++)
                    {
                        if ((value + 1 == naked_pairs[i].value_1) || (value + 1 == naked_pairs[i].value_2))
                        {
                            unset_candidate(p_board->p_rows[naked_pairs[i].row][j], value + 1);
                        }
                    }
                }
            }
        }
        else if (naked_pairs[i].col != 9)
        {
            for (int j = 0; j <= 8; j++)
            {
                if ((p_board->p_cols[naked_pairs[i].col][j] != naked_pairs[i].p_cell_1) && (p_board->p_cols[naked_pairs[i].col][j] != naked_pairs[i].p_cell_2) && (p_board->p_cols[naked_pairs[i].col][j]->num_candidates != 1) )
                {
                    for (int value = 0; value <= 8; value++)
                    {
                        if ((value + 1 == naked_pairs[i].value_1) || (value + 1 == naked_pairs[i].value_2))
                        {
                            unset_candidate(p_board->p_rows[naked_pairs[i].col][j], value + 1);
                        }
                    }
                }
            }
        }
        else if (naked_pairs[i].box != 9)
        {
            for (int j = 0; j <= 8; j++)
            {
                if ((p_board->p_boxes[naked_pairs[i].box][j] != naked_pairs[i].p_cell_1) && (p_board->p_boxes[naked_pairs[i].box][j] != naked_pairs[i].p_cell_2) && (p_board->p_boxes[naked_pairs[i].box][j]->num_candidates != 1) )
                {
                    for (int value = 0; value <= 8; value++)
                    {
                        if ((value + 1 == naked_pairs[i].value_1) || (value + 1 == naked_pairs[i].value_2))
                        {
                            unset_candidate(p_board->p_boxes[naked_pairs[i].box][j], value + 1);
                        }
                    }
                }
            }
        }
    }

    return counter;
}