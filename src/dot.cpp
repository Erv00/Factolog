#include "dot.h"

using namespace factolog;

std::ostream& Dot::dotConnection(std::ostream& os, const void *from, const void *to, const char *label){
    return os << "\"" << from << "\" -> \"" << to << "\" [label=\"" << label << "\"];\n"; 
}

std::ostream& Dot::dotNode(std::ostream& os, const void *obj, const char *label, const char *style){
    os << "\"" << obj << "\" [label=\"" << label << "\"";
    if(style != NULL)
        os << "," << style;
    
    return os << "];\n";
}