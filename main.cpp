// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <omp.h>

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

float distancia(float longitud1,float longitud2, float latitud1,float latitud2 )
{
    float resultado = pow((longitud2 - longitud1),2) + pow((latitud2 - latitud1),2);
    resultado = sqrt(resultado);
    return resultado;
}

int main()
{
#pragma omp parallel
{printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());}

   float iniciallatitud = 0;

    float iniciallongitud = 0;
    vector <string> equipos;
   string line;
  ifstream myfile ("C:/Users/darkx/Desktop/taller03/equipos.csv");
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
 {  cout<<"--------------------equipo: "<< x +1 <<endl;
     //inside
vector <string > datos = split(equipos[x],";");
iniciallatitud = stod(datos[3]);
          iniciallongitud = stod(datos[4]);

     for (int i = 0; i < equipos.size(); i++)
  {
      vector <string > datos = split(equipos[i],";");
 cout << datos[0]<<endl;

     float latitudtemporal = stof(datos[3]);
    float longitudtemporal = stof(datos[4]);


      cout << i<<" distancia: "<< distancia(iniciallongitud,longitudtemporal,iniciallatitud,latitudtemporal)<<"\n";
//cout <<"depuracion: "<< " "<<iniciallongitud<< " "<<longitudtemporal<< " "<<iniciallatitud<< " "<<latitudtemporal<<"\n";

           iniciallatitud =latitudtemporal;
           iniciallongitud = longitudtemporal;
         }
         cout << "--------------------------------------------------------------------------------------"<<endl;


  }

  }
 }



  else cout << "Unable to open file";





    return 0;
}
