#pragma once
//librerie
#include <windows.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono> 
#include <iostream>
//definizione della gemma
struct Gemma
    {
    std::string string_fabled="",
                string_legendary="",
                string_mythical="",
                string_epic="",
                string_rare="",
                string_uncommon="",
                string_common="";

        int fabled=0,
            legendary=0,
            mythical=0,
            epic=0,
            rare=0,
            uncommon=0,
            common=0;

        int durability_fabled=0,
            durability_legendary=0,
            durability_mythical=0,
            durability_epic=0,
            durability_rare=0,
            durability_uncommon=0,
            durability_common=0;
    };

//dichiarazione varie gemme
Gemma diamante,cerchio,cuore;

//funzioni
void simulaTastiera(const std::string& testo);
int NumeriCasuali(int max,int min);
void ritardo(int delay);
void decrementoGemme(Gemma &diamante,Gemma&cerchio,Gemma&cuore);
std::string controlloQualeGemmaStoUsando(Gemma &gemma);
void ridimensionaGemme(Gemma &gemma);
void disponibilita_gemma_maggiore(Gemma &gemma);

std::string controlloNelMagazino(Gemma gemma);
