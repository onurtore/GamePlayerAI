#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#define HUMANVSMACHINE true
#define MAXIMIZE 1
#define MINIMIZE 0

using namespace std;




//global board
char board[8][8] = {};


//meaningful output
char cols[] = {'a','b','c','d','e','f','g'};
int rows[] = {1,2,3,4,5,6,7};

//value from the alpha beta pruning
int move[3] = {0,0,0};

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
void whoWon();


void player1_move();
void player2_move();
void computer_move();

ostringstream boardSS;
ostringstream possiblemovesSS;
string heuristic_str;
string str;



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
            	cout << setw(4)<< s_board[i][j];
        	}
        cout << '\n';
    	}
	}

    void copy_board(char sboard[8][8]){
        for(int i = 0 ;  i < 7 ; i++){
            for(int j = 0; j < 7 ; j++){
                s_board[i][j] = sboard[i][j];
            }
        }
    }


};


state ai_best_move(board);
vector<state> possibleMoves(state node,char  type);

int main(int argc,char *argv[]){

    char *p,*t;
	

	if(argc < 3 ){
		cout << "More argument needed,<turn limit>, <number_of_piece>\n";
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
    
	
	int i = 1;

	if(HUMANVSMACHINE){
		cout << "Am i the Player 1:";
		cin  >> whoAmI;
		
		if(whoAmI){
			cout << "\n---------------------I am the player1 playing with x---------------------\n";
			enemy_type = 'o';
			my_type = 'x';
		}
		else{
			cout << "---------------------I am the player2 playing with o---------------------\n";
			enemy_type = 'x';
			my_type = 'o';
		}
	}
	

	while(true){
		if(i == turn_limit){
			break;
		}
		player1_move();
		print_board();
		cout << "---------------------------------------------------------------\n";
		player2_move();
		print_board();
		i++;
	}
	

	whoWon();


}

void whoWon(){
	int player1_score = 0;
	int player2_score = 0;
	
		 
	state end_board(board);			
	vector<state> i = possibleMoves(end_board,'x');
	player1_score = i.size();

	state end_board2(board);
	vector<state> i2 = possibleMoves(end_board,'o');
	player2_score = i2.size();
			
	
	if(player1_score > player2_score){
		cout << "player 1 win by " << player1_score  <<  " to " <<  player2_score <<  " possible moves";
	}
	else if(player2_score > player1_score){
		cout << "player 2 win by " <<  player2_score <<  " to " <<  player1_score <<  " possible moves";
	}
	else{
		cout << "Berabere " << player1_score << ' ' << player2_score;  
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
	if(old_pos.size() != 2 ){
		cout << "Wrong position name\n";
		goto restart_move;
	
	}	
	cout << "Choose the new position for " + old_pos + ": ";
    cin >> new_pos; 
	if(new_pos.size() != 2 ){
		cout << "Wrong position name\n";
		goto restart_move;
	
	}
    
	int old_row = old_pos[0] - 'a';
    int old_col = (old_pos[1] - '0') -1;


	
	
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
	cout << "New row is " << new_row;
	cout << "New col is" << new_col << "\n";
	if(new_row > 7 || new_col > 7 || new_row < 0 || new_col < 0){
		cout << "yeni yer yanlis\n";
		goto restart_move;
	}


    board[new_row][new_col] = board[old_row][old_col];
    board[old_row][old_col] = ' ';

    cout << "Player moves the piece at " <<  old_pos + " to " + new_pos + "\n";

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
	if(old_pos.size() != 2){
		cout << "Wrong position name\n";
		goto restart_move;
	}

	
	cout << "Choose the new position for " + old_pos + ": ";
    cin >> new_pos; 
if(new_pos.size() != 2 ){
		cout << "Wrong position name\n";
		goto restart_move;
	
}
	

	int old_row = old_pos[0] - 'a';
    int old_col = (old_pos[1] - '0') -1;

	
	
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

	if(new_row > 7 || new_col > 7 || new_row < 0 || new_col < 0){
		cout << "yeni yer yanlis\n";
		goto restart_move;
	}

	cout << "Player moves the piece at " + old_pos + " to " + new_pos + "\n";
    

    board[new_row][new_col] = board[old_row][old_col];
    board[old_row][old_col] = ' ';
}







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


//work correctly
vector<state> possibleMoves(state node,char  type){

	vector<state> possible_moves;

	for(int i = 0 ; i < 7; i++){
		for(int j = 0 ; j < 7 ; j++){
			if(node.s_board[i][j] == type){
				if((j-1 >= 0 && node.s_board[i][j-1] == ' ' )){
					state new_state(node.s_board);
					new_state.s_board[i][j-1] = new_state.s_board[i][j]; 
					new_state.s_board[i][j] = ' ';
					possible_moves.push_back(new_state);
				}
				if((j+1 <= 7 && node.s_board[i][j+1] == ' ' )){
					state new_state(node.s_board);
					new_state.s_board[i][j+1] = new_state.s_board[i][j];
					new_state.s_board[i][j] = ' '; 
					possible_moves.push_back(new_state);
				}
				if((i-1 >= 0 && node.s_board[i-1][j] == ' ' )){
					state new_state(node.s_board);
					new_state.s_board[i-1][j] = new_state.s_board[i][j];
					new_state.s_board[i][j] = ' ';
					possible_moves.push_back(new_state);
				}
				if((i+1 <= 7 && node.s_board[i+1][j] == ' ' )){
					state new_state(node.s_board);
					new_state.s_board[i+1][j] = new_state.s_board[i][j];
					new_state.s_board[i][j] = ' '; 
					possible_moves.push_back(new_state);
				}
			}
		}
	}
	return possible_moves;
	
}


void print_possible_moves(vector<state> x){
		
		
	for(int i = 0 ; i < x.size(); i++){	
			state y = x[i];

			possiblemovesSS << setw(4) << " ";
				for(int i = 0 ; i < 7 ; i++){
					possiblemovesSS << setw(4) << rows[i];
				}
			possiblemovesSS << '\n';
		
			for(int i = 0 ; i < 7 ; i++){
				possiblemovesSS << setw(4) << cols[i];
				for(int j = 0; j< 7 ; j++){
					possiblemovesSS << setw(4)<< y.s_board[i][j];
				}
				possiblemovesSS <<'\n';

			}
			possiblemovesSS << "\n\n\n";
	}

	ofstream myfile3;
	myfile3.open("possible.txt");
	myfile3 << possiblemovesSS.str();
	myfile3.close();

}









int alphabeta(state node,int depth,int alpha,int beta,int node_type){


	if(depth == 0){
		return heuristic(node);
	}

	int v;


	if(node_type == MAXIMIZE){
		v = -999;
		
		vector<state>  all_moves = possibleMoves(node,my_type);		
		for(int i = 0 ; i < all_moves.size(); i++){
			state child = all_moves[i];
			v = alphabeta(child,depth-1,alpha,beta,MINIMIZE);
			if(v > alpha ){
				alpha = v;
				if(depth == 7){
					ai_best_move.copy_board(child.s_board);
				}
			} 
			if(alpha >= beta) break;			
		}
		return alpha;
	}
	else{
		v = +999;
		
		vector<state>  all_moves = possibleMoves(node,enemy_type);		

		for(int i = 0 ; i < all_moves.size(); i++){
			state child = all_moves[i];
			v = alphabeta(child,depth-1,alpha,beta,MAXIMIZE);
			if(v < beta ) {
				beta = v;
			}
			if(alpha >= beta) break;			
		}
		return beta;
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

void print_move(char initial[8][8] ,char second[8][8] ){

	int x,y;
	int x2,y2;
	bool first_time = true;
	bool change = true;
	for(int i = 0 ; i < 7 ; i ++){
		for(int j = 0 ; j < 7 ; j++){
			if(initial[i][j] != second[i][j]){
				if(!first_time){
					x2 = i;
					y2 = j;
					continue;
				}
				change = false;
				first_time = false;
				x = i;
				y = j;
			}
		}
	}


	if(change == true){
		cout << "No valid move\n";
		exit(1);
	}

	if(board[x][y] == my_type && second[x2][y2] == my_type){
		char row  = x + 'a';
		int col  = y + 1;
		
		char row2 = x2 + 'a';
		int col2 = y2 + 1;

		cout << "Computers move:" << row << col << " to " << row2 << col2 << '\n'; 

	}
	else if ( board[x2][y2] == my_type && second[x][y] == my_type){
		char row  = x + 'a';
		int col  = y + 1;
		
		char row2 = x2 + 'a';
		int col2 = y2 + 1;

		cout << "Computers move:" << row2 << col2 << " to " << row << col << '\n'; 


	}
	else{
		cout << "Computers move invalid move\n";
	}

}



void computer_move(){
	
	state current_state(board);

    int i =  alphabeta(current_state,7,-999,+999,MAXIMIZE);

	print_move(board,ai_best_move.s_board);
	
	for(int i = 0 ; i < 7 ; i++){
		for(int j = 0 ; j < 7 ; j++){
			board[i][j] = ai_best_move.s_board[i][j];
		}
	}

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

	char input[8];
	for(int i = 0 ; i < 7 ; i++){
			cout <<  "Enter first column no:" <<  i << '\n' ;	
			cin.getline(input,sizeof(input));
			for(int j = 0 ; j < 7 ; j++){
				board[i][j] = input[j];
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



