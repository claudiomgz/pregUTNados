/*****************************************************************************
		Alumnos:  Claudio Monguzzi | Santiago Monguzzi.
							 PregUTNados.
							UTN FRSF 2016.
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <ctime>
#define MAX_FILA 5
#define MAX_COL 88
#define TAMT 100
#define TAM 50
#include <fstream>
#include <iomanip>

using namespace std;

struct usuario
{
	int id;
	string nombre;
	string clave;
};

struct partida
{
	long idPartida;
	int idUI, idUO; //Identificador del usuario inicial y oponente.
	int categorias[10];
	int preguntas[10];
};

struct fecha
{
	int anio, mes, dia, hora, mins, segs;
};

struct Pregunta
{
	int idCategoria;
	int idPregunta;
	int numeroGrupo;
	string pregunta;
	string opciones[4];
	int opcionCorrecta; //Sub�ndice de la opci�n correcta.
};

struct jugada
{
	long idPartida;
	int idUsr;
	bool rtas[10];
	int puntaje; //Se computar� cuando el usuario finaliza su jugada.
};

bool buscarXNombreUsuario(string nombre, usuario &usr);
/*  Busca en el archivo usuarios.txt un usuario a partir del nombre. 
	Si lo encuentra retorna true y devuelve en usr los datos del usuario, 
	sino retorna false.
*/

bool buscarXIdUsuario(int id, usuario &usr);
/*  Busca en el archivo usuarios.txt un usuario a partir de un id de usuario. 
	Si lo encuentra retorna true y devuelve en usr los datos del usuario, 
	sino retorna false.
*/

bool grabarUsuario(usuario usr);
/*  Intenta registrar un nuevo usuario al sistema. 
	Si lo puede registrar retorna true, 
	pero si existe un usuario con el mismo nombre, o si hubo alg�n problema con la gesti�n del archivo, 
	no pudiendo registrarlo, retorna false. 
*/
bool obtenerXIdUsuario(int &id);
/*  Funci�n auxiliar utilizada por registrarUsuario que recorre todo el archivo usuarios.txt
	para as� obtener autom�ticamente el pr�ximo id a asignar.
*/
bool buscarClave(string, string, usuario &usr);
/*Funcion para obtener clave.*/
void registrarse();
/*Funcion que lleva a cabo la toma de datos de user y clave*/
bool validar_c(string);
/*Valida la clave.*/
bool validar_u(string);
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
void captcha(string P, string N, string);
/*Genera un codigo despues que se cometio en tres(3) oportunidades un inicio 
de sesion erroneo*/
void invertir(string c);
/*Funcion para poder generar el codigo Capcha, este se encarga de hacer 
una inversion del codigo generado dentro de la funcion captcha*/
void menu_principal(); /*Menu principal del juego*/
void menu_de_juego();  /*Menu de juego*/
void mi_cuenta();	   /*Menu Referida a la cuenta del usuario con sesion actual*/
void ruleta(partida &P, jugada &J);
/*Funcion que muestra en pantalla los graficos de las categorias y llama a cargar las preguntas*/
void Lami();
void Laedd();
void Lmatdis();
void Larq();
void Lfisica();
void gotoxy(short x, short y);
void obtenerFechaActual(fecha &f);
void obtenerFechaActual(fecha &f);
void mostrarPregunta(int, partida &P, jugada &J);
void cargaDePreguntas(Pregunta matrizPreguntas[][MAX_COL]);
void grabarPartida(partida &P);
int obtenerIdUsuario();
void obtenerPuntaje(jugada &J);
void grabarJugada(jugada &J);
void crearPartida();
void EstCat();
void PartIniciadas();  //Crea un arreglo con el id de partida y oponente de las partidas iniciadas.
void PartPendientes(); //Crea un arreglo con el id de partida y Oponente de las partidas Pendientes.
void PartTerminadas(); //Crea un arreglo con el id de partida y Oponente de las partidas terminadas.
bool repetido(long a[], int k);
void decodificar(long f2);

int Oponente;
int contPreg;

const char *archUsuarios = "usuarios.txt";
/* Constante de tipo char la cual esta igalada la informacion propia de los 
usuarios, Id User y Clave.*/
usuario usuarioActual;
/*Variable donde se almacenara el usuario que inicio sesion.*/
bool Bandera = false;
bool Bandera2 = false;
/*Variable donde almacena un valor logico el cual se 
encarga de hacer de bandera si se ingresa a la opcion de capcha.*/

int main(int argc, char *argv[])
{
	system("mode con: cols=80 lines=35"); /*Le doy un tama�o predeterminado a la consola*/

	inicio();		  /*Llamo a la funcion inicio.*/
	menu_principal(); /*Llamo a la funcion que contiene la estructura del menu principal.*/

	return 0;
}

void menu_principal()
{
	usuario u;	   /*Declaro una variable con la estructura usuario*/
	string nombre; /*Declaro una variable nombre para tomar dicho dato temporalmente.*/
	char opcion;   /*Declaro una variable char para utilizar como opcion del menu.*/
	while (opcion != '4')
	{
		/*Intero hasta que sea distinto de la salida o una opcion correcta.*/
		system("cls");
		logo();
		cout << "\n\t\t\t\t MENU PRINCIPAL\n";
		separacion();
		cout << endl
			 << endl;
		cout << "\t\t\t    1.- Registrarse" << endl;
		cout << "\t\t\t    2.- Iniciar Sesion" << endl;
		cout << "\t\t\t    3.- Estadisticas de juego" << endl;
		cout << "\t\t\t    4.- Salir" << endl
			 << endl;
		cout << "\t\t\t    Ingrese una opcion: ";
		cin >> opcion;
		cin.ignore(256, '\n');
		switch (opcion)
		{
		case '1':
			system("cls");
			registrarse();
			break;

		case '2':
			system("cls");
			Bandera = false;
			IniciarSesion();
			break;

		case '3':
			system("cls");
			logo();
			cout << "\n\t\t\t      ESTADISTICAS DEL JUEGO\n";
			separacion();
			EstCat();
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
			cout << endl
				 << "\t\t\n\n\n\t\t  >> Opcion incorrecta, vuelva a intentarlo <<" << endl
				 << endl;
			getch();

			break;
		}
	}
}

bool buscarXNombreUsuario(string nombre, usuario &usr)
{
	ifstream archivo;

	bool fin = false, encontrado = false;

	archivo.open(archUsuarios, ios::in);

	if (!archivo.fail())
	{
		while (!fin && !encontrado)
		{
			archivo >> usr.id >> usr.nombre >> usr.clave;

			if (usr.nombre == nombre)
			{
				encontrado = true;
			}

			if (archivo.eof())
				fin = true;
		}
		archivo.close();
	}
	Sleep(1000);
	system("cls");
	return encontrado;
}

bool buscarXIdUsuario(int id, usuario &usr)
{
	ifstream archivo;

	bool fin = false, encontrado = false;

	archivo.open(archUsuarios, ios::in);

	if (!archivo.fail())
	{
		while (!fin && !encontrado)
		{
			archivo >> usr.id >> usr.nombre >> usr.clave;

			if (usr.id == id)
			{
				encontrado = true;
			}

			if (archivo.eof())
				fin = true;
		}
		archivo.close();
	}
	return encontrado;
}

