#ifndef _COMPAT_H_
#define _COMPAT_H_

#define FAIL_INSTEAD_OF_TRYING_FALLBACK

#define __warn_references(x,y)

#ifndef	ALIGN
/* XXX: x86_64 only, see sys/arch/$arch/include/_types.h */
#define	ALIGNBYTES	(sizeof(long) - 1)
#define	ALIGN(p)	(((size_t)(p) + ALIGNBYTES) &~ ALIGNBYTES)
#endif

#define __UNUSED	__attribute__ ((unused))
/* XXX: __unused clashes with musls stat.h
#define __unused	__attribute__ ((unused))
*/

#define __dead		__attribute__((__noreturn__))

#define __BEGIN_DECLS
#define __END_DECLS

#define __BEGIN_HIDDEN_DECLS
#define __END_HIDDEN_DECLS

#ifndef	__CONCAT
#define	__CONCAT(x,y)	x ## y
#endif
#ifndef	__STRING
#define	__STRING(x)	#x
#endif

#undef __weak_alias
#define __weak_alias(new, old) \
	extern __typeof(old) new __attribute__((weak, alias(#old)))

#define __strong_alias(new, old) \
	extern __typeof(old) new __attribute__((alias(#old)))

#ifndef SA_LEN
#define SA_LEN(X) \
	(((struct sockaddr*)(X))->sa_family == AF_INET ? sizeof(struct sockaddr_in) : \
	 ((struct sockaddr*)(X))->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr))
#endif

#ifndef SS_LEN
#define SS_LEN(X) \
	(((struct sockaddr_storage*)(X))->ss_family == AF_INET ? sizeof(struct sockaddr_in) : \
	 ((struct sockaddr_storage*)(X))->ss_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr))
#endif

#define	_PW_BUF_LEN	1024
#define	_GR_BUF_LEN	1024

#define NOFILE_MAX	NOFILE

#if !defined(HAVE_ATTRIBUTE__BOUNDED__)
#define __bounded__(x, y, z)
#endif

#if !defined(DEF_WEAK)
#define DEF_WEAK(x)
#endif

#if !defined(DEF_STRONG)
#define DEF_STRONG(x)
#endif

#if !defined(PROTO_NORMAL)
#define PROTO_NORMAL(x)
#endif

/* sys/sys/param.h */
/*
 * File system parameters and macros.
 *
 * The file system is made out of blocks of at most MAXBSIZE units, with
 * smaller units (fragments) only in the last direct block.  MAXBSIZE
 * primarily determines the size of buffers in the buffer pool.  It may be
 * made larger without any effect on existing file systems; however making
 * it smaller makes some file systems unmountable.
 */
#define	MAXBSIZE	(64 * 1024)

#ifndef NL_TEXTMAX
#define	NL_TEXTMAX	2048
#endif

#ifndef howmany
#define howmany(n,d) (((n)+((d)-1))/(d))
#endif

/* API definitions lifted from OpenBSD src/include */

/* pwd.h */
#define _PW_NAME_LEN 63

/* stdlib.h */

/* unistd.h */
#ifndef HAVE_EXECVPE
int execvpe(const char *, char *const *, char *const *);
#endif /* !HAVE_EXECVPE */
#ifndef HAVE_SETRESUID
/* int setresuid(uid_t, uid_t, uid_t); */
#endif /* !HAVE_SETRESUID */

#ifndef HAVE_PLEDGE
int pledge(const char *, const char *[]);
#endif /* !HAVE_PLEDGE */

#ifndef HAVE_SETPROGNAME
const char * getprogname(void);
void setprogname(const char *progname);
#endif /* !HAVE_SETPROGNAME */

/* pwcache.c */
/* char *user_from_uid(uid_t, int); */
/* char *group_from_gid(gid_t gid, int); */

/* getbsize.c */
char *getbsize(int *, long *);

#define strtoq strtoll

/* inttypes.h */
/*
intmax_t	strtoimax(const char *, char **, int);
uintmax_t	strtoumax(const char *, char **, int);
*/

/* #define d_namlen d_reclen */
#if !defined(_DIRENT_HAVE_NAMLEN)
#define D_NAMLEN(x) \
	strnlen((x)->d_name, (x)->d_reclen)
#else
#define D_NAMLEN(x) \
	(x)->d_namlen
#endif

/* for musl, required by xinstall */
#ifndef S_BLKSIZE
#define S_BLKSIZE 512
#endif

/**/
#ifndef MAXNAMLEN
#define	MAXNAMLEN	255
#endif

/* XXX: read dynamically? */
#define UID_MAX 60000
#define GID_MAX 60000

/* sys/sys/stat.h */
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)	/* 00777 */
#define	ALLPERMS	 (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO) /* 00666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define S_ISTXT S_ISVTX

/* lib/libc/include/thread_private.h */
#define _MUTEX_LOCK(mutex)				do {} while (0)
#define _MUTEX_UNLOCK(mutex)				do {} while (0)

#define SHA512_Update SHA512Update
#define SHA512_CTX SHA2_CTX
#define SHA512_Init SHA512Init
#define SHA512_Final SHA512Final

/* sys/socket.h */
#define	RT_TABLEID_MAX	255

/* sys/syslimits.h */
#define	CHILD_MAX	80	/* max simultaneous processes */

/* setproctitle.c */
void setproctitle(const char *, ...);

/* pw_dup.c */
struct passwd *pw_dup(const struct passwd *);

int issetugid(void);

#define	OPEN_MAX	64	/* max open files per process */

/* TTY SHIT START */
#define	TTYDEF_IFLAG	(BRKINT | ICRNL | IMAXBEL | IXON | IXANY)
#define TTYDEF_OFLAG	(OPOST | ONLCR)
#define TTYDEF_LFLAG	(ECHO | ICANON | ISIG | IEXTEN | ECHOE|ECHOKE|ECHOCTL)
#define TTYDEF_CFLAG	(CREAD | CS8 | HUPCL)
#define TTYDEF_SPEED	(B9600)

#define CTRL(x)	(x&037)
#define	CEOF		CTRL('d')
#define	CEOL		((unsigned char)'\377')	/* XXX avoid _POSIX_VDISABLE */
#define	CERASE		0177
#define	CINTR		CTRL('c')
#define	CSTATUS		((unsigned char)'\377')	/* XXX avoid _POSIX_VDISABLE */
#define	CKILL		CTRL('u')
#define	CMIN		1
#define	CQUIT		034		/* FS, ^\ */
#define	CSUSP		CTRL('z')
#define	CTIME		0
#define	CDSUSP		CTRL('y')
#define	CSTART		CTRL('q')
#define	CSTOP		CTRL('s')
#define	CLNEXT		CTRL('v')
#define	CDISCARD 	CTRL('o')
#define	CWERASE 	CTRL('w')
#define	CREPRINT 	CTRL('r')
#define	CEOT		CEOF
/* compat */
#define	CBRK		CEOL
#define CRPRNT		CREPRINT
#define	CFLUSH		CDISCARD

#define VDSUSP		11	/* ISIG */

#define	TIOCEXT		_IOW('t', 96, int)	/* pty: external processing */
#define	TIOCSTOP	 _IO('t', 111)		/* stop output, like ^S */
#define	TIOCSTART	 _IO('t', 110)		/* start output, like ^Q */
#define	TTYDISC		0		/* termios tty line discipline */

#define ALTWERASE	0x00000200	/* use alternate WERASE algorithm */

#define OXTABS		0x00000004	/* expand tabs to spaces */
#define ONOEOT		0x00000008	/* discard EOT's (^D) on output */

#define	PPPDISC		5		/* ppp discipline */
#define	NMEADISC	7		/* NMEA0183 discipline */
/* TTY SHIT END */

#endif
