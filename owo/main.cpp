#include "main.hpp"
//funzione che simula la pressione di un tasto
void simulaTastiera(PINPUT input[4],const std::string& testo){
    for (char c : testo){
        input[1]->ki.wScan=input[0]->ki.wScan = c;
        SendInput(1, input[0], sizeof(INPUT));
        SendInput(1, input[1], sizeof(INPUT));
    }
    SendInput(1, input[2], sizeof(INPUT));
    SendInput(1, input[3], sizeof(INPUT));
}

//funzione che dati 2 numeri uno massimo e uno minimo generi dei numeri tra di loro compresi loro
int NumeriCasuali(int max,int min){
    return static_cast<int>(rand()%(max-min+1)+min);
}
//funzione che causa un ritardo
void ritardo(int delay){
    //stampa di quanto sarà il ritardo
    std::cout<<delay<<std::endl;
    for(size_t i=delay;i>0;--i){
        //crea un thread che serve per rallentare il programma e grazie a std::chrono::seconds impostiamo un ritardo in secondi
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
//controlla quale gemma sto utilizzando in un dato momento
int controlloQualeGemmaStoUsando(Gemma &gemma){
    //controlla quale è la cosa di rango più alto io abbia con della durabilità
    if(gemma.durability_fabled>0)return fabled;
    if(gemma.durability_legendary>0)return legendary;
    if(gemma.durability_mythical>0)return mythical;
    if(gemma.durability_epic>0)return epic;
    if(gemma.durability_rare>0)return rare;
    if(gemma.durability_uncommon>0)return uncommon;
    if(gemma.durability_common>0)return common;
    return massimo;
}
//controlla quali gemme ho di rango più alto
int controlloNelMagazino(Gemma gemma){
    //se ho più di 0 gemme di un determinato rango mi returna quel rango in modo che il programma sappia quale gemma di rango più alto io abbia
    if(gemma.fabled>0)return fabled;
    if(gemma.legendary>0)return legendary;
    if(gemma.mythical>0)return mythical;
    if(gemma.epic>0)return epic;
    if(gemma.rare>0)return rare;
    if(gemma.uncommon>0)return uncommon;
    if(gemma.common>0)return common;
    return massimo;
}
//vede quale gemma ho il rango più alto
void disponibilita_gemma_maggiore(PINPUT input[4],Gemma &gemma) {
    //switch per vedere quale gemma io abbia di rango più alto e userà quella gemma
    switch (controlloNelMagazino(gemma))
    {
    case fabled:
        simulaTastiera(input,"owo use " + gemma.id[fabled]);
        if(gemma.fabled>0){
            gemma.durability_fabled=1000;
        }
        ritardo(10);
        --gemma.fabled;
    break;
    case legendary:
        simulaTastiera(input,"owo use " + gemma.id[legendary]);
        if(gemma.legendary>0){
            gemma.durability_legendary=800;
        }
        ritardo(10);
        --gemma.legendary;
    break;
    case mythical:
        simulaTastiera(input,"owo use " + gemma.id[mythical]);
        if(gemma.mythical>0){
            gemma.durability_mythical=525;
        }
        ritardo(10);
        --gemma.mythical;
    break;
    case epic:
        simulaTastiera(input,"owo use " + gemma.id[epic]);
        if(gemma.epic>0){
            gemma.durability_epic=450;
        }
        ritardo(10);
        --gemma.epic;
    break;
    case rare:
        simulaTastiera(input,"owo use " + gemma.id[rare]);
        if(gemma.rare>0){
            gemma.durability_rare=250;
        }
        ritardo(10);
        --gemma.rare;
    break;
    case uncommon:
        simulaTastiera(input,"owo use " + gemma.id[uncommon]);
        if(gemma.uncommon>0){
            gemma.durability_uncommon=100;
        }
        ritardo(10);
        --gemma.uncommon;
    break;
    case common:
        simulaTastiera(input,"owo use " + gemma.id[common]);
        if(gemma.common>0){
            gemma.durability_common=50;
        }
        ritardo(10);
        --gemma.common;
    break;
    }
}
//data una gemma controlla quale è quella con il rango più alto con della durabilità e decrementa quella durabilità
void ridimensionaGemme(PINPUT input[4],Gemma &gemma,int decremento) {
    //switch che in base al valore returnato dalla funzione controlloQualeGemmaStoUsando suddivide il tutto  
    switch (controlloQualeGemmaStoUsando(gemma))
    {
        case fabled:{
            gemma.durability_fabled -= decremento;
            if (gemma.durability_fabled <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case legendary:{
            gemma.durability_legendary -= decremento;
            if (gemma.durability_legendary <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case mythical:{
            gemma.durability_mythical -= decremento;
            if (gemma.durability_mythical <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case epic:{
            gemma.durability_epic -= decremento;
            if (gemma.durability_epic <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case rare:{
            gemma.durability_rare -= decremento;
            if (gemma.durability_rare <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case uncommon:{
            gemma.durability_uncommon -= decremento;
            if (gemma.durability_uncommon <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        case common:{
            gemma.durability_common -= decremento;
            if (gemma.durability_common <= 0) {
                disponibilita_gemma_maggiore(input,gemma);
            }
        break;
        }
        default:{
            disponibilita_gemma_maggiore(input,gemma);
        }
    }
}
//controlla quale gemme diamante si sta usando e da essa decrementa le altre 2 gemme
void decrementoGemme(PINPUT input[4],Gemma &diamante,Gemma&cerchio,Gemma&cuore){
    //switch per verificare quale rango di tipo diamante stia usando
    switch (controlloQualeGemmaStoUsando(diamante))
    {        
        case fabled:{
            --diamante.durability_fabled;
            ridimensionaGemme(input,cuore,10);
            ridimensionaGemme(input,cerchio,10);
            break;
        }
        case legendary:{
            --diamante.durability_legendary;
            ridimensionaGemme(input,cuore,8);
            ridimensionaGemme(input,cerchio,8);
            break;
        }
        case mythical:{
            --diamante.durability_mythical;
            ridimensionaGemme(input,cuore,7);
            ridimensionaGemme(input,cerchio,7);
            break;
        }
        case epic:{
            --diamante.durability_epic;
            ridimensionaGemme(input,cuore,6);
            ridimensionaGemme(input,cerchio,6);
            break;
        }
        case rare:{
            --diamante.durability_rare;
            ridimensionaGemme(input,cuore,5);
            ridimensionaGemme(input,cerchio,5);
            break;
        }
        case uncommon:{
            --diamante.durability_uncommon;
            ridimensionaGemme(input,cuore,4);
            ridimensionaGemme(input,cerchio,4);
            break;
        }
        case common:{
            --diamante.durability_common;
            ridimensionaGemme(input,cuore,2);
            ridimensionaGemme(input,cerchio,2);
            break;
        }
        default:{
            disponibilita_gemma_maggiore(input,diamante);
            break;
        }
    }
}
//funziona che controlla quante gemme mi rimangono di 
void aggiornamentoDurability(Gemma &gemma){
    //imposta la durabilità a 0 se trova che non ho gemme di quel rango
    if(gemma.fabled<=0) gemma.durability_fabled=0;
    if(gemma.legendary<=0) gemma.durability_legendary=0;
    if(gemma.epic<=0) gemma.durability_epic=0;
    if(gemma.mythical<=0) gemma.durability_mythical=0;
    if(gemma.rare<=0) gemma.durability_rare=0;
    if(gemma.uncommon<=0) gemma.durability_uncommon=0;
    if(gemma.common<=0) gemma.durability_common=0;
}
//funzione per utilizzare le gemme
void usaGemme(PINPUT input[4],Gemma gemma){
    disponibilita_gemma_maggiore(input,gemma);
}
//assegna l'id di ogni rango dato un n iniziale messo in id lui inizia a contare per tutti i ranghi aumentando di 1 ogni volta
void assegnazioneid(Gemma &gemma,int id){
    for(int i=0;i<massimo;++i){
        gemma.id.push_back(std::to_string(id));
        ++id;
    }
}
//funzione che fa un conto alla rovescia funziona grazie agli ansi code
void conto_alla_rovescia(int inizio){
    //for per ripetere il tutto per il valore di inizio
    for(int i=inizio;i>0;--i){
        //colora il testo di verde grazie al 32m e lo mette in grassetto grazie a quel 1
        std::cout<<"\033[1;32m tra "<<i<<"sec inizia il programma \033[0;0m";
        //ritardo di 1 sec
        ritardo(1);
        //mette il mouse nell'angolo in alto a destra e poi cancella quella riga
        std::cout<<"\033[1A\033[2K";
    }
}
//al inizio per qualche motivo anche se scrivi che hai 2 gemme comuni di tipo cuore per esempio lui quando fa il comando al inizio del programma non scala queste gemme ma solo all'inizio questa funzione serve per risolvere questo problema
void aggiornaGemmeAllInizio(Gemma &gemme){
    switch (controlloNelMagazino(gemme))
    {
    case fabled:
        --gemme.fabled;
        break;
    
    case legendary:
        --gemme.legendary;
        break;
    
    case mythical:
        --gemme.mythical;
        break;

    case epic:
        --gemme.epic;
        break;
    
    case rare:
        --gemme.rare;
        break;
    
    case uncommon:
        --gemme.uncommon;
        break;
    case common:
        --gemme.common;
        break;
    }
}
int main() {
    PINPUT input[4];
    for(size_t i=0;i<5;++i){
        input[i]=new INPUT();
    }
    input[0]->type = input[1]->type = input[2]->type = input[3]->type = INPUT_KEYBOARD;
    input[0]->ki.wVk =0;
    input[1]->ki.wVk = 0;
    input[2]->ki.wVk = VK_RETURN;
    input[3]->ki.wVk = VK_RETURN;
    input[2]->ki.dwFlags = 0;    
    input[0]->ki.dwFlags = KEYEVENTF_UNICODE;
    input[3]->ki.dwFlags = KEYEVENTF_KEYUP;
    input[1]->ki.dwFlags = KEYEVENTF_KEYUP;
    input[2]->ki.wScan = MapVirtualKey(VK_RETURN,0);
    input[3]->ki.wScan = MapVirtualKey(VK_RETURN,0);
    //imposta il seed in base al tempo in modo che siano numeri casuali
    srand(time(0));

    //conto alla rovescia da 5 sec 
    conto_alla_rovescia(5);

    //funzioni per mettere l'id ai vari tipi di diamanti
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
    //regolazione iniziale delle gemme
    aggiornaGemmeAllInizio(diamante);
    aggiornaGemmeAllInizio(cuore);
    aggiornaGemmeAllInizio(cerchio);

    //comando che dice owo use poi scrive l'id delle gemme con il rango maggiore
    // usaGemme(diamante);
    // usaGemme(cuore);
    // usaGemme(cerchio);
    
    //variabile per il conteggio
    int conteggio=0;
    bool antiRipetizione=true,vai=true;

    while(true){
        if(GetAsyncKeyState(0x53)!=0&&antiRipetizione){
            antiRipetizione=false;
            vai=!vai;
        }
        if(GetAsyncKeyState(0x53)==0&&!antiRipetizione){
            antiRipetizione=true;
        }
        //scrittura di owob
        if(vai){
            simulaTastiera(input,"owob");
            ritardo(NumeriCasuali(16,8));
        }
        else{
            std::cout<<"non stampo\n";
            ritardo(1);
        }
        //ritarda il prossimo comando per un ritardo casuale tra 16 e gli 8 secondi
        //incremento per il conteggio
        ++conteggio;
        //scrittura di owoh
        if(vai){
            simulaTastiera(input,"owoh");
            ritardo(NumeriCasuali(16,8));
        }
        else{
            std::cout<<"non stampo\n";
            ritardo(1);
        }
        //funzione che serve per decrementare il valore della durability dell gemme
        //decrementoGemme(diamante,cerchio,cuore);
            //ritarda il prossimo comando per un ritardo casuale tra 16 e gli 8 secondi
            //incremento per il conteggio
            ++conteggio;
            //ritardo dopo un ora di n casuale tra i 600 e i 300
            if(conteggio%360==0){
                ritardo(NumeriCasuali(600,300));
            }
        }
    delete [] input;
    return 0;
}