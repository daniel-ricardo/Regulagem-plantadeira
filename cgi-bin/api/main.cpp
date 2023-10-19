#include <iostream>
#include "json.hpp"
#include "regulagem.hpp"

int main(int argc, char **argv){
  std::cout << "Content-type: application/json\n" << '\n';

  std::string get {};

  if(std::getenv("QUERY_STRING")){
    get = std::getenv("QUERY_STRING");
  }

  auto r = new Regulagem;
  
  nlohmann::json json;
  
  json["cultura"] = r-> getCult();
  json["semente"] = r->getVar();
  json["adubo"] = r-> getForm();
  json["espacamento"] = r-> getEspc();
  json["tiro"] = r-> getTiro();
  json["gramSmt"] = r-> getGramSmt();
  json["gramAdb"] = r-> getGramAdb();

  std::cout << json << '\n';
 
  return 0;
}