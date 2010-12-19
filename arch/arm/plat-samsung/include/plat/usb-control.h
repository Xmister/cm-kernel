/* arch/arm/plat-samsung/include/plat/usb-control.h
 *
 * Copyright (c) 2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - USB host port information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_USBCONTROL_H
#define __ASM_ARCH_USBCONTROL_H

#include <linux/types.h>

#define S3C_HCDFLG_USED	(1)

struct s3c2410_hcd_port {
	unsigned char	flags;
	unsigned char	power;
	unsigned char	oc_status;
	unsigned char	oc_changed;
};

struct s3c2410_hcd_info {
	struct usb_hcd		*hcd;
	struct s3c2410_hcd_port	port[2];

	void		(*power_control)(int port, int to);
	void		(*enable_oc)(struct s3c2410_hcd_info *, int on);
	void		(*report_oc)(struct s3c2410_hcd_info *, int ports);
};

static void inline s3c2410_usb_report_oc(struct s3c2410_hcd_info *info, int ports)
{
	if (info->report_oc != NULL) {
		(info->report_oc)(info, ports);
	}
}

extern void s3c_ohci_set_platdata(struct s3c2410_hcd_info *info);

#if defined(CONFIG_USB_GADGET_S3C2410) && defined(CONFIG_CONSOLE_POLL)
	
struct usb_ep;
	
int usb_loop_poll_hw(struct usb_ep *_ept, int is_rx);
	
#endif /* CONFIG_USB_GADGET_S3C2410 && CONFIG_CONSOLE_POLL */


#endif /*__ASM_ARCH_USBCONTROL_H */
