// SPDX-License-Identifier: GPL-2.0
/*
 * NUMA support for s390
 *
 * Implement NUMA core code.
 *
 * Copyright IBM Corp. 2015
 */

#include <linux/kernel.h>
#include <linux/mmzone.h>
#include <linux/cpumask.h>
#include <linux/memblock.h>
#include <linux/node.h>
#include <asm/numa.h>

void __init numa_setup(void)
{
	int nid;

	nodes_clear(node_possible_map);
	node_set(0, node_possible_map);
	node_set_online(0);
	for (nid = 0; nid < MAX_NUMNODES; nid++)
		NODE_DATA(nid) = memblock_alloc_or_panic(sizeof(pg_data_t), 8);
	NODE_DATA(0)->node_spanned_pages = memblock_end_of_DRAM() >> PAGE_SHIFT;
	NODE_DATA(0)->node_id = 0;
}
