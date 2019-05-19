#!/bin/bash

sysctl -w fs.file-max=11000000
sysctl -w fs.nr_open=11000000

sysctl -w net.core.somaxconn=65535
sysctl -w net.ipv4.tcp_max_syn_backlog=65535

sysctl -w net.ipv4.ip_local_port_range="1025 65535"

sysctl -w net.ipv4.tcp_mem="100000000 100000000 100000000"
sysctl -w net.ipv4.tcp_rmem='4096 4096 4096'
sysctl -w net.ipv4.tcp_wmem='4096 4096 4096'

sysctl -w net.core.rmem_default=4096
sysctl -w net.core.wmem_default=4608

sysctl -w net.core.rmem_max=4096
sysctl -w net.core.wmem_max=4608
