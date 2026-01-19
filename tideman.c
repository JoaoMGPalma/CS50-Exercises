/*
    Tideman (Ranked Pairs) Election Algorithm

    This program implements the Tideman voting method, a ranked‑choice
    election system that determines a winner without eliminating candidates.
    Voters rank candidates in order of preference, and the program builds
    a directed graph of pairwise victories while avoiding cycles.

    Features:
    - Records each voter’s ranked preferences
    - Builds a preference matrix of head‑to‑head matchups
    - Generates all winning pairs between candidates
    - Sorts pairs by strength of victory (margin)
    - Locks pairs into a directed graph while preventing cycles
    - Identifies the source of the graph as the election winner

    To test, run the program from the terminal and pass as arguments the
    names of the candidates. After that, especify the number of voters and
    the ranked preferences of each one. The output will show the winner of
    the election.

    Expected output:
    .\tideman.exe Alex Jordan Taylor
    Number of voters: 3
    Rank 1: Jordan
    Rank 2: Taylor
    Rank 3: Alex

    Rank 1: Taylor
    Rank 2: Jordan
    Rank 3: Alex

    Rank 1: Alex
    Rank 2: Jordan
    Rank 3: Taylor
    
    Jordan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int calculate_margin(pair p);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

        for (int j = 0; j < candidate_count; j++)
        {
            char name[100];
            printf("Rank %i: ", j + 1);
            scanf("%99s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        printf("\n");
        record_preferences(ranks);
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int vote_a = ranks[i];

        for (int j = i + 1; j < candidate_count; j++)
        {
            int vote_b = ranks[j];
            preferences[vote_a][vote_b]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int best_index = i;
        int best_margin = calculate_margin(pairs[i]);

        for (int j = i + 1; j < pair_count; j++)
        {
            int margin_j = calculate_margin(pairs[j]);
            if (margin_j > best_margin)
            {
                best_margin = margin_j;
                best_index = j;
            }
        }

        if (best_index != i)
        {
            pair temp = pairs[i];
            pairs[i] = pairs[best_index];
            pairs[best_index] = temp;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        bool cycle = false;

        int stack[MAX];
        int top = 0;

        stack[top++] = pairs[i].loser;

        bool visited[MAX] = {false};

        for (int s = 0; s < top; s++)
        {
            int current = stack[s];
            visited[current] = true;

            if (current == pairs[i].winner)
            {
                cycle = true;
                break;
            }

            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[current][j] && !visited[j])
                {
                    stack[top++] = j;
                }
            }
        }

        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming = false;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming = true;
                break;
            }
        }

        if (!has_incoming)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

int calculate_margin(pair p)
{
    return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}