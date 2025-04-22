
#include "misc.h"
#include <cctype>

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

string nameToID(string f_name, string l_name) {
    string ID = "";
    for(int i = 0; i < f_name.size(); i++) {
        f_name[i] = tolower(f_name[i]);
        if(f_name[i] != ' ') {
            ID += f_name[i];
        }
    }
    for(int i = 0; i < l_name.size(); i++) {
        l_name[i] = tolower(l_name[i]);
        if(l_name[i] != ' ') {
            ID += l_name[i];
        }
    }
    return ID;
}