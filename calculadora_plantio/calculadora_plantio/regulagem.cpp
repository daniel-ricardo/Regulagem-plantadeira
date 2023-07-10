#include "regulagem.hpp"

Regulagem::Semente::Semente() :variedade(""), gramas(0.0) {}
Regulagem::Semente::Semente(float g) :variedade(""), gramas(g) {}
Regulagem::Semente::Semente(std::string v, float g) :variedade(v), gramas(g) {}
Regulagem::Semente::~Semente() { }
void Regulagem::Semente::setGram(float g) { this->gramas = g; }
void Regulagem::Semente::setVari(std::string v) { this->variedade = v; }
float Regulagem::Semente::getGram() { return this->gramas; }
std::string Regulagem::Semente::getVari() { return this->variedade; }

Regulagem::Adubo::Adubo() :formula(""), gramas(0.0) {}
Regulagem::Adubo::Adubo(float g) :formula(""), gramas(g) {}
Regulagem::Adubo::Adubo(std::string f, float g) :formula(f), gramas(g) {}
Regulagem::Adubo::~Adubo() {  }
void Regulagem::Adubo::setGram(float g) { this->gramas = g; }
void Regulagem::Adubo::setForm(std::string f) { this->formula = f; }
float Regulagem::Adubo::getGram() { return this->gramas; }
std::string Regulagem::Adubo::getForm() { return this->formula; }

    /// Valores padrão: 17 centímetros de espaçamento e 25 metros de tiro
Regulagem::Regulagem() :espacamento(17), tiro(25), cultura(""),
        semente(static_cast<Regulagem::Semente*>(new Regulagem::Semente())), adubo(static_cast<Regulagem::Adubo*>(new Regulagem::Adubo())) {}
Regulagem::Regulagem(float e, float t, std::string c, float g) :espacamento(e), tiro(t), cultura(c),
        semente(static_cast<Regulagem::Semente*>(new Regulagem::Semente(g))), adubo(static_cast<Regulagem::Adubo*>(new Regulagem::Adubo())) {}
Regulagem::~Regulagem() { delete& espacamento; delete& tiro; delete& cultura; delete semente; delete adubo; }

void Regulagem::setEspc(float e) 
{
    auto kgha = calcularQuilosHectare(this);
    this->espacamento = e;
    this->semente->setGram(calcularGramasTiro(kgha[0], this));
    this->adubo->setGram(calcularGramasTiro(kgha[1], this));
}
void Regulagem::setTiro(float t)
{
    auto kgha{ calcularQuilosHectare(this) };
    this->tiro = t;
    this->semente->setGram(calcularGramasTiro(kgha[0], this));
    this->adubo->setGram(calcularGramasTiro(kgha[1], this));
}
void Regulagem::setCult(std::string c)    { this->cultura = c; }
void Regulagem::setGramS(float g)         { this->semente->setGram(g); }
void Regulagem::setGramA(float g)         { this->adubo->setGram(g); }
void Regulagem::setVariSmt(std::string v) { this->semente->setVari(v); }
void Regulagem::setFormAdb(std::string f) { this->adubo->setForm(f); }

float Regulagem::getEspc()         { return this->espacamento; }
float Regulagem::getTiro()         { return this->tiro; }
std::string Regulagem::getCult()   { return this->cultura; }
float Regulagem::getGramSmt()      { return this->semente->getGram(); }
float Regulagem::getGramAdb()      { return this->adubo->getGram(); }

// para linha de comando
void Regulagem::printRegulagem()
{
    auto kgha = calcularQuilosHectare(this);
    if (std::strcmp(this->getCult().c_str(), "") != 0)
    {
        std::printf("Cultura: %s\n", this->getCult().c_str());
    }
    std::printf("Regulagem: espacamento de %.0f centímetros\n", round(this->getEspc()));
    std::printf("\nSemente: ");
    if (std::strcmp(this->semente->getVari().c_str(), "") != 0)
    {
        std::printf("%s\n", this->semente->getVari().c_str());
    }
    std::printf("%.0f gramas em %.0f metros\n\tTotal: %.0f kg/ha\n",
        round(this->semente->getGram()), round(this->getTiro()), round(kgha[0]));
    std::printf("\nAdubo: ");
    if (std::strcmp(this->adubo->getForm().c_str(), "") != 0)
    {
        std::printf("%s\n", this->adubo->getForm().c_str());
    }
    std::printf("%.0f gramas em %.0f metros\n\tTotal: %.0f kg/ha\n",
        round(this->adubo->getGram()), round(this->getTiro()), round(kgha[1])
    );
}

float calcularGramasTiro(float k, Regulagem* r)
{
    return static_cast<float>( (k * r->getTiro() * r->getEspc()) ) / static_cast<float>(1000.0);
}

std::array<float, 2> calcularQuilosHectare(Regulagem* r)
{
    /*
     * array kgha armazena quilos por hectare tanto da semente quanto do adubo
     * 0 -> kg/ha de semente
     * 1 -> kg/ha de adubo
     */
    std::array<float, 2> kgha;
    kgha[0] = static_cast<float>( (r->getGramSmt() * 1000.0) ) / static_cast<float>( (r->getEspc() * r->getTiro()) );
    kgha[1] = static_cast<float>( (r->getGramAdb() * 1000.0) ) / static_cast<float>( (r->getEspc() * r->getTiro()) );
    return kgha;
}