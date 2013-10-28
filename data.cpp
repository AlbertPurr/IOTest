#ifndef datac
#define datac

#include "data.hpp"


Data::Data()
:i(0)
,error_lines(0)
,version("0.0.1")
,gameName("Alcubierre")
,FileName("Data/Data.dat")
,gameStudio("Purrr Code Studio")
,ConfFileName("Config.conf")
{

}

bool Data::LoadFiles()
{
    string line;
    int return_value;
    //=============================log.txt
    logs.open("Logs/logs.log", ios::trunc | ios::out);
    logs<<gameName<<" v."<<version<<" by "<<gameStudio<<"\n\n==============================\n";
    //=============================Config.conf
    file.open(ConfFileName.c_str(), ios::in);
    if(!file.is_open()){ logs<<"Error opening "<<FileName<<" file.\n"; return 0;}
    else logs<<"Configuration found.\n";
                                return_value=LoadConfiguration();
                                if(return_value==1) logs<<"Loading of configuration falied\n";
                                else if(return_value==2) logs<<"Lack of debug mode seting\n";
                                else if(return_value==0) Loaded[0]=1;
                                else logs<<"Unknown error while loading configuration\n";
    file.close();
    //=============================Data.dat
    file.open(FileName.c_str(), ios::in);
    if(!file.is_open()){ logs<<"Error opening "<<FileName<<" file.\n"; return 0;}

    while(!file.eof())
    {
        i++;
        getline(file,line);
        logs<<"                #"<<line<<endl;


        if(line=="Locations")
                            {
                                logs<<"Location found!\n";
                                return_value=LoadLocations();
                                if(return_value==1) logs<<"Loading of location falied\n";
                                else if(return_value==0) Loaded[1]=1;
                            else logs<<"Unknown error while loading location\n";
                            }
        else if(line=="\n"||line==" "||line=="") logs<<"Empty line found\n";
        else { logs<<"Error loading line "<<i<<endl; error_lines++; }//tu


    }
        logs<<endl<<"===========Settings============"<<endl;
        logs<<"Debug mode "<<Configuration.Debug_Mode<<endl;
        logs<<"Player name "<<Configuration.Player_Name<<endl;
        logs<<"Resolution "<<Configuration.Screen_Height<<"x"<<Configuration.Screen_Width<<endl;
        logs<<"Default language "<<Configuration.Default_Language<<endl;
    logs<<error_lines*100/i<<" % of file data corrupted.\n";
    logs<<"Loaded data: ";
    for(int j=0;j<5;j++)
        logs<<Loaded[j]<<" ";
    logs<<endl;
    file.close();
    return true;
}

string Data::LoadString(string input)   //load string in " "
{
    string tmp;
    size_t tmpt;
    tmpt=input.find("\"");
    if(input.find("\"",tmpt+1)==string::npos)
        return "";
    if(tmpt!=string::npos)
            tmp.insert(0,input, tmpt+1,input.find("\"",tmpt+1)-tmpt-1);
    else return "";
    return tmp;
};

int Data::LoadInt(string input)   //load string in = ;
{
    string tmp;
    size_t tmpt;
    tmpt=input.find("=");
    if(input.find(";",tmpt+1)==string::npos)
        return -2147483648; //lowest value of int!
    if(tmpt!=string::npos)
            tmp.insert(0,input, tmpt+1,input.find(";",tmpt+1)-tmpt-1);
    else return -2147483648;
    return atoi(tmp.c_str());
};


