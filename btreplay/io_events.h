#ifndef IOP_EVENTS_H
#define IOP_EVENTS_H

#include <asm/types.h>

#define IOP_MAGIC	0x69635200

/*
 * TS DIR PID NAME MAJOR MINOR LBA NR MD5 PATH BIO_FLAGS
 * PAGE_FLAGS QLBA QFLIGHT  QSORTED QREQUESTS
 * TSC is the timestamp of the system by ktime_get (same as blktrace)
 * TS is the timestamp of the system by ktime_get_real (real wall time)
 * DIR is WR for writes, RD for reads
 * PID is the pid of the process
 * NAME is the process "name"
 * MAJOR is the major number of the device (SCSI, IDE, etc)
 * MINOR is the minor number of the device (partition number, etc)
 * LBA is the sector requested
 * NR is the index of the page in the BIO
 * MD5 is the digest of the page (4096 Bytes)
 * PATH is the absolute path of the inode related to the page in the page
 * cache. For the ones that don't have an inode related (i.e. stuff written
 * by the journal) an ? is shown instead
 * BIO_FLAGS are the flags of the BIO in hex
 * QLBA is the last dispatched requests' sector in the request_queue by the
 * IO scheduler
 * QFLIGHT is the number of in-flight requests in the request queue
 * QSORTED ??? I think this is the count of already sorted requests in the
 * request_queue
 * QREQUESTS is the maximum number of requests in the request_queue
 */

struct iop_event {
	unsigned		magic;
	__u64			time;
	unsigned char 		dir;
	unsigned	 	pid;
	unsigned char		major;
	unsigned char		minor;
	__u64			sector;
	unsigned long 		bi_flags;
	__u64	 		qsector;
	unsigned 		qflight;
	unsigned 		qsorted;
	unsigned 		qrequests;
	
	/*
	 * these counters are used to "predict" the number
	 * of digests and the lengths of paths and processes
	 * names that follows these events on a stream.
	 */
	unsigned int 		size;
	unsigned char 		path_len;
	unsigned char 		proc_len;
};

#endif
