from collections import namedtuple

def camel_case(txt):
    return ''.join([word.title()
                    for word in txt.split('_')])

class TreeType(namedtuple('TreeType', 'SYM, STRING, TYPE, NARGS')):
    def camel_cased_string(self):
        return camel_case(self.STRING)

    # "type" seems to be an "enum_tree_code_class"; see GCC's tree.h

def iter_tree_types():
    import re
    f = open('autogenerated-tree-types.txt')
    for line in f:
        # e.g.
        #   ERROR_MARK, "error_mark", tcc_exceptional, 0
        m = re.match('(.+), (.+), (.+), (.+)', line)
        if m:
            yield TreeType(SYM=m.group(1),
                           STRING=m.group(2)[1:-1],
                           TYPE=m.group(3),
                           NARGS=int(m.group(4)))
        else:
            #    print 'UNMATCHED: ', line
            assert(line.startswith('#') or line.strip() == '')
    f.close()

class GimpleType(namedtuple('GimpleType', 'gimple_symbol printable_name gss_symbol')):
    def camel_cased_string(self):
        return camel_case(self.gimple_symbol)

def iter_gimple_types():
    import re
    f = open('autogenerated-gimple-types.txt')
    for line in f:
        # e.g.
        #   GIMPLE_ERROR_MARK, "gimple_error_mark", GSS_BASE
        m = re.match('(.+), (.+), (.+)', line)
        if m:
            yield GimpleType(gimple_symbol=m.group(1),
                             printable_name=m.group(2)[1:-1],
                             gss_symbol=m.group(3))
        else:
            #    print 'UNMATCHED: ', line
            assert(line.startswith('#') or line.strip() == '')
    f.close()
