#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define area_without_player 0
#define area_player1 1
#define area_player2 2
#define area_player1_and_player2 3

void Initialization();
void Change_Location_In_Map(int , int , int , int , int , int );
void Free_Location(int , int , int , int , int , int );
void Draw();
int Int_Timer(int );
char Char_Timer();
void Timed_game_mode(int );
void Select_Mode();

typedef struct Player {		//Define Player property
	int row;	//Define Player Position
	int column;
	bool ball;	//To judge whether Player has a ball
	int player_number;
	int shoot_level = 1;	//Record the player's level of shooting skill at that time
};

typedef struct Football {	//Define Football position
	int row;
	int column;
};

typedef struct Football_areas {		//Define Zones property
	bool football;		//To judge whether there is a ball in this area
	int player;			//To judge whether there is a player in this area
};

Player player1;	// Player 1
Player player2; // Player 2
Football_areas Areas[3][5]; // Football field
Football Football_position; // Record Football Location
char map[13][31]; // Screen
int player1_goal = 0, player2_goal = 0;

//	Initialization function:
//	Initialization at the beginning of the game.
void Initialization() {
	Football_position.row = 1;	//Initialize Football position
	Football_position.column = 2;

	player1.ball = true;		//Initialize Player1
	player1.row = 1;
	player1.column = 2;
	player1.player_number = 1;

	player2.ball = false;		//Initialize Player2
	player2.row = 1;
	player2.column = 4;
	player2.player_number = 2;

	Areas[1][0].football = false;
	Areas[1][4].football = false;
	Areas[1][2].football = true;		//Initialize Areas
	Areas[1][2].player = area_player1;
	Areas[1][2].football = false;
	Areas[1][4].player = area_player2;

	for (int i = 0; i < 13; i++)		//Draw the basic Football field
		for (int j = 0; j < 31; j++) {
			if (i % 4 == 0)
				map[i][j] = '-';
			else {
				if (j % 6 == 0)
					map[i][j] = '|';
				else
					map[i][j] = ' ';
			}
		}
}

/*	Player Move function:
	Player move to a new area when the player without football.
	Parameter->player_num:Player number 1 or 2*/
