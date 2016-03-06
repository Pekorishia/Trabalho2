#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int main(int argc, char *argv[]){
	
	//não dá para usar o argv na IDE
	//string file1;
	 // file1 = argv[1];
	//string file2;
	 // file2 = argv[2];
	//string file3;
	 // file3 = argv[3];
	//string file4; 	
	 // file4 = argv[4];

	list<string> lista;
	
	
	string file1;
	cout << "arquivo 1" << endl;
	cin >> file1;
	
	string file2;
	cout << "arquivo 2" << endl;
	cin >> file2;
	
	string file3;
	cout << "arquivo 3" << endl;
	cin >> file3;
	
		string file4;
	cout << "arquivo 4" << endl;
	cin >> file4;
	
	string line;
	
	ifstream f1 (file1.c_str());	
	if(f1.is_open()){
		while( getline (infile,line)){
			lista.push_back(line);
		}
		f1.close();
	}
	else cout << "unable to open file";
	
	ifstream f2 (file2.c_str());	
	if(f2.is_open()){
		while( getline (infile,line)){
			lista.push_back(line);
		}
		f2.close();
	}
	else cout << "unable to open file";
	
	ifstream f3 (file3.c_str());	
	if(f3.is_open()){
		while( getline (infile,line)){
			lista.push_back(line);
		}
		f3.close();
	}
	else cout << "unable to open file";
	
	//reorganiza a lista pela data	
	
	ofstream myfile ("saidas.txt");
	if(myfile.is_open()){
		myfile <<  "baka .\n";
		myfile << "suki" << "gyaa \n";
		myfile.close();
	}
	return 0;
}

