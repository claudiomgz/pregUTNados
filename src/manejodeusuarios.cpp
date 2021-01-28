#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <ctime>

using namespace std;

struct usuario {
	int id;
	string nombre;
	string clave;
};

bool buscarXNombreUsuario(string nombre, usuario & usr);
/*  Busca en el archivo usuarios.txt un usuario a partir del nombre. 
	Si lo encuentra retorna true y devuelve en usr los datos del usuario, 
	sino retorna false.
*/

bool buscarXIdUsuario(int id, usuario & usr);
/*  Busca en el archivo usuarios.txt un usuario a partir de un id de usuario. 
	Si lo encuentra retorna true y devuelve en usr los datos del usuario, 
	sino retorna false.
*/

bool grabarUsuario(usuario usr);
/*  Intenta registrar un nuevo usuario al sistema. 
	Si lo puede registrar retorna true, 
	pero si existe un usuario con el mismo nombre, o si hubo algún problema con la gestión del archivo, 
	no pudiendo registrarlo, retorna false. 
*/
bool obtenerIdUsuario(int & id);
/*  Función auxiliar utilizada por registrarUsuario que recorre todo el archivo usuarios.txt
	para así obtener automáticamente el próximo id a asignar.
*/
bool buscarClave(string, string ,usuario & usr);
/*Funcion para obtener clave.*/
void registrarse();
/*Funcion que lleva a cabo la toma de datos de user y clave*/
bool validar_c(string );
/*Valida la clave.*/
bool validar_u(string );
/*Valida el usuario.*/
bool validar_simbolos(string);
/*Valida los Simbolos propios de la Clave.*/
void IniciarSesion(); 
/*Funcion la cual inicia sesion.*/
int buscar_id(string nombre, string clave, usuario &usr); 
/*Hace una busqueda de el id correspondiernte al usuario.*/
void logo();
/*Funcion Logo de la Aplicaccion.*/
void separacion();
/*Decoracion de asteriscos.*/
void inicio();
/*Presentacion de ALumnos y logo del juego.*/ 
void cargando();
/*Animacion de barra cargando.*/
void captcha(string P, string N, string );
/*Genera un codigo despues que se cometio en tres(3) oportunidades un inicio 
de sesion erroneo*/
void invertir(string c);
/*Funcion para poder generar el codigo Capcha, este se encarga de hacer 
una inversion del codigo generado dentro de la funcion captcha*/
void menu_principal(); /*Menu principal del juego*/
void menu_de_juego(); /*Menu de juego*/
void mi_cuenta(); /*Menu Referida a la cuenta del usuario con sesion actual*/
void ruleta();
/*Funcion que muestra en pantalla los graficos de las categorias y llama a cargar las preguntas*/
void Lami();
void Laedd();
void Lmatdis();
void Larq();
void Lfisica();

const char * archUsuarios="usuarios.txt";
/* Constante de tipo char la cual esta igalada la informacion propia de los 
usuarios, Id User y Clave.*/
usuario usuarioActual;
/*Variable donde se almacenara el usuario que inicio sesion.*/
bool Bandera = false; 
/*Variable donde almacena un valor logico el cual se 
encarga de hacer de bandera si se ingresa a la opcion de capcha.*/

int main(int argc, char *argv[]) {
	system("mode con: cols=80 lines=35"); /*Le doy un tamaño predeterminado a la consola*/
	
	inicio(); /*Llamo a la funcion inicio.*/
	menu_principal(); /*Llamo a la funcion que contiene la estructura del menu principal.*/
	
	return 0;
}

void menu_principal(){
	usuario u; /*Declaro una variable con la estructura usuario*/
	string nombre; /*Declaro una variable nombre para tomar dicho dato temporalmente.*/
	char opcion; /*Declaro una variable char para utilizar como opcion del menu.*/
	while(opcion != '4') {
		/*Intero hasta que sea distinto de la salida o una opcion correcta.*/
		system("cls");
		logo();
		cout << "\n\t\t\t\t MENU PRINCIPAL\n";
		separacion();
		cout << endl << endl;
		cout << "\t\t\t    1.- Registrarse" << endl;
		cout << "\t\t\t    2.- Iniciar Sesion" << endl;
		cout << "\t\t\t    3.- Estadisticas de juego" << endl;
		cout << "\t\t\t    4.- Salir"<< endl << endl;
		cout << "\t\t\t    Ingrese una opcion: ";
		cin >> opcion;
		cin.ignore(256,'\n');
		switch(opcion) {
		case '1': 
			system("cls");
			registrarse();
			break;
			
		case '2': 
			system("cls");
			Bandera = false;
			IniciarSesion();
			;
			break;
		
		case '3': 
				system("cls");
				logo();
				cout << "\n\n\t\tFuncionalidad En Dearrollo";  ;
			break;	
			
		case '4': 
			system("cls");
			logo();
			cout << "\n\t\t\t\t      Chau!" << endl;
			separacion();
			cout << "\n\n\n\t\t\tGracias por utilizar PregUTNados!\n\n\n\n"; 
			getch();
			break;
		default: 
			system("cls");
			logo();
			cout << endl << "\t\t\n\n\n\t\t  >> Opcion incorrecta, vuelva a intentarlo <<" << endl << endl;
			getch();
			
			break;
		}
	}
}