bool grabarUsuario(usuario usr)
{
	//usuario usrBusc;
	bool rta = true;
	ofstream archivo;

	archivo.open(archUsuarios, ios_base::app);
	if (archivo.fail())
	{
		rta = false;
	}
	else
	{
		if (obtenerXIdUsuario(usr.id))
		{
			archivo << endl
					<< usr.id << " " << usr.nombre << " " << usr.clave;
		}
		else
			rta = false;
		archivo.close();
	}
	return rta;
}

bool obtenerXIdUsuario(int &id)
{
	ifstream archivo;
	usuario usr;
	int i = 0;
	bool fin = false, rta = true;

	archivo.open(archUsuarios, ios::in);

	if (archivo.fail())
		rta = false;
	else
	{
		while (!fin)
		{
			archivo >> usr.id >> usr.nombre >> usr.clave;
			if (archivo.eof())
				fin = true;
			i++;
		}
		id = ++i;
		archivo.close();
	}
	return rta;
}
bool validar_c(string p)
{
	bool k = false;
	if (p.size() < 6)
	{
		cout << "\t\tDebe tener mas de 6 caracteres!";
		return k = true;
		getch();
	} //Pregunto si es menor que el min definido.
	if (p.size() > 8)
	{
		cout << "\t\tDebe tener menos de 8 caracteres!";
		return k = true;
		getch();
	} //Pregunto si es mayor que el max definido.

	int i = 0, a = 0; //Declaro contadores.

	while (p[i] != '\0')
	{ //Intero hasta el final del arreglo.
		if (isupper(p[i]))
		{
			a++;
		} //Si es Mayuscula incremento el contador a en uno.
		i++;
	}
	if (a == 0)
	{
		cout << "\t\tDebe tener por lo menos una letra mayuscula!";
		return k = true;
		getch();
	} //Pregunto si a es igual a cero (es decir no contiene mayusculas), informo error y retorno k.

	a = 0;
	i = 0; //Pongo en cero los contadores para poder reutilizarlos.
	while (p[i] != '\0')
	{ //Intero hasta el final del arreglo.
		if (isdigit(p[i]))
		{
			a++;
		} //Si es un numero incremento el contador a en uno.
		i++;
	}
	if (a == 0)
	{
		cout << "\t\tDebe tener por lo menos un Numero!";
		return k = true;
		getch();
	} //Pregunto si a es igual a cero (es decir no contiene numero), informo error y retorno k.

	i = 0; //Pongo el contador en cero para reutilizarlo.
	while (p[i] != '\0')
	{

		int b = 0, c = 0, d = 0, a = 0;

		if (isdigit(p[i]) && isdigit(p[i + 1]) && isdigit(p[i + 2]) && isdigit(p[i + 3]))
		{ //Si el elemento i y los 3 seiguientes son un num entonces comprueba el if interno.
			while (a != p[i])
			{
				a++;
			}
			while (b != p[i + 1])
			{
				b++;
			}
			while (c != p[i + 2])
			{
				c++;
			}
			while (d != p[i + 3])
			{
				d++;
			} //Busco los valores ascii de los 4 digitos.
			if (a + 1 == b && b + 1 == c && c + 1 == d)
			{ //Pregunto si son seguidos, sino salgo de este if.
				cout << "\tNo debe tener mas de tres(3) numeros consecutivos!";
				return k = true;
				getch(); //Si lo son informo el error y retorno k.
			}
		}

		if (islower(p[i]) && islower(p[i + 1]))
		{				  //Pregunto si en el elemento i y i+1 se encuentran minusculas.
			a = 0, b = 0; //Pongo en cero contadores para reutilizarlos.
			while (a != p[i])
			{
				a++;
			}
			while (b != p[i + 1])
			{
				b++;
			} //Busco los valores ascii de estos caracteres.
			if ((a + 1) == b)
			{ // �preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) Minusculas consecutivos ascendentes!";
				return k = true;
				getch(); //Si lo son informo el error y reotorno k.
			}
		}

		if (isupper(p[i]) && isupper(p[i + 1]))
		{				  //Pregunto si en el elemento i y i+1 se encuentran minusculas.
			a = 0, b = 0; //Pongo en cero contadores para reutilizarlos.
			while (a != p[i])
			{
				a++;
			}
			while (b != p[i + 1])
			{
				b++;
			} //Busco los valores ascii de estos caracteres.
			if ((a + 1) == b)
			{ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) Mayusculas consecutivos ascendentes!";
				return k = true;
				getch(); //Si lo son informo el error y reotorno k.
			}
		}

		if (islower(p[i]) && isupper(p[i + 1]))
		{								//Pregunto si en el elemento i se encuentra una minuscula y i+1 se encuentra una mayuscula.
			a = 0, b = 0;				//Pongo en cero contadores para reutilizarlos.
			char h = tolower(p[i + 1]); //Declaro una variable h la igualo a el formato minuscula del elemento p[i+a].
			while (a != p[i])
			{
				a++;
			}
			while (b != h)
			{
				b++;
			} //Busco los valores ascii de estos caracteres.
			if (((a + 1) == b) || a < b)
			{ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) caracteres consecutivos ascendentes!";
				return k = true;
				getch(); //Si lo son informo el error y reotorno k.
			}
		}

		if (isupper(p[i]) && islower(p[i + 1]))
		{							//Pregunto si en el elemento i se encuentra una mayuscula y i+1 una minuscula.
			a = 0, b = 0;			//Pongo en cero contadores para reutilizarlos.
			char h = tolower(p[i]); //Declaro una variable h la igualo a el formato minuscula del elemento p[i+a].
			while (a != h)
			{
				a++;
			}
			while (b != p[i + 1])
			{
				b++;
			} //Busco los valores ascii de estos caracteres.
			if (((a + 1) == b) || a > b)
			{ // Preguntos si estos valores son consecutivos.
				cout << "\tNo debe tener dos(2) caracteres consecutivos ascendentes!";
				return k = true;
				getch(); //Si lo son informo el error y reotorno k.
			}
		}

		i++; //Si no entra en ninguna condicion incremento el contador i para continuar el ciclo while.
	}
	return k; //Si k no fue alterada previamente, lo retorno.
}

