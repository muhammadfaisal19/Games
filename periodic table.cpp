#include <iostream>
#include <iomanip>
using namespace std;

struct Element{
	int AtomicNo;
	string name, symbol;
	float mass;
};

display(Element el[], int size){
	cout<<"Modern Periodic Table"<<endl;
cout<<"--------------------------------------------"<<endl;
cout<<"| No | Element Name | Symbol | Atomic Mass |"<<endl;
cout<<"--------------------------------------------"<<endl;
	for(int i=0; i<size; i++){
cout<<"|"<<setw(3)<<el[i].AtomicNo<<" |";
cout<<setw(13)<<el[i].name<<" |";
cout<<setw(8)<<el[i].symbol<<" |";
cout<<setw(12)<<el[i].mass<<" |"<<endl;
	}
}

int main(){
	int size = 118;
	Element table[size]={
{1, "Hydrogen", "H", 1.0079},
{2, "Helium" , "He", 4.0026},
{3, "Lithium", "Li", 6.941},
{4, "Beryllium","Be", 9.0122},
{5, "Boron" , "B" , 10.811},
{6, "Carbon" , "C" , 12.0107},
{7, "Nitrogen", "N" , 14.0067},
{8, "Oxygen" , "O" , 15.9994},
{9, "Fluorine" , "F" , 18.9984},
{10, "Neon" , "Ne" , 20.1797}

	};
	
	display(table, size);
}
