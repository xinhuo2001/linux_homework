### 使用命令
netstat --statistics

### 获取数据如下
```sh
Ip:
    22915173 total packets received
    5 with invalid addresses
    72813 forwarded
    7000 with unknown protocol
    0 incoming packets discarded
    22835355 incoming packets delivered
    18760499 requests sent out
    1 dropped because of missing route
Icmp:
    138601 ICMP messages received
    6713 input ICMP message failed.
    InCsumErrors: 2
    ICMP input histogram:
        destination unreachable: 6431
        timeout in transit: 320
        echo requests: 131748
        echo replies: 45
        timestamp request: 52
        timestamp reply: 3
    333930 ICMP messages sent
    0 ICMP messages failed
    ICMP output histogram:
        destination unreachable: 202118
        echo request: 12
        echo replies: 131748
        timestamp replies: 52
IcmpMsg:
        InType0: 45
        InType3: 6431
        InType8: 131748
        InType11: 320
        InType13: 52
        InType14: 3
        OutType0: 131748
        OutType3: 202118
        OutType8: 12
        OutType14: 52
Tcp:
    471720 active connections openings
    18900 passive connection openings
    125758 failed connection attempts
    4632 connection resets received
    2 connections established
    20897800 segments received
    17364151 segments send out
    42952 segments retransmited
    2306 bad segments received.
    10552493 resets sent
    InCsumErrors: 2232
Udp:
    1048737 packets received
    751647 packets to unknown port received.
    1 packet receive errors
    1183265 packets sent
    InCsumErrors: 1
UdpLite:
TcpExt:
    31 SYN cookies sent
    1 SYN cookies received
    376 invalid SYN cookies received
    125456 resets received for embryonic SYN_RECV sockets
    403122 TCP sockets finished time wait in fast timer
    12 packets rejects in established connections because of timestamp
    36587 delayed acks sent
    11 delayed acks further delayed because of locked socket
    Quick ack mode was activated 3109 times
    31 SYNs to LISTEN sockets dropped
    14317 packets directly queued to recvmsg prequeue.
    2256735 bytes directly in process context from backlog
    17246137 bytes directly received in process context from prequeue
    1196878 packet headers predicted
    3804 packets header predicted and directly queued to user
    993548 acknowledgments not containing data payload received
    1409812 predicted acknowledgments
    4836 times recovered from packet loss by selective acknowledgements
    Detected reordering 25 times using FACK
    Detected reordering 286 times using SACK
    150 congestion windows fully recovered without slow start
    368 congestion windows recovered without slow start by DSACK
    675 congestion windows recovered without slow start after partial ack
    TCPLostRetransmit: 1511
    1058 timeouts after SACK recovery
    349 timeouts in loss state
    18182 fast retransmits
    275 forward retransmits
    10260 retransmits in slow start
    5840 other TCP timeouts
    TCPLossProbes: 7838
    TCPLossProbeRecovery: 257
    942 SACK retransmits failed
    3219 DSACKs sent for old packets
    338 DSACKs sent for out of order packets
    4363 DSACKs received
    9 DSACKs for out of order packets received
    470 connections reset due to unexpected data
    657 connections reset due to early user close
    353 connections aborted due to timeout
    TCPDSACKIgnoredOld: 1
    TCPDSACKIgnoredNoUndo: 2900
    TCPSpuriousRTOs: 41
    TCPSackShifted: 2386
    TCPSackMerged: 12049
    TCPSackShiftFallback: 36401
    TCPReqQFullDoCookies: 31
    TCPRcvCoalesce: 2160
    TCPOFOQueue: 237687
    TCPOFOMerge: 201
    TCPChallengeACK: 80
    TCPSYNChallenge: 74
    TCPFromZeroWindowAdv: 4
    TCPToZeroWindowAdv: 4
    TCPWantZeroWindowAdv: 10
    TCPSynRetrans: 5785
    TCPOrigDataSent: 4014799
    TCPHystartTrainDetect: 29
    TCPHystartTrainCwnd: 621
    TCPHystartDelayDetect: 32
    TCPHystartDelayCwnd: 1127
    TCPACKSkippedSynRecv: 6
    TCPACKSkippedSeq: 4
    TCPACKSkippedChallenge: 3
    TCPWinProbe: 8
    TCPKeepAlive: 664
IpExt:
    InOctets: 5844666226
    OutOctets: 2270559862
    InNoECTPkts: 24796739
    InECT0Pkts: 84

```