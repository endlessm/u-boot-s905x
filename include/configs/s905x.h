/*
 * include/configs/s905x.h
 *
 * Copyright (C) 2016 Endless Computers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __S905X_H__
#define __S905X_H__

#ifndef __SUSPEND_FIRMWARE__
#include <asm/arch/cpu.h>
#endif

#define CONFIG_SYS_GENERIC_BOARD
#ifndef __SUSPEND_FIRMWARE__
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif
#endif

/* platform power init config */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE		1120
#define CONFIG_VDDEE_INIT_VOLTAGE		1000
#define CONFIG_VDDEE_SLEEP_VOLTAGE		850

/* configs for CEC */
#define CONFIG_CEC_OSD_NAME			"Mbox"
#define CONFIG_CEC_WAKEUP

#define CONFIG_INSTABOOT

/* SMP Definitinos */
#define CPU_RELEASE_ADDR			secondary_boot_func

/* Serial config */
#define CONFIG_CONS_INDEX			2
#define CONFIG_BAUDRATE				115200
#define CONFIG_AML_MESON_SERIAL
#define CONFIG_SERIAL_MULTI			1

/* IR */
#define CONFIG_IR_REMOTE_POWER_UP_KEY_CNT	4
#define CONFIG_IR_REMOTE_USE_PROTOCOL		0
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1	0XE51AFB04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2	0XBB44FB04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3	0xF20DFE01
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4	0xBA45BD02

#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5	0x3ac5bd02

/* Environment */
#define CONFIG_SYS_MAXARGS			64
#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0x20000000\0"\
	"testfile=/boot/uEnv.txt\0"\
	"loadaddr=0x1080000\0"\
	"initrd_loadaddr=0x13000000\0"\
	"script_loadaddr=0x11000000\0"\
	"init_cvbs="\
		"cvbs init; cvbs output 576cvbs"\
		"\0"\
	"get_rootuuid="\
		"fsuuid mmc ${bootdev}:1 rootuuid"\
		"\0"\
	"load_boot_env="\
		"echo >>> Loading Boot Script <<<; "\
		"ext4load mmc ${bootdev}:1 ${script_loadaddr} /boot/uEnv.txt"\
		"\0"\
	"import_boot_env="\
		"echo >>> Importing environment <<<; "\
		"env import -t ${script_loadaddr} ${filesize}"\
		"\0"\
	"uenv_bootcmd="\
		"echo >>> Booting <<<; "\
		"ext4load mmc ${bootdev}:1 ${loadaddr} /boot/${kernel_image}; "\
		"ext4load mmc ${bootdev}:1 ${initrd_loadaddr} /boot/${ramdisk_image}; "\
		"bootm ${loadaddr} ${initrd_loadaddr}:${filesize}"\
		"\0"\
	"endless_select_bootdev="\
		"if test -e mmc 0:1 ${testfile}; then "\
			"setenv bootdev 0; "\
		"else if test -e mmc 1:1 ${testfile}; then "\
			"setenv bootdev 1; "\
		"fi;fi; "\
		"if test ${debug_board} = 1; then "\
			"setenv debug_board_bootarg console=ttyS0,115200; "\
		"fi; "\
		"run endless_boot"\
		"\0"\
	"endless_boot="\
		"run load_boot_env; "\
		"run import_boot_env; "\
		"run get_rootuuid; "\
		"setenv bootargs root=UUID=${rootuuid} ${debug_board_bootarg} ${bootargs} ${custom_bootargs}; "\
		"run uenv_bootcmd"\
		"\0"\

#define CONFIG_PREBOOT				"store init; run init_cvbs"
#define CONFIG_BOOTCOMMAND			"run endless_select_bootdev"

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE				(64 * 1024)
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CMD_SAVEENV

/* Image setup */
#define CONFIG_FIT
#define CONFIG_OF_LIBFDT
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_ANDROID_IMG
#define CONFIG_SYS_BOOTM_LEN			(64 << 20)

/* CPU */
#define CONFIG_CPU_CLK				1200	/* MHz. Range: 600-1800, should be multiple of 24 */

/* DDR */
#define CONFIG_DDR_SIZE				0	/* MB // 0 means ddr size auto-detect */
#define CONFIG_DDR_CLK				912	/* MHz, Range: 384-1200, should be multiple of 24 */
#define CONFIG_DDR4_CLK				1100	/* MHz, for boards which use different ddr chip */

/* DDR type setting
 *    CONFIG_DDR_TYPE_LPDDR3   : LPDDR3
 *    CONFIG_DDR_TYPE_DDR3     : DDR3
 *    CONFIG_DDR_TYPE_DDR4     : DDR4
 *    CONFIG_DDR_TYPE_AUTO     : DDR3/DDR4 auto detect */
#define CONFIG_DDR_TYPE				CONFIG_DDR_TYPE_DDR3

/* DDR channel setting, please refer hardware design.
 *    CONFIG_DDR0_RANK0        : DDR0 rank0
 *    CONFIG_DDR0_RANK01       : DDR0 rank0+1
 *    CONFIG_DDR0_16BIT        : DDR0 16bit mode
 *    CONFIG_DDR_CHL_AUTO      : auto detect RANK0 / RANK0+1 */
