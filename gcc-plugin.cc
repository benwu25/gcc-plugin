#include <gcc-plugin.h>
#include <plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <iostream>

int plugin_is_GPL_compatible = 0;

// callbacks
void handle_function(void *gcc_data, void *user_data) {
  std::cout << "well hullo!\n";
  if (gcc_data == NULL) {
    std::cout << "data is NULL\n";
  } else {
    std::cout << "data is not NULL, what is it?\n"; // a tree decl :P true for START and FINISH.
    tree decl1 = (tree) gcc_data;
    std::cout << "tree code is: " << TREE_CODE(decl1) << "\n";
  }
}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
  register_callback("GCCPlugin",
                    PLUGIN_FINISH_PARSE_FUNCTION,
                    (plugin_callback_func) handle_function,
                    NULL);
  return 0;
}
