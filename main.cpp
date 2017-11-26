#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>

#define HUMANVSMACHINE true
#define MAXIMIZE 1
#define MINIMIZE 0

using namespace std;

//global board
char board[8][8] = {};

//meaningful output
char cols[] = {'a','b','c','d','e','f','g'};
int rows[] = {1,2,3,4,5,6,7};

//o or x
bool whoAmI;
char enemy_type;
char my_type;

//command line arguments
int number_of_piece;
int turn_limit;

void getInitial_POS();
void create_Initial_POS(int);
void print_board();



void player1_move();
void player2_move();
void computer_move();

ostringstream boardSS;
string heuristic_str;
string str;

int main(int argc,char *argv[]){

    char *p,*t;
	
	if(argc < 3 ){
		cout << "More argument needed\n";
		return 42;
	}

	turn_limit =  strtol(argv[1], &p, 10);
	number_of_piece = strtol(argv[2], &p, 10);
	
	//Print initial board
    print_board();

	//Create a random position
	create_Initial_POS(number_of_piece);
		//getInitial_POS();
    
	print_board();
	
	cout << "Player1 is X, Player2 is O\n\n";
    
	
	if(HUMANVSMACHINE){
		cout << "Am i the Player 1:";
		cin  >> whoAmI;
		if(whoAmI){
			cout << "\nI am the player1 play with x\n";
			enemy_type = 'o';
			my_type = 'x';
		}
		else{
			cout << "I am the player2 play with o\n";
			enemy_type = 'x';
			my_type = 'o';
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
	
	if(HUMANVSMACHINE){
		if(whoAmI){
			cout << "My Turn(Player1)\n";
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
	
	if(HUMANVSMACHINE){
		if(!whoAmI){
			cout << "My turn(Player2)\n";
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


  std::string NumberToString ( int Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

int heuristic(state node){


	int val = 0;

	for(int i = 0; i < 7;i++){
		for(int j = 0; j < 7 ; j++){
			if(node.s_board[i][j] == enemy_type){

				if(! (j-1 >= 0 && node.s_board[i][j-1] == ' ' ) ){
					val = val + 5;
				}
				if(! (j+1 <= 7 && node.s_board[i][j+1] == ' ' )){
					val = val + 5;
				}
				if(! (i-1 >= 0 && node.s_board[i-1][j] == ' ' )){
					val = val + 5;
				}
				if(! (i+1 <= 7 && node.s_board[i+1][j] == ' ' )){
					val = val + 5;
				}
			}
		}
	}
	

	heuristic_str += NumberToString(val) + ',';
	return val;
	
}

int max(int x,int y){
	if(x >= y){
		return x;
	}
	else{
		return y;
	}
}

int min(int x,int y){
	if(x >= y){
		return y;
	}
	else{
		return x;
	}
}


void print_state(state node){
	
	
		boardSS << setw(4) << " ";
			for(int i = 0 ; i < 7 ; i++){
				boardSS << setw(4) << rows[i];
			}
		boardSS << '\n';
	
    	for(int i = 0 ; i < 7 ; i++){
			boardSS << setw(4) << cols[i];
			for(int j = 0; j< 7 ; j++){
            	boardSS << setw(4)<< node.s_board[i][j];
			}
			boardSS <<'\n';

    	}
        boardSS << "\n\n\n";
}


int alphabeta(state node,int depth,int alpha,int beta,int node_type){

	//print_state(node);

	if(depth == 0){
		return heuristic(node);
	}

	int v = 0;


	if(node_type == MAXIMIZE){
		v = -999;

		

		//for every taş,create successors,look for left right down up,create new node ,then apply same function.
		for(int i = 0 ; i < 7 ; i++){
			for(int  j = 0  ; j < 7 ; j ++){
				if(node.s_board[i][j] == my_type){
					if((j-1 >= 0 && node.s_board[i][j-1] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i][j-1] = new_state.s_board[i][j]; 
						new_state.s_board[i][j] = ' '; 
						v = max(v,alphabeta(new_state,depth-1,alpha,beta,MINIMIZE));
						if( v >= beta){
							str += "beta pruning\n";
							return v;
						}
						alpha = max(alpha,v);
					}
					if((j+1 <= 7 && node.s_board[i][j+1] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i][j+1] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' '; 
						v = max(v,alphabeta(new_state,depth-1,alpha,beta,MINIMIZE));
						if( v >= beta){
							str += "beta pruning\n";
							return v;
						}
						alpha = max(alpha,v);
						
					}
					if((i-1 >= 0 && node.s_board[i-1][j] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i-1][j] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' ';
						v = max(v,alphabeta(new_state,depth-1,alpha,beta,MINIMIZE));
						if( v >= beta){
							str += "beta pruning\n";
							return v;
						}
						alpha = max(alpha,v);
					}
					if((i+1 <= 7 && node.s_board[i+1][j] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i+1][j] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' '; 
						v = max(v,alphabeta(new_state,depth-1,alpha,beta,MINIMIZE));
						if( v >= beta){
							str += "beta pruning\n";
							return v;
						}
						alpha = max(alpha,v);
					}
				}

			}
		}
		str += "no pruning\n";
		return v;

			
	}

	else{
		v = +999;

		//for every taş,create successors,look for left right down up,create new node ,then apply same function.
		for(int i = 0 ; i < 7 ; i++){
			for(int  j = 0  ; j < 7 ; j ++){
				if(node.s_board[i][j] == enemy_type){
					if((j-1 >= 0 && node.s_board[i][j-1] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i][j-1] = new_state.s_board[i][j]; 
						new_state.s_board[i][j] = ' '; 
						v = min(v,alphabeta(new_state,depth-1,alpha,beta,MAXIMIZE));
						if( v <= alpha){
							str += "alpha pruning\n";
							return v;
						}
						beta = min(beta,v);
					}
					if((j+1 <= 7 && node.s_board[i][j+1] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i][j+1] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' '; 
						v = min(v,alphabeta(new_state,depth-1,alpha,beta,MAXIMIZE));
						if( v <= alpha){
							str += "alpha pruning\n";
							return v;
						}
						beta = min(beta,v);
						
					}
					if((i-1 >= 0 && node.s_board[i-1][j] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i-1][j] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' ';
						v = min(v,alphabeta(new_state,depth-1,alpha,beta,MAXIMIZE));
						if( v <= alpha){
							str += "alpha pruning\n";
							return v;
						}
						beta = min(beta,v);
					}
					if((i+1 <= 7 && node.s_board[i+1][j] == ' ' )){
						state new_state(node.s_board);
						new_state.s_board[i+1][j] = new_state.s_board[i][j];
						new_state.s_board[i][j] = ' '; 
						v = min(v,alphabeta(new_state,depth-1,alpha,beta,MAXIMIZE));
						if( v <= alpha){
							str += "alpha pruning\n";
							return v;
						}
						beta = min(beta,v);

					}
				}

			}
		}
		str += "no pruning\n";
		return v;
	}
}

void writeStrToFile(){
	
	ofstream myfile;
	myfile.open ("output.txt");
	myfile << str;
	myfile.close();
	

	ofstream myfile2;
	myfile2.open("str_output.txt");
	myfile2 << heuristic_str;
	myfile2.close();

	ofstream myfile3;
	myfile3.open("board_output.txt");
	myfile3 << boardSS.str();
	myfile3.close();


}


void computer_move(){
	
	state current_state(board);

//	int alphabeta(state node,int depth,int alpha,int beta,int node_type)
	int i = alphabeta(current_state,9,-999,+999,MAXIMIZE);

	writeStrToFile();

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



