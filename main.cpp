
#include "data.hpp"





//******************************
//
//         Main Function (basically nothing here)
//
//******************************

int main(int argc, char *argv[])
{
    Data *data;
    data=new Data();
    data->LoadFiles();

    data->logs << "Program finished!" << endl;
    return 0;
}
