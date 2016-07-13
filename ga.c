/*
 ============================================================================
 Project    : Genetic Algorithm for the SUPBR Problem
 File       : ga.c
 Author     : Jose Luis Soncco-Alvarez and Mauricio Ayala-Rincon
                Group of Theory of Computation
                Universidade de Brasilia (UnB) - Brazil
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h> //malloc, free
#include <string.h>
#include "operators.h"
#include "structs_ga.h"

#include <time.h>
#include <sys/time.h>

static void readCommandLine(int argc, char *argv[], parameters *params); 
static double timeval_diff(struct timeval *a, struct timeval *b);
static int start_ga(parameters *params, int *num_eval_fit_function, int *num_used_generations);

int main(int argc, char **argv){
    parameters params;
	int score, num_eval_fit_function, num_used_generations;
    struct timeval t_ini, t_fin;
    
    params.seed = time(NULL);
    params.number_generations = -1;
    params.num_eval_fit_function = -1;
    params.number_reversals = -1;
    params.print_mode = SHOW_FINAL_RESULT;

    score = -1;
    num_eval_fit_function = 0;
    
    readCommandLine(argc, argv, &params);
    
    srand(params.seed);//initialize random generator
    gettimeofday(&t_ini, NULL);//--take start time
    
    score = start_ga(&params, &num_eval_fit_function, &num_used_generations);
    
    gettimeofday(&t_fin, NULL);//--take final time
    timeval_diff(&t_fin, &t_ini);//determine total time
    
    if (params.print_mode == SHOW_FINAL_RESULT){
	   printf("%d\n",score);//show result (number of reversals)
	   printf("%d\n",num_eval_fit_function);//show number of evalutions of fit_function
       printf("%d\n",num_used_generations);//show number of used generations
    }
    return 0;
}

static int start_ga(parameters *params, int *num_eval_fit_function, int *num_used_generations)
{
    /***Variables***/
    int i,generation_number;
    permutation perm;
    population pop;
    int best_solution;
    int number_of_generations;
    int start_breeding = TRUE;
    
    read_permutation_from_file("i", &perm);
    
    /***START GENETIC_ALG**/
    generation_number = 1;
    generate_initial_population(&pop,&perm);
    calculate_fitness_population(&pop,1,num_eval_fit_function);
    best_solution = pop.chromosomes[0].fitness;
    number_of_generations = perm.length;

    if (params->number_generations > -1) 
        number_of_generations = params->number_generations;

    if (params->print_mode == BEST_BY_GENERATION)
        printf("%d ",best_solution); //print best solution by generation
    if (params->print_mode == EVALS_BY_GENERATION)
        printf("%d ", *num_eval_fit_function); //print number of evaluations
    //other stop conditions
    if (params->num_eval_fit_function > -1 &&
        *num_eval_fit_function >= params->num_eval_fit_function)
        start_breeding = FALSE;
    if (best_solution <= params->number_reversals)
        start_breeding = FALSE;

    if (start_breeding == TRUE){
        for(generation_number=2; generation_number<=number_of_generations; generation_number++){
            selection(&pop,generation_number,&best_solution);
            crossover(&pop, &perm);
            mutation(&pop, &perm);
            calculate_fitness_population(&pop,generation_number,num_eval_fit_function);
            replacement(&pop);
            
            if (params->print_mode == BEST_BY_GENERATION)
                printf("%d ",best_solution); //print best solution by generation
            if (params->print_mode == EVALS_BY_GENERATION)
                printf("%d ", *num_eval_fit_function); //print number of evaluations

            //other stop conditions
            if (params->num_eval_fit_function > -1 &&
                *num_eval_fit_function >= params->num_eval_fit_function)
                break;
            if (best_solution <= params->number_reversals)
                break;
        }
    }
       
    if (generation_number > number_of_generations)
        *num_used_generations = number_of_generations;
    else
        *num_used_generations = generation_number;
    
    /***Free Memory***/
    for(i=0;i<pop.total_size;i++){
        free(pop.chromosomes[i].genes);
    }
    free(pop.chromosomes);
    free(perm.pi);
    
    return best_solution;
}

static void readCommandLine(int argc, char *argv[], parameters *params)
{
    int i;
    char option;
    
    /* read parameters from command line */
    i = 1;
    while ( i < argc) {
        if ( argv[ i ][ 0 ] == '-' && (i + 1) < argc ) {
            option = argv[ i ][ 1 ];
            switch ( option ) {
                case 's':
                    params->seed = atoi( argv[ i + 1 ] );
                    break;
                case 'g':
                    params->number_generations = atoi( argv[ i + 1 ] );
                    break;
                case 'e':
                    params->num_eval_fit_function = atoi( argv[ i + 1 ] );
                    break;
                case 'r':
                    params->number_reversals = atoi( argv[ i + 1 ] );
                    break;
                case 'm':
                    if ( strcmp( argv[ i + 1], "final_result" ) == 0 ) {
                        params->print_mode = SHOW_FINAL_RESULT;
                    }
                    else if ( strcmp( argv[ i + 1], "best_by_gen" ) == 0 ) {
                        params->print_mode = BEST_BY_GENERATION;
                    }
                    else if ( strcmp( argv[ i + 1], "eval_by_gen" ) == 0 ) {
                        params->print_mode = EVALS_BY_GENERATION;
                    }
                    else{
                        fprintf( stderr, " stderr: incorrect mode (-m).\n" );
                        exit( EXIT_FAILURE );
                    }
                    break;
                default:
                    fprintf( stderr, " stderr: incorrect option: %c.\n", option );
                    exit( EXIT_FAILURE );
            }
            i = i + 2;
        }
        else{
            fprintf( stderr, " stderr: incorrect options or parameters.\n" );
            exit( EXIT_FAILURE );
        }
    }  
}

static double timeval_diff(struct timeval *a, struct timeval *b)
{
    return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}


