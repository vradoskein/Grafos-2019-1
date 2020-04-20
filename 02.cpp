#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

struct Edge{
	public:
		int v1;
		int v2;
		float dist;
		void set(int v1, int v2, float dist){
			this->v1=v1;
			this->v2=v2;
			this->dist=dist;
		}
		void clone(Edge e){
			this->v1=e.v1;
			this->v2=e.v2;
			this->dist=e.dist;
		}
};
// Class used to store and process Graphs
class Grafo {
		int numbVert;
		float** matrixDistance;
		float** matrixPosition;
	public:
		Grafo(int numbVert);
		void addVert(float x,float y,int pos);
		void createMatrixDistance();
		void printMatrixDistance();
		float primCost();
};
//constructor
Grafo::Grafo(int numbVert){
	this->numbVert=numbVert;
	matrixPosition = new float*[numbVert];
	for(int i=0;i<numbVert;i++)
		matrixPosition[i]=new float[2];
}
void Grafo::addVert(float x,float y,int pos){
	matrixPosition[pos][0]=x;
	matrixPosition[pos][1]=y;
}
//instantiates and fills the distance matrix
void Grafo::createMatrixDistance(){
	// Loop to fill distance Matrix
	matrixDistance = new float*[numbVert];
	for(int i=0;i<numbVert;i++){
		matrixDistance[i] = new float[numbVert];
		for(int j=0;j<numbVert;j++){
			float deltaXpow=pow((matrixPosition[i][0]-matrixPosition[j][0]),2);
			float deltaYpow=pow((matrixPosition[i][1]-matrixPosition[j][1]),2);
			matrixDistance[i][j]=sqrt(deltaXpow + deltaYpow);
		}
	}
}

float Grafo::primCost(){
	// Calc number of Edges.
	int numbEdges=(numbVert*(numbVert-1))/2;
	Edge edges[numbEdges];
	int iter=0;
	// Save Edges into array
	for(int i=0;i<numbVert-1;i++){
		for(int j=i+1;j<numbVert;j++){
			edges[iter].set(i,j,matrixDistance[i][j]);
			iter++;
		}
	}
	// Sort edges array
	Edge tmp;
	for(int i=0;i<numbEdges-1;i++){
		int menor=i;
		for(int j=i+1;j<numbEdges;j++){
			if (edges[j].dist < edges[menor].dist)
				menor=j;
		}
		tmp.clone(edges[i]);
		edges[i].clone(edges[menor]);
		edges[menor].clone(tmp);
	}
	// Simplified prim ( it works :D )
	Edge prim[numbVert-1];
	bool vertAlready[numbVert];
	for(int i=0;i<numbVert;i++) vertAlready[i]=false;
	int next=1;
	prim[0].clone(edges[0]);
	vertAlready[prim[0].v1]=true;
	vertAlready[prim[0].v2]=true;
	while(next<numbVert-1){
		for(int j=1;j<numbEdges;j++){
			if(vertAlready[edges[j].v1] && !vertAlready[edges[j].v2]){
				prim[next].clone(edges[j]);
				vertAlready[prim[next].v1]=true;
				vertAlready[prim[next++].v2]=true;
				j=0;
			}
			else if(!vertAlready[edges[j].v1] && vertAlready[edges[j].v2]){
				prim[next].clone(edges[j]);
				vertAlready[prim[next].v1]=true;
				vertAlready[prim[next++].v2]=true;
				j=0;
			}
			j++;
		}
	}
	float sum=0.0;
	for(int i=0;i<numbVert-1;i++){
		sum=sum+prim[i].dist;
	}
	sum=sum/100;
	return sum;
}

int main(int argc, char **argv){
	int numbCases;
	cin >> numbCases;
	for(int c=1;c<=numbCases;c++){	
		int n;
		cin >> n;
		Grafo g(n);
		for(int i=0;i<n;i++){
			float x, y;
			cin >> x >> y;
			g.addVert(x,y,i);
		}
		g.createMatrixDistance();
		cout << setprecision(2) << fixed;
		cout << g.primCost() << "\n\n";	
	}
}
