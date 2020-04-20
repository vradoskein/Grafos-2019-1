#include <iostream>

using namespace std;
class edge{
	public:
		int a, b;
};
void visit(int **matrix,const int& numbVert, string color[], const int& u, int& time, int d[], int n[], int f[]){
		color[u]="gray";
		time++;
		d[u]=time;
		for(int v=0;v<numbVert;v++){
			if(matrix[u][v]==1 && color[v]=="white"){
				n[v]=u;
				visit(matrix,numbVert, color, v, time, d, n, f);
			}
		}
		color[u]="black";
		f[u]=++time;
}

int main(int argc, char **argv){
	int cases;
	cin >> cases;
	// Loop for each Case
	for(int numbCase=1;numbCase<=cases;numbCase++){
		char resp='N';
		int v, m, p, k, a, b;
		cin >> v >> m >> p >> k;
		int color[v];
		int **adj;
		//int adj[v][v];
		// Fills the adjMatrix with zeros
		adj = new int*[v];
		for(int i=0;i<v;i++){
			adj[i]=new int[v];
			for(int j=0;j<v;j++)
				adj[i][j]=0;
		}
		// Read the color of vertices	
		for(int i=0;i<v;i++){
			cin >> color[i];
		}
		// Calculate the max number of edges
		int maxEdges=v*(v-1)/2;
		// Calculate the max possible edges to be inserted
		int remainingEdges=maxEdges-m;
		
		// Read the edges
		for(int i=0;i<m;i++){
			cin >> a >> b;
			adj[a-1][b-1]=1;
			adj[b-1][a-1]=1;
		}

		// if: the number of inserting edges is possible
		// else: the number of inserting edges is bigger than max possible
		if(remainingEdges>=p){
			// go through the adj matrix inserting the verts when condition is met
			for(int i=0;i<v;i++){
				for(int j=0;j<v;j++){
					if(adj[i][j]==0 && color[i]!=color[j]){
						if(p>0){
							p--;
							adj[i][j]=1;
							adj[j][i]=1;
						}
					}
				}
			}
			// if there is no verts left to insert (all were inserted with no problems)
			if(!p){
				// Counting connected components
				string color2[v];
				int n[v];
				int d[v];
				int f[v];
				int time=0;
				int connectedCount=0;
				for(int u=0;u<v;u++){
					color2[u]="white";
					n[u]=-1;
				}
				for(int u=0;u<v;u++){
					if(color2[u]=="white"){
						connectedCount++;
						visit(adj,v,color2,u,time,d,n,f);
					}
				}
				// if: graph is connected
				// else: graph has at least one unconnected element
				if(connectedCount==1)				
					resp = 'Y';	
			}
		}
		cout << resp << "\n\n";
	
	}
}
