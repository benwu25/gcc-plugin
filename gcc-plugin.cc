#include <gcc-plugin.h>
#include <plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <tree-iterator.h>
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
    if (TREE_CODE (function_body) == STATEMENT_LIST) { // yes :P
      std::cout << "function_body is a STATEMENT_LIST\n";
      tree_stmt_iterator it;
      for (it = tsi_start (function_body); !tsi_end_p (it); tsi_next (&it)) {
        tree stmt = it.ptr->stmt;
        if (TREE_CODE (stmt) == BIND_EXPR) {
          std::cout << "bind expr\n";
        } else if (TREE_CODE (stmt) == RETURN_EXPR) {
          std::cout << "return expr\n";
        }
      }
    } else {
      std::cout << "something else\n";
    }
  }
}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
  register_callback("GCCPlugin",
                    PLUGIN_FINISH_PARSE_FUNCTION,
                    (plugin_callback_func) handle_function,
                    NULL);
  return 0;
}
