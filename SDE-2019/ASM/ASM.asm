.586
.model flat, stdcall
includelib SDElib.lib
includelib kernel32.lib

ExitProcess PROTO : DWORD

.stack
4096
.const
	L0 dword 100
	L1 dword 200
	L2 dword 5
	L3 dword 6
	T0 byte 'tt', 0
	L4 dword 100
	L5 dword 1
	L6 dword 0

.data
	buffer00000 dword 0
	z01000 dword 0
	x02000 dword 0

.code
proc_sum proc, parameter_s : dword, parameter_s : byte
