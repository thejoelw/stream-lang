#include "astident.h"

AstIdent * const AstIdent::ImplicitIn = new AstIdent("/* << implicit in >> */");
AstIdent * const AstIdent::ImplicitOut = new AstIdent("/* << implicit out >> */");
