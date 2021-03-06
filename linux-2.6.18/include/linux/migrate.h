#include "linux/autoconf.h"
#ifndef _LINUX_MIGRATE_H
#define _LINUX_MIGRATE_H

#include <linux/mm.h>

typedef struct page *new_page_t(struct page *, unsigned long private, int **);

#ifdef CONFIG_MIGRATION
extern int isolate_lru_page(struct page *p, struct list_head *pagelist);
extern int putback_lru_pages(struct list_head *l);
extern int migrate_page(struct address_space *,
			struct page *, struct page *);
extern int migrate_pages(struct list_head *l, new_page_t x, unsigned long);

extern int fail_migrate_page(struct address_space *,
			struct page *, struct page *);

extern int migrate_prep(void);
extern int migrate_vmas(struct mm_struct *mm,
		const nodemask_t *from, const nodemask_t *to,
		unsigned long flags);
#else

static inline int isolate_lru_page(struct page *p, struct list_head *list)
					{ return -ENOSYS; }
static inline int putback_lru_pages(struct list_head *l) { return 0; }
static inline int migrate_pages(struct list_head *l, new_page_t x,
		unsigned long private) { return -ENOSYS; }

static inline int migrate_pages_to(struct list_head *pagelist,
			struct vm_area_struct *vma, int dest) { return 0; }

static inline int migrate_prep(void) { return -ENOSYS; }

static inline int migrate_vmas(struct mm_struct *mm,
		const nodemask_t *from, const nodemask_t *to,
		unsigned long flags)
{
	return -ENOSYS;
}

/* Possible settings for the migrate_page() method in address_operations */
#define migrate_page NULL
#define fail_migrate_page NULL

#endif /* CONFIG_MIGRATION */
#endif /* _LINUX_MIGRATE_H */