bool buscarXNombreUsuario(string nombre, usuario & usr){
	ifstream archivo;
	
	bool fin=false, encontrado=false;
	
	archivo.open(archUsuarios, ios::in);
	
	if(!archivo.fail()){
		while(!fin && !encontrado){
			archivo >> usr.id >> usr.nombre >> usr.clave;
			
			if(usr.nombre==nombre) {
				encontrado=true;
			}
			
			if(archivo.eof()) 
				fin=true;
		}
		archivo.close();
	}
	Sleep(1000);
	system("cls");
	return encontrado;
}

bool buscarXIdUsuario(int id, usuario & usr){
	ifstream archivo;
	
	bool fin=false, encontrado=false;
	
	archivo.open(archUsuarios, ios::in);
	
	if(!archivo.fail()){
		while(!fin && !encontrado){
			archivo >> usr.id >> usr.nombre >> usr.clave;
			
			if(usr.id==id) {
				encontrado=true;
			}
			
			if(archivo.eof())
				fin=true;
		}
		archivo.close();
	}
	return encontrado;
}

bool grabarUsuario(usuario usr) {
	//usuario usrBusc;
	bool rta=true;
		ofstream archivo;
		
		archivo.open(archUsuarios, ios_base::app);
		if(archivo.fail()) {
			rta=false;
		}
		else {
			if(obtenerIdUsuario(usr.id)) {
				archivo << endl << usr.id << " " << usr.nombre << " " << usr.clave;
			}
			else
				rta=false;				
			archivo.close();
		}
	return rta;
}

