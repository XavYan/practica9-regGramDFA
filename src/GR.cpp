#include "../include/GR.hpp"


GR::GR (void) : alphabet_(), V_(), S_(), P_() {}
GR::~GR (void) {
  alphabet_.clear();
  V_.clear();
  P_.clear();
}

void GR::gen_GR (const char* nombreFichero, bool& errorApertura) {
  DFA dfa;
  errorApertura = 0;
  dfa.create_dfa(nombreFichero,errorApertura);
  if (errorApertura) {
    cerr << "Error. Ha ocurrido un problema al abrir el archivo. No se puede continuar.\n";
    return;
  }
  dfa.minDFA(); //Nos aseguramos de que el DFA sea minimo.

  //EMPEZAMOS A OBTENER LOS VALORES
  alphabet_ = dfa.alphabet(); //Alfabeto de la gramatica

  //Establecemos los valores de los simbolos no terminales
  vector<char> V(dfa.size());
  S_ = V[dfa.init()] = 'S';
  V_.insert(S_);
  char ascii = 65;
  for (int i = 0; i < V.size(); i++) {
    if (i != dfa.init()) {
      if (ascii >= 65 && ascii <= 90) {
        V[i] = ascii; //Le asignamos una letra
        V_.insert(ascii); //Añadimos ese simbolo al conjunto
        ascii++;
      }
    }
  }
  //Prototipos
  /* Como habra tantos prototipos como estados del DFA */
  for (state_t state : dfa.getStates()) {
    string aux_s;
    aux_s = V[state.id()];
    aux_s += " -> ";
    unsigned cont = 0;
    for (pair<char,unsigned> pair : state.getNext()) {
      aux_s += get<0>(pair);
      aux_s += V[get<1>(pair)];
      if (++cont < state.getNext().size()) aux_s += "|";
    }
    if (state.is_accept()) aux_s += "|~";
    P_.insert(aux_s);
  }
}

void GR::export_to (const char* nombreFichero, bool& errorApertura) {

}

const set<char> GR::alphabet (void) {
  return alphabet_;
}

ostream& GR::write (ostream& os) {
  //Imprimimos el alfabeto
  os << "{";
  unsigned cont = 0;
  for (char c : alphabet_) {
    os << c << (++cont < alphabet_.size() ? "," : "");
  }
  os << "}\n";

  //Imprimimos axioma de la gramatica
  os << S_ << "\n";

  //Imprimimos los simbolos no terminales
  for (char c : V_) {
    os << c << " ";
  }
  os << "\n";


  //Imprimimos los prototipos
  for (string s : P_) {
    os << s << "\n";
  }
  return os;
}
