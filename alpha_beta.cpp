#include <iostream>
#include <vector>

using namespace std;


class state{

public:
    int val;
    vector<state*> childs;

    state(int val = 0){
        this->val = val;
    }
};





int alphabeta(state * node,int alpha,int beta,int node_type){


	if(node->childs.size() == 0 ){
		return node->val;
	}

	int v;


	if(node_type == 1){
		v = -999;
		
		for(int i = 0 ; i < node->childs.size(); i++){
			state * child = node->childs.at(i); 

			v = alphabeta(child,alpha,beta,-1);
			if(v > alpha ){
				alpha = v;
			} 
			if(alpha >= beta) break;			
		}
		return alpha;
	}
	else{
		v = +999;
		
		for(int i = 0 ; i < node->childs.size(); i++){
			state * child = node->childs.at(i); 
			v = alphabeta(child,alpha,beta,1);
			if(v < beta ) {
				beta = v;
			}
			if(alpha >= beta) break;			
		}
		return beta;
	}
}







int main(){

    state * head = new state();
    
    state * child1 = new state();
    state * child2 = new state();
    head->childs.push_back(child1);
    head->childs.push_back(child2);


    state * child11 = new state();
    state * child12 = new state();
    child1->childs.push_back(child11);
    child1->childs.push_back(child12);


    state * child111 = new state(-2);
    state * child112 = new state(-7);
    child11->childs.push_back(child111);
    child11->childs.push_back(child112);


    state * child121 = new state(13);
    state * child122 = new state(-17);

    child12->childs.push_back(child121);
    child12->childs.push_back(child122);

    state * child21 = new state();
    state * child22 = new state();
  

    child2->childs.push_back(child21);
    child2->childs.push_back(child22);


    state * child211 = new state(-9);
    state * child212 = new state(-5);

    child21->childs.push_back(child211);
    child21->childs.push_back(child212);

    state * child221 = new state(-18);
    state * child222 = new state(5);
    child22->childs.push_back(child221);
    child22->childs.push_back(child222);



    int i = alphabeta(head,-999,999,1);
    cout <<"The value of alpha-beta algorithm" << i << '\n';
}