/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "syncReplication.h"
#include "syncMessage.h"

// TLA+ Spec
// AppendEntries(i, j) ==
//    /\ i /= j
//    /\ state[i] = Leader
//    /\ LET prevLogIndex == nextIndex[i][j] - 1
//           prevLogTerm == IF prevLogIndex > 0 THEN
//                              log[i][prevLogIndex].term
//                          ELSE
//                              0
//           \* Send up to 1 entry, constrained by the end of the log.
//           lastEntry == Min({Len(log[i]), nextIndex[i][j]})
//           entries == SubSeq(log[i], nextIndex[i][j], lastEntry)
//       IN Send([mtype          |-> AppendEntriesRequest,
//                mterm          |-> currentTerm[i],
//                mprevLogIndex  |-> prevLogIndex,
//                mprevLogTerm   |-> prevLogTerm,
//                mentries       |-> entries,
//                \* mlog is used as a history variable for the proof.
//                \* It would not exist in a real implementation.
//                mlog           |-> log[i],
//                mcommitIndex   |-> Min({commitIndex[i], lastEntry}),
//                msource        |-> i,
//                mdest          |-> j])
//    /\ UNCHANGED <<serverVars, candidateVars, leaderVars, logVars>>
//
int32_t syncNodeAppendEntriesPeers(SSyncNode* pSyncNode) {
  int32_t ret = 0;
  return ret;
}

int32_t syncNodeReplicate(SSyncNode* pSyncNode) {
  // start replicate
  int32_t ret = syncNodeAppendEntriesPeers(pSyncNode);
  return ret;
}

int32_t syncNodeAppendEntries(SSyncNode* pSyncNode, const SRaftId* destRaftId, const SyncAppendEntries* pMsg) {
  sTrace("syncNodeAppendEntries pSyncNode:%p ", pSyncNode);
  int32_t ret = 0;

  SRpcMsg rpcMsg;
  syncAppendEntries2RpcMsg(pMsg, &rpcMsg);
  syncNodeSendMsgById(destRaftId, pSyncNode, &rpcMsg);
  return ret;
}