bool obtenerIdUsuario(int & id) {
	ifstream archivo;
	usuario usr;
	int i=0;
	bool fin=false, rta=true;
	
	archivo.open(archUsuarios, ios::in);
	
	if(archivo.fail())
		rta=false;
	else {
		while(!fin){
			archivo >> usr.id >> usr.nombre >> usr.clave;
			if(archivo.eof())
				fin=true;
			i++;
		}
		id=++i;
		archivo.close();
	}
	return rta;
}
bool validar_c(string p){
	bool k=false;
	system("cls");
	if ( p.size() < 6){ cout << "\t\tDebe tener mas de 6 caracteres!"; return k=true; } //Pregunto si es menor que el min definido.
	if ( p.size() > 8){cout << "\t\tDebe tener menos de 8 caracteres!"; return k=true; } //Pregunto si es mayor que el max definido.
	
	int i=0, a=0; //Declaro contadores.
	
	while(p[i]!='\0'){ //Intero hasta el final del arreglo.
		if( isupper(p[i]) ){a++;} //Si es Mayuscula incremento el contador a en uno.
		i++;
	}
	if (a==0){cout << "\t\tDebe tener por lo menos una letra mayuscula!"; return k=true;}//Pregunto si a es igual a cero (es decir no contiene mayusculas), informo error y retorno k.
	
	a=0; i=0; //Pongo en cero los contadores para poder reutilizarlos.
	while(p[i]!='\0'){ //Intero hasta el final del arreglo.
		if(isdigit(p[i])){a++;} //Si es un numero incremento el contador a en uno.
		i++;
	}
	if(a==0){cout << "\t\tDebe tener por lo menos un Numero!"; return k=true;}//Pregunto si a es igual a cero (es decir no contiene numero), informo error y retorno k.
	
	i=0; //Pongo el contador en cero para reutilizarlo.
	while( p[i]!='\0'){
		
		int  b=0, c=0, d=0, a=0;
		
		if( isdigit(p[i]) && isdigit(p[i+1]) && isdigit(p[i+2]) && isdigit(p[i+3]) ){ //Si el elemento i y los 3 seiguientes son un num entonces comprueba el if interno.
			while(a!=p[i]){a++;} while(b!=p[i+1]){b++;} while(c!=p[i+2]){c++;} while(d!=p[i+3]){d++;} //Busco los valores ascii de los 4 digitos.
			if (a+1==b && b+1==c && c+1==d ){ //Pregunto si son seguidos, sino salgo de este if.
				cout << "\tNo debe tener mas de tres(3) numeros consecutivos!"; return k=true; //Si lo son informo el error y retorno k.
			}
		}
		
		if ( islower(p[i]) && islower(p[i+1]) ){ //Pregunto si en el elemento i y i+1 se encuentran minusculas.
			a=0, b=0; //Pongo en cero contadores para reutilizarlos.
			while(a!=p[i]){a++;} while(b!=p[i+1]){b++;} //Busco los valores ascii de estos caracteres.
			if( (a+1)==b ){ // ñpreguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) Minusculas consecutivos ascendentes!"; return k=true; //Si lo son informo el error y reotorno k.
			}
		}
		
		if ( isupper(p[i]) && isupper(p[i+1]) ){ //Pregunto si en el elemento i y i+1 se encuentran minusculas.
			a=0, b=0; //Pongo en cero contadores para reutilizarlos.
			while(a!=p[i]){a++;} while(b!=p[i+1]){b++;} //Busco los valores ascii de estos caracteres.
			if( (a+1)== b ){ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) Mayusculas consecutivos ascendentes!"; return k=true; //Si lo son informo el error y reotorno k.
			}
		}
		
		if ( islower(p[i]) && isupper(p[i+1]) ){ //Pregunto si en el elemento i se encuentra una minuscula y i+1 se encuentra una mayuscula.
			a=0, b=0; //Pongo en cero contadores para reutilizarlos.
			char h=tolower(p[i+1]); //Declaro una variable h la igualo a el formato minuscula del elemento p[i+a].
			while(a!=p[i]){a++;} while(b!=h){b++;} //Busco los valores ascii de estos caracteres.
			if( ((a+1) == b) || a<b){ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) caracteres consecutivos ascendentes!"; return k=true; //Si lo son informo el error y reotorno k.
			}
		}
		
		if ( isupper(p[i]) && islower(p[i+1]) ){ //Pregunto si en el elemento i se encuentra una mayuscula y i+1 una minuscula.
			a=0, b=0; //Pongo en cero contadores para reutilizarlos.
			char h=tolower(p[i]); //Declaro una variable h la igualo a el formato minuscula del elemento p[i+a].
			while(a!=h){a++;} while(b!=p[i+1]){b++;} //Busco los valores ascii de estos caracteres.
			if( ((a+1) == b) || a>b){ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) caracteres consecutivos ascendentes!"; return k=true; //Si lo son informo el error y reotorno k.
			}
		}
		
		i++; //Si no entra en ninguna condicion incremento el contador i para continuar el ciclo while.
		
	}
	return k; //Si k no fue alterada previamente, lo retorno. 
	
}


bool validar_u(string x){
	int i=0,M=0, d=0; bool k=false;
	system("cls");
	
	if( x.size() < 6 || x.size() > 10 ){
		/*Valido que tenga mas de 6 y menos de 8 caracteres, si no se cumple ingresa
		muestra un mensaje de error y retorna a k como true.*/
		if( x.size() < 6){
			cout<<"\n\n\t\tDebe tener mas de 6 caracteres!"; Sleep(1500);system("cls");
			return k=true;
		}
		if( x.size() > 10){
			cout<<"\n\n\t\tDebe tener menos de 10 caracteres!"; Sleep(1500);system("cls");
			return k=true;
		}
	}
	if (!islower(x[0])){
		/*Compruebo que el elemento sea una minuscula, si no lo es entra muestra
		el mensaje de error y retorna a k como un true. */
		cout << "\n\n\t\tDebe empezar con al menos una minuscula!"; Sleep(1500);system("cls");
		return k=true;
	}
	
	while(x[i]!='\0'){//recorro el arreglo para acumular cantidad de digitos y caracteres.
		if (isupper(x[i])){M++; }
		if(isdigit(x[i])){d++; }
		i++;
	}
	
	if (M<2){
	/*Pregunto si el acumulador de mayusculas es menor a 2, si no se cumple 
		muestra mensaje de error y retorna k como true.*/
		cout <<"\n\n\t\tDebe tener al menos dos(2) letras mayusculas!\n"; Sleep(1500);system("cls");
		return k=true;
	}
	
	if (d>3){/*pregunto si el acumulador de numeros es mayor a 3, si no se
		cumple ingresa a la condicion muestra mensaje de error y retorna k como true.*/
		cout << "\n\n\t\tDebe tener como maximo tres(3) numeros!\n"; Sleep(1500);system("cls");
		return k=true;
	}
	
	else
		return k;//si no se pone en true en ningun momento retorno el valor por defecto de k.
}


