/*****************************************************************************

 @(#) src/include/sys/openss7/sc.h

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation; version 3 of the License.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

#ifndef __SYS_OPENSS7_SC_H__
#define __SYS_OPENSS7_SC_H__

#ifndef __SYS_SC_H__
#warning "Do not include sys/openss7/sc.h directly, include sys/sc.h instead."
#endif

/* This file can be processed with doxygen(1). */

/**
  * @ingroup sc STREAMS Configuration Module sc(4)
  * @{
  * @file
  * STREAMS Configuration Module sc(4) Header File.
  * @{
  */

#define SC_IOC_MAGIC 'C' /**< Magic number for the sc(4) STREAMS module. */

/**
  * @name STREAMS Configuration Module Input-Output Controls
  * @brief Structures for use with the sc(4) module input-output controls.
  *
  * These data structures are primarily aimed at passing STREAMS module and
  * driver information from the kernel to the user for debugging and system
  * interrogation purposes.
  * @{ */

#define SC_IOC_LIST	((SC_IOC_MAGIC << 8) | 0x01) /**< List info and stats.
  * List module or driver information and statistics.
  * This input-output control command requests that the STREAMS Configuration
  * Module, sc(4), provide information pertaining to a list of STREAMS modules
  * and drivers.
  * 
  * The argument to the ioctl(2) call is a pointer to a #sc_list structure
  * describing the array of module and driver names to list.
  *
  * The information requested can include the module identification, major
  * device number, driver flags, module information per the kernel
  * module_info(9) structure and module statistics per the kernel module_stat(9)
  * structure.  The user can obtain information on a per-queue basis, that is,
  * for the upper multiplex read, write, lower multiplex read and write queues.
  *
  * The primary purpose of this input-output control was to provide a mechanism
  * whereby the scls(8) utility program can interrogate the kernel data
  * structures and return information to the program for display.  This might
  * also have been possible with the /proc filesystem interface, however, the
  * sc(4) driver is a classical approach and is present in many SVR4 and other
  * UNIX implementations.  */

#define SC_IOC_RESET	((SC_IOC_MAGIC << 8) | 0x02) /**< Reset statistics.
  * Requests that the module reset the statistics associated with the requested
  * STREAMS(9) modules and drivers. */

#define SC_IOC_TUNE	((SC_IOC_MAGIC << 8) | 0x03) /**< Set tunables.
  * Request that the tunables in the associated str_tune structure be set and
  * current values returned. */

#define SC_IOC_STATS	((SC_IOC_MAGIC << 8) | 0x04) /**< Get statistics.
  * Requests that general STREAMS statistics be returned in an array of 12
  * sc_stat structures. */

#define SC_SET_MINPSZ	(1<<0)	/**< Set minimum packet size. */
#define SC_SET_MAXPSZ	(1<<1)	/**< Set maximum packet size. */
#define SC_SET_HIWAT	(1<<2)	/**< Set high water mark. */
#define SC_SET_LOWAT	(1<<3)	/**< Set low water mark. */
#define SC_SET_TRCLEVEL	(1<<4)	/**< Set trace level. */
#define SC_SET_RDQUEUE	(1<<5)	/**< Set read queues. */
#define SC_SET_WRQUEUE	(1<<6)	/**< Set write queues. */
#define SC_SET_LOWERMUX	(1<<7)	/**< Set lower multiplex queues. */

/** @} */

/** @struct sc_module_info include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Configuration Module Information.  Aside from the #index member, the
  * #mi_idnum, #mi_idname, #mi_minpsz, #mi_maxpsz, #mi_hiwat and #mi_lowat
  * members correspond precisely to the user space representation of the
  * equivalent kernel value in the @c module_info(9) kernel structure.  The
  * purpose of this structure is to retrieve that information with the
  * #SC_IOC_LIST input-output control.
  */
struct sc_module_info {
	int index;			/**< Same as index. */
	ushort mi_idnum;		/**< Module id number. */
	char mi_idname[FMNAMESZ + 1];	/**< Module name. */
	ssize_t mi_minpsz;		/**< Min packet size accepted. */
	ssize_t mi_maxpsz;		/**< Max packet size accepted. */
	size_t mi_hiwat;		/**< Hi water mark. */
	size_t mi_lowat;		/**< Lo water mark. */
};

