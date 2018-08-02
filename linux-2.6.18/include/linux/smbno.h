#include "linux/autoconf.h"
#ifndef _SMBNO_H_
#define _SMBNO_H_

/* these define the attribute byte as seen by DOS */
#define aRONLY	(1L<<0)
#define aHIDDEN	(1L<<1)
#define aSYSTEM	(1L<<2)
#define aVOLID	(1L<<3)
#define aDIR	(1L<<4)
#define aARCH	(1L<<5)

/* error classes */
#define SUCCESS 0  /* The request was successful. */
#define ERRDOS 0x01 /*  Error is from the core DOS operating system set. */
#define ERRSRV 0x02 /* Error is generated by the server network file manager.*/
#define ERRHRD 0x03  /* Error is an hardware error. */
#define ERRCMD 0xFF  /* Command was not in the "SMB" format. */

/* SMB X/Open error codes for the ERRdos error class */

#define ERRbadfunc 1            /* Invalid function (or system call) */
#define ERRbadfile 2            /* File not found (pathname error) */
#define ERRbadpath 3            /* Directory not found */
#define ERRnofids 4             /* Too many open files */
#define ERRnoaccess 5           /* Access denied */
#define ERRbadfid 6             /* Invalid fid */
#define ERRbadmcb 7             /* Memory control blocks destroyed */
#define ERRnomem 8              /* Out of memory */
#define ERRbadmem 9             /* Invalid memory block address */
#define ERRbadenv 10            /* Invalid environment */
#define ERRbadformat 11         /* Invalid format */
#define ERRbadaccess 12         /* Invalid open mode */
#define ERRbaddata 13           /* Invalid data (only from ioctl call) */
#define ERRres 14               /* reserved */
#define ERRbaddrive 15          /* Invalid drive */
#define ERRremcd 16             /* Attempt to delete current directory */
#define ERRdiffdevice 17        /* rename/move across different filesystems */
#define ERRnofiles 18           /* no more files found in file search */
#define ERRbadshare 32          /* Share mode on file conflict with open mode */
#define ERRlock 33              /* Lock request conflicts with existing lock */
#define ERRfilexists 80         /* File in operation already exists */
#define ERRbadpipe 230          /* Named pipe invalid */
#define ERRpipebusy 231         /* All instances of pipe are busy */
#define ERRpipeclosing 232      /* named pipe close in progress */
#define ERRnotconnected 233     /* No process on other end of named pipe */
#define ERRmoredata 234         /* More data to be returned */

#define ERROR_INVALID_PARAMETER	 87
#define ERROR_DISK_FULL		112
#define ERROR_INVALID_NAME	123
#define ERROR_DIR_NOT_EMPTY	145
#define ERROR_NOT_LOCKED	158
#define ERROR_ALREADY_EXISTS	183  /* see also 80 ? */
#define ERROR_EAS_DIDNT_FIT	275 /* Extended attributes didn't fit */
#define ERROR_EAS_NOT_SUPPORTED	282 /* Extended attributes not supported */

/* Error codes for the ERRSRV class */

#define ERRerror 1              /* Non specific error code */
#define ERRbadpw 2              /* Bad password */
#define ERRbadtype 3            /* reserved */
#define ERRaccess 4          /* No permissions to do the requested operation */
#define ERRinvnid 5             /* tid invalid */
#define ERRinvnetname 6         /* Invalid servername */
#define ERRinvdevice 7          /* Invalid device */
#define ERRqfull 49             /* Print queue full */
#define ERRqtoobig 50           /* Queued item too big */
#define ERRinvpfid 52           /* Invalid print file in smb_fid */
#define ERRsmbcmd 64            /* Unrecognised command */
#define ERRsrverror 65          /* smb server internal error */
#define ERRfilespecs 67         /* fid and pathname invalid combination */
#define ERRbadlink 68           /* reserved */
#define ERRbadpermits 69        /* Access specified for a file is not valid */
#define ERRbadpid 70            /* reserved */
#define ERRsetattrmode 71       /* attribute mode invalid */
#define ERRpaused 81            /* Message server paused */
#define ERRmsgoff 82            /* Not receiving messages */
#define ERRnoroom 83            /* No room for message */
#define ERRrmuns 87             /* too many remote usernames */
#define ERRtimeout 88           /* operation timed out */
#define ERRnoresource  89   /* No resources currently available for request. */
#define ERRtoomanyuids 90       /* too many userids */
#define ERRbaduid 91            /* bad userid */
#define ERRuseMPX 250    /* temporarily unable to use raw mode, use MPX mode */
#define ERRuseSTD 251    /* temporarily unable to use raw mode, use std.mode */
#define ERRcontMPX 252          /* resume MPX mode */
#define ERRbadPW                /* reserved */
#define ERRnosupport 0xFFFF

