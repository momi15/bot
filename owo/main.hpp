#pragma once
//librerie
#include <windows.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <vector>
#include <chrono> 
#include <iostream>
//definizione della gemma
struct Gemma
    {
    std::vector<std::string> id;

        int fabled=0,
            legendary=0,
            mythical=0,
            epic=0,
            rare=0,
            uncommon=0,
            common=0;

        int durability_fabled=1000,
            durability_legendary=800,
            durability_mythical=525,
            durability_epic=450,
            durability_rare=250,
            durability_uncommon=100,
            durability_common=50;
    };

//dichiarazione varie gemme
Gemma diamante,cerchio,cuore;

//funzioni
void simulaTastiera(const std::string& testo);
int NumeriCasuali(int max,int min);
void ritardo(int delay);
void decrementoGemme(Gemma &diamante,Gemma&cerchio,Gemma&cuore);
int controlloQualeGemmaStoUsando(Gemma &gemma);
void ridimensionaGemme(Gemma &gemma,int decremento);
void disponibilita_gemma_maggiore(Gemma &gemma);
int controlloNelMagazino(Gemma gemma);
void assegnazioneid(Gemma &gemma,int inizio);
void conto_alla_rovescia(int inizio);
void aggiornaGemmeAllInizio(Gemma &gemme);
//enum dei vari ranghi
enum ranghi{
    common,
    uncommon,
    rare,
    epic,
    mythical,
    legendary,
    fabled,
    massimo,
};