bool validar_u(string x)
{
	int i = 0, M = 0, d = 0;
	bool k = false;

	if (x.size() < 6 || x.size() > 10)
	{
		/*Valido que tenga mas de 6 y menos de 8 caracteres, si no se cumple ingresa
		muestra un mensaje de error y retorna a k como true.*/
		if (x.size() < 6)
		{
			cout << "\n\n\t\tDebe tener mas de 6 caracteres!";
			getch();
			return k = true;
		}
		if (x.size() > 10)
		{
			cout << "\n\n\t\tDebe tener menos de 10 caracteres!";
			getch();
			return k = true;
		}
	}
	if (!islower(x[0]))
	{
		/*Compruebo que el elemento sea una minuscula, si no lo es entra muestra
		el mensaje de error y retorna a k como un true. */
		cout << "\n\n\t\tDebe empezar con al menos una minuscula!";
		getch();
		return k = true;
	}

	while (x[i] != '\0')
	{ //recorro el arreglo para acumular cantidad de digitos y caracteres.
		if (isupper(x[i]))
		{
			M++;
		}
		if (isdigit(x[i]))
		{
			d++;
		}
		i++;
	}

	if (M < 2)
	{
		/*Pregunto si el acumulador de mayusculas es menor a 2, si no se cumple 
		muestra mensaje de error y retorna k como true.*/
		cout << "\n\n\t\tDebe tener al menos dos(2) letras mayusculas!\n";
		getch();
		return k = true;
	}

	if (d > 3)
	{ /*pregunto si el acumulador de numeros es mayor a 3, si no se
		cumple ingresa a la condicion muestra mensaje de error y retorna k como true.*/
		cout << "\n\n\t\tDebe tener como maximo tres(3) numeros!\n";
		getch();
		return k = true;
	}

	else
		return k; //si no se pone en true en ningun momento retorno el valor por defecto de k.
}

bool validar_simbolos(string x)
{

	bool k = false;
	int i = 0;
	while ((x[i] != '\0'))
	{ //Se mantiene el ciclo hasta el final del arreglo o hasta que lo corte el retorno de k.

		if (!islower(x[i]) && !isupper(x[i]) && !isdigit(x[i]))
		{
			/* Ingresa al if si el elemento es distinto de una minuscula, mayuscula y digito*/

			if (x[i] != '+' && x[i] != '-' && x[i] != '/' && x[i] != '*' && x[i] != '?' && x[i] != '!')
			{
				//Pregunta si el elemento es distinto del conjunto (no pude validar los extendidos � y �).

				cout << "\n\n\tLos simbolos no pretenecen al conjunto definido!";
				getch();
				return k = true; //Informa y el error y retorna k.
			}
			else
				i++; //Si no entra al if anterior incrementa i en uno.
		}
		i++; //Si no entra al if mayor incrementa el i en uno.
	}
	return k; //Si el k no se modifica y retorna durante el ciclo while, retorna el valor default de k.
}
void registrarse()
{

	bool error = false, error1 = false, error2 = false;
	usuario usr;
	usuario usrBusc;
	string claveReingresar;

	if (obtenerIdUsuario() == 100)
	{
		system("cls");
		logo();
		gotoxy(15, 20);
		cout << "El registro de cuantas a llegado a su cantidad maxima";
		getch();
	}

	else
		do
		{
			Sleep(1500);
			logo();
			cout << "\n\n\n\t\t\tUsuario: ";
			fflush(stdin);
			cin >> usr.nombre;
			fflush(stdin);						   //pido ingresar nombre de usuario
			error1 = validar_u(usr.nombre);		   //igualo error a la llamada de la funcion para validar el user
			error2 = validar_simbolos(usr.nombre); //Igualo error2 a la llamada de la funcion de validar simbolos.

			if (buscarXNombreUsuario(usr.nombre, usrBusc))
			{
				/*Llamo a la funcion para saber si se encuentra disponible el uruario 
			de lo contrario imprime el mensaje*/
				cout << "\n\n\t\t\tEl nombre de usuario no esta disponible." << endl;
				getch();
			}

		} while (error1 || error2 || buscarXNombreUsuario(usr.nombre, usrBusc));
	/*Se mantiene el ciclo mientras alguno de los errores sean diferente de false*/

	do
	{

		cout << "\n\t\tContrase" << char(164) << "a: ";
		cin >> usr.clave;
		fflush(stdin);				  //Pido Ingresar la clave elegida.
		error = validar_c(usr.clave); //Igualo error a la funcion validar contrase�a.

	} while (error); //Se mantiene el ciclo mientras error sea distinto de false.
	system("cls");
	cout << "\n\n\t\tReingrese la contrase�a para terminar el registro: ";
	cin >> claveReingresar;

	if (claveReingresar == usr.clave)
	{
		system("cls");
		cout << "\n\n\t\tUsuario creado con exito!";
		Sleep(1000);
		grabarUsuario(usr); //LLamo a esta funcion para grabar los datos de usario en el .txt.
	}

	else
	{
		system("cls");
		cout << "\n\n\t\tReingreso incorrecto, registro sin exito!";
		Sleep(1000);
	}

	system("cls");
}

bool buscarClave(string nombre, string clave, usuario &usr)
{
	ifstream archivo;

	bool fin = false, encontrado = false;

	archivo.open(archUsuarios, ios::in);

	if (!archivo.fail())
	{
		while (!fin && !encontrado)
		{
			archivo >> usr.id >> usr.nombre >> usr.clave;

			if ((usr.clave == clave) && (usr.nombre == nombre))
			{
				encontrado = true;
			}

			if (archivo.eof())
				fin = true;
		}
		archivo.close();
	}
	Sleep(1000);
	system("cls");
	return encontrado;
}

