#include "linux/generated/autoconf.h"
/*
 *	PCI BIOS function numbering for conventional PCI BIOS 
 *	systems
 */

#define PCIBIOS_PCI_FUNCTION_ID 	0xb1XX
#define PCIBIOS_PCI_BIOS_PRESENT 	0xb101
#define PCIBIOS_FIND_PCI_DEVICE		0xb102
#define PCIBIOS_FIND_PCI_CLASS_CODE	0xb103
#define PCIBIOS_GENERATE_SPECIAL_CYCLE	0xb106
#define PCIBIOS_READ_CONFIG_BYTE	0xb108
#define PCIBIOS_READ_CONFIG_WORD	0xb109
#define PCIBIOS_READ_CONFIG_DWORD	0xb10a
#define PCIBIOS_WRITE_CONFIG_BYTE	0xb10b
#define PCIBIOS_WRITE_CONFIG_WORD	0xb10c
#define PCIBIOS_WRITE_CONFIG_DWORD	0xb10d
#define PCIBIOS_GET_ROUTING_OPTIONS	0xb10e
#define PCIBIOS_SET_PCI_HW_INT		0xb10f

