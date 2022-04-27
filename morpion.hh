//
// Created by tedac on 14/04/2022.
//

#ifndef MORPION_MORPION_HH
#define MORPION_MORPION_HH

#include <iostream>
#include <vector>
#include <algorithm>

class TicTacToe {

public:

    TicTacToe() { };

    // GAMEPLAY //

    int game() {

        std::cout << "Hello, World!" << std::endl;

        // Initialize the pieces of the players
        std::string piece;
        std::cout << "What do you want to play ? X or O ?" << std::endl;
        std::cin >> piece;

        // Check if the piece is valid
        std::vector<char> available_pieces = {'X', 'x', 'O', 'o'};
        char pawn;

        if (piece.size() != 1 || std::find(available_pieces.begin(), available_pieces.end(), piece[0]) == available_pieces.end()) { // Modifié par Max
            std::cout << "Wrong input, you will play with X" << std::endl;
            pawn = 'X';
        }

        else {
            pawn = piece[0];
        }

        // Initialize the turns
        std::string response;
        std::cout << "Do you want to play first ? (Y/N)" << std::endl;
        std::cin >> response;

        int player;
        int winner = 0;
        int turn = 0;

        // Set the turns
        if (response == "Y" || response == "y" || response == "yes" || response == "Yes" || response == "YES") {
            player = 1;
        }
        else if (response == "N" || response == "n" || response == "no" || response == "No" || response == "NO") {
            player = 2;
        }
        else {
            std::cout << "Wrong input, so you will play first" << std::endl;
            player = 1;
        }

        srand(time(NULL)); // So the random number is different each time

        while (winner == 0){

            // Print the grid
            print_grid(pawn);

            // If the game is finished
            if (turn == 9) {
                std::cout << "It's a draw !" << std::endl;
                break;
            }

            // Player turn
            if (player == 1){
                playing();
                turn++;
            }
            // Computer turn
            else {
                computer();
                turn++;
            }

            // Check if someone won
            winner = is_winning();

            // Switch player
            player = (player == 1) ? 10 : 1;
        }

        // Print the grid
        print_grid(pawn);

        // Print the winner
        if (winner == 1){
            std::cout << "Player won !" << std::endl;
        }
        else if (winner == 10){
            std::cout << "Computer won !" << std::endl;
        }

        return 0;
    }

    // FUNCTIONS //

    /* Ask the player to play */
    bool playing();

    /* Find the coordinates of the first move of the player */
    std::vector<std::pair<int, int>> find_in_matrix(int value);

    /* Return the position to play if the player is almost winning */
    std::pair<int, int> almost_win(int player);

    /* Defines the computer moves */
    bool computer();

    /* Returns 1 when the player is winning, 10 if the computer is winning and 0 if no one is winning */
    int is_winning();

    /* Print the grid */
    void print_grid(char p1);


    // ATTRIBUTES //

    // Initialize the grid
    int grid[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };
};

#endif//MORPION_MORPION_HH
