#include <iostream>
#include <ctime>
#define MAX_FILA 5
#define MAX_COL 88
#include <cstdlib>
#include <fstream>
using namespace std;

struct Pregunta {
	int idCategoria;    
	int idPregunta;
	int numeroGrupo;
	string pregunta;
	string opciones[4];
	int opcionCorrecta; //Subíndice de la opción correcta.
}; 


void cargaDePreguntas(Pregunta matrizPregutnas[][MAX_COL]);
void mostrarPregunta(int);


int main(int argc, char *argv[]) {
	int c;
	cin >> c;
	mostrarPregunta(c);
	
	
	return 0;
}


void mostrarPregunta(int c){
	srand(time(NULL)); //Actualizo la semilla del reloj.
	int i;
	Pregunta matrizPreguntas[MAX_FILA][MAX_COL];
	cargaDePreguntas(matrizPreguntas);
	switch(c){
		case 0:  i=1+rand()%86; ;  ; break;
		case 1:  i=1+rand()%88; ;  ; break;
		case 2:  i=1+rand()%87; ;  ; break;
		case 3:  i=1+rand()%86; ;  ; break;
		case 4:  i=1+rand()%84; ;  ; break;
	}
	
	cout << matrizPreguntas[c][i].idCategoria << endl;
	cout << matrizPreguntas[c][i].idPregunta << endl;
	cout << matrizPreguntas[c][i].numeroGrupo << endl;
	cout << matrizPreguntas[c][i].pregunta << endl;
	cout << matrizPreguntas[c][i].opciones[0] << endl;
	cout << matrizPreguntas[c][i].opciones[1] << endl;
	cout << matrizPreguntas[c][i].opciones[2] << endl;
	cout << matrizPreguntas[c][i].opciones[3] << endl;
	
	//cout << matrizPreguntas[c][i].opcionCorrecta << endl;
	
}

void cargaDePreguntas(Pregunta matrizPreguntas[][MAX_COL]){
	ifstream  baseDePreguntas;
	int numeroAtributo = 0, idCategoria, idPregunta, numeroGrupo, opcionCorrecta;
	char pregunta[1000], opcion1[1000], opcion2[1000], opcion3[1000], opcion4[1000],entrada[1000];
	baseDePreguntas.open("basepreguntas.txt");
	if(!baseDePreguntas){
		//Error al abrir el archivo
		cout << "El archivo no pudo ser abierto. Se cerrara el programa." << endl;
		system("pause");
		exit(-1);
	}
	baseDePreguntas.unsetf(ios::skipws);
	while(!baseDePreguntas.eof()){
		if(numeroAtributo == 8 )
			baseDePreguntas.getline(entrada,1000,'\n'); //Consume el \n que hay entre las preguntas, ya que no estan separadas por un arroba
		else{
			baseDePreguntas.getline(entrada,1000,'@');
		}
		switch(numeroAtributo){
		case 0:
			idPregunta = atoi(entrada)-1;
			break;
		case 1:
			idCategoria = atoi(entrada) ;
			break;
		case 2:
			numeroGrupo = atoi(entrada);
			break;
		case 3:
			strcpy(pregunta,entrada);
			break;
		case 4:
			strcpy(opcion1,entrada);
			break;
		case 5:
			strcpy(opcion2,entrada);
			break;
		case 6:
			strcpy(opcion3,entrada);
			break;
		case 7:
			strcpy(opcion4,entrada);
			break;
		case 8:
			opcionCorrecta=atoi(entrada);
			break;
		}
		numeroAtributo++;
		if(numeroAtributo == 9){
			numeroAtributo = 0;
			matrizPreguntas[idCategoria][idPregunta].idCategoria = idCategoria;
			matrizPreguntas[idCategoria][idPregunta].idPregunta = idPregunta;
			matrizPreguntas[idCategoria][idPregunta].numeroGrupo = numeroGrupo;
			matrizPreguntas[idCategoria][idPregunta].pregunta = pregunta;
			matrizPreguntas[idCategoria][idPregunta].opciones[0] = opcion1;
			matrizPreguntas[idCategoria][idPregunta].opciones[1] = opcion2;
			matrizPreguntas[idCategoria][idPregunta].opciones[2] = opcion3;
			matrizPreguntas[idCategoria][idPregunta].opciones[3] = opcion4;
			matrizPreguntas[idCategoria][idPregunta].opcionCorrecta = opcionCorrecta;
		}
	}
}