bool validar_simbolos( string x){
	
	bool k=false; int i=0;
	while( (x[i]!='\0') ){ //Se mantiene el ciclo hasta el final del arreglo o hasta que lo corte el retorno de k.
		
		if(!islower(x[i]) && !isupper(x[i]) && !isdigit(x[i])){
		/* Ingresa al if si el elemento es distinto de una minuscula, mayuscula y digito*/
			
			if (x[i]!='+' && x[i]!= '-' && x[i]!= '/' && x[i]!= '*' && x[i]!= '?' && x[i]!= '!'){
				//Pregunta si el elemento es distinto del conjunto (no pude validar los extendidos ¡ y ¿).

				cout <<"\n\n\tLos simbolos no pretenecen al conjunto definido!"; Sleep(1500);system("cls");
				return k=true; //Informa y el error y retorna k.
			}
			else
				i++; //Si no entra al if anterior incrementa i en uno.
		}
		i++; //Si no entra al if mayor incrementa el i en uno.
	}
	return k; //Si el k no se modifica y retorna durante el ciclo while, retorna el valor default de k.
}
void registrarse(){
	
	bool error=false, error1=false, error2=false;
	usuario usr; usuario usrBusc;
	string claveReingresar;
	
	do{
		Sleep(1500);
		logo();
		cout<<"\n\n\n\t\t\tUsuario: ";
		fflush(stdin); cin >> usr.nombre; fflush(stdin);//pido ingresar nombre de usuario
		error1 = validar_u(usr.nombre); //igualo error a la llamada de la funcion para validar el user
		error2= validar_simbolos(usr.nombre); //Igualo error2 a la llamada de la funcion de validar simbolos.
		
		if (buscarXNombreUsuario(usr.nombre, usrBusc)){ 
			/*Llamo a la funcion para saber si se encuentra disponible el uruario 
			de lo contrario imprime el mensaje*/
			cout << "\n\n\t\t\tEl nombre de usuario no esta disponible." << endl;
		}
		
	}while(error1 || error2 || buscarXNombreUsuario(usr.nombre,usrBusc));
	/*Se mantiene el ciclo mientras alguno de los errores sean diferente de false*/
	
	
	do{
		
		Sleep(1500);
		system("cls");
		cout<<"\t\tContrase"<< char (164)<<"a: ";
		cin >> usr.clave; fflush(stdin); //Pido Ingresar la clave elegida.
		error = validar_c(usr.clave);//Igualo error a la funcion validar contraseña.
	
	}while(error); //Se mantiene el ciclo mientras error sea distinto de false.
	system ("cls");
	cout << "\n\n\t\tReingrese la contraseña para terminar el registro: ";
	cin >> claveReingresar;
	
	if(claveReingresar == usr.clave){
	system("cls");
	cout << "\n\n\t\tUsuario creado con exito!";
	Sleep(1000);
	grabarUsuario(usr); //LLamo a esta funcion para grabar los datos de usario en el .txt.
	}
	
	else{
		system("cls");
		cout << "\n\n\t\tReingreso incorrecto, registro sin exito!";
		Sleep(1000);
	}
	
	system ("cls");

}

bool buscarClave(string nombre, string clave, usuario &usr){
	ifstream archivo;
	
	bool fin=false, encontrado=false;
	
	archivo.open(archUsuarios, ios::in);
	
	if(!archivo.fail()){
		while(!fin && !encontrado){
			archivo >> usr.id >> usr.nombre >> usr.clave;
			
			if((usr.clave==clave) && (usr.nombre==nombre)) {
				encontrado=true;
			}
			
			if(archivo.eof()) 
				fin=true;
		}
		archivo.close();
	}
	Sleep(1000);
	system("cls");
	return encontrado;
	
}

