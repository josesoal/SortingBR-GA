/*
 ============================================================================
 Author :
 Jose Luis Soncco-Alvarez and Mauricio Ayala-Rincon
 Group of Theory of Computation
 Universidade de Brasilia (UnB) - Brazil
 ============================================================================
 */

#ifndef OPERATORS_H_
#define OPERATORS_H_

#include "structs_ga.h"

void generate_initial_population(population *pob, permutation *perm);
void calculate_fitness_population(population *pob, int generation_number, int *num_eval_fit_function);
void selection(population *pob, int generation_number, int *best_solution);
void crossover(population *pob, permutation *perm);
void mutation(population *pob, permutation *perm);
void replacement(population *pob);

void read_permutation(permutation *perm);
void read_permutation_from_file(char* nombre_archivo, permutation *perm);
void show_population(population *pop, permutation *perm, int generation_number);

#endif /* OPERADORES_H_ */
