#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner; // Winner index
    int loser;  // Loser index
}
pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char* name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char* argv[])
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
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[20];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char* name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;

            } else if (preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Swap pairs by index
void swap_pairs(int i, int j) {
    pair temp = pairs[i];
    pairs[i] = pairs[j];
    pairs[j] = temp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble Sort
    bool sorted;
    do {
        sorted = true;
        int curr_w, curr_l, next_w, next_l;

        for (int i = 0; i < pair_count - 1; i++) {
            curr_w = preferences[pairs[i].winner][pairs[i].loser];
            curr_l = preferences[pairs[i].loser][pairs[i].winner];

            next_w = preferences[pairs[i+1].winner][pairs[i+1].loser]; 
            next_l = preferences[pairs[i+1].loser][pairs[i+1].winner];

            // Decreasing order
            if (curr_w - curr_l < next_w - next_l) {
                sorted = false;
                swap_pairs(i, i + 1);
            }
        }
    } while (!sorted);

    return;
}

// Check if locking coordinates will create a cycle
bool creates_cycle(int src_i, int src_j, int i, int j) {

    // If original winner eventually becomes the loser
    if (src_i == j) {
        return true;
    }

    for (int k = 0; k < candidate_count; k++) {
        if (locked[j][k]) {
            if (creates_cycle(src_i, src_j, j, k)) {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        bool source = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                source = false;
            }
        }
        if (source) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}