#define CONFIG_DDR_CHANNEL_SET			CONFIG_DDR_CHL_AUTO

#define CONFIG_DDR_FULL_TEST			0	/* 1 for ddr full test */
#define CONFIG_NR_DRAM_BANKS			1

/* DDR functions */
#define CONFIG_CMD_DDR_D2PLL			0	/* 0:disable, 1:enable. d2pll cmd */
#define CONFIG_CMD_DDR_TEST			0	/* 0:disable, 1:enable. ddrtest cmd */
#define CONFIG_DDR_LOW_POWER			0	/* 0:disable, 1:enable. ddr clk gate for lp */
#define CONFIG_DDR_ZQ_PD			0	/* 0:disable, 1:enable. ddr zq power down */
#define CONFIG_DDR_USE_EXT_VREF			0	/* 0:disable, 1:enable. ddr use external vref */

/* storage: eMMC/NAND/SD */
#define	CONFIG_STORE_COMPATIBLE

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

#define CONFIG_AML_SD_EMMC			1
#ifdef CONFIG_AML_SD_EMMC
#define CONFIG_GENERIC_MMC
#define CONFIG_CMD_MMC
#define CONFIG_SYS_MMC_ENV_DEV			1
#define CONFIG_EMMC_DDR52_EN			1
#define CONFIG_EMMC_DDR52_CLK			35000000
#endif

#define CONFIG_SYS_NO_FLASH

/* VPU */
#define CONFIG_AML_VPU
#ifdef CONFIG_AML_VPU
#define CONFIG_VPU_PRESET
#endif

/* Display & HDMITX */
#define CONFIG_AML_HDMITX20
#define CONFIG_AML_CANVAS
#define CONFIG_AML_VOUT
#define CONFIG_AML_OSD
#define CONFIG_OSD_SCALE_ENABLE
#define CONFIG_CMD_BMP

#if defined(CONFIG_AML_VOUT)
#define CONFIG_AML_CVBS
#endif

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
#define CONFIG_CMD_USB
#if defined(CONFIG_CMD_USB)
#define CONFIG_GXL_XHCI_BASE			0xc9000000
#define CONFIG_GXL_USB_PHY2_BASE		0xd0078000
#define CONFIG_GXL_USB_PHY3_BASE		0xd0078080
#define CONFIG_USB_STORAGE
#define CONFIG_USB_XHCI
#define CONFIG_USB_XHCI_AMLOGIC_GXL
#endif

/* U-Boot Factory USB/SD burning config */
#define CONFIG_AML_V2_FACTORY_BURN
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN
#define CONFIG_SD_BURNING_SUPPORT_UI		1

#define CONFIG_AML_SECURITY_KEY
#define CONFIG_UNIFY_KEY_MANAGE

/* NET */
#define CONFIG_CMD_NET
#if defined(CONFIG_CMD_NET)
#define CONFIG_DESIGNWARE_ETH
#define CONFIG_PHYLIB
#define CONFIG_NET_MULTI
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_RARP
#define CONFIG_HOSTNAME				arm_gxbb
#define CONFIG_ETHADDR				00:15:18:01:81:31	/* Ethernet address */
#define CONFIG_IPADDR				10.18.9.97		/* Our ip address */
#define CONFIG_GATEWAYIP			10.18.9.1		/* Our getway ip address */
#define CONFIG_SERVERIP				10.18.9.113		/* Tftp server ip address */
#define CONFIG_NETMASK				255.255.255.0
#endif

/* other devices */
#define CONFIG_EFUSE
#define CONFIG_SYS_I2C_AML
#define CONFIG_SYS_I2C_SPEED			400000

/* commands */
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_BOOTI
#define CONFIG_CMD_EFUSE
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_GPIO
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_JTAG
#define CONFIG_CMD_AUTOSCRIPT
#define CONFIG_CMD_MISC
#define CONFIG_CMD_FS_UUID

/* file systems */
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_MMC
#define CONFIG_FS_FAT
#define CONFIG_FS_EXT4
#define CONFIG_LZO

/* other functions */
#define CONFIG_NEED_BL301
#define CONFIG_NEED_BL32
#define CONFIG_FIP_IMG_SUPPORT
#define CONFIG_BOOTDELAY			1
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMD_MISC
#define CONFIG_CMD_ITEST
#define CONFIG_CMD_CPU_TEMP
#define CONFIG_SYS_MEM_TOP_HIDE			0x08000000	/* hide 128MB for kernel reserve */
#define CONFIG_MULTI_DTB
#define CONFIG_SUPPORT_RAW_INITRD

/* debug mode defines */
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG			636
#define CONFIG_CPU_CLK_DEBUG			600
#endif

/* support secure boot */
#define CONFIG_AML_SECURE_UBOOT
#if defined(CONFIG_AML_SECURE_UBOOT)
#define CONFIG_AML_CRYPTO_UBOOT
#endif

#define CONFIG_SECURE_STORAGE
#define CONFIG_SUPPORT_RAW_INITRD

#if defined(CONFIG_CUSTOMER_ID)
#undef CONFIG_AML_CUSTOMER_ID
#define CONFIG_AML_CUSTOMER_ID			CONFIG_CUSTOMER_ID
#endif

#define ETHERNET_INTERNAL_PHY

#endif
