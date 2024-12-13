#include "argumentpass.h"

ArgumentPass ArgumentPass::instance;
ArgumentPass & ArgumentPass::Instance()
{
	return instance;
}