void IniciarSesion(){
	usuario usr, usrBusc;
	int i=0; bool ingresa=false;
	usuarioActual.nombre = ""; usuarioActual.clave = ""; usuarioActual.id = '\0';
	system("cls");
	
	do{
		logo();
		
		cout << "\n\t\t\t\tINICIAR SESION\n";
		separacion();
		
		cout << "\n\n\n\t\t\tUsuario:    ";
		fflush(stdin); cin >> usr.nombre; fflush(stdin);
		/*Se pide de ingresar el nombre de usuario.*/
		
		cout << "\n\t\t\tContraseña: ";
		fflush(stdin); cin >> usr.clave; 
		/*Se pide de ingresar la Contraseña o clave del respectivo user.*/
		
		if ( buscarXNombreUsuario(usr.nombre, usrBusc) && buscarClave(usr.nombre, usr.clave, usrBusc) ){
		/*Si el user y contraseña son correctos se da el valor de true a 
		ingresa y se corta la interacion del do while.*/
			ingresa  = true;
		}
		
		else{
			/*Si el usario y/o contraseña son erroneos se da el mensaje, 
			incrementa i en uno y vuelve al comienzo del do while.*/
			logo();
			cout << "\n\n\n\n\n\n\n\t\t     ----------------------------------------\n";
			cout << "\t\t    | El usuario y/o password son incorrectos|";
			if (i==0 && Bandera == false){cout << "\n\t\t    |       Tiene tres(3) intentos mas       |";}
			cout << "\n\t\t     ----------------------------------------\n";
			i++;
			getch();
			system ("cls");
		}
		
	}while( ingresa==false && i<4 );
	
		
		if( ingresa == true && i < 4 ){
		/*Si el usuario y contraseña son correctos ingresa se pone en true en
			el paso anterior asi ingresando a el if y mostrando estos datos
		
		cout << "\n\n\n\t\t\tBienvenido!\n\n";*/
		usuarioActual.nombre = usr.nombre;
		usuarioActual.clave	 = usr.clave;
		usuarioActual.id = buscar_id(usr.nombre, usr.clave, usrBusc);
		/*cout << "Id: " << usuarioActual.id <<endl;
		cout << "Nombre: " << usuarioActual.nombre <<endl;
		cout << "Clave: " << usuarioActual.clave <<endl;
		*/
		
		menu_de_juego();
			
		}
		
		string userCapcha, ingresarCaptcha, cp; 
		
		if (Bandera == false){
		if (ingresa != true && i==4 ) {
			/*Si los intentos de iniciar sesionn se acabaron se entra a este if 
			donde se genera un codigo captcha*/
			logo();
			cout << "\n\t\t\t        COMPROBACION DE CAPCHA\n";
			separacion();
		    cout << "\n\n\n\n\t\t\t:: Ingrese el nombre de usuario ::\n\n\t\t\t\t    ";
			
			fflush(stdin); cin >> userCapcha; fflush(stdin);
			/*Se pide el ingreso del usuario con el que deseaba iniciar sesion.*/
		
			cout << "\n\n\t\t\t\t*******************\n\t\t\t\t* ";
			captcha("AlGoRiTmOs", userCapcha, cp); 
			/*Se llama a la funcion captcha la cual se encarga de generar este codigo.*/
			for(int i =0 ; i<15; i++){ cout << cp[i];} 
			/*Se muestra en pantalla el codigo.*/
			cout << " *\n\t\t\t\t*******************\n\n\n\t\t\t >>>\t  ";
			cin >> ingresarCaptcha;
			/*Se pide que ingresar lo que contiene el codigo captcha.*/
			int cont=0;
			
			for(int i =0 ; i<15; i++){if (cp[i] == ingresarCaptcha[i]){ cont++; } }
			/*Comparo el capcha generado con el ingresado.*/
			
			if (cont < 14 ){ 
			/*Si el capcha ingresado a validar no es correcto se muestra 
			mensaje de error y cierra la aplicacion*/
				system("cls");
				logo();
				cout << "\n\t\t\t    >> ¡ERROR DE CAPTCHA! <<\n";
				separacion();
						 cout << "\n\n\n\n\n\n\t\t\t------------------------------------\n";
				cout << "\t\t\t| ¡Posible violacion de Seguridad! |\n\t\t\t|    Esta Aplicacion se cerrara.   |\n";
				cout << "\t\t\t------------------------------------\n\n\n\n\n\n\n\n";
			}
			
			if (cont == 15){
			/*Si lo ingresado es igual al codigo generado ingresa a este if 
			muestra este mensaje y vuelve a dar solamente una posibilidad de un 
			inicio de sesion con tres intentos*/
				system ("cls");
				logo();
				cout << "\n\t\t\t\tCAPTCHA CORRECTO\n";
				separacion();
				cout << "\n\n\n\n\n\t>> Tiene otros tres intentos para lograr el inicio de sesion. <<";
				fflush (stdin); getch(); fflush(stdin);
				
				Bandera = true; 
				/*Pongo en true a Bandera, el cual quiere decir que ya se dio 
				una oportunidad mas de inicio de sesion.*/
				
				IniciarSesion(); //Llamo la funcion IniciarSesion.
			}
		}
			
		}
}