Player move(int player_num) {		//Player move to new area without football
	if (player_num == 1) {
		printf("Input your move direction:");
		char Dir;
		while (1) {
			Dir = Char_Timer();
			printf("\n");
			//The following eight directions are handled
			if (Dir == 'd' || Dir == 'D') {		//Move to right
				if (player1.column + 1 > 4) {		//To judge whether the character has reached the edge
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row][player1.column + 1].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row][player1.column + 1].player = area_player1_and_player2;
						player1.column++;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row][player1.column + 1].player = area_player1;
						player1.column++;
						break;
					}
				}
			}	
			else if (Dir == 'w' || Dir == 'W') {	//Move up
				if (player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row - 1][player1.column].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column].player = area_player1_and_player2;
						player1.row--;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column].player = area_player1;
						player1.row--;
						break;
					}
				}
			}
			else if (Dir == 'a' || Dir == 'A') {	//Move to left
				if (player1.column - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row][player1.column - 1].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row][player1.column - 1].player = area_player1_and_player2;
						player1.column--;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row][player1.column - 1].player = area_player1;
						player1.column--;
						break;
					}
				}
			}
			else if (Dir == 'x' || Dir == 'X') {	//Move to down
				if (player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row + 1][player1.column].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row + 1][player1.column].player = area_player1_and_player2;
						player1.row++;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row + 1][player1.column].player = area_player1;
						player1.row++;
						break;
					}
				}
			}
			else if (Dir == 'e' || Dir == 'E') {	//Move to Top right
				if (player1.column + 1 > 4 || player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row - 1][player1.column + 1].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column + 1].player = area_player1_and_player2;
						player1.row--;
						player1.column++;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column + 1].player = area_player1;
						player1.row--;
						player1.column++;
						break;
					}
				}
			}
			else if (Dir == 'q' || Dir == 'Q') {	//Move to Top left
				if (player1.column - 1 < 0 || player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row - 1][player1.column - 1].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column - 1].player = area_player1_and_player2;
						player1.row--;
						player1.column--;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row - 1][player1.column - 1].player = area_player1;
						player1.row--;
						player1.column--;
						break;
					}
				}
			}
			else if (Dir == 'z' || Dir == 'Z') {	//Move to Down left
				if (player1.column - 1 < 0 || player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					if (Areas[player1.row + 1][player1.column - 1].player == area_player2) {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row + 1][player1.column - 1].player = area_player1_and_player2;
						player1.row++;
						player1.column--;
						break;
					}
					else {
						Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
						Areas[player1.row + 1][player1.column - 1].player = area_player1;
						player1.row++;
						player1.column--;
						break;
					}
				}
			}
			else if (Dir == 'c' || Dir == 'C') {	//Move to Down right
				if (player1.column + 1 > 4 || player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row + 1][player1.column + 1].player == area_player2) {
						Areas[player1.row + 1][player1.column + 1].player = area_player1_and_player2;
					}
					else
						Areas[player1.row + 1][player1.column + 1].player = area_player1;
					player1.row++;
					player1.column++;
					break;
				}
			}
			else if (Dir == 'P') {
				printf("Your turn is over!\n");
				Sleep(1500);
				break;
			}
			else {
				printf("This option is not available!\nplease input again:");
				continue;
			}
		}
		return player1;
	}
	else {		//Player 2 Move action
	printf("Input your move direction:");
	char Dir;
	while (1) {
		//getchar();
		//scanf_s("%c", &Dir, 1);
		Dir = Char_Timer();
		printf("\n");
		if (Dir == 'k' || Dir == 'K') {		//Move to right
			if (player2.column + 1 > 4) {		//To judge whether the character has reached the edge
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row][player2.column + 1].player == area_player1) {
					Areas[player2.row][player2.column + 1].player = area_player1_and_player2;
				}
				else {
					Areas[player2.row][player2.column + 1].player = area_player2;
				}
				player2.column++;
				break;
			}
		}
		else if (Dir == 'i' || Dir == 'I') {	//Move up
			if (player2.row - 1 < 0) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row - 1][player2.column].player == area_player1) {
					Areas[player2.row - 1][player2.column].player = area_player1_and_player2;
				}
				else {
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					Areas[player2.row - 1][player2.column].player = area_player2;
				}
				player2.row--;
				break;
			}
		}
		else if (Dir == 'h' || Dir == 'H') {	//Move to left
			if (player2.column - 1 < 0) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row][player2.column - 1].player == area_player1) {
					Areas[player2.row][player2.column - 1].player = area_player1_and_player2;
				}
				else {
					Areas[player2.row][player2.column - 1].player = area_player2;
				}
				player2.column--;
				break;
			}
		}
		else if (Dir == 'n' || Dir == 'N') {	//Move to down
			if (player2.row + 1 > 2) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row + 1][player2.column].player == area_player1) {
					Areas[player2.row + 1][player2.column].player = area_player1_and_player2;	
				}
				else {
					Areas[player2.row + 1][player2.column].player = area_player2;
				}
				player2.row++;
				break;
			}
		}
		else if (Dir == 'o' || Dir == 'O') {	//Move to Top right
			if (player2.column + 1 > 4 || player2.row - 1 < 0) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row - 1][player2.column + 1].player == area_player1) {
					Areas[player2.row - 1][player2.column + 1].player = area_player1_and_player2;
					
				}
				else {
					Areas[player2.row - 1][player2.column + 1].player = area_player2;
				}
				player2.row--;
				player2.column++;
				break;
			}
		}
		else if (Dir == 'u' || Dir == 'U') {	//Move to Top left
			if (player2.column - 1 < 0 || player2.row - 1 < 0) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row - 1][player2.column - 1].player == area_player1) {
					Areas[player2.row - 1][player2.column - 1].player = area_player1_and_player2;
				}
				else {
					Areas[player2.row - 1][player2.column - 1].player = area_player2;
				}
				player2.row--;
				player2.column--;
				break;
			}
		}
		else if (Dir == 'b' || Dir == 'B') {	//Move to Down left
			if (player2.column - 1 < 0 || player2.row + 1 > 2) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {
				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row + 1][player2.column - 1].player == area_player1) {
					Areas[player2.row + 1][player2.column - 1].player = area_player1_and_player2;
				}
				else {
					Areas[player2.row + 1][player2.column - 1].player = area_player2;
				}
				player2.row++;
				player2.column--;
				break;
			}
		}
		else if (Dir == 'm' || Dir == 'M') {	//Move to Down right
			if (player2.column + 1 > 4 || player2.row + 1 > 2) {
				printf("The character has reached the edge,can't moved!\nplease input again:");
				continue;
			}
			else {

				Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
				if (Areas[player2.row + 1][player2.column + 1].player == area_player1) {
					Areas[player2.row + 1][player2.column + 1].player = area_player1_and_player2;
				}
				else
					Areas[player2.row + 1][player2.column + 1].player = area_player2;
				player2.row++;
				player2.column++;
				break;
			}
		}
		else if (Dir == 'P') {
		printf("Your turn is over!\n");
		Sleep(1500);
		break;
			}
		else {
			printf("This option is not available!\nplease input again:");
			continue;
		}
	}
	return player2;
	}
}

