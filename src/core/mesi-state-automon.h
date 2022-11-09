#ifndef MESI_STATE_H
#define MESI_STATE_H

#include <string>

typedef enum {
  S,    // Shared
  I,    // Invalid
  M,    // Modified
  E     // Exclusive
} MesiState_t;

// It is also a constructor less class.
class MesiStateAutomon {
public:
  typedef enum {
    WL,   // Write local
    RL,   // Read local
    WR,   // Write Remote
    RR    // Read Remote
  } CacheOperation_t;

  static MesiState_t TransferState (MesiState_t cur, CacheOperation_t opt);
  static std::string Mesi2String (MesiState_t state);

private:
  const static MesiState_t stateAutomonMatrix [4][4];
};

#endif