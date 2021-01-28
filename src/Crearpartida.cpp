#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
using namespace std;

void iniciar_partida();
bool valida_n_p(string);

struct partida {
	long idPartida;
	int idUI, idUO; //Identificador del usuario inicial y oponente.
	int categorias[10];
	int preguntas[10];
};

struct fecha {
	int anio, mes, dia, hora, mins, segs;
};


int main(int argc, char *argv[]) {
	
	iniciar_partida();
	
	
	return 0;
}


void iniciar_partida(){
	string nom_partida; bool error=false;
	do{
		cout <<"\n\t\t\t\tINICIAR PARTIDA\n";
		cout << "\n\n\t\tIngrese el nombre de la partida: "; 
		cin >> nom_partida; fflush(stdin);
		error = valida_n_p(nom_partida);
	}while(error);
	
	system("cls");
	
	
	
	
	/*logo();
	cout << "\n\t\t\t\t" << nom_partida << "\n"; separacion();
	cout << "\n\n\t\tLa partida se jugara contra el oponente: " << 1+rand()%100 << "\n\n\n";
	cout << "\n\n\t\t\tPara girar ruleta, presione y!";
	char op;
	do{
		cin >> op; 
		if (op =='y'|| op=='Y'){
			ruleta();
		}
	}while(op!='y'||op!='Y');
	*/
}	

bool valida_n_p(string np){
	bool k=false;
	system("cls");
	
	if(np.size() < 6){
		cout<<"\n\n\t\tDebe tener mas de 6 caracteres!"; getch(); system("cls");
		return k=true;
	}
	if(np.size() > 15){
		cout <<"\n\n\t\tDebe tener menos de 15 caracteres!"; getch(); system("cls");
		return k=true;
	}
	
	int z = np.size();
	
	for(int i=0; i<z; i++){
		
		if(!islower(np[i]) && !isupper(np[i]) && !isdigit(np[i])){
			
			if ( np[i]== '+' || np[i]=='*' || np[i]=='/' || np[i]=='?' || np[i]=='¿' || np[i]=='!' || np[i]=='¡' || np[i]=='-' ){ 
				/*Pregunta si el elemento es distinto del conjunto (no pude validar los extendidos ¡! ¿? +-* / ).*/
				k=false;
			}
			else {
				cout <<"\n\n\tLos simbolos no pretenecen al conjunto definido!"; getch(); system("cls");
				return k=true;
			}
		}
	}
	return k;
}
