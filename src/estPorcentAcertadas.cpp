#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <conio.h>
using namespace std;

struct partida {
	long idPartida;
	int idUI, idUO;
	int categorias[10];
	int preguntas[10];
};

struct jugada {
	long idPartida;
	int idUsr;
	bool rtas[10];
	int puntaje;
};
bool repetido (long , int);
void porcentajeAcertadas();
int main(int argc, char *argv[]) {
	porcentajeAcertadas();
	return 0;
}


void porcentajeAcertadas(){
	partida part1; jugada jugada1;
	ifstream entrada1,entrada2;
	
	entrada1.open("partidas.dat", ios::in | ios::binary);
	entrada2.open("jugadas.dat", ios::in | ios::binary);
	
	if(!entrada1 || !entrada2){
		cout << "\n\tEl archivo no pudo ser abierto";
		exit(-1); getch();
	}
	else{ 
		entrada1.seekg(0, ios::beg);
		entrada1.read((char *) (&part1), sizeof(part1));
		entrada2.seekg(0, ios::beg);
		entrada2.read((char *) (&jugada1), sizeof(jugada1));
		
		while(!entrada1.eof()){
			if (  (part1.idUI == usuarioActual.id) && (repetido ( terminadas, i )) ){
				
				terminadas[i]= part1.idPartida;
				terminadas[i+1] = part1.idUO;
				i=i+2;
				
			}
		entrada1.read((char *) (&part1), sizeof(part1));
		}
		int acertadas=0;
		while(!entrada2.eof()){
			for(int i =0; i<10; i++){}
				if (jugada1.rtas[i] == true){
					acertadas++;
				}
			
		entrada2.read((char *) (&jugada1), sizeof(jugada1));
		}
	}	
	
	cout << "\n\t\t\t\tPorcentaje de preguntas que fueron acertadas por los dos usuarios en una partida\n"; //separacion (); cout << "\n";
	
	if(i!=0){
		for (int j=0; j<i; j++){
			cout << "\n\t\t|  ID de Partida:  " << terminadas[j] << " Usuario: " << terminadas[j+1] << (acertadas*100)/10 << "Usuario: " <<  << (acertadas*100)/10 << " |";
			cout << "\n\t\t-------------------------------------------------------------------------------------------------------------------------------------";
			j=j+1;
		}
		
		cout << "\n\n\t\t    >> Presione una tecla para continuar <<"; getch();
		
	}
	/*else{
		gotoxy( 20, 20);
		cout << "No se encuentran partidas terminadas.";
		gotoxy( 20, 30 );
		cout << ">>Presione una tecla para continuar <<";
	}*/
	
}

bool repetido (long a[], int k){
	
	for (int i =0; i<k; i++){
		for (int j=i+1; j<k; j++){
			if (a[i] == a[k]){
				return true;
			}
		} 
	}
	
	return false;
}