int buscar_id(string nombre, string clave, usuario &usr){
	
	ifstream archivo;
	
	bool fin=false, encontrado=false;
	int i=0;
	archivo.open(archUsuarios, ios::in);
	
	if(!archivo.fail()){
		while(!fin && !encontrado){
			archivo >> usr.id >> usr.nombre >> usr.clave;
			
			if((usr.clave==clave) && (usr.nombre==nombre)) {
				
				encontrado=true;
				
			}
			
			if(archivo.eof()) {
				fin=true;
			}
			i++;
		}
		archivo.close();
	}	
	return i;
}

void logo(){ //El logo.
	separacion(); //Llamo a decoracion separacion.
	system("color 0A");
	cout << "\n\t\t\t      00  00 000000 00  00\n";
	cout << "  00000  00000   0000   0000  00  00 000000 00  00  0000  00000   0000   0000 \n"<<
		"  00  00 00  00 00  00 00  00 00  00   00   00 000 00  00 00  00 00  00 00  00\n"<<
		"  00  00 00  00 00     00     00  00   00   000000 00  00 00  00 00  00 00    \n"<<
		"  0000   0000   0000   00 000 00  00   00   000000 000000 00  00 00  00  0000\n"<<
		"  00     00 00  0000   00  00 00  00   00   000000 00  00 00  00 00  00     00\n"<<
		"  00     00  00 00     00  00 00  00   00   000 00 00  00 00  00 00  00     00\n"<<
		"  00     00  00 00  00 00  00 00  00   00   00  00 00  00 00  00 00  00 00  00\n"<<
		"  00     00  00  0000   0000  00  00   00   00  00 00  00 00000   0000   0000 \n";
	cout << "\t\t\t      000000   00   00  00\n";
	separacion();
}
void separacion(){ //Separacion (Decoracion de asteriscos).
	for (int i=0; i<26; i++){
		cout <<" **";
	}
}
void inicio(){
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\n\n\n\t\t\t\t    CARGANDO\n\n\t\t\t  ";
	cargando(); //Llamo a cargando (decoracion barra progresando).
	system("cls"); //Limpio pantalla.
	logo();
	system("color F1");
	cout << "\n\n\n\t  FLORENCIA ANCHAVAL - flor.anchaval12@gmail.com - COMISION F\n\n\t"<<
		"  CLAUDIO MONGUZZI - claudio_monguzzi@hotmail.com - COMISION F"<< 
		"\n\n\t  SANTIAGO MONGUZZI - santiagomonguzzi@gmail.com - COMISION F\n" << endl;
	cout << "\t\t\t\tVERSION 2.0 - 2015" << endl; //Muestro info en pantalla.
	Sleep(2000);system("cls");
}
void cargando(){ //cargando (decoracion barra progresando),
	system("color E");
	for(int i=0; i<28; i++){
		Sleep(50); cout << char(219);
	}
	cout << "\a"; Sleep(10); system("cls");
}
void captcha(string P, string N, string cp){
	srand(time(NULL));
	int R=(10000+rand()%50000); 
	//string P = "AlGoRiTmOs";
	char a=N[0], b=N[N.size()-1]; //declaro una variable con el primer caracter del nombre de usuario y otra con el ultimo 
	int i=0, h=0;//Declaro h e i (son contadores) y aux.
	while(i!=a){i++;} while(h!=b){h++;} //intero hasta llegar al valor ascii de la variable a y b.
	int aux=i+h+R; //sumo en Aux los valores de los contadores a y b mas el numero aleatorio .
	
	char n[5];
	for(int i =0; i<5; i++){
		
		int k=100000, h = aux%k; //declaro k, igualo h a el modulo de aux de k(que es 100000 en ese momento)
		
		sprintf(n, "%d", h); //hago que n de i sea igual al modulo de k(seria h).
		k=k/10; //achico k para optener otro modulo de aux.
	}
	
	for (int i=0; i<5; i++){ //Ordeno el arreglo de mayor a menor.
		for (int k=0; k<4; k++){
			if (n[i]>n[k]){int aux=n[i]; n[i]=n[k]; n[k]=aux;}
		}
	}
	
	string c; int j=2, k=0, d=0; //construyo la cadena intermedia.
	for (int i=0; i<15; i++){
		if (i==j){c[i]=n[k]; j=j+3; k++;}
		else
		{c[i]=P[d]; d++;}
	}
	
	invertir(c); //llamo a la funcion invertir.
	
	cp = c; //igualo a cp con el codigo generado.
}

