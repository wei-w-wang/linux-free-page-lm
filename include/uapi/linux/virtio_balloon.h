#ifndef _LINUX_VIRTIO_BALLOON_H
#define _LINUX_VIRTIO_BALLOON_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */
#include <linux/types.h>
#include <linux/virtio_types.h>
#include <linux/virtio_ids.h>
#include <linux/virtio_config.h>

/* The feature bitmap for virtio balloon */
#define VIRTIO_BALLOON_F_MUST_TELL_HOST	0 /* Tell before reclaiming pages */
#define VIRTIO_BALLOON_F_STATS_VQ	1 /* Memory Stats virtqueue */
#define VIRTIO_BALLOON_F_DEFLATE_ON_OOM	2 /* Deflate balloon on OOM */
#define VIRTIO_BALLOON_F_FREE_PAGE_HINT	3 /* VQ to report free pages */

/* Size of a PFN in the balloon interface. */
#define VIRTIO_BALLOON_PFN_SHIFT 12

#define VIRTIO_BALLOON_FREE_PAGE_REPORT_STOP_ID		0
struct virtio_balloon_config {
	/* Number of pages host wants Guest to give up. */
	__u32 num_pages;
	/* Number of pages we've actually got in balloon. */
	__u32 actual;
	/* Free page report command id, readonly by guest */
	__u32 free_page_report_cmd_id;
};

#define VIRTIO_BALLOON_S_SWAP_IN  0   /* Amount of memory swapped in */
#define VIRTIO_BALLOON_S_SWAP_OUT 1   /* Amount of memory swapped out */
#define VIRTIO_BALLOON_S_MAJFLT   2   /* Number of major faults */
#define VIRTIO_BALLOON_S_MINFLT   3   /* Number of minor faults */
#define VIRTIO_BALLOON_S_MEMFREE  4   /* Total amount of free memory */
#define VIRTIO_BALLOON_S_MEMTOT   5   /* Total amount of memory */
#define VIRTIO_BALLOON_S_AVAIL    6   /* Available memory as in /proc */
#define VIRTIO_BALLOON_S_NR       7

/*
 * Memory statistics structure.
 * Driver fills an array of these structures and passes to device.
 *
 * NOTE: fields are laid out in a way that would make compiler add padding
 * between and after fields, so we have to use compiler-specific attributes to
 * pack it, to disable this padding. This also often causes compiler to
 * generate suboptimal code.
 *
 * We maintain this statistics structure format for backwards compatibility,
 * but don't follow this example.
 *
 * If implementing a similar structure, do something like the below instead:
 *     struct virtio_balloon_stat {
 *         __virtio16 tag;
 *         __u8 reserved[6];
 *         __virtio64 val;
 *     };
 *
 * In other words, add explicit reserved fields to align field and
 * structure boundaries at field size, avoiding compiler padding
 * without the packed attribute.
 */
struct virtio_balloon_stat {
	__virtio16 tag;
	__virtio64 val;
} __attribute__((packed));

#endif /* _LINUX_VIRTIO_BALLOON_H */