void IniciarSesion()
{
	usuario usr, usrBusc;
	int i = 0;
	bool ingresa = false;
	usuarioActual.nombre = "";
	usuarioActual.clave = "";
	usuarioActual.id = '\0';
	system("cls");

	do
	{
		logo();

		cout << "\n\t\t\t\tINICIAR SESION\n";
		separacion();

		cout << "\n\n\n\t\t\tUsuario:    ";
		fflush(stdin);
		cin >> usr.nombre;
		fflush(stdin);
		/*Se pide de ingresar el nombre de usuario.*/

		cout << "\n\t\t\tContrase�a: ";
		fflush(stdin);
		cin >> usr.clave;
		/*Se pide de ingresar la Contrase�a o clave del respectivo user.*/

		if (buscarXNombreUsuario(usr.nombre, usrBusc) && buscarClave(usr.nombre, usr.clave, usrBusc))
		{
			/*Si el user y contrase�a son correctos se da el valor de true a 
		ingresa y se corta la interacion del do while.*/
			ingresa = true;
		}

		else
		{
			/*Si el usario y/o contrase�a son erroneos se da el mensaje, 
			incrementa i en uno y vuelve al comienzo del do while.*/
			logo();
			cout << "\n\n\n\n\n\n\n\t\t     ----------------------------------------\n";
			cout << "\t\t    | El usuario y/o password son incorrectos|";
			if (i == 0 && Bandera == false)
			{
				cout << "\n\t\t    |       Tiene tres(3) intentos mas       |";
			}
			cout << "\n\t\t     ----------------------------------------\n";
			i++;
			getch();
			system("cls");
		}

	} while (ingresa == false && i < 4);

	if (ingresa == true && i < 4)
	{
		/*Si el usuario y contrase�a son correctos ingresa se pone en true en
			el paso anterior asi ingresando a el if y mostrando estos datos
		
		cout << "\n\n\n\t\t\tBienvenido!\n\n";*/
		usuarioActual.nombre = usr.nombre;
		usuarioActual.clave = usr.clave;
		usuarioActual.id = buscar_id(usr.nombre, usr.clave, usrBusc);
		/*cout << "Id: " << usuarioActual.id <<endl;
		cout << "Nombre: " << usuarioActual.nombre <<endl;
		cout << "Clave: " << usuarioActual.clave <<endl;
		*/

		menu_de_juego();
	}

	string userCapcha, ingresarCaptcha, cp;

	if (Bandera == false)
	{
		if (ingresa != true && i == 4)
		{
			/*Si los intentos de iniciar sesionn se acabaron se entra a este if 
			donde se genera un codigo captcha*/
			logo();
			cout << "\n\t\t\t        COMPROBACION DE CAPCHA\n";
			separacion();
			cout << "\n\n\n\n\t\t\t:: Ingrese el nombre de usuario ::\n\n\t\t\t\t    ";

			fflush(stdin);
			cin >> userCapcha;
			fflush(stdin);
			/*Se pide el ingreso del usuario con el que deseaba iniciar sesion.*/

			cout << "\n\n\t\t\t\t*******************\n\t\t\t\t* ";
			captcha("AlGoRiTmOs", userCapcha, cp);
			/*Se llama a la funcion captcha la cual se encarga de generar este codigo.*/
			for (int i = 0; i < 15; i++)
			{
				cout << cp[i];
			}
			/*Se muestra en pantalla el codigo.*/
			cout << " *\n\t\t\t\t*******************\n\n\n\t\t\t >>>\t  ";
			cin >> ingresarCaptcha;
			/*Se pide que ingresar lo que contiene el codigo captcha.*/
			int cont = 0;

			for (int i = 0; i < 15; i++)
			{
				if (cp[i] == ingresarCaptcha[i])
				{
					cont++;
				}
			}
			/*Comparo el capcha generado con el ingresado.*/

			if (cont < 14)
			{
				/*Si el capcha ingresado a validar no es correcto se muestra 
			mensaje de error y cierra la aplicacion*/
				system("cls");
				logo();
				cout << "\n\t\t\t    >> �ERROR DE CAPTCHA! <<\n";
				separacion();
				cout << "\n\n\n\n\n\n\t\t\t------------------------------------\n";
				cout << "\t\t\t| �Posible violacion de Seguridad! |\n\t\t\t|    Esta Aplicacion se cerrara.   |\n";
				cout << "\t\t\t------------------------------------\n\n\n\n\n\n\n\n";
				getch();
			}

			if (cont == 15)
			{
				/*Si lo ingresado es igual al codigo generado ingresa a este if 
			muestra este mensaje y vuelve a dar solamente una posibilidad de un 
			inicio de sesion con tres intentos*/
				system("cls");
				logo();
				cout << "\n\t\t\t\tCAPTCHA CORRECTO\n";
				separacion();
				cout << "\n\n\n\n\n\t>> Tiene otros tres intentos para lograr el inicio de sesion. <<";
				fflush(stdin);
				getch();
				fflush(stdin);

				Bandera = true;
				/*Pongo en true a Bandera, el cual quiere decir que ya se dio 
				una oportunidad mas de inicio de sesion.*/

				IniciarSesion(); //Llamo la funcion IniciarSesion.
			}
		}
	}
}

int buscar_id(string nombre, string clave, usuario &usr)
{

	ifstream archivo;

	bool fin = false, encontrado = false;
	int i = 0;
	archivo.open(archUsuarios, ios::in);

	if (!archivo.fail())
	{
		while (!fin && !encontrado)
		{
			archivo >> usr.id >> usr.nombre >> usr.clave;

			if ((usr.clave == clave) && (usr.nombre == nombre))
			{

				encontrado = true;
			}

			if (archivo.eof())
			{
				fin = true;
			}
			i++;
		}
		archivo.close();
	}
	return i;
}

void logo()
{				  //El logo.
	separacion(); //Llamo a decoracion separacion.
	system("color 0A");
	cout << "\n\t\t\t      00  00 000000 00  00\n";
	cout << "  00000  00000   0000   0000  00  00 000000 00  00  0000  00000   0000   0000 \n"
		 << "  00  00 00  00 00  00 00  00 00  00   00   00 000 00  00 00  00 00  00 00  00\n"
		 << "  00  00 00  00 00     00     00  00   00   000000 00  00 00  00 00  00 00    \n"
		 << "  0000   0000   0000   00 000 00  00   00   000000 000000 00  00 00  00  0000\n"
		 << "  00     00 00  0000   00  00 00  00   00   000000 00  00 00  00 00  00     00\n"
		 << "  00     00  00 00     00  00 00  00   00   000 00 00  00 00  00 00  00     00\n"
		 << "  00     00  00 00  00 00  00 00  00   00   00  00 00  00 00  00 00  00 00  00\n"
		 << "  00     00  00  0000   0000  00  00   00   00  00 00  00 00000   0000   0000 \n";
	cout << "\t\t\t      000000   00   00  00\n";
	separacion();
}
void separacion()
{ //Separacion (Decoracion de asteriscos).
	for (int i = 0; i < 26; i++)
	{
		cout << " **";
	}
}
void inicio()
{
	gotoxy(35, 15);
	cout << "   CARGANDO\n\n\t\t\t  ";
	cargando();	   //Llamo a cargando (decoracion barra progresando).
	system("cls"); //Limpio pantalla.
	logo();
	system("color F1");
	cout << "\n\n\t  CLAUDIO MONGUZZI - claudio_monguzzi@hotmail.com - COMISION F"
		 << "\n\n\t  SANTIAGO MONGUZZI - santiagomonguzzi@gmail.com - COMISION F\n"
		 << endl;
	cout << "\t\t\t\tVERSION 3.0 - 2015" << endl; //Muestro info en pantalla.
	Sleep(2000);
	system("cls");
}
void cargando()
{ //cargando (decoracion barra progresando),
	system("color E");
	for (int i = 0; i < 28; i++)
	{
		Sleep(50);
		cout << char(219);
	}
	cout << "\a";
	Sleep(10);
	system("cls");
}
void captcha(string P, string N, string cp)
{
	srand(time(NULL));
	int R = (10000 + rand() % 50000);
	//string P = "AlGoRiTmOs";
	char a = N[0], b = N[N.size() - 1]; //declaro una variable con el primer caracter del nombre de usuario y otra con el ultimo
	int i = 0, h = 0;					//Declaro h e i (son contadores) y aux.
	while (i != a)
	{
		i++;
	}
	while (h != b)
	{
		h++;
	}					 //intero hasta llegar al valor ascii de la variable a y b.
	int aux = i + h + R; //sumo en Aux los valores de los contadores a y b mas el numero aleatorio .

	char n[5];
	for (int i = 0; i < 5; i++)
	{

		int k = 100000, h = aux % k; //declaro k, igualo h a el modulo de aux de k(que es 100000 en ese momento)

		sprintf(n, "%d", h); //hago que n de i sea igual al modulo de k(seria h).
		k = k / 10;			 //achico k para optener otro modulo de aux.
	}

	for (int i = 0; i < 5; i++)
	{ //Ordeno el arreglo de mayor a menor.
		for (int k = 0; k < 4; k++)
		{
			if (n[i] > n[k])
			{
				int aux = n[i];
				n[i] = n[k];
				n[k] = aux;
			}
		}
	}

	string c;
	int j = 2, k = 0, d = 0; //construyo la cadena intermedia.
	for (int i = 0; i < 15; i++)
	{
		if (i == j)
		{
			c[i] = n[k];
			j = j + 3;
			k++;
		}
		else
		{
			c[i] = P[d];
			d++;
		}
	}

	invertir(c); //llamo a la funcion invertir.

	cp = c; //igualo a cp con el codigo generado.
}

