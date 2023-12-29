#include "util.h"
#include "Kind.h"

Kind::Kind () : kind(SPHERE)
{
	return;
}

Kind::Kind (kind_t const kind) : kind(kind)
{
	return;
}

void *Kind::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Kind::operator delete (void *p)
{
	p = Util_Free(p);
}