void invertir(string c){
	int k=14, i=0; 
	while (i!=k){
		char aux=c[i]; c[i]=c[k]; c[k]=aux;
		k--; i++;
	}	
}

void menu_de_juego(){
	system("cls");
	char opcion;
	
	while(opcion != '7'){
		system("cls");
		logo();
		cout << "\n\t\t\t    BIENVENIDO "<< char(34) << usuarioActual.nombre << char(34) << "!\n";
		separacion();
		cout << "\n\n\t\t\t1.- MI CUENTA\n\t\t\t2.- INCIAR PARTIDA"
			<< "\n\t\t\t3.- PARTIDAS INICIADAS\n\t\t\t4.- PARTIDAS PENDIENTES DE JUEGO"
			<<"\n\t\t\t5.- PARTIDAS TERMINADAS POR EL OPONENTE"
			<<"\n\t\t\t6.- MIS ESTADISTICAS\n\t\t\t7.- CERRAR SESION"
			<< "\n\n\t\t\tOPCION: ";
			cin >> opcion;
			cin.ignore(256,'\n');
			system("cls");
		switch(opcion){
		case '1': system("cls"); mi_cuenta(); getch(); ; break;  
			case '2': system("cls"); cout << "desarrollo"; getch(); ; break;
			case '3': system("cls"); cout << "desarrollo"; getch(); ; break;
			case '4': system("cls"); cout << "desarrollo"; getch(); ; break; 
			case '5': system("cls"); cout << "desarrollo"; getch(); ; break;
			case '6': system("cls"); cout <<"\n\n\t\t\tFUNCIONALIDAD EN DESARROLLO"; getch(); ;break; 
			case '7':
				system("cls");
				logo();
				usuarioActual.nombre = "";
				usuarioActual.clave  = "";
				usuarioActual.id     = '\0';
				cout << "\n\n\n\t\t\tGracias por utilizar PregUTNados!\n\n\n\n"; 
				getch();
				; break;
			default: 
				system("cls");
				logo();
				cout << endl << "\t\t\n\n\n\t\t  >> Opcion incorrecta, vuelva a intentarlo <<" << endl << endl;
				getch();
				; break;
	}
	}
}

void mi_cuenta(){
	
	system("cls");
	logo();
	cout << "\t\t\t\t\t   MI CUENTA \n";
	separacion(); cout <<"\n\n\n\n\n";
	cout << "\t..........\n\t.   --   .\tNombre de usuario: "<< usuarioActual.nombre << "\n\t.  ----  .\n\t.  ----  ."<<
		"\tContrase"<< char(164) <<"a: " << usuarioActual.clave << "\n\t.   --   .\n\t.  ----  .\tId de Usuario: " << usuarioActual.id << "\n\t. ------ .\n\t."<<
			" ------ .\n\t.........." ;
	cout << "\n\n\n\n\n\n\t>> PRESIONE UNA TECLA CUALQUIERA PARA RETORNAR AL MENU DE JUEGO <<\n";
}

void ruleta(){
	srand(time(NULL)); //Actualizo la semilla del reloj.
	int op; //Declaro un entero que va a ser usado para igualar a la opcion del Switch.
	for (;;){
		Sleep(80); //Le doy un delay al for para que puedan ser vistos las graficas.
		int x=1+rand()%5; //Genero una opcion del uno a el cinco cada vez que intera el for.
		system("cls"); //Hago un borrado de pantalla. 
		switch(x){
			/*Este switch llama a las graficas de las categorias hasta que corte el for.*/
			case 1:	Lami();   ; break; 
			case 2: Laedd();  ; break;
			case 3: Lmatdis();; break;
			case 4: Larq();   ; break;
			case 5: Lfisica();; break;
		}
		op=x;//Igualo op a la ultima opcion generada (la cual fue seleccionada).
		if (kbhit()){break;} 
		/*kbhit es una funcion la cual se encarga de cortar el bucle for cuando
		es presionada una tecla*/
	}
	Sleep(2000); //Delay el cual se encarga de dejar por unos segundos la grafica de la categoria.
	system("cls"); //Borra la pantalla.
	switch(op){
	/*Este switch se encarga de llamar a la funcion que muestra la pregunta y 
		envia el id de categoria para que cargue preguntas de ella.*/
	case 1:	cout << "Analisis Matematico 1"; ; break;
	case 2:	cout << "Algoritmos y Estructuras de Datos"; ; break;
	case 3: cout << "Matematica Discreta"; ; break;
	case 4:	cout << "Arquitectura de Computadoras"; ; break;
	case 5: cout << "Fisica 1"; ; break;
	}
	system ("pause");
	
}