void invertir(string c)
{
	int k = 14, i = 0;
	while (i != k)
	{
		char aux = c[i];
		c[i] = c[k];
		c[k] = aux;
		k--;
		i++;
	}
}

void menu_de_juego()
{
	system("cls");
	char opcion;

	while (opcion != '7')
	{
		system("cls");
		logo();
		cout << "\n\t\t\t    BIENVENIDO " << char(34) << usuarioActual.nombre << char(34) << "!\n";
		separacion();
		cout << "\n\n\t\t\t1.- MI CUENTA\n\t\t\t2.- INCIAR PARTIDA"
			 << "\n\t\t\t3.- PARTIDAS INICIADAS\n\t\t\t4.- PARTIDAS PENDIENTES DE JUEGO"
			 << "\n\t\t\t5.- PARTIDAS TERMINADAS POR EL OPONENTE"
			 << "\n\t\t\t6.- MIS ESTADISTICAS\n\t\t\t7.- CERRAR SESION"
			 << "\n\n\t\t\tOPCION: ";
		cin >> opcion;
		cin.ignore(256, '\n');
		system("cls");
		switch (opcion)
		{
		case '1':
			system("cls");
			mi_cuenta();
			getch();
			;
			break;
		case '2':
			system("cls");
			logo();
			gotoxy(20, 20);
			cout << "\n>> Presione una tecla para continuar <<";
			getch();
			crearPartida();
			;
			break;
		case '3':
			system("cls");
			logo();
			PartIniciadas();
			getch();
			;
			break;
		case '4':
			system("cls");
			logo();
			PartPendientes();
			getch();
			;
			break;
		case '5':
			system("cls");
			logo();
			PartTerminadas();
			getch();
			;
			break;
		case '6':
			system("cls");
			cout << "\n\n\t\t\tFUNCIONALIDAD EN DESARROLLO";
			getch();
			;
			break;
		case '7':
			system("cls");
			logo();
			usuarioActual.nombre = "";
			usuarioActual.clave = "";
			usuarioActual.id = '\0';
			cout << "\n\n\n\t\t\tGracias por utilizar PregUTNados!\n\n\n\n";
			getch();
			;
			break;
		default:
			system("cls");
			logo();
			cout << endl
				 << "\t\t\n\n\n\t\t  >> Opcion incorrecta, vuelva a intentarlo <<" << endl
				 << endl;
			getch();
			;
			break;
		}
	}
}

void mi_cuenta()
{

	system("cls");
	logo();
	cout << "\t\t\t\t\t   MI CUENTA \n";
	separacion();
	gotoxy(8, 18);
	cout << "..........\n\t.   --   .\tNombre de usuario: " << usuarioActual.nombre << "\n\t.  ----  .\n\t.  ----  ."
		 << "\tContrase" << char(164) << "a: " << usuarioActual.clave << "\n\t.   --   .\n\t.  ----  .\tId de Usuario: " << usuarioActual.id << "\n\t. ------ .\n\t."
		 << " ------ .\n\t..........";
	cout << "\n\n\n\n\n\n\t>> PRESIONE UNA TECLA CUALQUIERA PARA RETORNAR AL MENU DE JUEGO <<\n";
}

void ruleta(partida &P, jugada &J)
{
	srand(time(NULL)); //Actualizo la semilla del reloj.
	int op;			   //Declaro un entero que va a ser usado para igualar a la opcion del Switch.
	//partida P;
	while (contPreg < 10)
	{
		for (;;)
		{
			Sleep(80);				//Le doy un delay al for para que puedan ser vistos las graficas.
			int x = 0 + rand() % 5; //Genero una opcion del uno a el cinco cada vez que intera el for.
			system("cls");			//Hago un borrado de pantalla.
			logo();
			cout << "\n\t\t\t\t    �GIRANDO!\n";
			separacion();
			switch (x)
			{
				/*Este switch llama a las graficas de las categorias hasta que corte el for.*/
			case 0:
				gotoxy(0, 20);
				Lfisica();
				;
				break;
			case 1:
				gotoxy(0, 20);
				Lmatdis();
				;
				break;
			case 2:
				gotoxy(0, 20);
				Laedd();
				;
				break;
			case 3:
				gotoxy(0, 20);
				Larq();
				;
				break;
			case 4:
				gotoxy(0, 20);
				Lami();
				;
				break;
			}
			op = x; //Igualo op a la ultima opcion generada (la cual fue seleccionada).
			if (kbhit())
			{
				break;
			}
			/*kbhit es una funcion la cual se encarga de cortar el bucle for cuando
			es presionada una tecla*/
		}
		Sleep(2000); //Delay el cual se encarga de dejar por unos segundos la grafica de la categoria.

		system("cls"); //Borra la pantalla.

		switch (op)
		{
			/*Este switch se encarga de llamar a la funcion que muestra la pregunta, se 
			envia el id de categoria para que cargue preguntas de dicho indentificador.*/
		case 0:
			P.categorias[contPreg] = op;
			mostrarPregunta(op, P, J);
			;
			break;
		case 1:
			P.categorias[contPreg] = op;
			mostrarPregunta(op, P, J);
			;
			break;
		case 2:
			P.categorias[contPreg] = op;
			mostrarPregunta(op, P, J);
			;
			break;
		case 3:
			P.categorias[contPreg] = op;
			mostrarPregunta(op, P, J);
			;
			break;
		case 4:
			P.categorias[contPreg] = op;
			mostrarPregunta(op, P, J);
			;
			break;
		}
	}

	system("pause");
}

