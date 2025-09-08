#include "my-pass.h"

unsigned int my_opt_pass::execute(function *fun) {
  // TODO: analysis/optimization on fun.
  //       inspect execute on other passes. Also
  //       look for other passes to go before/after.
  std::cerr << "                     my_opt_pass!\n";
  return 0;
}

opt_pass *my_opt_pass::clone() {
  return this;
}

