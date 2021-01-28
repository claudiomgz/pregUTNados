#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

struct fecha {
	int anio, mes, dia, hora, mins, segs;
};

void obtenerFechaActual(fecha & f);

int main(int argc, char *argv[]) {
	fecha f,f2;
	long idPartida;
	obtenerFechaActual(f);
	cout << setfill('0') << setw(2) << f.dia << "/" << 
		setfill('0') << setw(2) << f.mes << "/" << 
		f.anio << " " << 
		setfill('0') << setw(2) << f.hora << ":" << 
		setfill('0') << setw(2) << f.mins << ":" << 
		setfill('0') << setw(2) << f.segs << endl;
	idPartida=f.segs+(f.mins*100)+(f.hora*10000)+(f.dia*1000000)+(f.mes*100000000);
	cout << "Id de la partida: " << idPartida << endl;
	
	f2.anio=2015;
	f2.mes=idPartida/100000000;
	f2.dia=(idPartida/1000000)%100;
	f2.hora=(idPartida/10000)%100;
	f2.mins=(idPartida/100)%100;
	f2.segs=idPartida%100;
	cout << setfill('0') << setw(2) << f2.dia << "/" << 
		setfill('0') << setw(2) << f2.mes << "/" << 
		f2.anio << " " << 
		setfill('0') << setw(2) << f2.hora << ":" << 
		setfill('0') << setw(2) << f2.mins << ":" << 
		setfill('0') << setw(2) << f2.segs << endl;
	
	return 0;
}


void obtenerFechaActual(fecha & f) {
	struct tm *tiempo;

	
	time_t fecha_sistema;
	time(&fecha_sistema);
	tiempo=localtime(&fecha_sistema);
	
	f.anio=tiempo->tm_year + 1900;
	f.mes=tiempo->tm_mon + 1;
	f.dia=tiempo->tm_mday;
	f.hora=tiempo->tm_hour;
	f.mins=tiempo->tm_min;
	f.segs=tiempo->tm_sec;
	
}