void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*-------------------- Estos son las graficas de las categorias --------------*/
void Lami()
{
	/*Grafica de la categoria Analisis Matematico*/
	system("color 3");
	cout << "\t\t\t db         7MMM      ,MMF       \n\t\t        ;MM:         MMMb    dPMM     __  \n"
			"\t\t       ,V^MM.        M YM   ,M MM    /MM  \n\t\t      ,M   MM        M  Mb  M  MM     MM  \n"
			"\t\t      AbmmmqMA       M  YM.P   MM     MM  \n\t\t     A      VML      M  .YM.   MM     MM  \n"
			"\t\t   .AMA.    .AMMA. .JML.     .JMML. .JMML.\n"
		 << endl;
}
void Laedd()
{
	/*Grafica de la categoria Algoritmo y estructura de datos */
	system("color A");
	cout << "\t             db      `7MM111YMM  `7MM111Yb.   `7MM111Yb.\n\t	    ;MM:       MM    `7    MM    `Yb.   MM    `Yb.\n"
			"\t	   ,V^MM.      MM   d      MM     `Mb   MM     `Mb\n\t	  ,M  `MM      MMmmMM      MM      MM   MM      MM\n"
			"\t	  AbmmmqMA     MM   Y      MM     ,MP   MM     ,MP\n\t	 A      VML    MM      M   MM    ,dP    MM    ,dP\n"
			"\t       .AMA.   .AMMA..JMMmmmmMMM .JMMmmmdP    .JMMmmmdP\n";
}
void Lmatdis()
{
	/*Grafica de la categoria Matematica Discreta*/
	system("color c");
	cout << "\t `7MMM.     ,MMF            mm    `7MM111Yb.     db\n\t   MMMb    dPMM             MM      MM    `Yb.\n"
			"\t   M YM   ,M MM   ,61Yb.  mmMMmm    MM     `Mb `7MM  ,pP1Ybd\n\t   M  Mb  M  MM  8)   MM    MM      MM      MM   MM  8I   `;\n"
			"\t   M  YM.P   MM   ,pm9MM    MM      MM     ,MP   MM  `YMMMa.\n\t   M  `YM    MM  8M   MM    MM      MM    ,dP    MM  L.   I8\n"
			"\t .JML. `   .JMML.`Moo9^Yo.  `Mbmo .JMMmmmdP    .JMML.M9mmmP\n";
}
void Larq()
{
	/*Grafica de la categoria Arquitectua de Computadoras*/
	system("color D");
	cout << "\t\t     db                                  .g81bgd\n"
			"\t	    ;MM:                               .dP     `M\n"
			"		   ,V^MM.    `7Mb,od8   ,dW1Yvd        dM       `\n		  ,M  `MM      MM  ;   ,W    MM        MM\n"
			"		  AbmmmqMA     MM      8M    MM  mmmm  MM.\n		 A      VML    MM      YA.   MM        `Mb.     ,\n"
			"	       .AMA.   .AMMA. JMML.     `MbmdMM          `:bmmmd\n\t\t\t\t\t     MM\n\t\t\t\t\t   .JMML.\n";
}
void Lfisica()
{
	/*Grafica de la categoria Fisica 1*/
	system("color E");
	cout << "\t `7MM111YMM   db            db\n\t   MM    `7                                             __,\n"
			"\t   MM   d   `7MM  ,pP1Ybd `7MM   ,p61bo   ,61Yb.       /MM\n\t   MM11MM     MM  8I   `;   MM  6M   OO  8)   MM        MM\n"
			"\t   MM   Y     MM  `YMMMa.   MM  8M        ,pm9MM        MM\n\t   MM         MM  L.   I8   MM  YM.    , 8M   MM        MM\n"
			"\t .JMML.     .JMML.M9mmmP  .JMML. YMbmd   `Moo9^Yo.    .JMML\n";
}
/*----------------------------------------------------------------------------*/
void crearPartida()
{
	partida P; //Declaro una variable tipo "Struct partida".
	jugada J;
	//usuario usr; //Declaro una Variable tipo "struct usuario".
	fecha f;
	char op;

	contPreg = 0; //Pongo la esta variable en cero para evitar inconvenietes.

	obtenerFechaActual(f); //Llamo a esta para obtener la fecha actual del ordenador.
	P.idPartida = f.segs + (f.mins * 100) + (f.hora * 10000) + (f.dia * 1000000) + (f.mes * 100000000);
	J.idPartida = P.idPartida;

	/*Genero el id de la partida*/
	P.idUI = usuarioActual.id;
	J.idUsr = usuarioActual.id;
	system("cls");
	logo();
	cout << "\n\t\t\t\tCREAR PARTIDA\n";
	separacion();
	gotoxy(20, 20);
	cout << "Id de la partida Ininciada: " << P.idPartida << endl; //Lo muestro en pantalla.
	//if (Bandera2 == false){
	do
	{
		srand(time(NULL));
		Oponente = (1 + rand() % (obtenerIdUsuario() - 1));
		/*Igualo oponente a un aleatorio entre uno y la cantidad de usuarios registrados.*/
	} while (Oponente == usuarioActual.id); //Intero mientras que Oponente sea igual al usuario actual.

	P.idUO = Oponente;
	//}
	//else{
	//P.idUO = Oponente;
	//}
	//Bandera2 = false;
	gotoxy(22, 22);
	cout << "El ID de su oponente es => " << Oponente;
	getch();
	//Informo por pantalla el id y nombre de su Oponente;

	while (op != 's' && op != 'S' && op != 'n' && op != 'N')
	{
		/*Intero mientras no sea la opcion correcta, pregunto si desea jugar o volver al menu de juego*/
		system("cls");
		gotoxy(29, 15);
		cout << "Para jugar presione S \n\n\t\t\t    De lo contrario N.";
		gotoxy(38, 20);
		fflush(stdin);
		cin >> op;
		fflush(stdin);
	}

	if (op == 'S' || op == 's')
	{
		system("cls");
		logo();
		cout << "\n\t\t\t\t    GIRAR!\n";
		separacion();
		gotoxy(20, 20);
		cout << ">> Presione cualquier tecla para GIRAR! <<";
		getch();
		system("cls");
		ruleta(P, J);
	}
	if (op == 'N' || op == 'n')
	{
		return;
	}
}

void obtenerFechaActual(fecha &f)
{
	struct tm *tiempo;

	time_t fecha_sistema;
	time(&fecha_sistema);
	tiempo = localtime(&fecha_sistema);

	f.anio = tiempo->tm_year + 1900;
	f.mes = tiempo->tm_mon + 1;
	f.dia = tiempo->tm_mday;
	f.hora = tiempo->tm_hour;
	f.mins = tiempo->tm_min;
	f.segs = tiempo->tm_sec;
}