//	Player Dribble function:
//	Player move to a new area when the player have the football.
//	Parameter->player_num:Player number 1 or 2
void dribble(int player_num) {
	if (player_num == 1) {
		printf("Input your move direction:");
		char Dir;
		while (1) {
			//getchar();
			//scanf_s("%c", &Dir, 1);
			Dir = Char_Timer();
			printf("\n");
			if (Dir == 'd' || Dir == 'D') {		//Move to right
				if (player1.column + 1 > 4) {	//To judge whether the character has reached the edge
					printf("The character has reached the edge,can't dribble!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row][player1.column + 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row][player1.column + 1].player == area_player2) {
						Areas[player1.row][player1.column + 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row][player1.column + 1].player = area_player1;
					}
					Football_position.column++;
					player1.column++;
					break;
				}
			}
			else if (Dir == 'w' || Dir == 'W') {	//Move up
				if (player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row - 1][player1.column].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row - 1][player1.column].player == area_player2) {
						Areas[player1.row - 1][player1.column].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row - 1][player1.column].player = area_player1;
					}
					Football_position.row--;
					player1.row--;
					break;
				}
			}
			else if (Dir == 'a' || Dir == 'A') {	//Move to left
				if (player1.column - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row][player1.column - 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row][player1.column - 1].player == area_player2) {
						Areas[player1.row][player1.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row][player1.column - 1].player = area_player1;
					}
					Football_position.column--;
					player1.column--;
					break;
				}
			}
			else if (Dir == 'x' || Dir == 'X') {	//Move to down
				if (player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row + 1][player1.column].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row + 1][player1.column].player == area_player2) {
						Areas[player1.row + 1][player1.column].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row + 1][player1.column].player = area_player1;
					}
					Football_position.row++;
					player1.row++;
					break;
				}
			}
			else if (Dir == 'e' || Dir == 'E') {	//Move to Top right
				if (player1.column + 1 > 4 || player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row - 1][player1.column + 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row - 1][player1.column + 1].player == area_player2) {
						Areas[player1.row - 1][player1.column + 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row - 1][player1.column + 1].player = area_player1;
					}
					Football_position.row--;
					Football_position.column++;
					player1.row--;
					player1.column++;
					break;
				}
			}
			else if (Dir == 'q' || Dir == 'Q') {	//Move to Top left
				if (player1.column - 1 < 0 || player1.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row - 1][player1.column - 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row - 1][player1.column - 1].player == area_player2) {
						Areas[player1.row - 1][player1.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row - 1][player1.column - 1].player = area_player1;
					}
					Football_position.row--;
					Football_position.column--;
					player1.row--;
					player1.column--;
					break;
				}
			}
			else if (Dir == 'z' || Dir == 'Z') {	//Move to Down left
				if (player1.column - 1 < 0 || player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row + 1][player1.column - 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row + 1][player1.column - 1].player == area_player2) {
						Areas[player1.row + 1][player1.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row + 1][player1.column - 1].player = area_player1;
					}
					Football_position.row++;
					Football_position.column--;
					player1.row++;
					player1.column--;
					break;
				}
			}
			else if (Dir == 'c' || Dir == 'C') {	//Move to Down right
				if (player1.column + 1 > 4 || player1.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player1.row][player1.column].football = false;
					Areas[player1.row + 1][player1.column + 1].football = true;
					Areas[player1.row][player1.column].player = area_without_player;	//Change properties after move
					if (Areas[player1.row + 1][player1.column + 1].player == area_player2) {
						Areas[player1.row + 1][player1.column + 1].player = area_player1_and_player2;
					}
					else {
						Areas[player1.row + 1][player1.column + 1].player = area_player1;
					}
					Football_position.row++;
					Football_position.column++;
					player1.row++;
					player1.column++;
					break;
				}
			}
			else if (Dir == 'P') {
			printf("Your turn is over!\n");
			Sleep(1500);
			break;
			}
			else {
				printf("This option is not available!\nplease input again:");
				continue;
			}
		}
	}
	else {		//Player 2 Move action
		printf("Input your move direction:");
		char Dir;
		while (1) {
			//getchar();
			//scanf_s("%c", &Dir, 1);
			Dir = Char_Timer();
			printf("\n");
			if (Dir == 'k' || Dir == 'K') {		//Move to right
				if (player2.column + 1 > 4) {		//To judge whether the character has reached the edge
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row][player2.column + 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row][player2.column + 1].player == area_player1) {
						Areas[player2.row][player2.column + 1].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row][player2.column + 1].player = area_player2;
					}
					Football_position.column++;
					player2.column++;
					break;
				}
			}
			else if (Dir == 'i' || Dir == 'I') {	//Move up
				if (player2.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row - 1][player2.column].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row - 1][player2.column].player == area_player1) {
						Areas[player2.row - 1][player2.column].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
						Areas[player2.row - 1][player2.column].player = area_player2;
					}
					Football_position.row--;
					player2.row--;
					break;
				}
			}
			else if (Dir == 'h' || Dir == 'H') {	//Move to left
				if (player2.column - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row][player2.column - 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row][player2.column - 1].player == area_player1) {
						Areas[player2.row][player2.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row][player2.column - 1].player = area_player2;
					}
					Football_position.column--;
					player2.column--;
					break;
				}
			}
			else if (Dir == 'n' || Dir == 'N') {	//Move to down
				if (player2.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row + 1][player2.column].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row + 1][player2.column].player == area_player1) {
						Areas[player2.row + 1][player2.column].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row + 1][player2.column].player = area_player2;
					}
					Football_position.row++;
					player2.row++;
					break;
				}
			}
			else if (Dir == 'o' || Dir == 'O') {	//Move to Top right
				if (player2.column + 1 > 4 || player2.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row - 1][player2.column + 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row - 1][player2.column + 1].player == area_player1) {
						Areas[player2.row - 1][player2.column + 1].player = area_player1_and_player2;

					}
					else {
						Areas[player2.row - 1][player2.column + 1].player = area_player2;
					}
					Football_position.row--;
					Football_position.column++;
					player2.row--;
					player2.column++;
					break;
				}
			}
			else if (Dir == 'u' || Dir == 'U') {	//Move to Top left
				if (player2.column - 1 < 0 || player2.row - 1 < 0) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row - 1][player2.column - 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row - 1][player2.column - 1].player == area_player1) {
						Areas[player2.row - 1][player2.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row - 1][player2.column - 1].player = area_player2;
					}
					Football_position.row--;
					Football_position.column--;
					player2.row--;
					player2.column--;
					break;
				}
			}
			else if (Dir == 'b' || Dir == 'B') {	//Move to Down left
				if (player2.column - 1 < 0 || player2.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row + 1][player2.column - 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row + 1][player2.column - 1].player == area_player1) {
						Areas[player2.row + 1][player2.column - 1].player = area_player1_and_player2;
					}
					else {
						Areas[player2.row + 1][player2.column - 1].player = area_player2;
					}
					Football_position.row++;
					Football_position.column--;
					player2.row++;
					player2.column--;
					break;
				}
			}
			else if (Dir == 'm' || Dir == 'M') {	//Move to Down right
				if (player2.column + 1 > 4 || player2.row + 1 > 2) {
					printf("The character has reached the edge,can't moved!\nplease input again:");
					continue;
				}
				else {
					Areas[player2.row][player2.column].football = false;
					Areas[player2.row + 1][player2.column + 1].football = true;
					Areas[player2.row][player2.column].player = area_without_player;	//Change properties after move
					if (Areas[player2.row + 1][player2.column + 1].player == area_player1) {
						Areas[player2.row + 1][player2.column + 1].player = area_player1_and_player2;
					}
					else
						Areas[player2.row + 1][player2.column + 1].player = area_player2;
					Football_position.row++;
					Football_position.column++;
					player2.row++;
					player2.column++;
					break;
				}
			}
			else if (Dir == 'P') {
			printf("Your turn is over!\n");
			Sleep(1500);
			break;
			}
			else {
				printf("This option is not available!\nplease input again:");
				continue;
			}
		}
	}
}

