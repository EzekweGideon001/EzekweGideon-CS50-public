#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate over candidates
    for(int i = 0; i < candidate_count; i++)
    {

        // Validate the candidate chosen
        if(strcmp(name,candidates[i].name) == 0)
        {

            // Update preferences array
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate over all voters
    for (int i = 0; i < voter_count; i++)
    {
        // Find the highest-ranked non-eliminated candidate for each voter
        for (int j = 0; j < candidate_count; j++)
        {
            int choice = preferences[i][j];

            // If the candidate is not eliminated, increase their vote count
            if (!candidates[choice].eliminated)
            {
                candidates[choice].votes += 1;
                break;  // Exit the loop after counting the vote for the first non-eliminated candidate
            }
        }
    }
    return;
}

// Print the winner(s) of the election, if there is one
bool print_winner(void)
{
    int highest_vote = 0;

    // First loop to find the highest number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= highest_vote)
        {
            highest_vote = candidates[i].votes;
        }
    }

    bool winner_found = false;

    // Second loop to print all candidates with the highest number of votes
    bool majority = highest_vote > (voter_count/2);

    if(majority){
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == highest_vote)
            {
                printf("%s\n", candidates[i].name);
                winner_found = true;
            }
        }
    }

    return winner_found;  // Return true if any winners were found
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //initialize minimum number of votes
    int min_votes = MAX_VOTERS;

    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //update the minimum number of votes
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }

    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if any non-eliminated candidate has more than the minimum number of votes
        if (!candidates[i].eliminated && candidates[i].votes > min)
        {
            return false; // It's not a tie if any candidate has more than the minimum votes
        }
    }
    // If no candidate has more than the minimum votes, it's a tie
    return true;
}


// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check for uneliminated candidate with minimum votes
        if(!candidates[i].eliminated && candidates[i].votes == min)
        {
            // Eliminate them
            candidates[i].eliminated = true;
        }
    }
    return;
}
