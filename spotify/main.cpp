#include "main.hpp"
int main(){
    std::cout<<"benvenuto/a nel programma da spotify a ytmusic\n\n ora fai i tuoi 5 click\n";
    INPUT tastiera{0};
    tastiera.type = INPUT_KEYBOARD;
    tastiera.ki.wVk = 0;
    tastiera.ki.time = 0;
    tastiera.ki.dwExtraInfo = 0;
    INPUT mouse={0};
    mouse.type=INPUT_MOUSE;
    mouse.mi.dwExtraInfo=0;
    mouse.mi.time=0;
    WPARAM prog;
    POINT Punti[5]={0};
    size_t i=0;
    std::string titoli="";
    bool antiRipetizione=true;
    std::ofstream file("playlist.txt");
    
    //sistema che salva i 5 click necessari per l'aggiunta della canzone
    #pragma region click
    while(i<=5){
        if(GetAsyncKeyState(MK_LBUTTON)!=0&&antiRipetizione){
            Punti[i].x=mouse.mi.dx;
            Punti[i].y=mouse.mi.dy;
            ++i;
            antiRipetizione=false;
        }
        if(GetAsyncKeyState(MK_LBUTTON)==0&&!antiRipetizione){
            antiRipetizione=true;
        }
    }
    #pragma endregion
    std::cout<<"incollare qui quello che avete copiato da spotify ricordati di salvare e chiudere prima di continuare\n";
    file.close();
    system("start playlist.txt");
    system("pause");

    std::ifstream leggi("playlist.txt");
    while(std::getline(leggi,titoli)){
        std::cout<<titoli<<"\n";
    }
    leggi.close();
    return 0;
}