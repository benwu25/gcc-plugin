#include <gcc-plugin.h>
#include <plugin.h>

int plugin_is_GPL_compatible = 0;

// callbacks
void handle_function(void *gcc_data, void *user_data) {

}

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
  register_callback("GCCPlugin",
                    PLUGIN_START_PARSE_FUNCTION,
                    (plugin_callback_func) handle_function,
                    NULL);
  return 0;
}
