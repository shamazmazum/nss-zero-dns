include_directories (${ZEROMQ_INCLUDE_DIR})
add_definitions (-DMDNS_ALLOW_FILE="${ALLOW_FILE}" -DZDNS_SOCKET_DIRECTORY="${ZDNS_SOCKET_DIRECTORY}")

add_library (nss-zero-dns SHARED
  nss.c
  util.c
  zero-dns.c
  bsdnss.c)
target_link_libraries (nss-zero-dns ${ZEROMQ_LIBRARY})
set_target_properties (nss-zero-dns PROPERTIES
  OUTPUT_NAME nss_zerodns
  PREFIX ""
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  C_VISIBILITY_PRESET hidden)

install (TARGETS nss-zero-dns LIBRARY
  DESTINATION lib)
