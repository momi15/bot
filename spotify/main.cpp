#include "main.hpp"
void rovescia(int tempo){
    for(size_t i=tempo;i>0;--i){
        std::cout<<"ti rimangono altri "<<i;
        ritardo(1);
        std::cout<<"\033[2J\033[H";
    }
}
void ritardo(int delay){
    //crea un thread che serve per rallentare il programma e grazie a std::chrono::seconds impostiamo un ritardo in secondi
    std::this_thread::sleep_for(std::chrono::seconds(delay));
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
    std::cout<<"benvenuto/a nel programma da spotify a ytmusic\n ti daro' 5secondi dopo di essi dovrai gia' essere su yt e star facendo i click miraccomando non farli prima altrimenti non li vedra'\n";
    system("pause");
    rovescia(5);
    std::vector<std::string> titoli;
    INPUT tastiera{0};
    tastiera.type = INPUT_KEYBOARD;
    tastiera.ki.wVk = 0;
    tastiera.ki.time = 0;
    tastiera.ki.dwExtraInfo = 0;
    
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

    INPUT mouse={0};
    mouse.type=INPUT_MOUSE;
    mouse.mi.dwExtraInfo=0;
    mouse.mi.time=0;
    WPARAM prog;
    POINT Punti[4]={0};
    size_t i=0;
    std::string titolo="";
    bool antiRipetizione=true;
    std::ofstream file("playlist.txt");
    
    //sistema che salva i 5 click necessari per l'aggiunta della canzone
    #pragma region click
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
    #pragma endregion
    std::cout<<"incollare qui quello che avete copiato da spotify ricordati di salvare e chiudere prima di continuare\n";
    file.close();
    system("start playlist.txt");
    system("pause");
    
    std::ifstream leggi("playlist.txt");
    while(std::getline(leggi,titolo)){
        titoli.push_back(titolo);
    }
    leggi.close();
    rovescia(10);
    for(size_t i=0;i<titoli.size();++i){
        SetCursorPos(Punti[0].x,Punti[0].y);
        mouse.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
        SendInput(1,&mouse,sizeof(mouse));
        mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
        SendInput(1,&mouse,sizeof(mouse));
        SendInput(4, pulisci, sizeof(INPUT));
        ritardo(1);
        simulaTastiera(titoli[i]);
        ritardo(1);
        for(size_t j=1;j<5;++j){
            SetCursorPos(Punti[j].x,Punti[j].y);
            ritardo(1);
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
            SendInput(1,&mouse,sizeof(mouse));
            ritardo(1);
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
            SendInput(1,&mouse,sizeof(mouse));
            ritardo(1);
            mouse.mi.dwFlags=MOUSEEVENTF_LEFTUP;
            SendInput(1,&mouse,sizeof(mouse));
            ritardo(1);
        }
    }
    return 0;
}