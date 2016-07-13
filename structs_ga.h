/*
 ============================================================================
 Author :
 Jose Luis Soncco-Alvarez and Mauricio Ayala-Rincon
 Group of Theory of Computation
 Universidade de Brasilia (UnB) - Brazil
 ============================================================================
 */

#ifndef STRUCTS_GA_H_
#define STRUCTS_GA_H_

#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif


/*define types of print modes */
#define SHOW_FINAL_RESULT   0 //show final results (score and number of evaluations)
#define BEST_BY_GENERATION  1 //show best solution by generation
#define EVALS_BY_GENERATION 2 //show number of evaluations fit funct by generation

typedef struct{
    unsigned int seed;
    int number_generations;
    int num_eval_fit_function;
    int number_reversals;
    int print_mode; //types of print modes
}parameters;


typedef struct{
    int *pi;		// permutation (array)
    int length; 	// lenght of permutation
}permutation;

typedef struct{
	int *genes;
	int length;
	int fitness;
}chromosome;

typedef struct{
	chromosome *chromosomes;
	int population_size; 		
	int limit_for_selection;	//lastindex+1 for selection
	int replacement_base; 		//start index for substitution 

	int population_base; 		//base index for population
	int population_top; 		//lastindex+1 for population

	int offspring_base; 		//base index for offspring 
	int offspring_top; 			//lastindex+1 for offspring

	int total_size;				//total_size = population + offspring
}population;

#endif /* STRUCTS_GA_H_ */
