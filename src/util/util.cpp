#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#define HEAD ((size_t) 0xffffffffffffffff)
#define HASH ((size_t) 0xdb0f1d1d0dec2023)

typedef struct m_chain_s {
	struct m_chain_s *prev;
	struct m_chain_s *next;
	void *data;
	size_t hash;
	size_t size;
} m_chain_t;

static m_chain_t m_chain;
static size_t m_size = 0;
static size_t m_count = 0;

static m_chain_t *Util_Chain (m_chain_t *node)
{
	m_chain_t *next = (m_chain.next)? m_chain.next : NULL;
	if (next) {
		next->prev = node;
	}

	node->next = next;
	node->prev = &m_chain;
	m_chain.next = node;
	return node;
}

static m_chain_t *Util_Remove (m_chain_t *node)
{
	m_chain_t *prev = node->prev;
	m_chain_t *next = node->next;
	if (next) {
		next->prev = prev;
	}

	prev->next = next;
	node->next = NULL;
	node->prev = NULL;
	node->data = NULL;
	free(node);
	node = NULL;
	return node;
}

void *Util_Free (void *p)
{
	if (!p) {
		return NULL;
	}

	m_chain_t *node = ((m_chain_t*) p) - 1;
	if (node->hash != HASH) {
		fprintf(stderr, "Util_Free: unregistered object error\n");
		return p;
	}

	size_t const size = node->size;
	node = Util_Remove(node);

	m_size -= size;
	--m_count;

	return NULL;
}

void Util_Clear (void)
{
	m_chain_t *next = NULL;
	for (m_chain_t *node = m_chain.next; node; node = next) {
		next = node->next;
		void *data = node->data;
		node = (m_chain_t*) Util_Free(data);
	}
}

void *Util_Malloc (size_t const sz)
{
	size_t const size = sizeof(m_chain_t) + sz;
	void *p = malloc(size);
	if (!p) {
		fprintf(stderr, "Util_Malloc: %s\n", strerror(errno));
		return NULL;
	}

	m_chain_t* node = (m_chain_t*) p;
	void *data = (node + 1);

	node = Util_Chain(node);
	node->data = data;
	node->hash = HASH;
	node->size = size;

	m_size += size;
	++m_count;

	return data;
}