/** @struct sc_module_stat include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Configuration Module Statistics.  Aside from the #index member, the
  * #ms_pcnt, #ms_scnt, #ms_ocnt, #ms_ccnt, #ms_acnt, #ms_xptr, #ms_xsize and
  * #ms_flags members correspond precisely to the user space representation of
  * the equivalent kernel value in the @c module_stat(9) kernel structure.  The
  * purpose of this structure is to retrieve that information with the
  * #SC_IOC_LIST input-output control.
  */
typedef struct sc_module_stat {
	int index;			/**< Same as index. */
	long ms_pcnt;			/**< Calls to qi_putp(). */
	long ms_scnt;			/**< Calls to qi_srvp(). */
	long ms_ocnt;			/**< Calls to qi_qopen(). */
	long ms_ccnt;			/**< Calls to qi_qclose(). */
	long ms_acnt;			/**< Calls to qi_qadmin(). */
	void *ms_xptr;			/**< Module private stats. */
	short ms_xsize;			/**< Len of private stats. */
	uint ms_flags;			/**< Bool stats -- for future use. */
} sc_module_stat_t;

/** @struct sc_mlist include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Configuration Module Data List.  This structure if for collecting
  * module information and statistics for up to 4 queues: the upper multiplex
  * read and write queue and the lower multiplex read and write queue.  The
  * structure need only allocate sufficient room to hold the values of interest.
  */
struct sc_mlist {
	long major;			/**< Major device number, -1 for module. */
	char name[FMNAMESZ + 1];	/**< Module or driver name. */

	struct sc_module_info mi[4];	/**< Four module_info structures (top r/wq, bot r/wq).
	  * Four @c module_info(9) structures. (Upper multiplex: read queue,
	  * write queue; lower multiplex: read queue, write queue.) The #mi
	  * member contains four #sc_module_info structures, one for each of the
	  * upper multiplex read and write queue and lower multiplex read and
	  * write queue.  See sc(4) and scls(8) for more information.  */

	struct sc_module_stat ms[4];	/**< Four module_stat structures (top r/wq, bot r/wq).
	  * Four @c module_stat(9) structures.  (Upper multiplex: read queue,
	  * write queue; lower multiplex: read queue, write queue.) The #ms
	  * member contains four #sc_module_stat structures, one for each of the
	  * upper multiplex read and write queue and lower multiplex read and
	  * write queue.  See sc(4) and scls(8) for more information.  */
};

/** @struct sc_list include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Configuration Module List.  Provides a pointer to an array,
  * #sc_mlist, and the number of elements in the array, #sc_nmods.  */
struct sc_list {
	int sc_nmods;			/**< Number of structures in #sc_mlist. */
	struct sc_mlist *sc_mlist;	/**< Pointer to array of #sc_nmods elements. */
};

/** @struct sc_tune include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Tunables Structure.  Provides a specification structure for
  * setting and querying tunables.  The #sc_minpsz, #sc_maxpz, #sc_hiwat,
  * #sc_lowat and #sc_trclevel members always return the current value upon
  * return to the input-output control.
  */
struct sc_tune {
	int sc_flags;			/**< Tunable flags. */
	ssize_t sc_minpsz;		/**< Min packet size accepted. */
	ssize_t sc_maxpsz;		/**< Max packet size accepted. */
	size_t sc_hiwat;		/**< Hi water mark. */
	size_t sc_lowat;		/**< Lo water mark. */
	int sc_trclevel;		/**< Trace level. */
};

/** @struct sc_tlist include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Tunables list.  Provides a pointer to an array,
  * #sc_tlist, and the number of elements in the array, #sc_ntune.  */
struct sc_tlist {
	long sc_major;			/**< Major device number, -1 for module. */
	char sc_name[FMNAMESZ + 1];	/**< Module name. */
	int sc_ntune;			/**< Number of structures in #sc_tlist. */
	struct sc_tune *sc_tlist;	/**< Pointer to array of #sc_ntune elements. */
};

