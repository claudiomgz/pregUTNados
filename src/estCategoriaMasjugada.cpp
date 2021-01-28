#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct partida {
	long idPartida;
	int idUI, idUO;
	int categorias[10];
	int preguntas[10];
	
};

void EstCat();
int main(int argc, char *argv[]) {
	
	EstCat();
	
	return 0;
}

void EstCat(){
	partida part1;
	ifstream entrada;
	entrada.open("partida.dat", ios::in | ios::binary);
	if(!entrada){
		cout << "\n\tEl archivo no pudo ser abierto";
		exit(-1);
		}
	else 
		entrada.seekg(0, ios::beg);
		entrada.read((char *) (&part1), sizeof(part1));
		int fis=0,matd=0,ana=0,alg=0,arq=0, catmasjugada=0, cantidaddepreg=0;
		while(!entrada.eof()){
			for(int i=0; i<10; i++){
				switch(part1.categorias[i]){
					case(0): fis++; break;
					case(1): matd++; break;
					case(2): alg++; break;
					case(3): arq++; break;
					case(4): ana++; break;
				}
			}
			int a[]={fis,matd,alg,arq,ana};
			int mayor=a[0], cat=0;
			for(int j=1; j<5; j++){
				if (a[j]>mayor) {mayor=a[j], cat=j;}
			}
			catmasjugada=cat; cantidaddepreg=mayor;
			entrada.read((char *) (&part1), sizeof(part1));
		}
		gotoxy(2 ,20 ); for(int i=0; i < 75; i++){cout <<"-";}
		gotoxy(5, 22); cout << "La categoria mas jugada es: "; 
		switch(catmasjugada){
		case 0: cout <<"Fisica";break;
		case 1: cout <<"Mat. Discreta";break;
		case 2: cout <<"Algortimos";break;
		case 3: cout <<"Arquitectura";break;
		case 4: cout <<"Analisis mat";break;
		} 
		cout << " con " << cantidaddepreg << " preguntas sorteadas. " << endl;
		gotoxy(2 ,24 ); for(int i=0; i < 75; i++){cout <<"-";}
		gotoxy(7, 32);
		cout << ">> PRESIONE UNA TECLA CUALQUIERA PARA RETORNAR AL MENU PRINCIPAL <<";
		getch();
}
