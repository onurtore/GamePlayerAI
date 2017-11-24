#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <cstring>

#define HumanVSComputer false
#define MAXIMIZE 1
#define MINIMIZE 0

using namespace std;




char board[8][8] = {};
char new_board[8][8] = {};
char cols[] = {'a','b','c','d','e','f','g'};
char enemy_type;

int rows[] = {1,2,3,4,5,6,7};
int *player1a_rocks;
int *player1b_rocks;
int *player2a_rocks;
int *player2b_rocks;
int *computer1a_rocks;
int *computer1b_rocks;
int number_of_piece;

void computer_move();
void print_board();
void getInitial_POS();
void move();
void findSuccessors(int x,int y);
void get_move();
void move_board(string,string);
void player1_move();
void player2_move();
void create_Initial_POS(int);

int left[2] = {0,-1};
int right[2] = {0,1};
int up[2]    = {-1,0};
int down[2]  = {1,0};


bool whoAmI;

int main(int argc,char *argv[]){

    char *p,*t;
	
	
	if(argc < 3 ){
		cout << "More argument needed\n";
		return 42;
	}


	int  turn_limit =  strtol(argv[1], &p, 10);
	number_of_piece = strtol(argv[2], &p, 10);
	
    

	
	
    print_board();
	create_Initial_POS(number_of_piece);
	//	getInitial_POS(); //Elle girmek gerekirse
    cout << "\n\n\n";
	print_board();
	cout << "\n\n\n";
	cout << "\nPlayer1 is X, Player2 is O\n\n";
    	
	
	if(HumanVSComputer){
		cout << "Am i the Player 1";
		cin >> whoAmI;
		if(whoAmI){
			cout << "I am the player 1 play with x\n";
			enemy_type = 'o';
		}
		else{
			cout << "I am the player 2 play with o\n";
			enemy_type = 'x';
		}
	}
	

	while(true){
		player1_move();
		print_board();
	
		player2_move();
		print_board();
	}
	

}


void player1_move(){
	
	if(HumanVSComputer){
		if(whoAmI){
			return computer_move();
		}
	}
	
	restart_move:
	
	string old_pos,new_pos;
	cout<< "Player1(X)'s turn:\n";
	cout << "Choose piece to move: ";
	cin >> old_pos;
	cout << "Choose the new position for " + old_pos + ": ";
    cin >> new_pos; 
    cout << "Player moves the piece at " + old_pos + " to " + new_pos + "\n";
    
	int old_row = old_pos[0] - 'a';
    int old_col = (old_pos[1] - '0') -1;

	cout << "col is: " << old_col << "row is: "<< old_row << '\n';
	
	
	if(old_row > 7 || old_col > 7 || old_row < 0 || old_col < 0){
		cout << "Oyle bir koordinat yok\n";
		goto restart_move;
	}
	
	if(board[old_row][old_col] != 'x'){
		cout << "O tas senin degil\n";
		goto restart_move;
	}
	
	
    int new_row = new_pos[0] - 'a';
    int new_col = (new_pos[1] - '0')-1;

    board[new_row][new_col] = board[old_row][old_col];
    board[old_row][old_col] = ' ';




}

void player2_move(){
	
	if(HumanVSComputer){
		if(!whoAmI){
			return computer_move();
		}
	}
	
	restart_move:
	
	string old_pos,new_pos;
	cout<< "Player2(O)'s turn:\n";
	cout << "Choose piece to move: ";
	cin >> old_pos;
	cout << "Choose the new position for " + old_pos + ": ";
    cin >> new_pos; 
    cout << "Player moves the piece at " + old_pos + " to " + new_pos + "\n";
    
	int old_row = old_pos[0] - 'a';
    int old_col = (old_pos[1] - '0') -1;

	cout << "col is: " << old_col << "row is: "<< old_row << '\n';
	
	
	if(old_row > 7 || old_col > 7 || old_row < 0 || old_col < 0){
		cout << "Oyle bir koordinat yok\n";
		goto restart_move;
	}
	
	if(board[old_row][old_col] != 'o'){
		cout << "O tas senin degil\n";
		goto restart_move;
	}
	
	
    int new_row = new_pos[0] - 'a';
    int new_col = (new_pos[1] - '0')-1;

    board[new_row][new_col] = board[old_row][old_col];
    board[old_row][old_col] = ' ';
}


class state {

public:

	char s_board[8][8];
	int val;
	
	state(char o_board[8][8]){
		for(int i = 0 ; i < 7; i ++){
			for(int j = 0; j < 7 ; j++ ){
				s_board[i][j] = o_board[i][j];
			}
		}	
	}

	void print_board(){
		cout << setw(4) << " ";
			for(int i = 0 ; i < 7 ; i++){
				cout << setw(4) << rows[i];
			}
		cout << '\n';
	
    	for(int i = 0 ; i < 7 ; i++){
			cout << setw(4) << cols[i];
			for(int j = 0; j< 7 ; j++){
            	cout << setw(4)<< board[i][j];
        	}
        cout << '\n';
    	}
	}
};