/**
  * @struct sc_stat include/sys/openss7/sc.h <sys/sc.h>
  *
  * STREAMS Statistic Structure.  Provides a statistics structure for querying
  * STREAMS statistics.  The #sc_alloc member returns the currently allocated
  * value, the #sc_hiwat member returns the allocation high water mark for the
  * statistic.  These structures are returned in an array, where each element
  * in the array represents a different statistic.
  */
struct sc_stat {
	unsigned long sc_alloc;
	unsigned long sc_hiwat;
};

struct sc_slist {
	int sc_nstat;			/**< Number of structures in #sc_slist. */
	struct sc_stat *sc_slist;	/**< Pointer to array of #sc_nstat elements. */
};

#define SC_DYN_STREAM	0	/* struct shinfo */
#define SC_DYN_QUEUE	1	/* struct queinfo */
#define SC_DYN_MSGBLOCK	2	/* struct mbinfo */
#define SC_DYN_MDBBLOCK	3	/* struct dbinfo */
#define SC_DYN_LINKBLK	4	/* struct linkinfo */
#define SC_DYN_STREVENT	5	/* struct seinfo */
#define SC_DYN_QBAND	6	/* struct bandinfo */
#define SC_DYN_STRAPUSH	7	/* struct apinfo */
#define SC_DYN_DEVINFO	8	/* struct devinfo */
#define SC_DYN_MODINFO	9	/* struct mdlinfo */
#define SC_DYN_SYNQ	10	/* struct syncq */
#define SC_DYN_BUFFERS	11	/* buffer memory */

#ifdef __KERNEL__
#ifdef __LP64__
/* These are just to help the kernel with compatibility functions. */

struct sc_module_info32 {
	int32_t index;			/**< Same as index. */
	u_int16_t mi_idnum;		/**< Module id number. */
	char mi_idname[FMNAMESZ + 1];	/**< Module name. */
	int32_t mi_minpsz;		/**< Min packet size accepted. */
	int32_t mi_maxpsz;		/**< Max packet size accepted. */
	u_int32_t mi_hiwat;		/**< Hi water mark. */
	u_int32_t mi_lowat;		/**< Lo water mark. */
};

struct sc_module_stat32 {
	int32_t index;			/**< Same as index. */
	int32_t ms_pcnt;		/**< Calls to qi_putp(). */
	int32_t ms_scnt;		/**< Calls to qi_srvp(). */
	int32_t ms_ocnt;		/**< Calls to qi_qopen(). */
	int32_t ms_ccnt;		/**< Calls to qi_qclose(). */
	int32_t ms_acnt;		/**< Calls to qi_qadmin(). */
	u_int32_t ms_xptr;		/**< Module private stats. */
	int16_t ms_xsize;		/**< Len of private stats. */
	u_int32_t ms_flags;		/**< Bool stats -- for future use. */
};

struct sc_mlist32 {
	int32_t major;
	char name[FMNAMESZ + 1];
	struct sc_module_info32 mi[4];
	struct sc_module_stat32 ms[4];
};

struct sc_list32 {
	int32_t sc_nmods;
	u_int32_t sc_mlist;
};

struct sc_tune32 {
	int32_t sc_flags;		/**< Tunable flags. */
	int32_t sc_minpsz;		/**< Min packet size accepted. */
	int32_t sc_maxpsz;		/**< Max packet size accepted. */
	u_int32_t sc_hiwat;		/**< Hi water mark. */
	u_int32_t sc_lowat;		/**< Lo water mark. */
	int32_t sc_trclevel;		/**< Trace level. */
};

struct sc_tlist32 {
	int32_t sc_major;		/**< Major device number. */
	char sc_name[FMNAMESZ + 1];	/**< Module name. */
	int32_t sc_ntune;
	u_int32_t sc_tlist;
};

struct sc_stat32 {
	uint32_t sc_alloc;
	uint32_t sc_hiwat;
};

struct sc_slist32 {
	int32_t sc_nstat;
	u_int32_t sc_slist;
};
#endif				/* __LP64__ */
#endif				/* __KERNEL__ */

/** @} */
/** @} */

#endif				/* __SYS_OPENSS7_SC_H__ */

// vim: com=sr\:/**,mb\:\ *,eb\:\ */,sr\:/*,mb\:*,eb\:*/,b\:TRANS
