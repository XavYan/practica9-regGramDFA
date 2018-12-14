#include "../include/GR.hpp"

int main (void) {
  GR gram;

  bool errorApertura;
  gram.gen_GR("../examples/ejemplo1.dfa", errorApertura);
  gram.export_to("../build/ejemplo1.grammar", errorApertura);
  if (!errorApertura) cout << "Todo correcto.\n"; else cout << "Ha habido algun problema durante la ejecucion del programa.\n";
}
