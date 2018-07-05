#include <iostream>
#include <queue>
#include <climits>
#include <string>
#include <set>
#include <vector>
#include <fstream>

struct Node{
	std::string name;
	int zeros, ones, indx, prior, dist, firstBit;

	bool operator() (const Node *A, const Node *B){
		int a = A->prior, b = B->prior;
		int a1 = A->dist, b1 = B->dist;

		if(a1 != b1) return a1 > b1;
		else if(a != b) return a > b;
		else return A->firstBit < B->firstBit;
	}
};

int a, b, exp;
std::vector<Node*> all;
std::set< std::pair<Node*, Node*> > E;
Node* start;
Node* finish;

void init(std::string file, std::string strt){
	start = NULL;
	finish = NULL;

	std::ifstream ifs;
	ifs.open(file.c_str());
	if(ifs.fail()) return;

	std::string lines, buff;
	char c;
	int zCnt = 0, oCnt = 0;

	getline(ifs, lines);
	while(ifs.get(c)){
		Node * n = new Node;

		if(c != '\n') {
			buff += c;
			if(c == '0') zCnt++;
			else oCnt++;	
			continue;		
		}

		(*n).name = buff;
		(*n).zeros = zCnt;
		(*n).ones = oCnt;
		all.push_back(n);

		if(!zCnt) finish = n;
		buff.clear(); zCnt = 0; oCnt = 0;
	}
	ifs.close();

	unsigned int i = 0, nSize = all.size();
	while(i < nSize){
		unsigned int j = i + 1;
		while(j < nSize){

			unsigned int count = 0, k = 0;
			bool tOf = false;

			while(k < (*all.at(i)).name.size()) {
				if((*all.at(i)).name.at(k) != (*all.at(j)).name.at(k)) count++;
				k++;
			}

			if(count != 1) tOf = false;
			else tOf = true;

			if(tOf) E.insert(std::make_pair(all.at(i), all.at(j)));
			j++;
		}
		i++;
	}

	std::vector<Node*>::iterator it = all.begin();
	int front = 0, back = 0;

	while(it != all.end()){
		if(*it == finish) b = back;
		if((*(*it)).name == strt){
			start = *it;
			a = front;
		}
		front++; back++; it++;
	}
}

std::vector<int> dist, pred, newP;
std::vector<bool> visit;
std::priority_queue<Node*, std::vector<Node*>, Node> N;
void path_help(Node *s, int a, bool tOf){
	(*s).indx = a;
	int ind = (*s).indx;

	if(tOf){
		(*s).dist = 0;
		visit[a] = true;
		dist[a] = 0;
	}

	int z = all[ind]->zeros, d = dist[ind];
	(*s).prior = z + d;

	newP[ind] = (*s).prior;
	(*s).firstBit = all[ind]->name[0];
	(*s).dist = dist[ind];

	N.push(s);
}

void path(){
	Node * s = new Node;
	path_help(s, a, true);

	while(!N.empty()){
		Node *vert = N.top();
		N.pop();
		int ind2 = (*vert).indx;
		if(ind2 == b){
			while(!N.empty()) N.pop();
			delete vert;
			break;
		}
		if(newP[ind2] == (*vert).prior){
			if(!visit[ind2]) exp++;
			unsigned int i = 0;
			while(i < all.size()){
				int i1p = E.count(std::make_pair(all[ind2], all[i]));
				int i2p = E.count(std::make_pair(all[i], all[ind2]));
				if(i1p || i2p){
					if(!visit[i] || dist[ind2] + 1 < dist[i]){
							dist[i] = dist[ind2] + 1;
							pred[i] = ind2;
							if(!visit[ind2]) visit[ind2] = true;
							Node * w = new Node;
							path_help(w, i, false);						
					}
				}
				i++;
			}
		}
		delete vert;
	}
}

void print_help(int n){
	if(pred[n] == -1){
		std::cout << all[n]->name << std::endl;
		return;
	}
	print_help(pred[n]);
	std::cout << all[n]->name << std::endl;
}

void print() {
	if(pred[b] == -1) std::cout << "No transformation"  << std::endl;
	else print_help(b);
	std::cout << "expansions = " << exp << std::endl;
}

int main(int argc, char * argv[]){
	std::string file = argv[2]; 
	std::string s = argv[1];

	init(file, s);
	unsigned int n = all.size();
	unsigned int i = 0;
	while(i < n){
		dist.push_back(INT_MAX);
		visit.push_back(false);
		pred.push_back(-1);
		newP.push_back(INT_MAX);
		i++;
	}
	exp = 1;

	path();
	print();

	std::vector<Node*>::iterator it = all.begin();
	while(it != all.end()){
		delete *it;
		it++;
	}
	return 0;
}