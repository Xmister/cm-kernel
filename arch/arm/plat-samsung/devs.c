//Xmister
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/platform_device.h>
#include <linux/input.h>//add by hui 09-08-31
#include <linux/gpio_keys.h>//add by hui 09-08-31

#include <asm/mach/arch.h>
#include <asm/mach/irq.h>
#include <mach/hardware.h>
#include <mach/map.h>
#include <mach/spica.h>

#include <plat/devs.h>
#include <plat/adc.h>
#include <plat/spi.h>
#include <linux/android_pmem.h>
#include <plat/reserved_mem.h>

/* Keypad interface */
static struct resource s3c_keypad_resource[] = {
        [0] = {
                .start = S3C_PA_KEYPAD,
                .end   = S3C_PA_KEYPAD+ S3C_SZ_KEYPAD - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_KEYPAD,
                .end   = IRQ_KEYPAD,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_keypad = {
        .name             = "s3c-keypad",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_keypad_resource),
        .resource         = s3c_keypad_resource,
};
EXPORT_SYMBOL(s3c_device_keypad);

/* Camif controller */

static struct resource s3c_camif_resource[] = {
        [0] = {
                .start = S3C64XX_PA_FIMC,
                .end   = S3C64XX_PA_FIMC + S3C64XX_SZ_FIMC - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_CAMIF_C,
                .end   = IRQ_CAMIF_C,
                .flags = IORESOURCE_IRQ,
        },
        [2] = {
                .start = IRQ_CAMIF_P,
                .end   = IRQ_CAMIF_P,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_camif = {
        .name           = "s3c-camif",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_camif_resource),
        .resource       = s3c_camif_resource,
};

EXPORT_SYMBOL(s3c_device_camif);

/* MFC controller */
static struct resource s3c_mfc_resource[] = {
        [0] = {
                .start  = S3C6400_PA_MFC,
                .end    = S3C6400_PA_MFC + S3C_SZ_MFC - 1,
                .flags  = IORESOURCE_MEM,
        },
        [1] = {
                .start  = IRQ_MFC,
                .end    = IRQ_MFC,
                .flags  = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_mfc = {
        .name           = "s3c-mfc",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_mfc_resource),
        .resource       = s3c_mfc_resource
};

EXPORT_SYMBOL(s3c_device_mfc);

/* FIMG-2D controller */
static struct resource s3c_g2d_resource[] = {
        [0] = {
                .start  = S3C64XX_PA_G2D,
                .end    = S3C64XX_PA_G2D + S3C64XX_SZ_G2D - 1,
                .flags  = IORESOURCE_MEM,
        },
        [1] = {
                .start  = IRQ_2D,
                .end    = IRQ_2D,
                .flags  = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_g2d = {
        .name           = "s3c-g2d",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_g2d_resource),
        .resource       = s3c_g2d_resource
};
EXPORT_SYMBOL(s3c_device_g2d);


/* FIMG-3D controller */
static struct resource s3c_g3d_resource[] = {
        [0] = {
                .start  = S3C64XX_PA_G3D,
                .end    = S3C64XX_PA_G3D + S3C64XX_SZ_G3D - 1,
                .flags  = IORESOURCE_MEM,
        },
        [1] = {
                .start  = IRQ_S3C6410_G3D,
                .end    = IRQ_S3C6410_G3D,
                .flags  = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_g3d = {
        .name           = "s3c-g3d",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_g3d_resource),
        .resource       = s3c_g3d_resource
};
EXPORT_SYMBOL(s3c_device_g3d);


/* VPP controller */
static struct resource s3c_vpp_resource[] = {
        [0] = {
            .start = S3C6400_PA_VPP,
            .end   = S3C6400_PA_VPP + S3C_SZ_VPP - 1,
            .flags = IORESOURCE_MEM,
        },
        [1] = {
               .start = IRQ_POST0,
               .end   = IRQ_POST0,
              .flags = IORESOURCE_IRQ,
         }
};

struct platform_device s3c_device_vpp = {
        .name             = "s3c-vpp",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_vpp_resource),
        .resource         = s3c_vpp_resource,
};
EXPORT_SYMBOL(s3c_device_vpp);

/* rotator interface */
static struct resource s3c_rotator_resource[] = {
        [0] = {
                .start = S3C6400_PA_ROTATOR,
                .end   = S3C6400_PA_ROTATOR + S3C_SZ_ROTATOR - 1,
                .flags = IORESOURCE_MEM,
                },
        [1] = {
                .start = IRQ_ROTATOR,
                .end   = IRQ_ROTATOR,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_rotator = {
        .name             = "s3c-rotator",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_rotator_resource),
        .resource         = s3c_rotator_resource
};

EXPORT_SYMBOL(s3c_device_rotator);

/* JPEG controller  */
static struct resource s3c_jpeg_resource[] = {
        [0] = {
                .start = S3C6400_PA_JPEG,
                .end   = S3C6400_PA_JPEG + S3C_SZ_JPEG - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_JPEG,
                .end   = IRQ_JPEG,
                .flags = IORESOURCE_IRQ,
        }

};

struct platform_device s3c_device_jpeg = {
        .name             = "s3c-jpeg",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_jpeg_resource),
        .resource         = s3c_jpeg_resource,
};