void mostrarPregunta(int c, partida &P, jugada &J)
{
	srand(time(NULL)); //Actualizo la semilla del reloj.
	int i;
	int opElegida;
	Pregunta matrizPreguntas[MAX_FILA][MAX_COL];
	cargaDePreguntas(matrizPreguntas);
	switch (c)
	{
	case 0:
		i = 1 + rand() % 87;
		;
		;
		break;
	case 1:
		i = 1 + rand() % 89;
		;
		;
		break;
	case 2:
		i = 1 + rand() % 88;
		;
		;
		break;
	case 3:
		i = 1 + rand() % 87;
		;
		;
		break;
	case 4:
		i = 1 + rand() % 85;
		;
		;
		break;
	}

	do
	{
		system("cls");
		logo();
		cout << "\n\t\t\t\t\tPREGUNTA\n";
		separacion();
		gotoxy(2, 20);
		cout << matrizPreguntas[c][i].pregunta << endl;
		gotoxy(33, 22);
		cout << "----------";
		gotoxy(32, 23);
		cout << "| Opciones | ";
		gotoxy(33, 24);
		cout << "----------";
		gotoxy(3, 26);
		cout << "1.- " << matrizPreguntas[c][i].opciones[0] << endl;
		gotoxy(3, 28);
		cout << "2.- " << matrizPreguntas[c][i].opciones[1] << endl;
		gotoxy(3, 30);
		cout << "3.- " << matrizPreguntas[c][i].opciones[2] << endl;
		gotoxy(3, 32);
		cout << "4.- " << matrizPreguntas[c][i].opciones[3] << endl;
		cout << "\n\t\t\t";

		fflush(stdin);
		cin >> opElegida;
		fflush(stdin);
	} while (opElegida != 1 && opElegida != 2 && opElegida != 3 && opElegida != 4);

	P.preguntas[contPreg] = matrizPreguntas[c][i].idPregunta;
	//igualo el id de la pregunta sorteada, en ell elementro de el arreglo preguntas.

	if ((opElegida) == (matrizPreguntas[c][i].opcionCorrecta))
	{
		system("cls");
		logo();
		cout << "\n\t\t\t        RESPUESTA CORRECTA\n";
		separacion();
		gotoxy(10, 20);
		cout << "ID de la Pregunta: " << matrizPreguntas[c][i].idPregunta;
		gotoxy(45, 22);
		cout << "Autor Grupo N� " << matrizPreguntas[c][i].numeroGrupo;
		gotoxy(35, 24);
		cout << "------------";
		gotoxy(34, 25);
		cout << "\a\a| �CORRECTO! |";
		gotoxy(35, 26);
		cout << "------------";

		J.rtas[contPreg] = true; //Pongo un true en el elemento contPreg en el array rtas.

		getch();

		if (contPreg == 9)
		{

			grabarPartida(P);
			obtenerPuntaje(J);
			gotoxy(25, 33);
			cout << "Su Puntaje es: " << J.puntaje;
			grabarJugada(J);
			getch();
		}

		contPreg++;
	}

	else
	{
		system("cls");
		logo();
		cout << "\n\t\t    RESPUESTA INCORRECTA\n";
		separacion();
		gotoxy(10, 20);
		cout << "ID de la Pregunta: " << matrizPreguntas[c][i].idPregunta;
		gotoxy(45, 22);
		cout << "Autor Grupo N� " << matrizPreguntas[c][i].numeroGrupo;
		gotoxy(35, 24);
		cout << "--------------";
		gotoxy(34, 25);
		cout << "\a| �INCORRECTO! |";
		gotoxy(35, 26);
		cout << "--------------";
		gotoxy(25, 28);
		cout << "La opcion correcta es: " << matrizPreguntas[c][i].opcionCorrecta << endl;
		gotoxy(8, 30);
		cout << "# " << matrizPreguntas[c][i].opciones[((matrizPreguntas[c][i].opcionCorrecta) - 1)] << endl;

		J.rtas[contPreg] = false; //Pongo un true en el elemento contPreg en el array rtas.
		getch();

		if (contPreg == 9)
		{

			grabarPartida(P);
			obtenerPuntaje(J);
			gotoxy(25, 33);
			cout << "Su Puntaje es: " << J.puntaje;
			grabarJugada(J);
			getch();
		}
		contPreg++;
	}
}

