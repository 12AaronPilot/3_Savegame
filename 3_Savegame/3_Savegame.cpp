#include <iostream>
#include <fstream>

#define MAXNAMESIZE 16

enum EWeapon
{
    none, saword, lance, bow
};

//Estructura de datos que deben persistir
struct SGameData
{
    char name[MAXNAMESIZE];
    EWeapon currentweapon;
    int enemyskilled;
};

void Log(const char* msg) 
{
    std::cout << msg << "\n";
}


int main()
{
    std::cout << "Hello World!\n";



    //leer el archivo de savegame
    std::fstream savefile("data.sav", std::ios::in | std::ios::out);

    if (savefile.is_open())
    {
        Log("savefile abierto");

        //Leer datos del archivo
        SGameData data;
        savefile.read(data.name, MAXNAMESIZE);
        savefile.read( (char*)&data.currentweapon, 4);
        savefile.read( (char*)&data.enemyskilled, 4);

        std::cout << "Hola" << data.name;
        std::cout << "Tienes arma " << data.currentweapon << " y has matado a " << data.enemyskilled;
    }
    else
    {
        Log("crear savefile vacio e inicial");
        SGameData data;
        Log("Escribe tu nombre aventurero");
        std::cin >> data.name;
        data.currentweapon = EWeapon::none;
        data.enemyskilled = 0;

        savefile.open("data.save", std::ios::out);
        if (savefile.is_open())
        {
            //Dumpear la estructura data
            savefile.seekp(0, std::ios::beg);
            savefile.write( ( const char *) & data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }
    }


    savefile.close();

    return 0;
}

//Hacer una narrativa, un auto save, 