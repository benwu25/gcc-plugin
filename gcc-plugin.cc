#include "my-pass.h"

int plugin_is_GPL_compatible = 0;

//== callbacks ==//


// PLUGIN_FINISH_PARSE_FUNCTION
void handle_function(void *gcc_data, void *user_data) {
  if (gcc_data == NULL) {
    std::cerr << "no function data\n";
    return;
  } else {
    tree decl1 = (tree) gcc_data;
    std::cout << IDENTIFIER_POINTER (DECL_NAME (decl1)) << "\n";
    tree function_body = DECL_SAVED_TREE (decl1);
    if (TREE_CODE (function_body) == STATEMENT_LIST) {
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

// PLUGIN_PASS_EXECUTION
void execute_pass(void *gcc_data, void *user_data) {
  opt_pass *pass = static_cast<opt_pass *>(gcc_data);
  if (pass == NULL) {
    std::cerr << "no execute pass data\n";
  }
  std::cerr << "executing pass # " << pass->static_pass_number << "\n";
  std::cerr << "  " << pass->name << "\n";
  switch (pass->type) {
    case GIMPLE_PASS:
    {
      std::cout << "  GIMPLE_PASS\n";
      break;
    }
    case RTL_PASS:
    {
      std::cout << "  RTL_PASS\n";
      break;
    }
    case SIMPLE_IPA_PASS:
    {
      std::cout << "  SIMPLE_IPA_PASS\n";
      break;
    }
    case IPA_PASS:
    {
      std::cout << "  IPA_PASS\n";
      break;
    }
  }
}

// PLUGIN_NEW_PASS
void new_pass(void *gcc_data, void *user_data) {
  opt_pass *new_pass = (opt_pass *) gcc_data;
  if (new_pass == NULL) {
    std::cerr << "no new pass data\n";
  }
  std::cout << "new pass with #: " << new_pass->static_pass_number << "\n";
}


//== ==//


int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {

  // Register callbacks
  register_callback("GCCPlugin",
                    PLUGIN_FINISH_PARSE_FUNCTION,
                    (plugin_callback_func) handle_function,
                    NULL);

  register_callback("GCCPlugin",
                    PLUGIN_PASS_EXECUTION,
                    (plugin_callback_func) execute_pass,
                    NULL);

  register_callback("GCCPlugin",
                    PLUGIN_NEW_PASS,
                    (plugin_callback_func) new_pass,
                    NULL);

  // New pass
  gcc::context *ctxt = g;
  register_pass_info rpi{};

  rpi.pass = new my_opt_pass(ctxt);
  rpi.pass->static_pass_number = 8000;
  rpi.reference_pass_name = "*warn_unused_result";
  rpi.ref_pass_instance_number = 0;
  rpi.pos_op = PASS_POS_INSERT_BEFORE;

  register_callback(plugin_info->base_name,
                    PLUGIN_PASS_MANAGER_SETUP,
                    NULL,
                    &rpi);

  return 0;
}