int heuristic(state node);

int alphabeta(state node,int depth,int alpha,int beta,int node_type){

	if(depth == 0){
		return heuristic(node);
	}

	int v = 0;


	if(node_type == MAXIMIZE){
		v = -999;

		

		//for every taş,create successors,look for left right down up,create new node ,then apply same function.
		for(int i = 0 ; i < 7 ; i++){

			
			//go left

			//go right

			//go up

			//go down
		}
		/*	
		
		*/
	}

	else{

	}
}



void computer_move(){
	
	state current_state(board);
	
	int i = alphabeta(current_state,10,-999,+999,MAXIMIZE);

}

/*
	for(int i = 0 ; i < 3;i ++){
		//left
		//is valid  and empty pos
		if( (!(col - 1 < 0))  && board[row][col-1] == ' ' ) {
			//left successor
			new_board[row][col-1] = new_board[row][col];
			new_board[row][col] = ' ';
			max = evalue_pos(new_board);
			if(max > move_arr[0]){
				move_arr[0] = max;
				move_arr[1] = row;
				move_arr[2] = col;
				move_arr[3] = row;
				move_arr[4] = col-1;
			}
		}
		new_board = board;
		//right
		//is valid  and empty pos
		if( (!(col + 1 > 7)) && board[row][col+1] == ' '){
			//right succesor
			new_board[row][col+1] = new_board[row][col];
			new_board[row][col] = ' ';
			max = evalue_pos(new_board);
			if(max > move_arr[0]){
				move_arr[0] = max;
				move_arr[1] = row;
				move_arr[2] = col;
				move_arr[3] = row;
				move_arr[4] = col+1;
			}
		}
		new_board = board;
		//up
		//is valid  and empty pos
		if((!(row -1 < 0 )) && board[row-1][col] == ' '  ){
			//up successor
			new_board[row-1][col] = new_board[row][col];
			new_board[row][col] = ' ';
			max = evalue_pos(new_board);
			if(max > move_arr[0]){
				move_arr[0] = max;
				move_arr[1] = row;
				move_arr[2] = col;
				move_arr[3] = row-1;
				move_arr[4] = col;
			}
		}
		new_board = board;
		//down
		//is valid  and empty pos
		if( (!(row + 1 > 7)) && board[row+1][col] == ' ' ){
			//down successor
			new_board[row+1][col] = new_board[row][col];
			new_board[row][col] = ' ';
			max = evalue_pos(new_board);
			if(max > move_arr[0]){
				move_arr[0] = max;
				move_arr[1] = row;
				move_arr[2] = col;
				move_arr[3] = row+1;
				move_arr[4] = col;
			}
		}
		new_board = board;
	}
	return move_arr;
}
*/
/*
int evaluate_pos(){

	/*
	int left[2] = {0,-1};
	int right[2] = {0,1};
	int up[2]    = {-1,0};
	int down[2]  = {1,0};


	*/
	
/*
	for(int i = 0 ; i < 7 ; i++){
		for(int j = 0; j < 7 ; j++){
			if(new_board[i][j] == enemy_type){
					if(isValid(i,j);
			}
		
		}
		
	}
}
*/


//is new position is a valid position
bool isValid(int i, int j ){
	return ((new_board[i][j] == ' ') && (i <= 7) && (j <= 7) && (i >= 0) && (j >= 0)); 
}



//print the board
void print_board(){
	
	cout << setw(4) << " ";
	for(int i = 0 ; i < 7 ; i++){
		cout << setw(4) << rows[i];
	}
	cout << '\n';
	
	
    for(int i = 0 ; i < 7 ; i++){
		cout << setw(4) << cols[i];
		for(int j = 0; j< 7 ; j++){
            cout << setw(4)<< board[i][j];
        }
        cout << '\n';
    }
}


//Create initial pos manual
void getInitial_POS(){
	
	char p;
	for(int i = 0 ; i < 7 ; i++){
    	for(int j = 0; j< 7 ; j++){
			cout <<  "Enter value for " << cols[i] << rows[j] << ":";
			cin >> p;
			board[i][j] = p;
        }
    }
}



//Create initial random position
void create_Initial_POS(int number_of_piece){
	
	int player1_counter = 0;
	int player2_counter = 0;
	int random_number;
		
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 7 ; j++){
			board[i][j] = ' ';
		}
	}
	srand(time(NULL));
	while( (player1_counter + player2_counter  ) < (2* number_of_piece)  ){
	
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				random_number = rand() % 2 + 0;

				if(random_number == 1 && (board[i][j] == ' ') ){
						random_number = rand() % 2 + 0;
						if(random_number == 0 && ( player1_counter < number_of_piece) ){
								board[i][j] = 'x';
								player1_counter++;
						}
						else if(random_number == 1 && ( player2_counter < number_of_piece ) ){
								board[i][j] = 'o';
								player2_counter++;
						}
				}
			}
		}
	}
}