/*	Player Shoot function:
	Make the ball fall into the corresponding area randomly.
	(Increase the probability of shooting into the door according to different shooting skill levels)
	Parameter->player_num:Player number 1 or 2*/
void shoot(int player_num) {
	srand((unsigned)time(NULL));
	if (player_num == 1) {	//Player 1
		int new_ball_pos_r;	
		int new_ball_pos_c;
		if (player1.shoot_level == 1) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
		}
		else if (player1.shoot_level == 2) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
			if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {	//shoot again(increase the probability of shooting)
				printf("calculating....\n");
				Sleep(1000);
				srand((unsigned)time(NULL));
				new_ball_pos_r = rand() % 3;	//Football's new position
				new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
			}
		}
		else if (player1.shoot_level == 3) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
			if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {//shoot again(increase the probability of shooting)
				printf("calculating....\n");
				Sleep(1000);
				srand((unsigned)time(NULL));
				new_ball_pos_r = rand() % 3;	//Football's new position
				new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
				if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {
					printf("calculating....\n");
					Sleep(1000);
					srand((unsigned)time(NULL));
					new_ball_pos_r = rand() % 3;	//Football's new position
					new_ball_pos_c = rand() % (4 - (player1.column + 1) + 1) + player1.column + 1;
				}
			}
		}
		player1.ball = false;	//Change properties of each object after shoot
		Areas[player1.row][player1.column].football = false;
		Areas[new_ball_pos_r][new_ball_pos_c].football = true;
		Football_position.row = new_ball_pos_r;
		Football_position.column = new_ball_pos_c;
	}
	else {
		int new_ball_pos_r;
		int new_ball_pos_c;
		if (player2.shoot_level == 1) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % player2.column;
		}
		else if (player2.shoot_level == 2) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % player2.column;
			if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {//shoot again(increase the probability of shooting)
				printf("calculating....\n");
				Sleep(1000);
				srand((unsigned)time(NULL));
				new_ball_pos_r = rand() % 3;	//Football's new position
				new_ball_pos_c = rand() % player2.column;
			}
		}
		else if (player2.shoot_level == 3) {
			 new_ball_pos_r = rand() % 3;	//Football's new position
			 new_ball_pos_c = rand() % player2.column;
			if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {//shoot again(increase the probability of shooting)
				printf("calculating....\n");
				Sleep(1000);
				srand((unsigned)time(NULL));
				new_ball_pos_r = rand() % 3;	//Football's new position
				new_ball_pos_c = rand() % player2.column;
				if (new_ball_pos_r != 1 && new_ball_pos_c != 4) {//shoot again(increase the probability of shooting)
					printf("calculating....\n");
					Sleep(1000);
					srand((unsigned)time(NULL));
					new_ball_pos_r = rand() % 3;	//Football's new position
					new_ball_pos_c = rand() % player2.column;
				}
			}
		}
		player2.ball = false;	//Change properties of each object after shoot
		Areas[player2.row][player2.column].football = false;
		Areas[new_ball_pos_r][new_ball_pos_c].football = true;
		Football_position.row = new_ball_pos_r;
		Football_position.column = new_ball_pos_c;
	}
}

