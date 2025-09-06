#include <gcc-plugin.h>
#include <plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <tree-iterator.h>
#include <tree-pass.h>
#include <iostream>

int plugin_is_GPL_compatible = 0;

//== callbacks ==//


// PLUGIN_FINISH_PARSE_FUNCTION
void handle_function(void *gcc_data, void *user_data) {
  if (gcc_data == NULL) {
    std::cerr << "no function data\n";
    return;
  } else {
    tree decl1 = static_cast<tree>(gcc_data);
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

// PLUGIN_PASS_EXECUTION
void execute_pass(void *gcc_data, void *user_data) {
  opt_pass *pass = static_cast<opt_pass *>(gcc_data);
  if (pass == NULL) {
    std::cerr << "no execute pass data\n";
  }
  std::cout << "executing pass # " << pass->static_pass_number << "\n";
  switch (pass->type) {
    case GIMPLE_PASS:
    {
      std::cout << "  GIMPLE_PASS\n";
      gimple_opt_pass *gp = reinterpret_cast<gimple_opt_pass *>(pass);
      break;
    }
    case RTL_PASS:
    {
      std::cout << "  RTL_PASS\n";
      rtl_opt_pass *rp = reinterpret_cast<rtl_opt_pass *>(pass);
      break;
    }
    case SIMPLE_IPA_PASS:
    {
      std::cout << "  SIMPLE_IPA_PASS\n";
      simple_ipa_opt_pass *sipa = reinterpret_cast<simple_ipa_opt_pass *>(pass);
      break;
    }
    case IPA_PASS:
    {
      std::cout << "  IPA_PASS\n";
      ipa_opt_pass_d *ipd = reinterpret_cast<ipa_opt_pass_d *>(pass);
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
  return 0;
}
