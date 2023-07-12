#include "tools.hpp"

std::string pontuarMilhares(float numero)
{
	char separator = std::use_facet< std::numpunct<char> >(std::cout.getloc()).thousands_sep();
	float milhares = numero / 1000;
	float unidades = static_cast<int>(numero) % 1000;
	if(numero < 1000 ){ return std::format("{:.2f}", unidades); }
	return std::format("{}", milhares) + separator + std::format("{:.2f}", unidades);
}
