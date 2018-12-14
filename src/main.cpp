#include "../include/GR.hpp"

int main (void) {
  GR gram;

  bool errorApertura;
  gram.gen_GR("../examples/ejemplo1.dfa", errorApertura);
  gram.write(cout);
}
