#include "mesi-state-automon.h"

// represent for MESI state transition matrix
// matrix row: S, I, M, E 
// matrix column: WL, RL, WR, RR
const MesiState_t MesiStateAutomon::stateAutomonMatrix [4][4] = 
{
  {E, S, I, I},
  {E, S, I, S},
  {M, M, I, S},
  {M, E, I, S}
};

// enum is a unsigned int.
// so we just use it to be the array index.
MesiState_t
MesiStateAutomon::TransferState (MesiState_t cur, CacheOperation_t opt)
{
  return stateAutomonMatrix [cur][opt];
}

std::string
MesiStateAutomon::Mesi2String (MesiState_t state)
{
  std::string res;
  switch (state) {
    case S:
      res = "S";
      break;
    case I:
      res = "I";
      break;
    case M:
      res = "M";
      break;
    case E:
      res = "E";
      break;
  }
  return res;
}