/*	Player action function:
	Execute the corresponding instructions according to whether the player carries the ball or not.
	Parameter->player_num:Player number 1 or 2
			 ->ball_status:Player whether have the football*/
void Action(int player_num, bool ball_status) {
	printf("Current player 1's position:(%d,%d)\n", player1.row, player1.column);
	printf("Current player 2's position:(%d,%d)\n", player2.row, player2.column);
	Change_Location_In_Map(player1.row, player1.column, player2.row, player2.column, Football_position.row, Football_position.column);
	Draw();
	Free_Location(player1.row, player1.column, player2.row, player2.column, Football_position.row, Football_position.column);
	printf("Player%d's Action\n", player_num);
	if (ball_status == true) {	//To judge whether player has a ball
		int order = 0;
		printf("1:dribble \n2:shoot\nInput your order");
		//scanf_s("%d", &order);
		order = Int_Timer(order);
		while (true) {
			if (order == 1 || order == 2) {		//Execute the corresponding action according to player's order
				if (order == 1) {
					dribble(player_num);
					if (player_num == 1) {
						printf("player 1 position: (%d,%d)\n", player1.row, player1.column);
						//Process the player with the ball to move to another player area
						if (Areas[player1.row][player1.column].player == area_player1_and_player2) {
							player2.ball = true;	//Exchange Right of use of ball
							player1.ball = false;
							system("cls");
							Action(2, player2.ball); //Get extra Action
						}
					}
					else {
						printf("player 2 position: (%d,%d)\n", player2.row, player2.column);
						if (Areas[player2.row][player2.column].player == area_player1_and_player2) {
							player1.ball = true;	//Exchange Right of use of ball
							player2.ball = false;
							system("cls");
							Action(1, player1.ball); //Get extra Action
						}
					}
				}
				else {
					shoot(player_num);
					if (player_num == 1) {	//The situation of kick the ball to the opponent's feet
						if (Areas[player2.row][player2.column].football == true) {
							player2.ball = true;
							system("cls");
							Action(2, player2.ball); //Get extra Action
						}
					}
					if (player_num == 2) {
						if (Areas[player1.row][player1.column].football == true) {
							player1.ball = true;
							system("cls");
							Action(1, player1.ball); //Get extra Action
						}
					}
					printf("Football position: (%d,%d)\n", Football_position.row, Football_position.column);
				}
				break;
			}
			else if (order == -1) {		//Time is over, Current player's turn passed.
				printf("Your turn is over!\n");
				Sleep(1500);
				break;
			}
			else {
				printf("Input error order,please input again!\nInput your order:");
				getchar();
				scanf_s("%d", &order);
			}
		}
	}
	else {	//The situation of the player has no ball
		Player TempPlayer = move(player_num);
		if (TempPlayer.row == Football_position.row && TempPlayer.column == Football_position.column) {	//The situation of grabbing the ball
			if (Areas[TempPlayer.row][TempPlayer.column].player == area_player1_and_player2) {
				if (player_num == 1) {	//Player1 grabbing the ball
					player1.ball = true;
					player2.ball = false;
					system("cls");
					Action(1, player1.ball);	//Get extra Action
				}
				else {
					player2.ball = true;	//Player2 grabbing the ball
					player1.ball = false;
					system("cls");
					Action(2, player2.ball);
				}
			}
			else {
				if (player_num == 1) {	//Player1 Pick up the ball
					player1.ball = true;
					system("cls");
					Action(1, player1.ball);	//Get extra Action
				}
				else {
					player2.ball = true;	//Player2 Pick up the ball
					system("cls");
					Action(2, player2.ball);
				}
			}
		}
	}
}

