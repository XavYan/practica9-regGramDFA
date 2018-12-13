#include "../include/GR.hpp"


GR::GR (void) : alphabet_(), V_(), S_(), P_() {}
GR::~GR (void) {
  alphabet_.clear();
  V_.clear();
  S_.clear();
  P_.clear();
}

void GR::gen_GR (const char* nombreFichero, bool& errorApertura) {
  DFA dfa;
  dfa.create_dfa(nombreFichero,errorApertura);
  if (errorApertura) {
    cerr << "Error. Ha ocurrido un problema al abrir el archivo. No se puede continuar.\n";
    return;
  }
  dfa.minDFA(); //Nos aseguramos de que el DFA sea minimo.
}

void GR::export (const char* nombreFichero, bool& errorApertura) {

}

const set<char> GR::alphabet (void) {
  return alphabet_;
}
