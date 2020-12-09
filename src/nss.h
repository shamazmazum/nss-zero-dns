#ifndef src_nss_h
#define src_nss_h

#if defined(NSS_IPV4_ONLY) && !defined(MDNS_MINIMAL)
#define _nss_zerodns_gethostbyname4_r _nss_zerodns4_gethostbyname4_r
#define _nss_zerodns_gethostbyname3_r _nss_zerodns4_gethostbyname3_r
#define _nss_zerodns_gethostbyname2_r _nss_zerodns4_gethostbyname2_r
#define _nss_zerodns_gethostbyname_r _nss_zerodns4_gethostbyname_r
#define _nss_zerodns_gethostbyaddr_r _nss_zerodns4_gethostbyaddr_r
#elif defined(NSS_IPV4_ONLY) && defined(MDNS_MINIMAL)
#define _nss_zerodns_gethostbyname4_r _nss_zerodns4_minimal_gethostbyname4_r
#define _nss_zerodns_gethostbyname3_r _nss_zerodns4_minimal_gethostbyname3_r
#define _nss_zerodns_gethostbyname2_r _nss_zerodns4_minimal_gethostbyname2_r
#define _nss_zerodns_gethostbyname_r _nss_zerodns4_minimal_gethostbyname_r
#define _nss_zerodns_gethostbyaddr_r _nss_zerodns4_minimal_gethostbyaddr_r
#elif defined(NSS_IPV6_ONLY) && !defined(MDNS_MINIMAL)
#define _nss_zerodns_gethostbyname4_r _nss_zerodns6_gethostbyname4_r
#define _nss_zerodns_gethostbyname3_r _nss_zerodns6_gethostbyname3_r
#define _nss_zerodns_gethostbyname2_r _nss_zerodns6_gethostbyname2_r
#define _nss_zerodns_gethostbyname_r _nss_zerodns6_gethostbyname_r
#define _nss_zerodns_gethostbyaddr_r _nss_zerodns6_gethostbyaddr_r
#elif defined(NSS_IPV6_ONLY) && defined(MDNS_MINIMAL)
#define _nss_zerodns_gethostbyname4_r _nss_zerodns6_minimal_gethostbyname4_r
#define _nss_zerodns_gethostbyname3_r _nss_zerodns6_minimal_gethostbyname3_r
#define _nss_zerodns_gethostbyname2_r _nss_zerodns6_minimal_gethostbyname2_r
#define _nss_zerodns_gethostbyname_r _nss_zerodns6_minimal_gethostbyname_r
#define _nss_zerodns_gethostbyaddr_r _nss_zerodns6_minimal_gethostbyaddr_r
#elif defined(MDNS_MINIMAL)
#define _nss_zerodns_gethostbyname4_r _nss_zerodns_minimal_gethostbyname4_r
#define _nss_zerodns_gethostbyname3_r _nss_zerodns_minimal_gethostbyname3_r
#define _nss_zerodns_gethostbyname2_r _nss_zerodns_minimal_gethostbyname2_r
#define _nss_zerodns_gethostbyname_r _nss_zerodns_minimal_gethostbyname_r
#define _nss_zerodns_gethostbyaddr_r _nss_zerodns_minimal_gethostbyaddr_r
#endif

// Define prototypes for nss function we're going to export (fixes GCC warnings)
#ifndef __FreeBSD__
enum nss_status _nss_zerodns_gethostbyname4_r(const char*, struct gaih_addrtuple**,
                                           char*, size_t, int*, int*, int32_t*);
#endif
enum nss_status _nss_zerodns_gethostbyname3_r(const char*, int, struct hostent*,
                                           char*, size_t, int*, int*, int32_t*,
                                           char**);
enum nss_status _nss_zerodns_gethostbyname2_r(const char*, int, struct hostent*,
                                           char*, size_t, int*, int*);
enum nss_status _nss_zerodns_gethostbyname_r(const char*, struct hostent*, char*,
                                          size_t, int*, int*);
enum nss_status _nss_zerodns_gethostbyaddr_r(const void*, int, int,
                                          struct hostent*, char*, size_t, int*,
                                          int*);

#endif
