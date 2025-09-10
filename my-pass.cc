#include "my-pass.h"

unsigned int my_opt_pass::execute(function *fun) {
  // TODO: analysis/optimization on fun.
  //       inspect execute on other passes. Also
  //       look for other passes to go before/after.
  std::cerr << "                     my_opt_pass!\n";
  if (fun->gimple_body == NULL) {
    std::cerr << "                     gimple_body is NULL\n";
  } else {
    std::cerr << "                     gimple_body is !NULL\n";
  }
  if (fun->cfg == NULL) {
    std::cerr << "                     cfg is NULL\n";
  } else {
    std::cerr << "                     cfg is !NULL\n";
  }

  return 0;
}

opt_pass *my_opt_pass::clone() {
  return this;
}
