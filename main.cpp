// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void replace(std::string& subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}// funcion reemplazar una palabra por otra, por cada vez que la encuentra

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

float distancia2(float longitud1,float longitud2, float latitud1,float latitud2 )
{
    float resultado = pow((longitud2 - longitud1),2) + pow((latitud2 - latitud1),2);
    resultado = sqrt(resultado);
    return resultado;
}

float distancia(float lonHome, float lonDest, float latHome, float latDest ) {

    float pi = 3.141592653589793;
    int R = 6371; //Radius of the Earth
    latHome = (pi/180)*(latHome);
    latDest = (pi/180)*(latDest);
    float differenceLon = (pi/180)*(lonDest - lonHome);
    float differenceLat = (pi/180)*(latDest - latHome);
    float a = sin(differenceLat/2) * sin(differenceLat/2) +
    cos(latHome) * cos(latDest) *
    sin(differenceLon/2) * sin(differenceLon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float distance = R * c;

    return distance;
}

int main(int argc, char** argv)
{
        if(argv[1] == NULL)

        {
            cout<<"Por favor, ingresa los parametros, ej: aplicacion \"ruta/equipos.csv\" \"ruta/resultado.csv\" "<<endl;

        }
     vector <string>distancias;
    vector <string>local;
    vector <string>visitante;
#pragma omp parallel
{printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());}
string temporal = "";
   float iniciallatitud = 0;

    float iniciallongitud = 0;
    vector <string> equipos;
   string line;
  ifstream myfile (argv[1]);
  if (myfile.is_open())
  {equipos.clear();
    while ( getline (myfile,line) )
    {
        if (line.find ("Longitud") == -1 )
      {

         replace(line,"\"","");
         equipos.push_back(line);}

    }
    myfile.close();


    //implementar omp



 #pragma omp paralell
     {
    #pragma omp for
 for (int x = 0; x < equipos.size(); x++)
 {  string temporallocal = "";
     //cout<<"--------------------equipo: "<< x +1 <<endl;
     //inside
vector <string > datos = split(equipos[x],";");

iniciallatitud = stod(datos[3]);
          iniciallongitud = stod(datos[4]);

     for (int i = 0; i < equipos.size(); i++)
  {
local.push_back(datos[0]);
      vector <string > datos2 = split(equipos[i],";");
 //cout << datos2[0]<<endl;
 temporal = temporal + datos2[0] + "\n";
visitante.push_back(datos2[0]);
     float latitudtemporal = stof(datos2[3]);
    float longitudtemporal = stof(datos2[4]);

       float temp = distancia(iniciallongitud,longitudtemporal,iniciallatitud,latitudtemporal);
    distancias.push_back(std::to_string (temp));
      //cout << i<<" distancia: "<< temp<<"\n";
       temporal = temporal + std::to_string (temp) +"\n";
//cout <<"depuracion: "<< " "<<iniciallongitud<< " "<<longitudtemporal<< " "<<iniciallatitud<< " "<<latitudtemporal<<"\n";

           iniciallatitud =latitudtemporal;
           iniciallongitud = longitudtemporal;
         }
        // cout << "--------------------------------------------------------------------------------------"<<endl;
        temporal = temporal + "----------------------------------------\n";

  }

  }
 }

ofstream myfile2 (argv[2]);
  if (myfile2.is_open())
  {
int jornada = 1;
    myfile2 << "\"Jornada\";\"Equipo Local\";\"Equipo Visitante\";\"Distancia\"\n";
    //myfile2 << temporal;
    for(int j=0;j<distancias.size();j++){

int a = jornada;
stringstream ss;
ss << a;
string str = ss.str();
        myfile2<< "Jornada " + str + ";"  + local[j] + ";" +  visitante[j] + ";" +distancias[j] ;
        myfile2<<"\n";
     jornada++;
     if (jornada == 19)
        jornada = 1;
    }
    myfile2.close();
  }

  else cout << "Unable to open file";





    return 0;
}
