#ifndef ASMARM_DMA_IOMMU_H
#define ASMARM_DMA_IOMMU_H

#ifdef __KERNEL__

#include <linux/mm_types.h>
#include <linux/scatterlist.h>
#include <linux/dma-debug.h>
#include <linux/kmemcheck.h>

struct dma_iommu_mapping {
	/* iommu specific data */
	struct iommu_domain	*domain;

	unsigned long		**bitmaps;	/* array of bitmaps */
	unsigned int		nr_bitmaps;	/* nr of elements in array */
	unsigned int		extensions;
	size_t			bitmap_size;	/* size of a single bitmap */
	size_t			bits;		/* per bitmap */
	unsigned int		size;		/* per bitmap */
	unsigned int		order;
	dma_addr_t		base;

	spinlock_t		lock;
	struct kref		kref;
};

struct dma_iommu_mapping *
arm_iommu_create_mapping(struct bus_type *bus, dma_addr_t base, size_t size,
			 int order);

void arm_iommu_release_mapping(struct dma_iommu_mapping *mapping);

int arm_iommu_attach_device(struct device *dev,
					struct dma_iommu_mapping *mapping);

#endif /* __KERNEL__ */
#endif
