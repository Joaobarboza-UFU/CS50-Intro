#include <cs50.h>
#include <stdio.h>
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
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
bool vote(int rank, string name, int ranks[])
{
    //look for a candidate called name
    // update ranks and return true if found . ranks[i] is the ith poreference.
    // refurn false if not found
    for (int i = 0 ; i < candidate_count ; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0 ; i < candidate_count ; i++)
    {
        for (int j = (i + 1) ; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //record the preference pair to the pairs array
    //update the global variable pirs_count
    for (int i = 0 ; i < candidate_count ; i++)
    {
        for (int j = 0 ; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int counter = 0;
    int ref = 0;
    bool tester = false;
    for (int i = 0 ; i < pair_count ; i++)
    {
        for (int j = 1 ; j < pair_count ; j++)
        {

            if (((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner])) < ((
                        preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner])))
            {
                int swap_winner = pairs[i].winner;
                int swap_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = swap_winner;
                pairs[j].loser = swap_loser;
                i = j;
                tester = true;
            }

        }

        if (!tester)
        {
            ref += 1;
        }

        if (counter < candidate_count)
        {
            i = 0 + ref ;
            counter += 1;
            ref = false;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int count = 0;
    for (int i = 0; i < pair_count ; i++)
    {
        if (count > 1)
        {
            bool flag = true;
            int k = i ;
            for (int w = count ; w >= 0 ; w --)
            {
                if (pairs[k].loser == pairs[w].winner)
                {
                    k = w;
                    w = count;

                    if (pairs[i].winner == pairs[k].loser)
                    {
                        flag = false;
                        w = -1;
                    }
                }
            }

            if (flag)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
                count += 1;
            }
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            count += 1;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int k = 0 ; k < candidate_count ; k++)
    {
        for (int i = 0 ; i < candidate_count ; i++)
        {
            if (locked[i][k])
            {
                for (int j = 0 ; j < candidate_count ; j++)
                {
                    locked[k][j] = false;
                }
            }
        }
    }

    for (int y = 0 ; y < candidate_count ; y++)
    {
        for (int z = 0 ; z < candidate_count ; z++)
        {
            if (locked[y][z])
            {
                printf("%s\n", candidates[y]);
            }
        }
    }

    return;
}
