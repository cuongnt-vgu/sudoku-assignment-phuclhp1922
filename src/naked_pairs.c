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
                if ( (p_cells[i]->num_candidates == 2) && (p_cells[i]->num_candidates == p_cells[j]->num_candidates) )
                {
                    int *candidates_1 = get_candidates(p_cells[i]); 
                    int *candidates_2 = get_candidates(p_cells[j]); 
                    if ((candidates_1[0] == candidates_2[0]) && (candidates_1[1] == candidates_2[1]))
                    {
                        // Update cells 
                        p_naked_pairs[*p_counter].p_cell_1 = p_cells[i]; 
                        p_naked_pairs[*p_counter].p_cell_2 = p_cells[j]; 
                        
                        // Check if the pair belongs to the row, the column, or the box
                        if (p_cells[i]->row_index == p_cells[j]->row_index)
                        {
                            p_naked_pairs[*p_counter].row = p_cells[i]->row_index;
                        }
                        if (p_cells[i]->col_index == p_cells[j]->col_index)
                        {
                            p_naked_pairs[*p_counter].col = p_cells[i]->col_index;
                        }
                        if (p_cells[i]->box_index == p_cells[j]->box_index)
                        {
                            p_naked_pairs[*p_counter].box = p_cells[i]->box_index;
                        }
                        
                        // Update both value                 
                        p_naked_pairs[*p_counter].value_1 = candidates_1[0]; 
                        p_naked_pairs[*p_counter].value_2 = candidates_1[1]; 

                        // Update the storing array and increment the counter                  
                        (*p_counter)++;
                    } 
                    free(candidates_1); 
                    free(candidates_2);
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

    NakedPairs naked_pairs[BOARD_SIZE * BOARD_SIZE / 2]; 

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE / 2; i++)
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

    int overlap = 0; 
    // Loop 
    for (int i = 0; i < counter; i++)
    {
        int is_overlap = 1; 
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
                            unset_candidate(p_board->p_rows[naked_pairs[i].row][j], value);
                            is_overlap = 0; 
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
                            unset_candidate(p_board->p_cols[naked_pairs[i].col][j], value + 1);
                            is_overlap = 0;
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
                            unset_candidate(p_board->p_boxes[naked_pairs[i].box][j], value);
                            is_overlap = 0;
                        }
                    }
                }
            }
        }
        overlap += is_overlap; 
    }

    return counter - overlap; 
}