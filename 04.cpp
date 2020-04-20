#include <iostream>
#include <queue>
#include <list>

using namespace std;
const int infinite=1000000;
class Grafo{
	public:
		int V;
		list<pair<int, int>>* adj;
		Grafo(int V){
			this->V=V;
			adj = new list<pair<int,int>>[V];
		}
		//add edges
		void addEdge(int v1, int v2, int value){
			adj[v1].push_back(make_pair(v2, value));
		}
		int dijkstra(int orig, int dest, int input[][3], int m){
			int dist[V];
			int visited[V];
			list<int> path[V];
			// priority queue
			priority_queue< pair<int, int>, 
				vector<pair<int,int> >, greater<pair<int,int>>> pq; 
			for(int i=0;i<V;i++){
				dist[i]=infinite;
				visited[i]=false;
			}
			
			dist[orig]=0;
			pq.push(make_pair(dist[orig], orig));
			path[orig].push_back(orig);
			// main loop
			while(!pq.empty()){
				pair<int, int> p = pq.top(); // get pair from top
				int u= p.second; // get vertice value
				pq.pop(); // pop from queue
				
				// checks if vertice is already computed
				if(visited[u]==false){
					// mark as visited
					visited[u]=true;
					list<pair<int, int>>::iterator it;
				
					// go through the adj list
					
	
					for(it = adj[u].begin(); it != adj[u].end(); it++){
						// get adj vert
						int v = it->first;
						int edge_cost = it->second;
						
						// update distance
						if(dist[v]>(dist[u]+edge_cost)){
							dist[v]=dist[u]+edge_cost;
							path[v].clear();
							path[v]=path[u];
							path[v].push_back(v);
							pq.push(make_pair(dist[v], v));
						}
					} 
					
				}	
			}
			int sizep=path[dest].size();
			int paths[sizep];
			int i=0;
			while(!path[dest].empty()){
				paths[i]=path[dest].front();
				path[dest].pop_front();
				i++;
			}
			for(int i=0;i<sizep;i++){
				for(int j=0;j<m;j++){
					if((input[j][0]==paths[i]+1 && input[j][1]==paths[i+1]+1) || (input[j][0]==paths[i+1]+1 && input[j][1]==paths[i]+1))
						input[j][2]=-1;
				}
			}
		return dist[dest];
	}
};

int main(int argc, char **argv){
	int instnumb=1;
	char ch = getc(stdin);
	while(ch!=EOF){
		ungetc(ch,stdin);
		int n, m, d, k;
		cin >> n >> m;
		Grafo g(n);
		int input[m][3];
		for(int i=0;i<m;i++)
			for(int j=0;j<3;j++){
				input[i][j]=0;
			}
		for(int i=0;i<m;i++){
			cin >> input[i][0] >> input[i][1] >>  input[i][2];
			g.addEdge(input[i][0]-1, input[i][1]-1, input[i][2]);
			g.addEdge(input[i][1]-1, input[i][0]-1, input[i][2]);
		}
		cin >> d >> k;
		int price=g.dijkstra(0,n-1,input,m);
		cout << "Instancia "<< instnumb<< "\n\n";
		if(price<infinite){
			if(d>k){
				int onBoard = k;
				int sum=price*onBoard;
				d=d-onBoard;
				while(d>0){
					if(d>k)
						onBoard=k;
					else
						onBoard=d;
					int count = 0;
					for(int i=0;i<m;i++) if(input[i][2]!=-1) count+=1;
					Grafo f(n);
					for(int i=0;i<m;i++){
						if(input[i][2]!=-1){
							f.addEdge(input[i][0]-1, input[i][1]-1, input[i][2]);
							f.addEdge(input[i][1]-1, input[i][0]-1, input[i][2]);
						}
					}
					price=f.dijkstra(0,n-1,input,m);
					if(price<infinite)
						sum=sum+price*onBoard;			
					else
						break;
					d=d-onBoard;
				}
				if(price<infinite)
					cout << sum;
				else
					cout << "impossivel";
			}else{
				cout << price*d;
			}
		}else{
			cout << "impossivel";
		}
		cout <<"\n\n\n\n";
		instnumb++;
		ch = getc(stdin);
	}
}