/* Error codes for the ERRHRD class */

#define ERRnowrite 19           /* read only media */
#define ERRbadunit 20           /* Unknown device */
#define ERRnotready 21          /* Drive not ready */
#define ERRbadcmd 22            /* Unknown command */
#define ERRdata 23              /* Data (CRC) error */
#define ERRbadreq 24            /* Bad request structure length */
#define ERRseek 25
#define ERRbadmedia 26
#define ERRbadsector 27
#define ERRnopaper 28
#define ERRwrite 29             /* write fault */
#define ERRread 30              /* read fault */
#define ERRgeneral 31           /* General hardware failure */
#define ERRwrongdisk 34
#define ERRFCBunavail 35
#define ERRsharebufexc 36       /* share buffer exceeded */
#define ERRdiskfull 39

/*
 * Access modes when opening a file
 */
#define SMB_ACCMASK	0x0003
#define SMB_O_RDONLY	0x0000
#define SMB_O_WRONLY	0x0001
#define SMB_O_RDWR	0x0002

/* offsets into message for common items */
#define smb_com 8
#define smb_rcls 9
#define smb_reh 10
#define smb_err 11
#define smb_flg 13
#define smb_flg2 14
#define smb_reb 13
#define smb_tid 28
#define smb_pid 30
#define smb_uid 32
#define smb_mid 34
#define smb_wct 36
#define smb_vwv 37
#define smb_vwv0 37
#define smb_vwv1 39
#define smb_vwv2 41
#define smb_vwv3 43
#define smb_vwv4 45
#define smb_vwv5 47
#define smb_vwv6 49
#define smb_vwv7 51
#define smb_vwv8 53
#define smb_vwv9 55
#define smb_vwv10 57
#define smb_vwv11 59
#define smb_vwv12 61
#define smb_vwv13 63
#define smb_vwv14 65

/* these are the trans2 sub fields for primary requests */
#define smb_tpscnt smb_vwv0
#define smb_tdscnt smb_vwv1
#define smb_mprcnt smb_vwv2
#define smb_mdrcnt smb_vwv3
#define smb_msrcnt smb_vwv4
#define smb_flags smb_vwv5
#define smb_timeout smb_vwv6
#define smb_pscnt smb_vwv9
#define smb_psoff smb_vwv10
#define smb_dscnt smb_vwv11
#define smb_dsoff smb_vwv12
#define smb_suwcnt smb_vwv13
#define smb_setup smb_vwv14
#define smb_setup0 smb_setup
#define smb_setup1 (smb_setup+2)
#define smb_setup2 (smb_setup+4)

/* these are for the secondary requests */
#define smb_spscnt smb_vwv2
#define smb_spsoff smb_vwv3
#define smb_spsdisp smb_vwv4
#define smb_sdscnt smb_vwv5
#define smb_sdsoff smb_vwv6
#define smb_sdsdisp smb_vwv7
#define smb_sfid smb_vwv8

/* and these for responses */
#define smb_tprcnt smb_vwv0
#define smb_tdrcnt smb_vwv1
#define smb_prcnt smb_vwv3
#define smb_proff smb_vwv4
#define smb_prdisp smb_vwv5
#define smb_drcnt smb_vwv6
#define smb_droff smb_vwv7
#define smb_drdisp smb_vwv8