/*	Change_Location_In_Map function:Mapping the coordinates of players and football to the map.
	Parameter->player1_x,player1_y:Coordination of Player 1
			 ->player2_x,player2_y:Coordination of Player 2
			 ->ball_x,ball_y:Coordination of Football*/
void Change_Location_In_Map(int player1_x, int player1_y, int player2_x, int player2_y, int ball_x, int ball_y) {
	map[4 * player1_x + 2][6 * player1_y + 1] = '1';
	map[4 * player2_x + 2][6 * player2_y + 5] = '2';
	map[4 * ball_x + 2][6 * ball_y + 3] = 'O';
}

/*	Free_Location function:Release transformed coordinates,prepare for the next drawing.
	Parameter->player1_x,player1_y:Coordinate of Player 1
			 ->player2_x,player2_y:Coordinate of Player 2
			 ->ball_x,ball_y:Coordinate of Football*/
void Free_Location(int player1_x, int player1_y, int player2_x, int player2_y, int ball_x, int ball_y) {
	map[4 * player1_x + 2][6 * player1_y + 1] = ' ';
	map[4 * player2_x + 2][6 * player2_y + 5] = ' ';
	map[4 * ball_x + 2][6 * ball_y + 3] = ' ';
}

//	Draw function: Draw the game screen.
void Draw() {
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 32; j++) {
			if (j < 31)
				printf("%c", map[i][j]);
			else {
				printf("    |");
			}
		}
		if (i == 1) {
			printf("Player 1's arrow keys: q w e	Player 2's arrow keys: u i o");}
		else if (i == 2) {
			printf("                       a   d	                       h   l");
		}
		else if (i == 3) {
			printf("                       z x c	                       b n m");
		}
		else if (i == 5) { printf("Player 1's score:%d	Player 2's score:%d", player1_goal, player2_goal); }
		else if (i == 7) { printf("Player 1's Shoot Level:%d	Player 2's Shoot Level:%d", player1.shoot_level, player2.shoot_level); }

		printf("\n");
	}
	printf("\n");
}

