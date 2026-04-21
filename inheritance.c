/**
 * FILE: inheritance.c
 * DESCRIPTION:
 * Simulates the genetic inheritance of blood types across multiple 
 * generations. The program builds a family tree where each child 
 * inherits one allele from each parent.
 * * USAGE:
 * ./inheritance
 * * TECHNICAL CONCEPTS:
 * 1. Recursive Data Structures: Uses a struct with self-referential pointers.
 * 2. Dynamic Memory: Allocates memory on the heap using malloc.
 * 3. Recursion: Implements recursive functions for tree creation, 
 * traversal (printing), and post-order destruction (freeing).
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator with standard srand
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents recursively
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Inherit alleles: randomly choose one from each parent
        for (int i = 0; i < 2; i++)
        {
            p->alleles[i] = p->parents[i]->alleles[rand() % 2];
        }
    }
    // Base case: first generation (grandparents)
    else
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    return p;
}

// Free `p` and all ancestors using post-order traversal
void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    // Recursively free parents first
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the current person
    free(p);
}

void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Visual indentation for tree structure
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    if (generation == 0)
    {
        printf("Child (Gen %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Gen %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Gen %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print ancestors
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

char random_allele()
{
    int r = rand() % 3;
    if (r == 0) return 'A';
    if (r == 1) return 'B';
    return 'O';
}
