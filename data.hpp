#ifndef datah
#define datah

#include "library.hpp"


//---------------------------------------------
// struct containing configuration settings
//---------------------------------------------
struct Lang
{
    string play;
    string game_options;
    string about_game;
    string exit_game;
};


//---------------------------------------------
// struct containing configuration settings
//---------------------------------------------
struct Config
{
    bool Debug_Mode; //jesli true wyrzuca logi do pliku log.txt
    string Player_Name;   // nazwa gracza
    int Screen_Height;      // pozycja w LY (light year)
    int Screen_Width;      // pozycja w LY
    string Default_Language; //defult language used
};


//---------------------------------------------
// struct containing location details
//---------------------------------------------
struct Location
{
    string Name; //Location Name
    char Type;   // p-planetary system, a-asteroid field only, s-space station
    float x;      // pozycja w LY (light year)
    float y;      // pozycja w LY
};


//---------------------------------------------
//class containing all data used in program
//---------------------------------------------
class Data
{
private:
    int i, error_lines;
    fstream file;
    string version; //program version
    string gameName;
    string gameStudio;
public:
    Data();
    fstream logs;
    string FileName;
    string ConfFileName;
    bool Loaded[5];
    //=====Data Containers=====
    Config Configuration;
    Location Tab[10];          // other way of containing location needed
    Lang lang;
    //=========================
    bool LoadFiles();
    string LoadString(string input);   //load string in " "
    int LoadInt(string input); //load string in = ;
    bool LoadConfiguration();
    bool LoadLocations();
    bool LoadLang();
};

#endif // datah
