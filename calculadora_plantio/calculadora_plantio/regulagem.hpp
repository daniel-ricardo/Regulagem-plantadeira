// Declaração da classe Regulagem e funções para calcular gramas/tiro e quilos/hectare
#pragma once

#include <iostream>
#include <locale>
#include <cmath>
#include <cstring>
#include <string>
#include <array>

class Regulagem
{
protected:
    class Semente
    {
    private:
        std::string variedade;
        float gramas;
    public:
        Semente();
        Semente(float g);
        Semente(std::string v, float g);
        ~Semente();
        void setGram(float g);
        void setVari(std::string v);
        float getGram();
        std::string getVari();
    };
    class Adubo
    {
    private:
        std::string formula;
        float gramas;
    public:
        Adubo();
        Adubo(float g);
        Adubo(std::string f, float g);
        ~Adubo();
        void setGram(float g);
        void setForm(std::string f);
        float getGram();
        std::string getForm();
    };
private:
    float espacamento;
    float tiro;
    std::string cultura;
    Semente* semente;
    Adubo* adubo;
public:
    Regulagem();
    Regulagem(float e, float t, std::string c, float g);
    ~Regulagem();

    void setEspc(float e);
    void setTiro(float t);
    void setCult(std::string c);
    void setGramS(float g);
    void setGramA(float g);
    void setVariSmt(std::string v);
    void setFormAdb(std::string f);

    float getEspc();
    float getTiro();
    std::string getCult();
    float getGramSmt();
    float getGramAdb();

    /// para linha de comando
    void printRegulagem();
};
float calcularGramasTiro(float k, Regulagem* r);
/*
 * retorna quilos por hectare tanto da semente quanto do adubo
 * 0 -> kg/ha de semente
 * 1 -> kg/ha de adubo
 */
std::array<float, 2> calcularQuilosHectare(Regulagem* r);
