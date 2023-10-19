#include <iostream>
#include <locale>
#include <cmath>
#include <cstring>
#include <string>
#include <array>

class Regulagem {
protected:
    class Semente {
    private:
        std::string variedade;
        float gramas;
    public:
        Semente() :variedade(""), gramas(0.0) {}
        Semente(float g) :variedade(""), gramas(g) {}
        Semente(std::string v, float g) :variedade(v), gramas(g) {}
        ~Semente() {}
        void setGram(float g) { this->gramas = g; }
        void setVari(std::string v) { this->variedade = v; }
        float getGram() { return this->gramas; }
        std::string getVar() { return this->variedade; }
	};
    class Adubo {
    private:
        std::string formula;
        float gramas;
    public:
        Adubo() :formula(""), gramas(0.0) {}
        Adubo(float g) :formula(""), gramas(g) {}
        Adubo(std::string f, float g) :formula(f), gramas(g) {}
        ~Adubo() {}
        void setGram(float g)  { this->gramas = g; }
        void setForm(std::string f) { this->formula = f; }
        float getGram() { return this->gramas; }
        std::string getForm() { return this->formula; }
    };
private:
    float espacamento;
    float tiro;
    std::string cultura;
    Semente* semente;
    Adubo* adubo;
public:

	float calcularGramasTiro(float k){
		return static_cast<float>( (k * this->getTiro() * this->getEspc()) ) / static_cast<float>(1000.0);
	}

	std::array<float, 2> calcularQuilosHectare(){
		/*
		 * array kgha armazena quilos por hectare tanto da semente quanto do adubo
		 * 0 -> kg/ha de semente
		 * 1 -> kg/ha de adubo
		 */
		std::array<float, 2> kgha;
		kgha[0] = static_cast<float>( (this->getGramSmt() * 1000.0) ) / static_cast<float>( (this->getEspc() * this->getTiro()) );
		kgha[1] = static_cast<float>( (this->getGramAdb() * 1000.0) ) / static_cast<float>( (this->getEspc() * this->getTiro()) );
		return kgha;
	}
	
    /// Valores padrão: 17 centímetros de espaçamento e 25 metros de tiro
	Regulagem() :espacamento(17), tiro(25), cultura(""), semente(static_cast<Regulagem::Semente*>(new Regulagem::Semente())), adubo(static_cast<Regulagem::Adubo*>(new Regulagem::Adubo())) {}
	Regulagem(float e, float t, std::string c, float g) :espacamento(e), tiro(t), cultura(c), semente(static_cast<Regulagem::Semente*>(new Regulagem::Semente(g))), adubo(static_cast<Regulagem::Adubo*>(new Regulagem::Adubo())) {}
	~Regulagem() { delete &espacamento; delete &tiro; delete &cultura; delete semente; delete adubo; }


	void setEspc(float e) 	{
		auto kgha = calcularQuilosHectare();
		this->espacamento = e;
		this->semente->setGram(calcularGramasTiro(kgha[0]));
		this->adubo->setGram(calcularGramasTiro(kgha[1]));
	}
	void setTiro(float t)	{
		auto kgha{ calcularQuilosHectare() };
		this->tiro = t;
		this->semente->setGram(calcularGramasTiro(kgha[0]));
		this->adubo->setGram(calcularGramasTiro(kgha[1]));
	}
	void setCult(std::string c)    { this->cultura = c; }
	void setGramS(float g)         { this->semente->setGram(g); }
	void setGramA(float g)         { this->adubo->setGram(g); }
	void setVariSmt(std::string v) { this->semente->setVari(v); }
	void setFormAdb(std::string f) { this->adubo->setForm(f); }

	float getEspc()         { return this->espacamento; }
	float getTiro()         { return this->tiro; }
	std::string getCult()   { return this->cultura; }
	float getGramSmt()      { return this->semente->getGram(); }
	float getGramAdb()      { return this->adubo->getGram(); }
	std::string getVar()      { return this->semente->getVar(); }
	std::string getForm()      { return this->adubo->getForm(); }

    /// para linha de comando
    void printRegulagem()	{
		auto kgha = calcularQuilosHectare();
		if (std::strcmp(this->getCult().c_str(), "") != 0)
		{
			std::printf("Cultura: %s\n", this->getCult().c_str());
		}
		std::printf("Regulagem: espacamento de %.0f cent?metros\n", round(this->getEspc()));
		std::printf("\nSemente: ");
		if (std::strcmp(this->semente->getVar().c_str(), "") != 0)
		{
			std::printf("%s\n", this->semente->getVar().c_str());
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
};

