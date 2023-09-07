#include <iostream>
#include <fstream>

#define MAXNAMESIZE 16

enum EWeapon
{
    none, sword, lance, bow
};

//estructura de datos que deben persistir
struct SGameData
{
    char name[MAXNAMESIZE];
    unsigned int tropasmuertas;
    unsigned int Ejercito;
    EWeapon  currentWeapon;
    unsigned int  enemysKilled;
   
};


void Log(const char* msg)
{
    std::cout << msg << "\n";
}


int main()
{
    std::cout << "Welcome to mordor!\n";


    //leer el archivo de savegame
    std::fstream savefile("archivo.sav", std::ios::in | std::ios::out);

    if (savefile.is_open())
    {
        Log("savefile abierto");

        //leer datos del archivo
        SGameData data;
        savefile.read(data.name, MAXNAMESIZE);
        savefile.read((char*)&data.tropasmuertas, 4);
        savefile.read((char*)&data.Ejercito, 4);
        savefile.read((char*)&data.currentWeapon, 4);
        savefile.read((char*)&data.enemysKilled, 4);

        std::cout << "hola " << data.name;
        std::cout << ", tienes arma " << data.currentWeapon << " y has matado a " << data.enemysKilled << " enemigos." << "Ni modo, perdiste a : " << data.tropasmuertas << "Tropas muertas" << "\n";

        Log(" 1. llevar anillo ");
        Log(" 2. llevar espadas");
        Log(" 3. llevar armamento");

        std::string Respuestas;
        std::cin >> Respuestas;

        if (Respuestas == "1")
        {
            Log("Oh no tendras que llevar el anillo de mordor");
        }
        else if (Respuestas == "2")
        {
            savefile.close();
            savefile.open("archivo.sav", std::ios::out);
            data.currentWeapon = sword;
            Log(" Felicidades te toca pelear en la primera linea");
            if (savefile.is_open())
            {
                savefile.seekp(0, std::ios::beg);
                savefile.write((const char*)&data, sizeof(SGameData));
            }
        }
        else if ( Respuestas == "3")
        {
            Log("Lo siento tendras que volver por armamento.");
            return 0;
        }

        Log("1. Te quieres ir en la mañana");
        Log("2. Te quieres ir en la tarde");
        Log("3. Te quieres ir en la noche");

            savefile.close();
        std::cin >> Respuestas;

        if (Respuestas == "1")
        {
            savefile.open("archivo.sav", std::ios::out);
            data.tropasmuertas += 10;
            Log("Te agarra el sol abrumador y  tus tropas empiezan a pedir agua");
            Log("Te pones muy ansioso porque no hay ningun rio o lago cerca");
            Log("Al final tomas una desicion muy importante");
            Log("Y...");
            if (savefile.is_open())
            {
                savefile.seekp(0,std::ios::beg);
                savefile.write((const char*)&data, sizeof(SGameData));
            }
        }
        if (Respuestas == "2")
        {
            savefile.open("archivo.sav", std::ios::out);
            data.tropasmuertas += 30;
            Log("Cuándo sales te encuntras con tropas enemigas...");
            Log(" Pierdes a 3 descenas de tropas");
            Log(" Continas tu largo camino despues de los incovenientes...");
            if (savefile.is_open())
            {
                savefile.seekp(0, std::ios::beg);
                savefile.write((const char*)&data, sizeof(SGameData));
            }
        }
        if (Respuestas == "3")
        {
            savefile.open("archivo.sav", std::ios::out);
            data.enemysKilled += 20;
            Log("Como dejaste que tus tropas descansaran, tomaran agua y comieran bien...");
            Log(" Recuperan fuerza, vision, agilidad");
            Log(" Logran ver tropas enemigos acampando...");
            Log(" Matan sigilosamente a 20");
            if (savefile.is_open())
            {
                savefile.seekp(0, std::ios::beg);
                savefile.write((const char*)&data, sizeof(SGameData));
            }

        }

    }
    else
    {
        Log("crear savefile vacio e inicial");
        SGameData data;
        Log("Tell me your fugging vermin name");
        std::cin >> data.name;
        data.tropasmuertas = 0;
        data.Ejercito = 220;
        data.currentWeapon = EWeapon::none;
        data.enemysKilled = 0;
        savefile.open("archivo.sav", std::ios::out);
        if (savefile.is_open())
        {
            //Dumpear la estructura data
            savefile.seekp(0, std::ios::beg);
            savefile.write((const char*)&data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }

    }

    savefile.close();

    return 0;
}