/* the complete */
#define SMBmkdir      0x00   /* create directory */
#define SMBrmdir      0x01   /* delete directory */
#define SMBopen       0x02   /* open file */
#define SMBcreate     0x03   /* create file */
#define SMBclose      0x04   /* close file */
#define SMBflush      0x05   /* flush file */
#define SMBunlink     0x06   /* delete file */
#define SMBmv         0x07   /* rename file */
#define SMBgetatr     0x08   /* get file attributes */
#define SMBsetatr     0x09   /* set file attributes */
#define SMBread       0x0A   /* read from file */
#define SMBwrite      0x0B   /* write to file */
#define SMBlock       0x0C   /* lock byte range */
#define SMBunlock     0x0D   /* unlock byte range */
#define SMBctemp      0x0E   /* create temporary file */
#define SMBmknew      0x0F   /* make new file */
#define SMBchkpth     0x10   /* check directory path */
#define SMBexit       0x11   /* process exit */
#define SMBlseek      0x12   /* seek */
#define SMBtcon       0x70   /* tree connect */
#define SMBtconX      0x75   /* tree connect and X*/
#define SMBtdis       0x71   /* tree disconnect */
#define SMBnegprot    0x72   /* negotiate protocol */
#define SMBdskattr    0x80   /* get disk attributes */
#define SMBsearch     0x81   /* search directory */
#define SMBsplopen    0xC0   /* open print spool file */
#define SMBsplwr      0xC1   /* write to print spool file */
#define SMBsplclose   0xC2   /* close print spool file */
#define SMBsplretq    0xC3   /* return print queue */
#define SMBsends      0xD0   /* send single block message */
#define SMBsendb      0xD1   /* send broadcast message */
#define SMBfwdname    0xD2   /* forward user name */
#define SMBcancelf    0xD3   /* cancel forward */
#define SMBgetmac     0xD4   /* get machine name */
#define SMBsendstrt   0xD5   /* send start of multi-block message */
#define SMBsendend    0xD6   /* send end of multi-block message */
#define SMBsendtxt    0xD7   /* send text of multi-block message */

/* Core+ protocol */
#define SMBlockread	  0x13   /* Lock a range and read */
#define SMBwriteunlock 0x14 /* Unlock a range then write */
#define SMBreadbraw   0x1a  /* read a block of data with no smb header */
#define SMBwritebraw  0x1d  /* write a block of data with no smb header */
#define SMBwritec     0x20  /* secondary write request */
#define SMBwriteclose 0x2c  /* write a file then close it */

/* dos extended protocol */
#define SMBreadBraw      0x1A   /* read block raw */
#define SMBreadBmpx      0x1B   /* read block multiplexed */
#define SMBreadBs        0x1C   /* read block (secondary response) */
#define SMBwriteBraw     0x1D   /* write block raw */
#define SMBwriteBmpx     0x1E   /* write block multiplexed */
#define SMBwriteBs       0x1F   /* write block (secondary request) */
#define SMBwriteC        0x20   /* write complete response */
#define SMBsetattrE      0x22   /* set file attributes expanded */
#define SMBgetattrE      0x23   /* get file attributes expanded */
#define SMBlockingX      0x24   /* lock/unlock byte ranges and X */
#define SMBtrans         0x25   /* transaction - name, bytes in/out */
#define SMBtranss        0x26   /* transaction (secondary request/response) */
#define SMBioctl         0x27   /* IOCTL */
#define SMBioctls        0x28   /* IOCTL  (secondary request/response) */
#define SMBcopy          0x29   /* copy */
#define SMBmove          0x2A   /* move */
#define SMBecho          0x2B   /* echo */
#define SMBopenX         0x2D   /* open and X */
#define SMBreadX         0x2E   /* read and X */
#define SMBwriteX        0x2F   /* write and X */
#define SMBsesssetupX    0x73   /* Session Set Up & X (including User Logon) */
#define SMBtconX         0x75   /* tree connect and X */
#define SMBffirst        0x82   /* find first */
#define SMBfunique       0x83   /* find unique */
#define SMBfclose        0x84   /* find close */
#define SMBinvalid       0xFE   /* invalid command */


/* Extended 2.0 protocol */
#define SMBtrans2        0x32   /* TRANS2 protocol set */
#define SMBtranss2       0x33   /* TRANS2 protocol set, secondary command */
#define SMBfindclose     0x34   /* Terminate a TRANSACT2_FINDFIRST */
#define SMBfindnclose    0x35   /* Terminate a TRANSACT2_FINDNOTIFYFIRST */
#define SMBulogoffX      0x74   /* user logoff */

/* these are the TRANS2 sub commands */
#define TRANSACT2_OPEN          0
#define TRANSACT2_FINDFIRST     1
#define TRANSACT2_FINDNEXT      2
#define TRANSACT2_QFSINFO       3
#define TRANSACT2_SETFSINFO     4
#define TRANSACT2_QPATHINFO     5
#define TRANSACT2_SETPATHINFO   6
#define TRANSACT2_QFILEINFO     7
#define TRANSACT2_SETFILEINFO   8
#define TRANSACT2_FSCTL         9
#define TRANSACT2_IOCTL           10
#define TRANSACT2_FINDNOTIFYFIRST 11
#define TRANSACT2_FINDNOTIFYNEXT  12
#define TRANSACT2_MKDIR           13

