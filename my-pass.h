#include <gcc-plugin.h>
#include <plugin.h>
#include <coretypes.h>
#include <tree.h>
#include <tree-iterator.h>
#include <tree-pass.h>
#include <context.h>
#include <iostream>

const pass_data my_pass =
{
  GIMPLE_PASS, /* type */
  "my_pass", /* name */
  OPTGROUP_NONE, /* optinfo_flags */
  TV_NONE, /* tv_id */
  0, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

// New pass. no additional functionality yet
class my_opt_pass : public gimple_opt_pass {
public:
  my_opt_pass(gcc::context *ctxt) : gimple_opt_pass(my_pass, ctxt) {}

  virtual unsigned int execute(function *fun) override;

  virtual opt_pass *clone() override;
};
