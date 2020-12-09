FIND_PATH(ZEROMQ_INCLUDE_DIR NAMES zmq.h)
MARK_AS_ADVANCED(ZEROMQ_INCLUDE_DIR)
 
FIND_LIBRARY(ZEROMQ_LIBRARY NAMES
  zmq
  libzmq
  zmqlib)
MARK_AS_ADVANCED(ZEROMQ_LIBRARY)
 
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ZeroMQ DEFAULT_MSG
  ZEROMQ_LIBRARY
  ZEROMQ_INCLUDE_DIR)