/* Information Levels -  Shared? */
#define SMB_INFO_STANDARD		1
#define SMB_INFO_QUERY_EA_SIZE		2
#define SMB_INFO_QUERY_EAS_FROM_LIST	3
#define SMB_INFO_QUERY_ALL_EAS		4
#define SMB_INFO_IS_NAME_VALID		6

/* Information Levels -  TRANSACT2_FINDFIRST */
#define SMB_FIND_FILE_DIRECTORY_INFO		0x101
#define SMB_FIND_FILE_FULL_DIRECTORY_INFO	0x102
#define SMB_FIND_FILE_NAMES_INFO		0x103
#define SMB_FIND_FILE_BOTH_DIRECTORY_INFO	0x104

/* Information Levels -  TRANSACT2_QPATHINFO */
#define SMB_QUERY_FILE_BASIC_INFO	0x101
#define SMB_QUERY_FILE_STANDARD_INFO	0x102
#define SMB_QUERY_FILE_EA_INFO		0x103
#define SMB_QUERY_FILE_NAME_INFO	0x104
#define SMB_QUERY_FILE_ALL_INFO		0x107
#define SMB_QUERY_FILE_ALT_NAME_INFO	0x108
#define SMB_QUERY_FILE_STREAM_INFO	0x109
#define SMB_QUERY_FILE_COMPRESSION_INFO	0x10b

/* Information Levels - TRANSACT2_SETFILEINFO */
#define SMB_SET_FILE_BASIC_INFO		0x101
#define SMB_SET_FILE_DISPOSITION_INFO	0x102
#define SMB_SET_FILE_ALLOCATION_INFO	0x103
#define SMB_SET_FILE_END_OF_FILE_INFO	0x104

/* smb_flg field flags */
#define SMB_FLAGS_SUPPORT_LOCKREAD	0x01
#define SMB_FLAGS_CLIENT_BUF_AVAIL	0x02
#define SMB_FLAGS_RESERVED		0x04
#define SMB_FLAGS_CASELESS_PATHNAMES	0x08
#define SMB_FLAGS_CANONICAL_PATHNAMES	0x10
#define SMB_FLAGS_REQUEST_OPLOCK	0x20
#define SMB_FLAGS_REQUEST_BATCH_OPLOCK	0x40
#define SMB_FLAGS_REPLY			0x80

/* smb_flg2 field flags (samba-2.2.0/source/include/smb.h) */
#define SMB_FLAGS2_LONG_PATH_COMPONENTS		0x0001
#define SMB_FLAGS2_EXTENDED_ATTRIBUTES		0x0002
#define SMB_FLAGS2_DFS_PATHNAMES		0x1000
#define SMB_FLAGS2_READ_PERMIT_NO_EXECUTE	0x2000
#define SMB_FLAGS2_32_BIT_ERROR_CODES		0x4000 
#define SMB_FLAGS2_UNICODE_STRINGS		0x8000


/*
 * UNIX stuff  (from samba trans2.h)
 */
#define MIN_UNIX_INFO_LEVEL		0x200
#define MAX_UNIX_INFO_LEVEL		0x2FF
#define SMB_FIND_FILE_UNIX		0x202
#define SMB_QUERY_FILE_UNIX_BASIC	0x200
#define SMB_QUERY_FILE_UNIX_LINK	0x201
#define SMB_QUERY_FILE_UNIX_HLINK	0x202
#define SMB_SET_FILE_UNIX_BASIC		0x200
#define SMB_SET_FILE_UNIX_LINK		0x201
#define SMB_SET_FILE_UNIX_HLINK		0x203
#define SMB_QUERY_CIFS_UNIX_INFO	0x200

/* values which means "don't change it" */
#define SMB_MODE_NO_CHANGE		0xFFFFFFFF
#define SMB_UID_NO_CHANGE		0xFFFFFFFF
#define SMB_GID_NO_CHANGE		0xFFFFFFFF
#define SMB_TIME_NO_CHANGE		0xFFFFFFFFFFFFFFFFULL
#define SMB_SIZE_NO_CHANGE		0xFFFFFFFFFFFFFFFFULL

/* UNIX filetype mappings. */
#define UNIX_TYPE_FILE		0
#define UNIX_TYPE_DIR		1
#define UNIX_TYPE_SYMLINK	2
#define UNIX_TYPE_CHARDEV	3
#define UNIX_TYPE_BLKDEV	4
#define UNIX_TYPE_FIFO		5
#define UNIX_TYPE_SOCKET	6
#define UNIX_TYPE_UNKNOWN	0xFFFFFFFF

#endif /* _SMBNO_H_ */