//  Int_Timer function: Count down to five seconds(The return value is of type int).
//  Parameter->Ord:Dribble or Shoot
int Int_Timer(int Ord) {
	time_t t1, t2;
	int i, tag = 1; //Set a tag
	printf("(Wait 5 seconds for the Player to enter, and the round is automatically skipped£¡):\n");
	time(&t1); //Record current time
	while (!_kbhit()){
		//Record the current time t2 compared with t1, if the difference of 5 change the tag value, make it skip input!
		time(&t2); 
		if ((int)(t2 - t1) == 1) { printf("\r"); printf("You have 4 second left"); }
		if ((int)(t2 - t1) == 2) { printf("\r"); printf("You have 3 second left"); }
		if ((int)(t2 - t1) == 3) { printf("\r"); printf("You have 2 second left"); }
		if ((int)(t2 - t1) == 4) { printf("\r"); printf("You have 1 second left"); }
		if ((int)(t2 - t1) > 5)
		{
			printf("\nEnd of the time£¡\n");
			tag = 0;
			return -1;
		}
	}
	if (tag)
	{
		scanf_s("%d", &Ord);
		printf("Your order is %d\n", Ord);
	}
	return Ord;
}

//  Char_Timer function: Count down to five seconds(The return value is of type char).
char Char_Timer() {
	char Dir;
	time_t t1, t2;
	int i, tag = 1; //Set a tag
	printf("(Wait 5 seconds for the Player to enter, and the round is automatically skipped£¡):\n");
	time(&t1); //Record current time
	while (!_kbhit()) {
		//Record the current time t2 compared with t1, if the difference of 5 change the tag value, make it skip input!
		time(&t2);
		if ((int)(t2 - t1) == 1) { printf("\r"); printf("You have 4 second left"); }
		if ((int)(t2 - t1) == 2) { printf("\r"); printf("You have 3 second left"); }
		if ((int)(t2 - t1) == 3) { printf("\r"); printf("You have 2 second left"); }
		if ((int)(t2 - t1) == 4) { printf("\r"); printf("You have 1 second left"); }
		if ((int)(t2 - t1) > 5)
		{
			printf("\nEnd of the time£¡\n");
			tag = 0;
			return 'P';
		}
	}
	if (tag)
	{
		Dir = _getch();
		printf("Your direction is %d\n", Dir);
	}
	return Dir;
}

