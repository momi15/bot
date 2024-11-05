#include "main.hpp"
void simulaTastiera(const std::string& testo) {
    for (char c : testo) {
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
int NumeriCasuali(int max,int min){
    return static_cast<int>(rand()%(max-min+1)+min);
}
void ritardo(int delay){
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    std::cout<<delay<<std::endl;
}
std::string controlloQualeGemmaStoUsando(Gemma &gemma){
    if(gemma.durability_fabled>0)return "fabled";
    if(gemma.durability_legendary>0)return "legendary";
    if(gemma.durability_mythical>0)return "mythical";
    if(gemma.durability_epic>0)return "epic";
    if(gemma.durability_rare>0)return "rare";
    if(gemma.durability_uncommon>0)return "uncommon";
    if(gemma.durability_common>0)return "common";
    return "";
}
std::string controlloNelMagazino(Gemma gemma){
    if(gemma.fabled>0)return "fabled";
    if(gemma.legendary>0)return "legendary";
    if(gemma.mythical>0)return "mythical";
    if(gemma.epic>0)return "epic";
    if(gemma.rare>0)return "rare";
    if(gemma.uncommon>0)return "uncommon";
    if(gemma.common>0)return "common";
    return "";
}
void disponibilita_gemma_maggiore(Gemma &gemma) {
    std::string gemmaDaUsare = controlloNelMagazino(gemma);
    if (gemmaDaUsare == "fabled") {
        simulaTastiera("owo use " + gemma.id[fabled]);
        if(gemma.fabled>0){
            gemma.durability_fabled=1000;
        }
        ritardo(10);
        --gemma.fabled;
    } else if (gemmaDaUsare == "legendary") {
        simulaTastiera("owo use " + gemma.id[legendary]);
        if(gemma.legendary>0){
            gemma.durability_legendary=800;
        }
        ritardo(10);
        --gemma.legendary;
    } else if (gemmaDaUsare == "mythical") {
        simulaTastiera("owo use " + gemma.id[mythical]);
        if(gemma.mythical>0){
            gemma.durability_mythical=525;
        }
        ritardo(10);
        --gemma.mythical;
    } else if (gemmaDaUsare == "epic") {
        simulaTastiera("owo use " + gemma.id[epic]);
        if(gemma.epic>0){
            gemma.durability_epic=450;
        }
        ritardo(10);
        --gemma.epic;
    } else if (gemmaDaUsare == "rare") {
        simulaTastiera("owo use " + gemma.id[rare]);
        if(gemma.rare>0){
            gemma.durability_rare=250;
        }
        ritardo(10);
        --gemma.rare;
    } else if (gemmaDaUsare == "uncommon") {
        simulaTastiera("owo use " + gemma.id[uncommon]);
        if(gemma.uncommon>0){
            gemma.durability_uncommon=100;
        }
        ritardo(10);
        --gemma.uncommon;
    } else if (gemmaDaUsare == "common") {
        simulaTastiera("owo use " + gemma.id[common]);
        if(gemma.common>0){
            gemma.durability_common=50;
        }
        ritardo(10);
        --gemma.common;
    }
}
void ridimensionaGemme(Gemma &gemma) {
    std::string gemmaInUso = controlloQualeGemmaStoUsando(gemma);
    if (gemmaInUso == "fabled") {
        gemma.durability_fabled -= 10;
        if (gemma.durability_fabled <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "legendary") {
        gemma.durability_legendary -= 8;
        if (gemma.durability_legendary <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "mythical") {
        gemma.durability_mythical -= 7;
        if (gemma.durability_mythical <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "epic") {
        gemma.durability_epic -= 6;
        if (gemma.durability_epic <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "rare") {
        gemma.durability_rare -= 5;
        if (gemma.durability_rare <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "uncommon") {
        gemma.durability_uncommon -= 4;
        if (gemma.durability_uncommon <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    } else if (gemmaInUso == "common") {
        gemma.durability_common -= 2;
        if (gemma.durability_common <= 0) {
            disponibilita_gemma_maggiore(gemma);
        }
    }else {
        disponibilita_gemma_maggiore(gemma);
    }
}
void decrementoGemme(Gemma &diamante,Gemma&cerchio,Gemma&cuore){
    if(controlloQualeGemmaStoUsando(diamante)=="fabled"){
        --diamante.durability_fabled;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="legendary"){
        --diamante.durability_legendary;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="mythical"){
        --diamante.durability_mythical;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="epic"){
        --diamante.durability_epic;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="rare"){
        --diamante.durability_rare;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="uncommon"){
        --diamante.durability_uncommon;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }
    else if(controlloQualeGemmaStoUsando(diamante)=="common"){
        --diamante.durability_common;
        ridimensionaGemme(cuore);
        ridimensionaGemme(cerchio);
    }else {
        disponibilita_gemma_maggiore(diamante);
    }
}
void aggiornamentoDurability(Gemma &gemma){
    if(gemma.fabled<=0) gemma.durability_fabled=0;
    if(gemma.legendary<=0) gemma.durability_legendary=0;
    if(gemma.epic<=0) gemma.durability_epic=0;
    if(gemma.mythical<=0) gemma.durability_mythical=0;
    if(gemma.rare<=0) gemma.durability_rare=0;
    if(gemma.uncommon<=0) gemma.durability_uncommon=0;
    if(gemma.common<=0) gemma.durability_common=0;
}
void usaGemme(Gemma gemma){
    disponibilita_gemma_maggiore(gemma);
}
void assegnazioneid(Gemma &gemma,int id){
    for(int i=0;i<massimo;++i){
        gemma.id.push_back(std::to_string(id));
        std::cout<<id<<std::endl;
        ++id;
    }
}
void conto_alla_rovescia(int inizio){
    for(int i=inizio;i>0;--i){
        std::cout<<"\033[1;32m tra "<<i<<" inizia il programma \033[0;0m";
        ritardo(1);
        std::cout<<"\033[1A\033[2K";
    }
}
int main() {
    //imposta il seed in base al tempo in modo che siano numeri casuali
    srand(time(0));
    //conto alla rovescia da 5 sec 
    conto_alla_rovescia(5);
    
    assegnazioneid(diamante,51);
    assegnazioneid(cerchio,65);
    assegnazioneid(cuore,72);
    
    //definizioni quantita diamanti
    diamante.common=0;
    diamante.uncommon=0;
    diamante.rare=0;
    diamante.epic=0;
    diamante.mythical=0;
    diamante.legendary=0;
    diamante.fabled=0;

    //definizioni quantita cerchio
    cerchio.common=0;
    cerchio.uncommon=0;
    cerchio.rare=0;
    cerchio.epic=0;
    cerchio.mythical=0;
    cerchio.legendary=0;
    cerchio.fabled=0;

    //definizioni quantita cuore
    cuore.common=0;
    cuore.uncommon=0;
    cuore.rare=0;
    cuore.epic=0;
    cuore.mythical=0;
    cuore.legendary=0;
    cuore.fabled=0;

    //per fare in modo che le durabilità delle gemme che non abbiamo siano a 0
    aggiornamentoDurability(diamante);
    aggiornamentoDurability(cuore);
    aggiornamentoDurability(cerchio);

    //comando che dice owo use poi scrive l'id delle gemme con il rango maggiore
    usaGemme(diamante);
    usaGemme(cuore);
    usaGemme(cerchio);
    //variabile per il conteggio
    int conteggio=0;
    while(true){
        //scrittura di owob
        simulaTastiera("owob");
        //ritarda il prossimo comando per un ritardo casuale tra 16 e gli 8 secondi
        ritardo(NumeriCasuali(16,8));
        //incremento per il conteggio
        ++conteggio;
        //scrittura di owoh
        simulaTastiera("owoh");
        keybd_event(VK_RETURN, 0, 0, 0);
        //funzione che serve per decrementare il valore della durability dell gemme
        decrementoGemme(diamante,cerchio,cuore);
        //schiaccia il tasto invio
        keybd_event(VK_RETURN, 0, 0, 0);
        //ritarda il prossimo comando per un ritardo casuale tra 16 e gli 8 secondi
        ritardo(NumeriCasuali(16,8));
        //incremento per il conteggio
        ++conteggio;
        //ritardo dopo un ora di n casuale tra i 600 e i 300
        if(conteggio%360==0){
            ritardo(NumeriCasuali(600,300));
        }
    }
    return 0;
}