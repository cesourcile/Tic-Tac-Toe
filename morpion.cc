//
// Created by tedac on 14/04/2022.
//

#include "morpion.hh"

/* Ask the player to play */
bool TicTacToe::playing() {
    int r, c;

    std::cout << "Enter the coordinates (column then row) : " << std::endl;
    std::cin >> c >> r;

    if (c < 0 || c > 2 || r < 0 || r > 2) {
        std::cout << "Invalid coordinates" << std::endl;
        playing();
        return false;
    }

    std::cout << "You chose: " << c << ", " << r << std::endl;

    if (grid[r][c] == 0){
        grid[r][c] = 1;
        return true;
    }
    else {
        std::cout << "This case is already taken" << std::endl;
        playing();
        return false;
    }
}

/* Find the coordinates of the moves of the player */
std::vector<std::pair<int, int>> TicTacToe::find_in_matrix(int value) {
    std::vector<std::pair<int, int>> list;
    bool found = false;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[r][c] == value) {
                list.emplace_back(r, c);
                found = true;
            }
        }
    }

    if (!found) {
        list.emplace_back(-1, -1);
        return list;
    }
    return list;
}

/* Return the position to play if the player is almost winning */
std::pair<int, int> TicTacToe::almost_win(int player){

    // The player positions
    std::vector<std::pair<int, int>> player_pos_list = find_in_matrix(player);
    if (player_pos_list[0].first == -1)
        return std::make_pair(-1, -1);

    int len = player_pos_list.size();
    for (int n = 0; n < len; n++) {
        int player_r = player_pos_list[n].first;
        int player_c = player_pos_list[n].second;


        // Player almost winning on the row
        int s_row = grid[player_r][0] + grid[player_r][1] + grid[player_r][2];
        if (s_row == 2 * player) {
            if (grid[player_r][0] == 0) {
                return std::make_pair(player_r, 0);
            } else if (grid[player_r][1] == 0) {
                return std::make_pair(player_r, 1);
            } else if (grid[player_r][2] == 0) {
                return std::make_pair(player_r, 2);
            }
        }

        // Player almost winning on the column
        int s_col = grid[0][player_c] + grid[1][player_c] + grid[2][player_c];
        if (s_col == 2 * player) {
            if (grid[0][player_c] == 0) {
                return std::make_pair(0, player_c);
            } else if (grid[1][player_c] == 0) {
                return std::make_pair(1, player_c);
            } else if (grid[2][player_c] == 0) {
                return std::make_pair(2, player_c);
            }
        }

        // Player almost winning on the diagonal
        int s_diag = grid[0][0] + grid[1][1] + grid[2][2];
        if (s_diag == 2 * player) {
            if (grid[0][0] == 0) {
                return std::make_pair(0, 0);
            } else if (grid[1][1] == 0) {
                return std::make_pair(1, 1);
            } else if (grid[2][2] == 0) {
                return std::make_pair(2, 2);
            }
        }

        // Player almost winning on the other diagonal
        int s_odiag = grid[0][2] + grid[1][1] + grid[2][0];
        if (s_odiag == 2 * player) {
            if (grid[0][2] == 0) {
                return std::make_pair(0, 2);
            } else if (grid[1][1] == 0) {
                return std::make_pair(1, 1);
            } else if (grid[2][0] == 0) {
                return std::make_pair(2, 0);
            }
        }
    }
    return std::make_pair(-1, -1);
}

/* Defines the computer moves */
bool TicTacToe::computer() {

    /* First objective : win if you can */
    std::pair<int, int> com_pos = almost_win(10);
    int com_r = com_pos.first;
    int com_c = com_pos.second;

    if (com_r != -1 && com_c != -1) {
        grid[com_r][com_c] = 10;
        std::cout << "Computer chose: " << com_c << ", " << com_r << std::endl;
        return true;
    }

    /* Second objective : block the player if he is winning */
    std::pair<int, int> player_almost_pos = almost_win(1);
    int play_almost_r = player_almost_pos.first;
    int play_almost_c = player_almost_pos.second;

    if (play_almost_r != -1 && play_almost_c != -1) {
        grid[play_almost_r][play_almost_c] = 10;
        std::cout << "Computer chose: " << play_almost_c << ", " << play_almost_r << std::endl;
        return true;
    }

    /* Play in the middle, and if you can't, random play */
    if (grid[1][1] == 0) {
        grid[1][1] = 10;
        std::cout << "Computer chose: 1, 1" << std::endl;
    }
    else {
        int rand_r = rand() % 3;
        int rand_c = rand() % 3;

        while (grid[rand_r][rand_c] != 0) {
            rand_r = rand() % 3;
            rand_c = rand() % 3;
        }

        grid[rand_r][rand_c] = 10;
        std::cout << "Computer chose: " << rand_c << ", " << rand_r << std::endl;
    }
    return true;
}

/* Returns 1 when the player is winning, 10 if the computer is winning and 0 if no one is winning */
int TicTacToe::is_winning(){

    // Win on the rows
    for (int r = 0; r < 3; r++){
        if (grid[r][0] == grid[r][1] && grid[r][1] == grid[r][2] && grid[r][0] != 0){
            return grid[r][0];
        }
    }

    // Win on the columns
    for (int c = 0; c < 3; c++){
        if (grid[0][c] == grid[1][c] && grid[1][c] == grid[2][c] && grid[0][c] != 0){
            return grid[0][c];
        }
    }

    // Win on the diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != 0){
        return grid[0][0];
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != 0){
        return grid[0][2];
    }

    return 0;
}

/* Print the grid */
void TicTacToe::print_grid(char p1){
    std::cout << "    0   1   2" << "\n   --- --- ---" << std::endl;
    char p2;
    if (p1 == 'o' || p1 == 'O' || p1 == '0')
        p2 = 'x';
    else
        p2 = 'o';
    for (int r = 0; r < 3; r++){
        std::cout << r << " |";
        for (int c = 0; c < 3; c++){
            if (grid[r][c] == 0){
                std::cout << "  ";
            }
            else if (grid[r][c] == 1){
                std::cout << " " << p1;
            }
            else if (grid[r][c] == 10){
                std::cout << " " << p2;
            }
            std::cout << " |";
        }
        if (r != 2){
            std::cout << "\n   ---+---+---" << std::endl;
        }
    }
    std::cout << "\n   --- --- ---" << std::endl;
}
