#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Method to split strings
const vector<string> split(const string& s, const char& c){
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
// Class to keep a graph structure
class Grafo {
		int numbVert;
	    int** matrixAdj;
	    int** matrixBolada;
	// Methods implementations found below class
	public:
		Grafo(int numbVert, vector<string> inputText);
		void print();
		bool isBolada(); 
		void fillBoladaLine(int i, int z); 	
};

// Constructor, receives numbVert and input. It fills the matrixAdj.
Grafo::Grafo(int numbVert, vector<string> inputText){
	this->numbVert=numbVert;
	matrixAdj = new int*[numbVert];
	// Memory allocation and filling the whole matrix with 0s
	for(int i=0;i<numbVert;i++){
		matrixAdj[i] = new int[numbVert];	
		for(int j=0;j<numbVert;j++){	
			matrixAdj[i][j]=0;
		}
	}
	// Actually filling the matrixAdj with correct values.
	for(auto line:inputText){
		vector<string> lineReader = split(line, ' ');
		int a = stoi(lineReader[0])-1;
		int b = stoi(lineReader[1])-1;
		matrixAdj[a][b]=1;
	}	
}
// Method to print matrix.
void Grafo::print() {
	for(int i=0;i<numbVert;i++){
		for(int j=0;j<numbVert;j++)
			cout << matrixAdj[i][j] << " ";
		cout << endl;
	}
}
// Method to check if the graph is "bolada"
bool Grafo::isBolada(){
	bool result=true;
	matrixBolada = new int*[numbVert];
	for(int i=0;i<numbVert;i++)
		matrixBolada[i] = new int[numbVert];
	for(int i=0;i<numbVert;i++)
		for(int j=0;j<numbVert;j++){
			if(i==j) matrixBolada[i][i]=1;
			else matrixBolada[i][j]=0;
		}
	// send main Lines
	for(int i=0;i<numbVert;i++){
			this->fillBoladaLine(i, i);
	}
	for(int i=0;i<numbVert;i++){
		for(int j=0;j<numbVert;j++){
			if(matrixBolada[i][j]==0 && matrixBolada[j][i]==0)
				result=false;
		}
	}
	return result;
}
void Grafo::fillBoladaLine(int i, int z){
	for(int j=0;j<numbVert;j++){
		if(matrixAdj[z][j]==1 && matrixBolada[i][j]==0) {
			matrixBolada[i][j]=1;
			// Check for adjacency of secondary lines
			fillBoladaLine(i, j);
		}
	}
}


int main(int argc, char **argv){
	vector<string> inputText;
	// Loop to read std input
	for (string line; getline(cin, line);)
	 	inputText.push_back(line);
	int i=0;
	vector<string> lineReader;
	int lineCount=0;
	lineReader = split(inputText[0],' ');
	int numbVert = stoi(lineReader[0]);
	int numbEdge = stoi(lineReader[1]);
	inputText.erase(inputText.begin());

	// Creation of graph structure
	Grafo g(numbVert, inputText);
	if(g.isBolada())
		cout << "Bolada";
	else	
		cout << "Nao Bolada";
	return 0;
}	



