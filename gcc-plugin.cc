#include <gcc-plugin.h>
#include <plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <iostream>

int plugin_is_GPL_compatible = 0;

// callbacks
void handle_function(void *gcc_data, void *user_data) {
  if (gcc_data == NULL) {
    std::cerr << "no data\n";
    return;
  } else {
    tree decl1 = (tree) gcc_data;
    std::cout << IDENTIFIER_POINTER (DECL_NAME (decl1)) << "\n";
    tree function_body = DECL_SAVED_TREE (decl1); // see tree-core.h:1964
  }
}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
  register_callback("GCCPlugin",
                    PLUGIN_FINISH_PARSE_FUNCTION,
                    (plugin_callback_func) handle_function,
                    NULL);
  return 0;
}