void cargaDePreguntas(Pregunta matrizPreguntas[][MAX_COL])
{
	ifstream baseDePreguntas;
	int numeroAtributo = 0, idCategoria, idPregunta, numeroGrupo, opcionCorrecta;
	char pregunta[1000], opcion1[1000], opcion2[1000], opcion3[1000], opcion4[1000], entrada[1000];
	baseDePreguntas.open("basepreguntas.txt");
	if (!baseDePreguntas)
	{
		//Error al abrir el archivo
		cout << "El archivo no pudo ser abierto. Se cerrara el programa." << endl;
		system("pause");
		exit(-1);
	}
	baseDePreguntas.unsetf(ios::skipws);
	while (!baseDePreguntas.eof())
	{
		if (numeroAtributo == 8)
			baseDePreguntas.getline(entrada, 1000, '\n'); //Consume el \n que hay entre las preguntas, ya que no estan separadas por un arroba
		else
		{
			baseDePreguntas.getline(entrada, 1000, '@');
		}
		switch (numeroAtributo)
		{
		case 0:
			idPregunta = atoi(entrada) - 1;
			break;
		case 1:
			idCategoria = atoi(entrada);
			break;
		case 2:
			numeroGrupo = atoi(entrada);
			break;
		case 3:
			strcpy(pregunta, entrada);
			break;
		case 4:
			strcpy(opcion1, entrada);
			break;
		case 5:
			strcpy(opcion2, entrada);
			break;
		case 6:
			strcpy(opcion3, entrada);
			break;
		case 7:
			strcpy(opcion4, entrada);
			break;
		case 8:
			opcionCorrecta = atoi(entrada);
			break;
		}
		numeroAtributo++;
		if (numeroAtributo == 9)
		{
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

int obtenerIdUsuario()
{
	ifstream archivo;
	usuario usr;
	int i = 0;
	bool fin = false;

	archivo.open(archUsuarios, ios::in);
	/*Incremento i hasta llegar al fin del fichero, el cual despues sera retornado.*/
	while (!fin)
	{
		archivo >> usr.id >> usr.nombre >> usr.clave;
		if (archivo.eof())
			fin = true;
		i++;
	}
	archivo.close();
	return i;
}

void grabarPartida(partida &P)
{
	ofstream ptrPartida;
	ptrPartida.open("partida.dat", ios::binary | ios::app | ios::ate);

	if (!ptrPartida)
	{
		cout << "Error al abrir el Fichero de partidas.";
	}

	else
	{
		ptrPartida.write((char *)&P, sizeof(P));
	}
	ptrPartida.close();
	return;
}

void grabarJugada(jugada &J)
{

	ofstream ptrJugada;
	ptrJugada.open("jugada.dat", ios::binary | ios::app | ios::ate);

	if (!ptrJugada)
	{
		cout << "Error al abrir el Fichero de partidas.";
	}

	else
	{
		ptrJugada.write((char *)&J, sizeof(J));
	}

	ptrJugada.close();
	return;
}
void obtenerPuntaje(jugada &J)
{

	//Saco el puntaje del usuario Actual.
	J.puntaje = 0;
	int aar[10];
	for (int i = 0; i < 10; i++)
	{
		aar[i] = J.rtas[i] * 3;
		J.puntaje = aar[i] + J.puntaje;
	}
}

void EstCat()
{
	partida part1;
	ifstream entrada;
	entrada.open("partida.dat", ios::in | ios::binary);
	if (!entrada)
	{
		cout << "\n\tEl archivo no pudo ser abierto";
		exit(-1);
	}
	else
		entrada.seekg(0, ios::beg);
	entrada.read((char *)(&part1), sizeof(part1));
	int fis = 0, matd = 0, ana = 0, alg = 0, arq = 0, catmasjugada = 0, cantidaddepreg = 0;
	while (!entrada.eof())
	{
		for (int i = 0; i < 10; i++)
		{
			switch (part1.categorias[i])
			{
			case (0):
				fis++;
				break;
			case (1):
				matd++;
				break;
			case (2):
				alg++;
				break;
			case (3):
				arq++;
				break;
			case (4):
				ana++;
				break;
			}
		}
		int a[] = {fis, matd, alg, arq, ana};
		int mayor = a[0], cat = 0;
		for (int j = 1; j < 5; j++)
		{
			if (a[j] > mayor)
			{
				mayor = a[j], cat = j;
			}
		}
		catmasjugada = cat;
		cantidaddepreg = mayor;
		entrada.read((char *)(&part1), sizeof(part1));
	}
	gotoxy(2, 20);
	for (int i = 0; i < 75; i++)
	{
		cout << "-";
	}
	gotoxy(5, 22);
	cout << "La categoria mas jugada es: ";
	switch (catmasjugada)
	{
	case 0:
		cout << "Fisica";
		break;
	case 1:
		cout << "Mat. Discreta";
		break;
	case 2:
		cout << "Algortimos";
		break;
	case 3:
		cout << "Arquitectura";
		break;
	case 4:
		cout << "Analisis mat";
		break;
	}
	cout << " con " << cantidaddepreg << " preguntas sorteadas. " << endl;
	gotoxy(2, 24);
	for (int i = 0; i < 75; i++)
	{
		cout << "-";
	}
	gotoxy(7, 32);
	cout << ">> PRESIONE UNA TECLA CUALQUIERA PARA RETORNAR AL MENU PRINCIPAL <<";
	getch();
}

void PartIniciadas()
{
	partida Part_Iniciadas;
	long iniciadas[TAMT];
	int i = 0;

	ifstream entrada;

	entrada.open("partida.dat", ios::in | ios::binary);
	if (!entrada)
	{
		cout << "\n\t\t\tEl archivo no pudo ser abierto";
		getch();
		exit(-1);
	}
	else
		entrada.seekg(0, ios::beg);
	entrada.read((char *)(&Part_Iniciadas), sizeof(Part_Iniciadas));

	while (!entrada.eof())
	{

		if ((Part_Iniciadas.idUI == usuarioActual.id) && (!repetido(iniciadas, i)))
		{

			iniciadas[i] = Part_Iniciadas.idPartida;
			iniciadas[i + 1] = Part_Iniciadas.idUO;
			i = i + 2;
		}

		entrada.read((char *)(&Part_Iniciadas), sizeof(Part_Iniciadas));
	}

	cout << "\n\t\t\t\tPARTIDAS INICIADAS\n";
	separacion();
	cout << "\n\n\n";

	for (int j = 0; j < i; j++)
	{

		cout << "\n | ID de Partida:  " << iniciadas[j] << " | ID Oponente: " << iniciadas[j + 1] << " | Fecha de creacion: ";
		decodificar(iniciadas[j]);
		cout << " |";
		cout << "\n  ----------------------------------------------------------------------------";
		j = j + 1;
	}
	cout << "\n\n\t\t    >> Presione una tecla para continuar <<";
}

void PartPendientes()
{
	partida Part_Pendientes;
	long pendientes[TAM];
	int i = 0;

	ifstream entrada;

	entrada.open("partida.dat", ios::in | ios::binary);
	if (!entrada)
	{
		cout << "\n\t\t\tEl archivo no pudo ser abierto";
		getch();
		exit(-1);
	}
	else
		entrada.seekg(0, ios::beg);
	entrada.read((char *)(&Part_Pendientes), sizeof(Part_Pendientes));

	while (!entrada.eof())
	{

		if ((Part_Pendientes.idUO == usuarioActual.id) && (!repetido(pendientes, i)))
		{

			pendientes[i] = Part_Pendientes.idPartida;
			pendientes[i + 1] = Part_Pendientes.idUI;
			i = i + 2;
		}

		entrada.read((char *)(&Part_Pendientes), sizeof(Part_Pendientes));
	}

	cout << "\n\t\t\t\tPARTIDAS PENDIENTES\n";
	separacion();
	cout << "\n";

	if (i != 0)
	{
		for (int j = 0; j < i; j++)
		{

			cout << "\n | ID de Partida:  " << pendientes[j] << " | ID Oponente: " << pendientes[j + 1] << " | Fecha de creacion: ";
			decodificar(pendientes[j]);
			cout << " |";
			cout << "\n  ----------------------------------------------------------------------------";
			j = j + 1;
		}
		cout << "\n\n\t\t    >> Presione una tecla para continuar <<";
	}

	else
	{
		gotoxy(20, 20);
		cout << "No se encuentran partidas pendientes.";
		gotoxy(20, 20);
		cout << ">> Presione una tecla para continuar <<";
	}
}

void PartTerminadas()
{
	partida Part_Terminadas;
	long terminadas[TAM];
	int i = 0;

	ifstream entrada;

	entrada.open("partida.dat", ios::in | ios::binary);
	if (!entrada)
	{
		cout << "\n\t\t\tEl archivo no pudo ser abierto";
		getch();
		exit(-1);
	}
	else
		entrada.seekg(0, ios::beg);
	entrada.read((char *)(&Part_Terminadas), sizeof(Part_Terminadas));

	while (!entrada.eof())
	{

		if ((Part_Terminadas.idUI == usuarioActual.id) && (repetido(terminadas, i)))
		{

			terminadas[i] = Part_Terminadas.idPartida;
			terminadas[i + 1] = Part_Terminadas.idUO;
			i = i + 2;
		}

		entrada.read((char *)(&Part_Terminadas), sizeof(Part_Terminadas));
	}

	cout << "\n\t\t\t\tPARTIDAS TERMINADAS\n";
	separacion();
	cout << "\n";

	if (i != 0)
	{
		for (int j = 0; j < i; j++)
		{

			cout << "\n\t\t|  ID de Partida:  " << terminadas[j] << " | ID Oponente: " << terminadas[j + 1] << " |";
			cout << "\n\t\t-----------------------------------------------";
			j = j + 1;
		}

		cout << "\n\n\t\t    >> Presione una tecla para continuar <<";
	}
	else
	{
		gotoxy(20, 20);
		cout << "No se encuentran partidas terminadas.";
		gotoxy(20, 30);
		cout << ">>Presione una tecla para continuar <<";
	}
}

bool repetido(long a[], int k)
{

	for (int i = 0; i < k; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (a[i] == a[k])
			{
				return true;
			}
		}
	}

	return false;
}

void decodificar(long idPartida)
{
	fecha f2;

	f2.anio = 2016;
	f2.mes = idPartida / 100000000;
	f2.dia = (idPartida / 1000000) % 100;
	f2.hora = (idPartida / 10000) % 100;
	f2.mins = (idPartida / 100) % 100;
	f2.segs = idPartida % 100;
	cout << setfill('0') << setw(2) << f2.dia << "/" << setfill('0') << setw(2) << f2.mes << "/" << f2.anio;
}

/* "  " */
