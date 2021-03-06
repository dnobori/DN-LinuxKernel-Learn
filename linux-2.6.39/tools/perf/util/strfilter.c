#include "linux/generated/autoconf.h"
#include "util.h"
#include "string.h"
#include "strfilter.h"

/* Operators */
static const char *OP_and	= "&";	/* Logical AND */
static const char *OP_or	= "|";	/* Logical OR */
static const char *OP_not	= "!";	/* Logical NOT */

#define is_operator(c)	((c) == '|' || (c) == '&' || (c) == '!')
#define is_separator(c)	(is_operator(c) || (c) == '(' || (c) == ')')

static void strfilter_node__delete(struct strfilter_node *self)
{
	if (self) {
		if (self->p && !is_operator(*self->p))
			free((char *)self->p);
		strfilter_node__delete(self->l);
		strfilter_node__delete(self->r);
		free(self);
	}
}

void strfilter__delete(struct strfilter *self)
{
	if (self) {
		strfilter_node__delete(self->root);
		free(self);
	}
}

static const char *get_token(const char *s, const char **e)
{
	const char *p;

	while (isspace(*s))	/* Skip spaces */
		s++;

	if (*s == '\0') {
		p = s;
		goto end;
	}

	p = s + 1;
	if (!is_separator(*s)) {
		/* End search */
retry:
		while (*p && !is_separator(*p) && !isspace(*p))
			p++;
		/* Escape and special case: '!' is also used in glob pattern */
		if (*(p - 1) == '\\' || (*p == '!' && *(p - 1) == '[')) {
			p++;
			goto retry;
		}
	}
end:
	*e = p;
	return s;
}

static struct strfilter_node *strfilter_node__alloc(const char *op,
						    struct strfilter_node *l,
						    struct strfilter_node *r)
{
	struct strfilter_node *ret = zalloc(sizeof(struct strfilter_node));

	if (ret) {
		ret->p = op;
		ret->l = l;
		ret->r = r;
	}

	return ret;
}

static struct strfilter_node *strfilter_node__new(const char *s,
						  const char **ep)
{
	struct strfilter_node root, *cur, *last_op;
	const char *e;

	if (!s)
		return NULL;

	memset(&root, 0, sizeof(root));
	last_op = cur = &root;

	s = get_token(s, &e);
	while (*s != '\0' && *s != ')') {
		switch (*s) {
		case '&':	/* Exchg last OP->r with AND */
			if (!cur->r || !last_op->r)
				goto error;
			cur = strfilter_node__alloc(OP_and, last_op->r, NULL);
			if (!cur)
				goto nomem;
			last_op->r = cur;
			last_op = cur;
			break;
		case '|':	/* Exchg the root with OR */
			if (!cur->r || !root.r)
				goto error;
			cur = strfilter_node__alloc(OP_or, root.r, NULL);
			if (!cur)
				goto nomem;
			root.r = cur;
			last_op = cur;
			break;
		case '!':	/* Add NOT as a leaf node */
			if (cur->r)
				goto error;
			cur->r = strfilter_node__alloc(OP_not, NULL, NULL);
			if (!cur->r)
				goto nomem;
			cur = cur->r;
			break;
		case '(':	/* Recursively parses inside the parenthesis */
			if (cur->r)
				goto error;
			cur->r = strfilter_node__new(s + 1, &s);
			if (!s)
				goto nomem;
			if (!cur->r || *s != ')')
				goto error;
			e = s + 1;
			break;
		default:
			if (cur->r)
				goto error;
			cur->r = strfilter_node__alloc(NULL, NULL, NULL);
			if (!cur->r)
				goto nomem;
			cur->r->p = strndup(s, e - s);
			if (!cur->r->p)
				goto nomem;
		}
		s = get_token(e, &e);
	}
	if (!cur->r)
		goto error;
	*ep = s;
	return root.r;
nomem:
	s = NULL;
error:
	*ep = s;
	strfilter_node__delete(root.r);
	return NULL;
}

/*
 * Parse filter rule and return new strfilter.
 * Return NULL if fail, and *ep == NULL if memory allocation failed.
 */
struct strfilter *strfilter__new(const char *rules, const char **err)
{
	struct strfilter *ret = zalloc(sizeof(struct strfilter));
	const char *ep = NULL;

	if (ret)
		ret->root = strfilter_node__new(rules, &ep);

	if (!ret || !ret->root || *ep != '\0') {
		if (err)
			*err = ep;
		strfilter__delete(ret);
		ret = NULL;
	}

	return ret;
}

static bool strfilter_node__compare(struct strfilter_node *self,
				    const char *str)
{
	if (!self || !self->p)
		return false;

	switch (*self->p) {
	case '|':	/* OR */
		return strfilter_node__compare(self->l, str) ||
			strfilter_node__compare(self->r, str);
	case '&':	/* AND */
		return strfilter_node__compare(self->l, str) &&
			strfilter_node__compare(self->r, str);
	case '!':	/* NOT */
		return !strfilter_node__compare(self->r, str);
	default:
		return strglobmatch(str, self->p);
	}
}

/* Return true if STR matches the filter rules */
bool strfilter__compare(struct strfilter *self, const char *str)
{
	if (!self)
		return false;
	return strfilter_node__compare(self->root, str);
}
