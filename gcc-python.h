#ifndef INCLUDED__GCC_PYTHON_H
#define INCLUDED__GCC_PYTHON_H

#include <gcc-plugin.h>
#include "tree.h"
#include "gimple.h"

#define DECLARE_SIMPLE_WRAPPER(ARG_structname, ARG_typeobj, ARG_typename, ARG_wrappedtype, ARG_fieldname) \
  struct ARG_structname {           \
     PyObject_HEAD                  \
     ARG_wrappedtype ARG_fieldname; \
  };                                \
                                    \
  typedef struct ARG_structname ARG_structname;                          \
                                                                         \
  extern PyObject *                                                      \
  gcc_python_make_wrapper_##ARG_typename(ARG_wrappedtype ARG_fieldname); \
                                                                         \
  extern PyTypeObject ARG_typeobj;                                       \
                                                                         \
  /* end of macro */

DECLARE_SIMPLE_WRAPPER(PyGccPass,
		       gcc_PassType,
		       pass,
		       struct opt_pass *, pass)

DECLARE_SIMPLE_WRAPPER(PyGccLocation, 
		       gcc_LocationType,
		       location,
		       location_t, loc)

DECLARE_SIMPLE_WRAPPER(PyGccGimple, 
		       gcc_GimpleType,
		       gimple,
		       gimple, stmt);

DECLARE_SIMPLE_WRAPPER(PyGccEdge, 
		       gcc_EdgeType,
		       edge,
		       edge, e)

DECLARE_SIMPLE_WRAPPER(PyGccBasicBlock, 
		       gcc_BasicBlockType,
		       basic_block,
		       basic_block, bb)

DECLARE_SIMPLE_WRAPPER(PyGccCfg, 
		       gcc_CfgType,
		       cfg,
		       struct control_flow_graph *, cfg)

DECLARE_SIMPLE_WRAPPER(PyGccFunction, 
		       gcc_FunctionType,
		       function,
		       struct function *, fun)

DECLARE_SIMPLE_WRAPPER(PyGccTree,
		       gcc_TreeType,
		       tree, tree, t)

DECLARE_SIMPLE_WRAPPER(PyGccVariable,
		       gcc_VariableType,
		       variable,
		       struct varpool_node *, var)

/* autogenerated-cfg.c */
int autogenerated_cfg_init_types(void);
void autogenerated_cfg_add_types(PyObject *m);

/* autogenerated-function.c */
int autogenerated_function_init_types(void);
void autogenerated_function_add_types(PyObject *m);

/* autogenerated-gimple.c */
int autogenerated_gimple_init_types(void);
void autogenerated_gimple_add_types(PyObject *m);
PyTypeObject* gcc_python_autogenerated_gimple_type_for_stmt(gimple g);

/* autogenerated-location.c */
int autogenerated_location_init_types(void);
void autogenerated_location_add_types(PyObject *m);

/* autogenerated-pass.c */
int autogenerated_pass_init_types(void);
void autogenerated_pass_add_types(PyObject *m);
extern PyTypeObject gcc_GimplePassType;
extern PyTypeObject gcc_RtlPassType;
extern PyTypeObject gcc_SimpleIpaPassType;
extern PyTypeObject gcc_IpaPassType;

/* autogenerated-pretty-printer.c */
int autogenerated_pretty_printer_init_types(void);
void autogenerated_pretty_printer_add_types(PyObject *m);


/* autogenerated-tree.c */
int autogenerated_tree_init_types(void);
void autogenerated_tree_add_types(PyObject *m);

PyTypeObject*
gcc_python_autogenerated_tree_type_for_tree(tree t, int borrow_ref);

PyTypeObject*
gcc_python_autogenerated_tree_type_for_tree_code(enum tree_code code, int borrow_ref);

/* autogenerated-variable.c */
int autogenerated_variable_init_types(void);
void autogenerated_variable_add_types(PyObject *m);


PyObject *
gcc_python_string_or_none(const char *str_or_null);

PyObject *
VEC_tree_as_PyList(VEC(tree,gc) *vec_nodes);

PyObject *
gcc_python_int_from_double_int(double_int di);


/* Python 2 vs Python 3 compat: */
#if PY_MAJOR_VERSION == 3
/* Python 3: use PyUnicode for "str" and PyLong for "int": */
#define gcc_python_string_from_format PyUnicode_FromFormat
#define gcc_python_string_from_string PyUnicode_FromString
#define gcc_python_string_from_string_and_size PyUnicode_FromStringAndSize
#define gcc_python_string_as_string _PyUnicode_AsString
#define gcc_python_int_from_long PyLong_FromLong
#else
/* Python 2: use PyString for "str" and PyInt for "int": */
#define gcc_python_string_from_format PyString_FromFormat
#define gcc_python_string_from_string PyString_FromString
#define gcc_python_string_from_string_and_size PyString_FromStringAndSize
#define gcc_python_string_as_string PyString_AsString
#define gcc_python_int_from_long PyInt_FromLong
#endif

/*
  PEP-7
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/

#endif /* INCLUDED__GCC_PYTHON_H */