// Load configuration into Data.Configuration
bool Data::LoadConfiguration()
{

    string line;
    string number;
    bool CheckConf[5]={0}; // 1=error
    size_t pozycja;
     do
    {
        i++;
        getline(file,line);

/*
        if(line.find("Debug_Mode")!=string::npos)                       //Debug Mode
           if(line.find("true")!=string::npos) Configuration.Debug_Mode=1;
           else if(line.find("false")!=string::npos) Configuration.Debug_Mode=0;
           else logs<<"Debug seting not found\n";
        else if(line.find("Player_Name")!=string::npos)                 // Player Name
            if(line.find("= ")!=string::npos) Configuration.Player_Name.insert(0,line, line.find("=")+2,line.find(";")-line.find("=")-2);
            else if(line.find("=")!=string::npos) Configuration.Player_Name.insert(0,line, line.find("=")+1,line.find(";")-line.find("=")-1);
            else logs<<"Player name not found\n";
        else if(line.find("Screen_Height")!=string::npos)
            if(line.find("= ")!=string::npos){ number.insert(0,line, line.find("= ")+2,line.find(";")-line.find("= ")-2); Configuration.Screen_Height=atoi(number.c_str()); number="";}
            else if(line.find("=")) { number.insert(0,line, line.find("=")+1,line.find(";")-line.find("=")-1); Configuration.Screen_Height=atoi(number.c_str()); number="";}
            else logs<<"Screen height not found\n";
        else if(line.find("Screen_Width")!=string::npos)
            if(line.find("= ")!=string::npos){ number.insert(0,line, line.find("= ")+2,line.find(";")-line.find("= ")-2); Configuration.Screen_Width=atoi(number.c_str()); number="";}
            else if(line.find("=")) { number.insert(0,line, line.find("=")+1,line.find(";")-line.find("=")-1); Configuration.Screen_Width=atoi(number.c_str()); number="";}
            else logs<<"Screen width not found\n";
        else {}
*/
        if(line.find("Debug_Mode")!=string::npos)
        {
            if(LoadString(line)=="true") {Configuration.Debug_Mode=1; CheckConf[0]=0;}
            else if(LoadString(line)=="false") {Configuration.Debug_Mode=0; CheckConf[0]=0;}
            else  CheckConf[0]=1;
        }
        else if(line.find("Player_Name")!=string::npos)
        {
            Configuration.Player_Name=LoadString(line);
            if(Configuration.Player_Name!="") CheckConf[1]=0;
            else CheckConf[1]=1;
        }
        else if(line.find("Screen_Height")!=string::npos)
        {
            Configuration.Screen_Height=LoadInt(line);
            if(Configuration.Screen_Height!=-2147483648) CheckConf[2]=0;
            else CheckConf[2]=1;
        }

        else if(line.find("Screen_Width")!=string::npos)
        {
            Configuration.Screen_Width=LoadInt(line);
            if(Configuration.Screen_Width!=-2147483648) CheckConf[3]=0;
            else CheckConf[3]=1;
        }
        else if(line.find("Default_Language")!=string::npos)
        {
                        Configuration.Default_Language=LoadString(line);
            if(Configuration.Default_Language!="") CheckConf[4]=0;
            else CheckConf[4]=0;
        }
        else {}

        logs<<"                #"<<line<<endl;
    pozycja=line.find("}");
    logs<<pozycja<<endl;
    }while(!file.eof()&&pozycja!=0);
    if(pozycja!=0) return 1;
    logs<<"Check Configurations"<<CheckConf[0]<<CheckConf[1]<<CheckConf[2]<<CheckConf[3]<<CheckConf[4]<<endl;

    logs<<"Out of lop\n";
    return 0;
};





bool Data::LoadLocations()
{
    string line;
    size_t pozycja;
     do
    {

        getline(file,line);
        i++;
        logs<<"                #"<<line<<endl;

    pozycja=line.find("}");
    logs<<pozycja<<endl;
    //if(pozycja!=string::npos&&pozycja!=1) logs<<"Cos!!!!!!!!!!!\n"; //if(line.find(" ")==0) logs<<"Found new loc\n"; else logs<<"Cos!!!!!!!!!!!\n";
    }while(!file.eof()&&pozycja!=0);
    //}while(line!="}");
    if(pozycja!=0) return 1;
    logs<<"Out of loop\n";
    return 0;
};


bool Data::LoadLang()
{
    return 0;
};



#endif // datac
