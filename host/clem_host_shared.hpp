#ifndef CLEM_HOST_SHARED_HPP
#define CLEM_HOST_SHARED_HPP

#include "clem_types.h"

#include <optional>
#include <string>

#define CLEM_HOST_LIBRARY_DIR "library"
#define CLEM_HOST_SNAPSHOT_DIR "snapshots"

struct ClemensBackendOutputText {
  int level;
  std::string text;
};

struct ClemensBackendBreakpoint {
  enum Type {
    Undefined,
    Execute,
    DataRead,
    Write
  };
  Type type;
  uint32_t address;
};

struct ClemensBackendDiskDriveState {
  std::string imagePath;
  bool isWriteProtected;
  bool isSpinning;
  bool isEjecting;
  bool saveFailed;
};


struct ClemensBackendState {
  const ClemensMachine* machine;
  double fps;
  uint64_t seqno;
  bool mmio_was_initialized;
  std::optional<bool> commandFailed;

  ClemensMonitor monitor;
  ClemensVideo text;
  ClemensVideo graphics;
  ClemensAudio audio;

  unsigned hostCPUID;

  const ClemensBackendOutputText* logBufferStart;
  const ClemensBackendOutputText* logBufferEnd;
  const ClemensBackendBreakpoint* bpBufferStart;
  const ClemensBackendBreakpoint* bpBufferEnd;
  const ClemensBackendBreakpoint* bpHit;
  const ClemensBackendDiskDriveState* diskDrives;
};

#endif
