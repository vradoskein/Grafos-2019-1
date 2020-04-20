#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> split(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	return v;
}
void visit(int **matrix,const int& numbVert, string color[], const int& u, int& time, int d[], int n[], int f[]){
		color[u]="gray";
		time++;
		d[u]=time;
		for(int v=0;v<numbVert;v++){
			if(matrix[u][v]==1 && color[v]=="white"){
				cout << char(v+97) << ',';
				n[v]=u;
				visit(matrix,numbVert, color, v, time, d, n, f);
			}
		}
		color[u]="black";
		f[u]=++time;
}
int main(int argc, char **argv){
	vector<string> inputText;
	for (string line; getline(cin, line);)
	 	inputText.push_back(line);
	int i=0;
	vector<string> lineReader;
	int numbVert = 0;
	int numbEdge = 0;
	int numbCases = stoi(inputText[0]);
	int lineCount = 1;
	// Loop for number of Cases
	for(int actualCase=1;actualCase<=numbCases;actualCase++){
		cout << "Case #" << actualCase << ":\n";
		lineReader = split(inputText[lineCount++], ' ');
		numbVert = stoi(lineReader[0]);
		numbEdge = stoi(lineReader[1]);
		lineReader.clear();
		// Loop to fill a vector with input
		for(int i=0;i<numbEdge;i++)
			lineReader.push_back(inputText[lineCount++]);
		// Loop to fill an adjMatrix with 0s
		int **matrix;
		matrix = new int*[numbVert];
		for(int i=0;i<numbVert;i++){
			matrix[i]=new int[numbVert];
			for(int j=0;j<numbVert;j++)
				matrix[i][j]=0;
		}
		// Loop to actually fill the adjMatrix with correct values
		for(auto line:lineReader){
			vector<string> vec = split(line, ' ');
			int a = vec[0][0]-97;
			int b = vec[1][0]-97;
			matrix[a][b]=1;
			matrix[b][a]=1;
		}
		// Counting connected components
		string color[numbVert];
		int n[numbVert];
		int d[numbVert];
		int f[numbVert];
		int time=0;
		int connectedCount=0;
		for(int u=0;u<numbVert;u++){
			color[u]="white";
			n[u]=-1;
		}
		for(int u=0;u<numbVert;u++){
			if(color[u]=="white"){
				connectedCount++;
				cout << char(u+97) << ',';
				visit(matrix,numbVert,color,u,time,d,n,f);
				cout << '\n';
			}
		}
		cout << connectedCount << " connected components\n\n";
	}
	return 0;
}	



