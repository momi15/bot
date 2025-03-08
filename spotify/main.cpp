#include "main.hpp"
void rovescia(int tempo){
    for(size_t i=tempo;i>0;--i){
        std::cout<<"ti rimangono altri "<<i;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<<"\033[2J\033[H";
    }
}
void simulaTastiera(const std::string& testo) {
    for (char c : testo){
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        
        input.ki.wScan = c;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags |= KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
    keybd_event(VK_RETURN, 0, 0, 0);
}

int main(){
    //vettore che dovrà contenere i vari titoli
    std::vector<std::string> titoli;

    //variabile per poter scrivere con la tastiera
    INPUT tastiera{0};
    tastiera.type = INPUT_KEYBOARD;
    tastiera.ki.wVk = 0;
    tastiera.ki.time = 0;
    tastiera.ki.dwExtraInfo = 0;

    //array per salvare il comando ctrl+a
    INPUT pulisci[4] = {};
    pulisci[0].type = INPUT_KEYBOARD;
    pulisci[0].ki.wVk = VK_CONTROL;
    
    // Premi A
    pulisci[1].type = INPUT_KEYBOARD;
    pulisci[1].ki.wVk = 'A';
    
    // Rilascia A
    pulisci[2].type = INPUT_KEYBOARD;
    pulisci[2].ki.wVk = 'A';
    pulisci[2].ki.dwFlags = KEYEVENTF_KEYUP;
    
    // Rilascia CTRL
    pulisci[3].type = INPUT_KEYBOARD;
    pulisci[3].ki.wVk = VK_CONTROL;
    pulisci[3].ki.dwFlags = KEYEVENTF_KEYUP;
    
    //variabile per poter muovere e cliccare con il mouse
    INPUT mouse={0};
    mouse.type=INPUT_MOUSE;
    mouse.mi.dwExtraInfo=0;
    mouse.mi.time=0;
    //array per poter salvare i vari click
    POINT Punti[4]={0};
    //contatore dei click
    size_t i=0;
    
    std::string titolo="";
    //variabile per prendere i click nella maniera più opportuna
    bool antiRipetizione=true;
    //variabile per creare il file playlist.txt che conterà i vari titoli
    std::ofstream file("playlist.txt");
    file.close();

    std::cout<<"benvenuto/a nel programma da spotify a ytmusic\n ti daro' 5secondi dopo di essi dovrai gia' essere su yt e star facendo i click miraccomando non farli prima altrimenti non li vedra' \n(schiacciare invio per continuare)\n";
    std::cin.get();
    rovescia(5);
    //sistema che salva i 5 click necessari per l'aggiunta della canzone
    while(i<5){
        if(GetAsyncKeyState(MK_LBUTTON)!=0&&antiRipetizione){
            GetCursorPos(&Punti[i]);
            ++i;
            antiRipetizione=false;
        }
        if(GetAsyncKeyState(MK_LBUTTON)==0&&!antiRipetizione){
            antiRipetizione=true;
        }
    }
    
    std::cout<<"incollare qui quello che avete copiato da spotify ricordati di salvare e chiudere prima di continuare(schiacciare invio per continuare)\n";
    ShellExecute(0,"open","playlist.txt",nullptr,nullptr,SW_SHOWNORMAL);
    std::cin.get();
    //variabile per leggere i vari titoli nel file playlist.txt
    std::ifstream leggi("playlist.txt");
    //salva i vari titoli nel vettore titoli
    while(std::getline(leggi,titolo)){
        titoli.push_back(titolo);
    }
    leggi.close();
    rovescia(10);
    //esegue i passaggi fatti dall'utente e scrive i vari titoli con la tastiera per aggiungere una canzone ci mette 3secondi 
    for(size_t i=0;i<titoli.size();++i){
        SetCursorPos(Punti[0].x,Punti[0].y);
        mouse.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
        SendInput(1,&mouse,sizeof(mouse));
        mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
        SendInput(1,&mouse,sizeof(mouse));
        SendInput(4, pulisci, sizeof(INPUT));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        simulaTastiera(titoli[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        for(size_t j=1;j<5;++j){
            SetCursorPos(Punti[j].x,Punti[j].y);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
            SendInput(1,&mouse,sizeof(mouse));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
            SendInput(1,&mouse,sizeof(mouse));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
            SendInput(1,&mouse,sizeof(mouse));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    if(!DeleteFile("playlist.txt")){
        std::cout<<"non è stato possibile eliminare il file playlist.txt";
        std::cin.get();
    }
    return 0;
}