//  Timed_game_mode function: In 2-minute timing mode, the winner with more goals.
//  Parameter->Time_limit: Countdown, the time is 0 to end the game
void Timed_game_mode(int Time_limit) {
	time_t t1, t2;
	time(&t1);
	while (1) {
		time(&t2);
		if ((int)(t2 - t1) <= 1) { printf("\r"); printf("You have 2 minutes left\n"); }
		if ((int)(t2 - t1) == 30) { printf("\r"); printf("You have 1 and half minutes left\n"); }
		if ((int)(t2 - t1) == 60) { printf("\r"); printf("You have 1 minute left\n"); }
		if ((int)(t2 - t1) == 90) { printf("\r"); printf("You have 30 second left\n"); }
		if ((int)(t2 - t1) >= Time_limit) {
			printf("Time is over!\n");
			if (player1_goal > player2_goal) { printf("Player 1 Wins!!!\n"); break; }
			else if (player1_goal < player2_goal) { printf("Player 2 Wins!!!\n"); break; }
			else {
				printf("\n30 seconds overtime!\n");
				Sleep(1500);
				Timed_game_mode(30);
				break;
			}
		}
		Action(1, player1.ball);	//Player 1's round
		if (Areas[1][4].football == true) {
			printf("Player 1 gets 1 point!!\n");
			player1_goal++;
			if (player1.shoot_level < 3)	//Increase skill level after goal
				player1.shoot_level++;
			Sleep(2000);
			Initialization();	//Strat a new game
			system("cls");
		}
		else system("cls");

		Action(2, player2.ball);	//Player 2's round
		if (Areas[1][0].football == true) {
			printf("Player 2 gets 1 point!!\n");
			player2_goal++;
			if (player2.shoot_level < 3)	//Increase skill level after goal
				player2.shoot_level++;
			Sleep(2000);
			Initialization();
			system("cls");
		}
		else system("cls");
	}
}

//	Scoring_game_mode function: Three points first to win the game
void Scoring_game_mode() {
	while (1) {
		Action(1, player1.ball);	//Player 1's round
		if (Areas[1][4].football == true) {
			printf("Player 1 gets 1 point!!\n");
			player1_goal++;
			if (player1.shoot_level < 3)	//Increase skill level after goal
				player1.shoot_level++;
			Sleep(2000);
			Initialization();
			system("cls");
		}
		else system("cls");

		if (player1_goal == 3) {
			printf("Player 1 Wins!!!\n"); break;
		}
		if (player2_goal == 3) {
			printf("Player 2 Wins!!!\n"); break;
		}

		Action(2, player2.ball);	//Player 2's round
		if (Areas[1][0].football == true) {
			printf("Player 2 gets 1 point!!\n");
			player2_goal++;
			if (player2.shoot_level < 3)	//Increase skill level after goal
				player2.shoot_level++;
			Sleep(2000);
			Initialization();
			system("cls");
		}
		else system("cls");

		if (player1_goal == 3) {
			printf("Player 1 Wins!!!\n"); break;
		}
		if (player2_goal == 3) {
			printf("Player 2 Wins!!!\n"); break;
		}
	}
	
}

// Select_Mode function: Select to the one of two games mode.
void Select_Mode() {
	Draw();
	printf("	>TIMED_GAME_MODE\n");
	printf("	 SCORING_GAME_MODE\n");
	int flag = 0;
	while (1) {
		char m = _getche();
		if (m == 80) {
			system("cls");
			Draw();
			printf("	 TIMED_GAME_MODE\n");
			printf("	>SCORING_GAME_MODE\n");
			flag = 0;
		}
		if (m == 72) {
			system("cls");
			Draw();
			printf("	>TIMED_GAME_MODE\n");
			printf("	 SCORING_GAME_MODE\n");
			flag = 1;
		}
		if (m == '\r') {
			if (flag == 1) {
				system("cls");
				Timed_game_mode(120);
				break;
			}
			else {
				system("cls");
				Scoring_game_mode();
				break;
			}
		}
	}
}

int main() {
	Initialization(); //Initialize all properties
	Draw();
	printf("	>START GAME(ENTER)");
	while (1) {
		char start = _getche();
		if (start == '\r') break;
		else continue;
	}
	system("cls");
	Select_Mode();
	return 0;
}