/*-------------------- Estos son las graficas de las categorias --------------*/
void Lami(){
	/*Grafica de la categoria Analisis Matematico*/
	system("color 1");
	cout <<"\t\t\t db         7MMM      ,MMF       \n\t\t        ;MM:         MMMb    dPMM     __  \n"
		"\t\t       ,V^MM.        M YM   ,M MM    /MM  \n\t\t      ,M   MM        M  Mb  M  MM     MM  \n"
		"\t\t      AbmmmqMA       M  YM.P   MM     MM  \n\t\t     A      VML      M  .YM.   MM     MM  \n"
		"\t\t   .AMA.    .AMMA. .JML.     .JMML. .JMML.\n"<<endl;
}
void Laedd(){
	/*Grafica de la categoria Algoritmo y estructura de datos */
	system("color A");
	cout << 
		"\t             db      `7MM111YMM  `7MM111Yb.   `7MM111Yb.\n\t	    ;MM:       MM    `7    MM    `Yb.   MM    `Yb.\n" 
		"\t	   ,V^MM.      MM   d      MM     `Mb   MM     `Mb\n\t	  ,M  `MM      MMmmMM      MM      MM   MM      MM\n" 
		"\t	  AbmmmqMA     MM   Y      MM     ,MP   MM     ,MP\n\t	 A      VML    MM      M   MM    ,dP    MM    ,dP\n"  
		"\t       .AMA.   .AMMA..JMMmmmmMMM .JMMmmmdP    .JMMmmmdP\n";  
}
void Lmatdis(){
	/*Grafica de la categoria Matematica Discreta*/
	system("color c");
	cout << "\t `7MMM.     ,MMF            mm    `7MM111Yb.     db\n\t   MMMb    dPMM             MM      MM    `Yb.\n"               
		"\t   M YM   ,M MM   ,61Yb.  mmMMmm    MM     `Mb `7MM  ,pP1Ybd\n\t   M  Mb  M  MM  8)   MM    MM      MM      MM   MM  8I   `;\n" 
		"\t   M  YM.P   MM   ,pm9MM    MM      MM     ,MP   MM  `YMMMa.\n\t   M  `YM    MM  8M   MM    MM      MM    ,dP    MM  L.   I8\n" 
		"\t .JML. `   .JMML.`Moo9^Yo.  `Mbmo .JMMmmmdP    .JMML.M9mmmP\n"; 
}
void Larq(){
	/*Grafica de la categoria Arquitectua de Computadoras*/
	system("color D");
	cout << "\t\t     db                                  .g81bgd\n" 
		"\t	    ;MM:                               .dP     `M\n" 
		"		   ,V^MM.    `7Mb,od8   ,dW1Yvd        dM       `\n		  ,M  `MM      MM  ;   ,W    MM        MM\n"          
		"		  AbmmmqMA     MM      8M    MM  mmmm  MM.\n		 A      VML    MM      YA.   MM        `Mb.     ,\n" 
		"	       .AMA.   .AMMA. JMML.     `MbmdMM          `:bmmmd\n\t\t\t\t\t     MM\n\t\t\t\t\t   .JMML.\n";
}
void Lfisica(){
	/*Grafica de la categoria Fisica 1*/
	system("color E");
	cout << "\t `7MM111YMM   db            db\n\t   MM    `7                                             __,\n"  
		"\t   MM   d   `7MM  ,pP1Ybd `7MM   ,p61bo   ,61Yb.       /MM\n\t   MM11MM     MM  8I   `;   MM  6M   OO  8)   MM        MM\n" 
		"\t   MM   Y     MM  `YMMMa.   MM  8M        ,pm9MM        MM\n\t   MM         MM  L.   I8   MM  YM.    , 8M   MM        MM\n"  
		"\t .JMML.     .JMML.M9mmmP  .JMML. YMbmd   `Moo9^Yo.    .JMML\n";
}
/*----------------------------------------------------------------------------*/
