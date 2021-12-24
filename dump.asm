
_temp/boot/BOOTX64.EFI:     file format pei-x86-64


Disassembly of section .text:

0000000180001000 <efi_main>:
   180001000:	41 54                	push   r12
   180001002:	57                   	push   rdi
   180001003:	56                   	push   rsi
   180001004:	53                   	push   rbx
   180001005:	48 83 ec 38          	sub    rsp,0x38
   180001009:	45 31 c9             	xor    r9d,r9d
   18000100c:	45 31 c0             	xor    r8d,r8d
   18000100f:	bf 01 00 00 00       	mov    edi,0x1
   180001014:	48 be 7d 3f 35 5e ba 	movabs rsi,0x20c49ba5e353f7d
   18000101b:	49 0c 02 
   18000101e:	48 8b 42 60          	mov    rax,QWORD PTR [rdx+0x60]
   180001022:	48 89 05 d7 4f 00 00 	mov    QWORD PTR [rip+0x4fd7],rax        # 180006000 <BS>
   180001029:	48 89 15 d8 4f 00 00 	mov    QWORD PTR [rip+0x4fd8],rdx        # 180006008 <ST>
   180001030:	49 89 cc             	mov    r12,rcx
   180001033:	31 d2                	xor    edx,edx
   180001035:	31 c9                	xor    ecx,ecx
   180001037:	ff 90 00 01 00 00    	call   QWORD PTR [rax+0x100]
   18000103d:	48 8b 05 c4 4f 00 00 	mov    rax,QWORD PTR [rip+0x4fc4]        # 180006008 <ST>
   180001044:	48 8b 40 40          	mov    rax,QWORD PTR [rax+0x40]
   180001048:	48 89 c1             	mov    rcx,rax
   18000104b:	ff 50 30             	call   QWORD PTR [rax+0x30]
   18000104e:	e8 6d 07 00 00       	call   1800017c0 <locateGOP>
   180001053:	ba 05 00 00 00       	mov    edx,0x5
   180001058:	48 89 c3             	mov    rbx,rax
   18000105b:	48 89 c1             	mov    rcx,rax
   18000105e:	e8 ad 07 00 00       	call   180001810 <get_graphics_mode>
   180001063:	48 89 d9             	mov    rcx,rbx
   180001066:	ba 05 00 00 00       	mov    edx,0x5
   18000106b:	e8 c0 07 00 00       	call   180001830 <set_graphics_mode>
   180001070:	48 8b 43 18          	mov    rax,QWORD PTR [rbx+0x18]
   180001074:	4c 89 e1             	mov    rcx,r12
   180001077:	48 8d 5c 24 28       	lea    rbx,[rsp+0x28]
   18000107c:	48 8b 50 18          	mov    rdx,QWORD PTR [rax+0x18]
   180001080:	4c 8b 40 20          	mov    r8,QWORD PTR [rax+0x20]
   180001084:	e8 e7 0b 00 00       	call   180001c70 <fetch_memory_map>
   180001089:	48 c7 44 24 28 00 00 	mov    QWORD PTR [rsp+0x28],0x200000
   180001090:	20 00 
   180001092:	eb 33                	jmp    1800010c7 <efi_main+0xc7>
   180001094:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   180001098:	48 0f c7 f1          	rdrand rcx
   18000109c:	48 89 ca             	mov    rdx,rcx
   18000109f:	83 c7 01             	add    edi,0x1
   1800010a2:	48 c1 ea 05          	shr    rdx,0x5
   1800010a6:	48 89 d0             	mov    rax,rdx
   1800010a9:	48 f7 e6             	mul    rsi
   1800010ac:	48 69 d2 a0 0f 00 00 	imul   rdx,rdx,0xfa0
   1800010b3:	48 29 d1             	sub    rcx,rdx
   1800010b6:	48 c1 e1 0c          	shl    rcx,0xc
   1800010ba:	48 89 4c 24 28       	mov    QWORD PTR [rsp+0x28],rcx
   1800010bf:	81 ff 28 0a 00 00    	cmp    edi,0xa28
   1800010c5:	74 46                	je     18000110d <efi_main+0x10d>
   1800010c7:	31 c9                	xor    ecx,ecx
   1800010c9:	41 b8 0a 00 00 00    	mov    r8d,0xa
   1800010cf:	48 89 da             	mov    rdx,rbx
   1800010d2:	e8 b9 10 00 00       	call   180002190 <mapalloc>
   1800010d7:	84 c0                	test   al,al
   1800010d9:	74 bd                	je     180001098 <efi_main+0x98>
   1800010db:	e8 b0 05 00 00       	call   180001690 <print_map>
   1800010e0:	48 8d 0d 19 1f 00 00 	lea    rcx,[rip+0x1f19]        # 180003000 <.rdata>
   1800010e7:	e8 a4 03 00 00       	call   180001490 <print_string>
   1800010ec:	48 63 cf             	movsxd rcx,edi
   1800010ef:	45 31 c9             	xor    r9d,r9d
   1800010f2:	45 31 c0             	xor    r8d,r8d
   1800010f5:	ba 0a 00 00 00       	mov    edx,0xa
   1800010fa:	e8 a1 02 00 00       	call   1800013a0 <print_num>
   1800010ff:	48 8d 0d 18 1f 00 00 	lea    rcx,[rip+0x1f18]        # 18000301e <.rdata+0x1e>
   180001106:	e8 85 03 00 00       	call   180001490 <print_string>
   18000110b:	eb fe                	jmp    18000110b <efi_main+0x10b>
   18000110d:	e8 7e 05 00 00       	call   180001690 <print_map>
   180001112:	eb fe                	jmp    180001112 <efi_main+0x112>
   180001114:	90                   	nop
   180001115:	90                   	nop
   180001116:	90                   	nop
   180001117:	90                   	nop
   180001118:	90                   	nop
   180001119:	90                   	nop
   18000111a:	90                   	nop
   18000111b:	90                   	nop
   18000111c:	90                   	nop
   18000111d:	90                   	nop
   18000111e:	90                   	nop
   18000111f:	90                   	nop

0000000180001120 <print_num.constprop.0>:
   180001120:	55                   	push   rbp
   180001121:	57                   	push   rdi
   180001122:	56                   	push   rsi
   180001123:	53                   	push   rbx
   180001124:	48 81 ec 28 02 00 00 	sub    rsp,0x228
   18000112b:	49 89 c8             	mov    r8,rcx
   18000112e:	48 85 c9             	test   rcx,rcx
   180001131:	0f 84 b1 00 00 00    	je     1800011e8 <print_num.constprop.0+0xc8>
   180001137:	31 ed                	xor    ebp,ebp
   180001139:	b9 02 00 00 00       	mov    ecx,0x2
   18000113e:	48 8d 74 24 20       	lea    rsi,[rsp+0x20]
   180001143:	49 ba 67 66 66 66 66 	movabs r10,0x6666666666666667
   18000114a:	66 66 66 
   18000114d:	eb 04                	jmp    180001153 <print_num.constprop.0+0x33>
   18000114f:	90                   	nop
   180001150:	48 89 c5             	mov    rbp,rax
   180001153:	4c 89 c0             	mov    rax,r8
   180001156:	4d 89 c1             	mov    r9,r8
   180001159:	48 63 fd             	movsxd rdi,ebp
   18000115c:	49 f7 ea             	imul   r10
   18000115f:	4c 89 c0             	mov    rax,r8
   180001162:	48 c1 f8 3f          	sar    rax,0x3f
   180001166:	48 c1 fa 02          	sar    rdx,0x2
   18000116a:	48 29 c2             	sub    rdx,rax
   18000116d:	48 8d 04 92          	lea    rax,[rdx+rdx*4]
   180001171:	49 89 d0             	mov    r8,rdx
   180001174:	48 01 c0             	add    rax,rax
   180001177:	49 29 c1             	sub    r9,rax
   18000117a:	41 80 f9 09          	cmp    r9b,0x9
   18000117e:	41 8d 51 30          	lea    edx,[r9+0x30]
   180001182:	41 8d 41 37          	lea    eax,[r9+0x37]
   180001186:	0f 46 c2             	cmovbe eax,edx
   180001189:	83 f9 01             	cmp    ecx,0x1
   18000118c:	83 d1 ff             	adc    ecx,0xffffffff
   18000118f:	88 04 2e             	mov    BYTE PTR [rsi+rbp*1],al
   180001192:	48 8d 45 01          	lea    rax,[rbp+0x1]
   180001196:	4d 85 c0             	test   r8,r8
   180001199:	75 b5                	jne    180001150 <print_num.constprop.0+0x30>
   18000119b:	85 c9                	test   ecx,ecx
   18000119d:	74 18                	je     1800011b7 <print_num.constprop.0+0x97>
   18000119f:	89 cb                	mov    ebx,ecx
   1800011a1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1800011a8:	b9 20 00 00 00       	mov    ecx,0x20
   1800011ad:	e8 9e 07 00 00       	call   180001950 <write_com1>
   1800011b2:	83 eb 01             	sub    ebx,0x1
   1800011b5:	75 f1                	jne    1800011a8 <print_num.constprop.0+0x88>
   1800011b7:	48 8d 1c 3e          	lea    rbx,[rsi+rdi*1]
   1800011bb:	48 8d 74 3c 1f       	lea    rsi,[rsp+rdi*1+0x1f]
   1800011c0:	48 29 ee             	sub    rsi,rbp
   1800011c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   1800011c8:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   1800011cb:	48 83 eb 01          	sub    rbx,0x1
   1800011cf:	e8 7c 07 00 00       	call   180001950 <write_com1>
   1800011d4:	48 39 de             	cmp    rsi,rbx
   1800011d7:	75 ef                	jne    1800011c8 <print_num.constprop.0+0xa8>
   1800011d9:	48 81 c4 28 02 00 00 	add    rsp,0x228
   1800011e0:	5b                   	pop    rbx
   1800011e1:	5e                   	pop    rsi
   1800011e2:	5f                   	pop    rdi
   1800011e3:	5d                   	pop    rbp
   1800011e4:	c3                   	ret    
   1800011e5:	0f 1f 00             	nop    DWORD PTR [rax]
   1800011e8:	b9 20 00 00 00       	mov    ecx,0x20
   1800011ed:	e8 5e 07 00 00       	call   180001950 <write_com1>
   1800011f2:	b9 30 00 00 00       	mov    ecx,0x30
   1800011f7:	48 81 c4 28 02 00 00 	add    rsp,0x228
   1800011fe:	5b                   	pop    rbx
   1800011ff:	5e                   	pop    rsi
   180001200:	5f                   	pop    rdi
   180001201:	5d                   	pop    rbp
   180001202:	e9 49 07 00 00       	jmp    180001950 <write_com1>
   180001207:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
   18000120e:	00 00 

0000000180001210 <print_num.constprop.1>:
   180001210:	56                   	push   rsi
   180001211:	53                   	push   rbx
   180001212:	48 81 ec 28 02 00 00 	sub    rsp,0x228
   180001219:	48 89 c8             	mov    rax,rcx
   18000121c:	48 85 c9             	test   rcx,rcx
   18000121f:	74 6f                	je     180001290 <print_num.constprop.1+0x80>
   180001221:	44 0f b6 c2          	movzx  r8d,dl
   180001225:	31 c9                	xor    ecx,ecx
   180001227:	48 8d 5c 24 20       	lea    rbx,[rsp+0x20]
   18000122c:	eb 14                	jmp    180001242 <print_num.constprop.1+0x32>
   18000122e:	66 90                	xchg   ax,ax
   180001230:	83 c2 30             	add    edx,0x30
   180001233:	88 14 0b             	mov    BYTE PTR [rbx+rcx*1],dl
   180001236:	48 8d 51 01          	lea    rdx,[rcx+0x1]
   18000123a:	48 85 c0             	test   rax,rax
   18000123d:	74 1f                	je     18000125e <print_num.constprop.1+0x4e>
   18000123f:	48 89 d1             	mov    rcx,rdx
   180001242:	48 99                	cqo    
   180001244:	4c 63 c9             	movsxd r9,ecx
   180001247:	49 f7 f8             	idiv   r8
   18000124a:	80 fa 09             	cmp    dl,0x9
   18000124d:	76 e1                	jbe    180001230 <print_num.constprop.1+0x20>
   18000124f:	83 c2 37             	add    edx,0x37
   180001252:	88 14 0b             	mov    BYTE PTR [rbx+rcx*1],dl
   180001255:	48 8d 51 01          	lea    rdx,[rcx+0x1]
   180001259:	48 85 c0             	test   rax,rax
   18000125c:	75 e1                	jne    18000123f <print_num.constprop.1+0x2f>
   18000125e:	4a 8d 74 0c 1f       	lea    rsi,[rsp+r9*1+0x1f]
   180001263:	4c 01 cb             	add    rbx,r9
   180001266:	48 29 ce             	sub    rsi,rcx
   180001269:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001270:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   180001273:	48 83 eb 01          	sub    rbx,0x1
   180001277:	e8 d4 06 00 00       	call   180001950 <write_com1>
   18000127c:	48 39 f3             	cmp    rbx,rsi
   18000127f:	75 ef                	jne    180001270 <print_num.constprop.1+0x60>
   180001281:	48 81 c4 28 02 00 00 	add    rsp,0x228
   180001288:	5b                   	pop    rbx
   180001289:	5e                   	pop    rsi
   18000128a:	c3                   	ret    
   18000128b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   180001290:	b9 30 00 00 00       	mov    ecx,0x30
   180001295:	48 81 c4 28 02 00 00 	add    rsp,0x228
   18000129c:	5b                   	pop    rbx
   18000129d:	5e                   	pop    rsi
   18000129e:	e9 ad 06 00 00       	jmp    180001950 <write_com1>
   1800012a3:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
   1800012aa:	00 00 00 00 
   1800012ae:	66 90                	xchg   ax,ax

00000001800012b0 <print_num.constprop.2>:
   1800012b0:	55                   	push   rbp
   1800012b1:	57                   	push   rdi
   1800012b2:	56                   	push   rsi
   1800012b3:	53                   	push   rbx
   1800012b4:	48 81 ec 28 02 00 00 	sub    rsp,0x228
   1800012bb:	48 85 c9             	test   rcx,rcx
   1800012be:	0f 84 ac 00 00 00    	je     180001370 <print_num.constprop.2+0xc0>
   1800012c4:	31 ed                	xor    ebp,ebp
   1800012c6:	ba 09 00 00 00       	mov    edx,0x9
   1800012cb:	48 8d 5c 24 20       	lea    rbx,[rsp+0x20]
   1800012d0:	eb 09                	jmp    1800012db <print_num.constprop.2+0x2b>
   1800012d2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   1800012d8:	48 89 c5             	mov    rbp,rax
   1800012db:	49 89 c8             	mov    r8,rcx
   1800012de:	48 63 f5             	movsxd rsi,ebp
   1800012e1:	49 c1 f8 3f          	sar    r8,0x3f
   1800012e5:	49 c1 e8 3c          	shr    r8,0x3c
   1800012e9:	4a 8d 04 01          	lea    rax,[rcx+r8*1]
   1800012ed:	83 e0 0f             	and    eax,0xf
   1800012f0:	4c 29 c0             	sub    rax,r8
   1800012f3:	4c 8d 41 0f          	lea    r8,[rcx+0xf]
   1800012f7:	48 85 c9             	test   rcx,rcx
   1800012fa:	44 8d 48 30          	lea    r9d,[rax+0x30]
   1800012fe:	49 0f 48 c8          	cmovs  rcx,r8
   180001302:	44 8d 40 37          	lea    r8d,[rax+0x37]
   180001306:	3c 09                	cmp    al,0x9
   180001308:	44 89 c8             	mov    eax,r9d
   18000130b:	41 0f 47 c0          	cmova  eax,r8d
   18000130f:	83 fa 01             	cmp    edx,0x1
   180001312:	83 d2 ff             	adc    edx,0xffffffff
   180001315:	48 c1 f9 04          	sar    rcx,0x4
   180001319:	88 04 2b             	mov    BYTE PTR [rbx+rbp*1],al
   18000131c:	48 8d 45 01          	lea    rax,[rbp+0x1]
   180001320:	75 b6                	jne    1800012d8 <print_num.constprop.2+0x28>
   180001322:	85 d2                	test   edx,edx
   180001324:	74 19                	je     18000133f <print_num.constprop.2+0x8f>
   180001326:	89 d7                	mov    edi,edx
   180001328:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   18000132f:	00 
   180001330:	b9 20 00 00 00       	mov    ecx,0x20
   180001335:	e8 16 06 00 00       	call   180001950 <write_com1>
   18000133a:	83 ef 01             	sub    edi,0x1
   18000133d:	75 f1                	jne    180001330 <print_num.constprop.2+0x80>
   18000133f:	48 01 f3             	add    rbx,rsi
   180001342:	48 8d 74 34 1f       	lea    rsi,[rsp+rsi*1+0x1f]
   180001347:	48 29 ee             	sub    rsi,rbp
   18000134a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   180001350:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   180001353:	48 83 eb 01          	sub    rbx,0x1
   180001357:	e8 f4 05 00 00       	call   180001950 <write_com1>
   18000135c:	48 39 de             	cmp    rsi,rbx
   18000135f:	75 ef                	jne    180001350 <print_num.constprop.2+0xa0>
   180001361:	48 81 c4 28 02 00 00 	add    rsp,0x228
   180001368:	5b                   	pop    rbx
   180001369:	5e                   	pop    rsi
   18000136a:	5f                   	pop    rdi
   18000136b:	5d                   	pop    rbp
   18000136c:	c3                   	ret    
   18000136d:	0f 1f 00             	nop    DWORD PTR [rax]
   180001370:	bb 08 00 00 00       	mov    ebx,0x8
   180001375:	0f 1f 00             	nop    DWORD PTR [rax]
   180001378:	b9 20 00 00 00       	mov    ecx,0x20
   18000137d:	e8 ce 05 00 00       	call   180001950 <write_com1>
   180001382:	83 eb 01             	sub    ebx,0x1
   180001385:	75 f1                	jne    180001378 <print_num.constprop.2+0xc8>
   180001387:	b9 30 00 00 00       	mov    ecx,0x30
   18000138c:	48 81 c4 28 02 00 00 	add    rsp,0x228
   180001393:	5b                   	pop    rbx
   180001394:	5e                   	pop    rsi
   180001395:	5f                   	pop    rdi
   180001396:	5d                   	pop    rbp
   180001397:	e9 b4 05 00 00       	jmp    180001950 <write_com1>
   18000139c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000001800013a0 <print_num>:
   1800013a0:	41 54                	push   r12
   1800013a2:	55                   	push   rbp
   1800013a3:	57                   	push   rdi
   1800013a4:	56                   	push   rsi
   1800013a5:	53                   	push   rbx
   1800013a6:	48 81 ec 20 02 00 00 	sub    rsp,0x220
   1800013ad:	48 89 c8             	mov    rax,rcx
   1800013b0:	48 85 c9             	test   rcx,rcx
   1800013b3:	0f 84 97 00 00 00    	je     180001450 <print_num+0xb0>
   1800013b9:	44 0f b6 d2          	movzx  r10d,dl
   1800013bd:	31 f6                	xor    esi,esi
   1800013bf:	48 8d 7c 24 20       	lea    rdi,[rsp+0x20]
   1800013c4:	eb 0d                	jmp    1800013d3 <print_num+0x33>
   1800013c6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   1800013cd:	00 00 00 
   1800013d0:	48 89 d6             	mov    rsi,rdx
   1800013d3:	48 99                	cqo    
   1800013d5:	48 63 ee             	movsxd rbp,esi
   1800013d8:	49 f7 fa             	idiv   r10
   1800013db:	80 fa 09             	cmp    dl,0x9
   1800013de:	44 8d 5a 30          	lea    r11d,[rdx+0x30]
   1800013e2:	8d 4a 37             	lea    ecx,[rdx+0x37]
   1800013e5:	41 0f 46 cb          	cmovbe ecx,r11d
   1800013e9:	41 83 f8 01          	cmp    r8d,0x1
   1800013ed:	48 8d 56 01          	lea    rdx,[rsi+0x1]
   1800013f1:	41 83 d0 ff          	adc    r8d,0xffffffff
   1800013f5:	88 0c 37             	mov    BYTE PTR [rdi+rsi*1],cl
   1800013f8:	48 85 c0             	test   rax,rax
   1800013fb:	75 d3                	jne    1800013d0 <print_num+0x30>
   1800013fd:	45 0f be e1          	movsx  r12d,r9b
   180001401:	44 89 c3             	mov    ebx,r8d
   180001404:	45 85 c0             	test   r8d,r8d
   180001407:	74 14                	je     18000141d <print_num+0x7d>
   180001409:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001410:	44 89 e1             	mov    ecx,r12d
   180001413:	e8 38 05 00 00       	call   180001950 <write_com1>
   180001418:	83 eb 01             	sub    ebx,0x1
   18000141b:	75 f3                	jne    180001410 <print_num+0x70>
   18000141d:	48 8d 1c 2f          	lea    rbx,[rdi+rbp*1]
   180001421:	48 8d 7c 2c 1f       	lea    rdi,[rsp+rbp*1+0x1f]
   180001426:	48 29 f7             	sub    rdi,rsi
   180001429:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001430:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   180001433:	48 83 eb 01          	sub    rbx,0x1
   180001437:	e8 14 05 00 00       	call   180001950 <write_com1>
   18000143c:	48 39 fb             	cmp    rbx,rdi
   18000143f:	75 ef                	jne    180001430 <print_num+0x90>
   180001441:	48 81 c4 20 02 00 00 	add    rsp,0x220
   180001448:	5b                   	pop    rbx
   180001449:	5e                   	pop    rsi
   18000144a:	5f                   	pop    rdi
   18000144b:	5d                   	pop    rbp
   18000144c:	41 5c                	pop    r12
   18000144e:	c3                   	ret    
   18000144f:	90                   	nop
   180001450:	41 83 f8 01          	cmp    r8d,0x1
   180001454:	76 1b                	jbe    180001471 <print_num+0xd1>
   180001456:	45 0f be e1          	movsx  r12d,r9b
   18000145a:	41 8d 70 ff          	lea    esi,[r8-0x1]
   18000145e:	31 db                	xor    ebx,ebx
   180001460:	44 89 e1             	mov    ecx,r12d
   180001463:	48 83 c3 01          	add    rbx,0x1
   180001467:	e8 e4 04 00 00       	call   180001950 <write_com1>
   18000146c:	48 39 f3             	cmp    rbx,rsi
   18000146f:	75 ef                	jne    180001460 <print_num+0xc0>
   180001471:	b9 30 00 00 00       	mov    ecx,0x30
   180001476:	48 81 c4 20 02 00 00 	add    rsp,0x220
   18000147d:	5b                   	pop    rbx
   18000147e:	5e                   	pop    rsi
   18000147f:	5f                   	pop    rdi
   180001480:	5d                   	pop    rbp
   180001481:	41 5c                	pop    r12
   180001483:	e9 c8 04 00 00       	jmp    180001950 <write_com1>
   180001488:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   18000148f:	00 

0000000180001490 <print_string>:
   180001490:	53                   	push   rbx
   180001491:	48 83 ec 20          	sub    rsp,0x20
   180001495:	0f b6 01             	movzx  eax,BYTE PTR [rcx]
   180001498:	84 c0                	test   al,al
   18000149a:	74 18                	je     1800014b4 <print_string+0x24>
   18000149c:	48 8d 59 01          	lea    rbx,[rcx+0x1]
   1800014a0:	0f be c8             	movsx  ecx,al
   1800014a3:	48 83 c3 01          	add    rbx,0x1
   1800014a7:	e8 a4 04 00 00       	call   180001950 <write_com1>
   1800014ac:	0f b6 43 ff          	movzx  eax,BYTE PTR [rbx-0x1]
   1800014b0:	84 c0                	test   al,al
   1800014b2:	75 ec                	jne    1800014a0 <print_string+0x10>
   1800014b4:	48 83 c4 20          	add    rsp,0x20
   1800014b8:	5b                   	pop    rbx
   1800014b9:	c3                   	ret    
   1800014ba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000001800014c0 <print_aozora_memory>:
   1800014c0:	55                   	push   rbp
   1800014c1:	57                   	push   rdi
   1800014c2:	56                   	push   rsi
   1800014c3:	53                   	push   rbx
   1800014c4:	48 83 ec 28          	sub    rsp,0x28
   1800014c8:	8b 39                	mov    edi,DWORD PTR [rcx]
   1800014ca:	48 8b 71 08          	mov    rsi,QWORD PTR [rcx+0x8]
   1800014ce:	48 8b 59 10          	mov    rbx,QWORD PTR [rcx+0x10]
   1800014d2:	83 ff 0d             	cmp    edi,0xd
   1800014d5:	0f 87 72 01 00 00    	ja     18000164d <print_aozora_memory+0x18d>
   1800014db:	48 8d 15 9a 1d 00 00 	lea    rdx,[rip+0x1d9a]        # 18000327c <.rdata+0x24c>
   1800014e2:	48 63 04 ba          	movsxd rax,DWORD PTR [rdx+rdi*4]
   1800014e6:	48 01 d0             	add    rax,rdx
   1800014e9:	ff e0                	jmp    rax
   1800014eb:	48 8d 3d f6 1c 00 00 	lea    rdi,[rip+0x1cf6]        # 1800031e8 <.rdata+0x1b8>
   1800014f2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   1800014f8:	48 83 c7 01          	add    rdi,0x1
   1800014fc:	b9 1b 00 00 00       	mov    ecx,0x1b
   180001501:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001508:	e8 43 04 00 00       	call   180001950 <write_com1>
   18000150d:	0f be 0f             	movsx  ecx,BYTE PTR [rdi]
   180001510:	48 83 c7 01          	add    rdi,0x1
   180001514:	84 c9                	test   cl,cl
   180001516:	75 f0                	jne    180001508 <print_aozora_memory+0x48>
   180001518:	b9 20 00 00 00       	mov    ecx,0x20
   18000151d:	48 8d 3d 3f 1d 00 00 	lea    rdi,[rip+0x1d3f]        # 180003263 <.rdata+0x233>
   180001524:	e8 27 04 00 00       	call   180001950 <write_com1>
   180001529:	48 89 f1             	mov    rcx,rsi
   18000152c:	e8 7f fd ff ff       	call   1800012b0 <print_num.constprop.2>
   180001531:	b9 20 00 00 00       	mov    ecx,0x20
   180001536:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   18000153d:	00 00 00 
   180001540:	e8 0b 04 00 00       	call   180001950 <write_com1>
   180001545:	0f be 0f             	movsx  ecx,BYTE PTR [rdi]
   180001548:	48 83 c7 01          	add    rdi,0x1
   18000154c:	84 c9                	test   cl,cl
   18000154e:	75 f0                	jne    180001540 <print_aozora_memory+0x80>
   180001550:	48 89 d9             	mov    rcx,rbx
   180001553:	48 8d 3d 0e 1d 00 00 	lea    rdi,[rip+0x1d0e]        # 180003268 <.rdata+0x238>
   18000155a:	e8 51 fd ff ff       	call   1800012b0 <print_num.constprop.2>
   18000155f:	b9 3a 00 00 00       	mov    ecx,0x3a
   180001564:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   180001568:	e8 e3 03 00 00       	call   180001950 <write_com1>
   18000156d:	0f be 0f             	movsx  ecx,BYTE PTR [rdi]
   180001570:	48 83 c7 01          	add    rdi,0x1
   180001574:	84 c9                	test   cl,cl
   180001576:	75 f0                	jne    180001568 <print_aozora_memory+0xa8>
   180001578:	48 29 f3             	sub    rbx,rsi
   18000157b:	ba 0a 00 00 00       	mov    edx,0xa
   180001580:	48 89 d9             	mov    rcx,rbx
   180001583:	48 8d 1d e8 1c 00 00 	lea    rbx,[rip+0x1ce8]        # 180003272 <.rdata+0x242>
   18000158a:	e8 81 fc ff ff       	call   180001210 <print_num.constprop.1>
   18000158f:	b9 20 00 00 00       	mov    ecx,0x20
   180001594:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   180001598:	e8 b3 03 00 00       	call   180001950 <write_com1>
   18000159d:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   1800015a0:	48 83 c3 01          	add    rbx,0x1
   1800015a4:	84 c9                	test   cl,cl
   1800015a6:	75 f0                	jne    180001598 <print_aozora_memory+0xd8>
   1800015a8:	48 83 c4 28          	add    rsp,0x28
   1800015ac:	5b                   	pop    rbx
   1800015ad:	5e                   	pop    rsi
   1800015ae:	5f                   	pop    rdi
   1800015af:	5d                   	pop    rbp
   1800015b0:	c3                   	ret    
   1800015b1:	48 8d 3d 78 1a 00 00 	lea    rdi,[rip+0x1a78]        # 180003030 <.rdata>
   1800015b8:	e9 3b ff ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015bd:	48 8d 3d 4c 1c 00 00 	lea    rdi,[rip+0x1c4c]        # 180003210 <.rdata+0x1e0>
   1800015c4:	e9 2f ff ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015c9:	48 8d 3d c8 1b 00 00 	lea    rdi,[rip+0x1bc8]        # 180003198 <.rdata+0x168>
   1800015d0:	e9 23 ff ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015d5:	48 8d 3d 94 1b 00 00 	lea    rdi,[rip+0x1b94]        # 180003170 <.rdata+0x140>
   1800015dc:	e9 17 ff ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015e1:	48 8d 3d 60 1b 00 00 	lea    rdi,[rip+0x1b60]        # 180003148 <.rdata+0x118>
   1800015e8:	e9 0b ff ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015ed:	48 8d 3d 2c 1b 00 00 	lea    rdi,[rip+0x1b2c]        # 180003120 <.rdata+0xf0>
   1800015f4:	e9 ff fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   1800015f9:	48 8d 3d c0 1b 00 00 	lea    rdi,[rip+0x1bc0]        # 1800031c0 <.rdata+0x190>
   180001600:	e9 f3 fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001605:	48 8d 3d 4c 1a 00 00 	lea    rdi,[rip+0x1a4c]        # 180003058 <.rdata+0x28>
   18000160c:	e9 e7 fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001611:	48 8d 3d 20 1c 00 00 	lea    rdi,[rip+0x1c20]        # 180003238 <.rdata+0x208>
   180001618:	e9 db fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   18000161d:	48 8d 3d d4 1a 00 00 	lea    rdi,[rip+0x1ad4]        # 1800030f8 <.rdata+0xc8>
   180001624:	e9 cf fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001629:	48 8d 3d a0 1a 00 00 	lea    rdi,[rip+0x1aa0]        # 1800030d0 <.rdata+0xa0>
   180001630:	e9 c3 fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001635:	48 8d 3d 6c 1a 00 00 	lea    rdi,[rip+0x1a6c]        # 1800030a8 <.rdata+0x78>
   18000163c:	e9 b7 fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001641:	48 8d 3d 38 1a 00 00 	lea    rdi,[rip+0x1a38]        # 180003080 <.rdata+0x50>
   180001648:	e9 ab fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   18000164d:	48 8d 2d 06 1c 00 00 	lea    rbp,[rip+0x1c06]        # 18000325a <.rdata+0x22a>
   180001654:	b9 1b 00 00 00       	mov    ecx,0x1b
   180001659:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001660:	e8 eb 02 00 00       	call   180001950 <write_com1>
   180001665:	0f be 4d 00          	movsx  ecx,BYTE PTR [rbp+0x0]
   180001669:	48 83 c5 01          	add    rbp,0x1
   18000166d:	84 c9                	test   cl,cl
   18000166f:	75 ef                	jne    180001660 <print_aozora_memory+0x1a0>
   180001671:	89 f9                	mov    ecx,edi
   180001673:	ba 10 00 00 00       	mov    edx,0x10
   180001678:	48 8d 3d d2 19 00 00 	lea    rdi,[rip+0x19d2]        # 180003051 <.rdata+0x21>
   18000167f:	e8 8c fb ff ff       	call   180001210 <print_num.constprop.1>
   180001684:	e9 6f fe ff ff       	jmp    1800014f8 <print_aozora_memory+0x38>
   180001689:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

0000000180001690 <print_map>:
   180001690:	41 54                	push   r12
   180001692:	55                   	push   rbp
   180001693:	57                   	push   rdi
   180001694:	56                   	push   rsi
   180001695:	53                   	push   rbx
   180001696:	48 83 ec 40          	sub    rsp,0x40
   18000169a:	48 8b 3c 25 08 80 00 	mov    rdi,QWORD PTR ds:0x8008
   1800016a1:	00 
   1800016a2:	ba 0a 00 00 00       	mov    edx,0xa
   1800016a7:	4c 8b 24 25 10 80 00 	mov    r12,QWORD PTR ds:0x8010
   1800016ae:	00 
   1800016af:	48 8d 1d ff 1b 00 00 	lea    rbx,[rip+0x1bff]        # 1800032b5 <.rdata+0x285>
   1800016b6:	48 89 f9             	mov    rcx,rdi
   1800016b9:	e8 52 fb ff ff       	call   180001210 <print_num.constprop.1>
   1800016be:	b9 20 00 00 00       	mov    ecx,0x20
   1800016c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   1800016c8:	e8 83 02 00 00       	call   180001950 <write_com1>
   1800016cd:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   1800016d0:	48 83 c3 01          	add    rbx,0x1
   1800016d4:	84 c9                	test   cl,cl
   1800016d6:	75 f0                	jne    1800016c8 <print_map+0x38>
   1800016d8:	4c 89 e1             	mov    rcx,r12
   1800016db:	ba 0a 00 00 00       	mov    edx,0xa
   1800016e0:	48 8d 1d e9 1b 00 00 	lea    rbx,[rip+0x1be9]        # 1800032d0 <.rdata+0x2a0>
   1800016e7:	e8 24 fb ff ff       	call   180001210 <print_num.constprop.1>
   1800016ec:	b9 20 00 00 00       	mov    ecx,0x20
   1800016f1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1800016f8:	e8 53 02 00 00       	call   180001950 <write_com1>
   1800016fd:	0f be 0b             	movsx  ecx,BYTE PTR [rbx]
   180001700:	48 83 c3 01          	add    rbx,0x1
   180001704:	84 c9                	test   cl,cl
   180001706:	75 f0                	jne    1800016f8 <print_map+0x68>
   180001708:	48 8d 47 01          	lea    rax,[rdi+0x1]
   18000170c:	bb 18 80 00 00       	mov    ebx,0x8018
   180001711:	be 01 00 00 00       	mov    esi,0x1
   180001716:	48 8d 6c 24 20       	lea    rbp,[rsp+0x20]
   18000171b:	48 83 f8 01          	cmp    rax,0x1
   18000171f:	76 7f                	jbe    1800017a0 <print_map+0x110>
   180001721:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001728:	4c 8d 25 b5 1b 00 00 	lea    r12,[rip+0x1bb5]        # 1800032e4 <.rdata+0x2b4>
   18000172f:	b9 6d 00 00 00       	mov    ecx,0x6d
   180001734:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   180001738:	e8 13 02 00 00       	call   180001950 <write_com1>
   18000173d:	41 0f be 0c 24       	movsx  ecx,BYTE PTR [r12]
   180001742:	49 83 c4 01          	add    r12,0x1
   180001746:	84 c9                	test   cl,cl
   180001748:	75 ee                	jne    180001738 <print_map+0xa8>
   18000174a:	48 89 f1             	mov    rcx,rsi
   18000174d:	4c 8d 25 8d 1b 00 00 	lea    r12,[rip+0x1b8d]        # 1800032e1 <.rdata+0x2b1>
   180001754:	e8 c7 f9 ff ff       	call   180001120 <print_num.constprop.0>
   180001759:	b9 3a 00 00 00       	mov    ecx,0x3a
   18000175e:	66 90                	xchg   ax,ax
   180001760:	e8 eb 01 00 00       	call   180001950 <write_com1>
   180001765:	41 0f be 0c 24       	movsx  ecx,BYTE PTR [r12]
   18000176a:	49 83 c4 01          	add    r12,0x1
   18000176e:	84 c9                	test   cl,cl
   180001770:	75 ee                	jne    180001760 <print_map+0xd0>
   180001772:	f3 0f 6f 03          	movdqu xmm0,XMMWORD PTR [rbx]
   180001776:	48 89 e9             	mov    rcx,rbp
   180001779:	48 83 c3 18          	add    rbx,0x18
   18000177d:	0f 29 44 24 20       	movaps XMMWORD PTR [rsp+0x20],xmm0
   180001782:	48 8b 43 f8          	mov    rax,QWORD PTR [rbx-0x8]
   180001786:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
   18000178b:	e8 30 fd ff ff       	call   1800014c0 <print_aozora_memory>
   180001790:	48 8d 46 01          	lea    rax,[rsi+0x1]
   180001794:	48 39 f7             	cmp    rdi,rsi
   180001797:	74 07                	je     1800017a0 <print_map+0x110>
   180001799:	48 89 c6             	mov    rsi,rax
   18000179c:	eb 8a                	jmp    180001728 <print_map+0x98>
   18000179e:	66 90                	xchg   ax,ax
   1800017a0:	b9 0a 00 00 00       	mov    ecx,0xa
   1800017a5:	48 83 c4 40          	add    rsp,0x40
   1800017a9:	5b                   	pop    rbx
   1800017aa:	5e                   	pop    rsi
   1800017ab:	5f                   	pop    rdi
   1800017ac:	5d                   	pop    rbp
   1800017ad:	41 5c                	pop    r12
   1800017af:	e9 9c 01 00 00       	jmp    180001950 <write_com1>
   1800017b4:	90                   	nop
   1800017b5:	90                   	nop
   1800017b6:	90                   	nop
   1800017b7:	90                   	nop
   1800017b8:	90                   	nop
   1800017b9:	90                   	nop
   1800017ba:	90                   	nop
   1800017bb:	90                   	nop
   1800017bc:	90                   	nop
   1800017bd:	90                   	nop
   1800017be:	90                   	nop
   1800017bf:	90                   	nop

00000001800017c0 <locateGOP>:
   1800017c0:	48 83 ec 48          	sub    rsp,0x48
   1800017c4:	31 d2                	xor    edx,edx
   1800017c6:	48 b8 de a9 42 90 dc 	movabs rax,0x4a3823dc9042a9de
   1800017cd:	23 38 4a 
   1800017d0:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
   1800017d5:	48 8d 4c 24 30       	lea    rcx,[rsp+0x30]
   1800017da:	4c 8d 44 24 28       	lea    r8,[rsp+0x28]
   1800017df:	48 b8 96 fb 7a de d0 	movabs rax,0x6a5180d0de7afb96
   1800017e6:	80 51 6a 
   1800017e9:	48 89 44 24 38       	mov    QWORD PTR [rsp+0x38],rax
   1800017ee:	48 8b 05 db 1b 00 00 	mov    rax,QWORD PTR [rip+0x1bdb]        # 1800033d0 <.refptr.BS>
   1800017f5:	48 8b 00             	mov    rax,QWORD PTR [rax]
   1800017f8:	ff 90 40 01 00 00    	call   QWORD PTR [rax+0x140]
   1800017fe:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
   180001803:	48 83 c4 48          	add    rsp,0x48
   180001807:	c3                   	ret    
   180001808:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   18000180f:	00 

0000000180001810 <get_graphics_mode>:
   180001810:	48 83 ec 38          	sub    rsp,0x38
   180001814:	4c 8d 4c 24 20       	lea    r9,[rsp+0x20]
   180001819:	4c 8d 44 24 28       	lea    r8,[rsp+0x28]
   18000181e:	ff 11                	call   QWORD PTR [rcx]
   180001820:	48 8b 44 24 20       	mov    rax,QWORD PTR [rsp+0x20]
   180001825:	48 83 c4 38          	add    rsp,0x38
   180001829:	c3                   	ret    
   18000182a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000180001830 <set_graphics_mode>:
   180001830:	48 ff 61 08          	rex.W jmp QWORD PTR [rcx+0x8]
   180001834:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
   18000183b:	00 00 00 00 
   18000183f:	90                   	nop

0000000180001840 <draw_pixel_xy>:
   180001840:	48 8b 41 18          	mov    rax,QWORD PTR [rcx+0x18]
   180001844:	48 8b 48 08          	mov    rcx,QWORD PTR [rax+0x8]
   180001848:	44 0f af 41 20       	imul   r8d,DWORD PTR [rcx+0x20]
   18000184d:	c1 e2 02             	shl    edx,0x2
   180001850:	48 63 d2             	movsxd rdx,edx
   180001853:	41 c1 e0 02          	shl    r8d,0x2
   180001857:	4c 03 40 18          	add    r8,QWORD PTR [rax+0x18]
   18000185b:	49 01 d0             	add    r8,rdx
   18000185e:	46 89 0c 85 00 00 00 	mov    DWORD PTR [r8*4+0x0],r9d
   180001865:	00 
   180001866:	c3                   	ret    
   180001867:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
   18000186e:	00 00 

0000000180001870 <draw_pixel_pos>:
   180001870:	48 8b 41 18          	mov    rax,QWORD PTR [rcx+0x18]
   180001874:	48 8b 40 18          	mov    rax,QWORD PTR [rax+0x18]
   180001878:	c1 e2 02             	shl    edx,0x2
   18000187b:	48 63 d2             	movsxd rdx,edx
   18000187e:	44 89 04 10          	mov    DWORD PTR [rax+rdx*1],r8d
   180001882:	c3                   	ret    
   180001883:	90                   	nop
   180001884:	90                   	nop
   180001885:	90                   	nop
   180001886:	90                   	nop
   180001887:	90                   	nop
   180001888:	90                   	nop
   180001889:	90                   	nop
   18000188a:	90                   	nop
   18000188b:	90                   	nop
   18000188c:	90                   	nop
   18000188d:	90                   	nop
   18000188e:	90                   	nop
   18000188f:	90                   	nop

0000000180001890 <outb>:
   180001890:	89 d0                	mov    eax,edx
   180001892:	48 89 ca             	mov    rdx,rcx
   180001895:	ee                   	out    dx,al
   180001896:	c3                   	ret    
   180001897:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
   18000189e:	00 00 

00000001800018a0 <inb>:
   1800018a0:	48 89 ca             	mov    rdx,rcx
   1800018a3:	ec                   	in     al,dx
   1800018a4:	c3                   	ret    
   1800018a5:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
   1800018ac:	00 00 00 00 

00000001800018b0 <init_com1>:
   1800018b0:	48 83 ec 28          	sub    rsp,0x28
   1800018b4:	45 31 d2             	xor    r10d,r10d
   1800018b7:	41 bb f9 03 00 00    	mov    r11d,0x3f9
   1800018bd:	44 89 d0             	mov    eax,r10d
   1800018c0:	4c 89 da             	mov    rdx,r11
   1800018c3:	ee                   	out    dx,al
   1800018c4:	41 b9 fb 03 00 00    	mov    r9d,0x3fb
   1800018ca:	b8 80 ff ff ff       	mov    eax,0xffffff80
   1800018cf:	4c 89 ca             	mov    rdx,r9
   1800018d2:	ee                   	out    dx,al
   1800018d3:	41 b8 03 00 00 00    	mov    r8d,0x3
   1800018d9:	b9 f8 03 00 00       	mov    ecx,0x3f8
   1800018de:	44 89 c0             	mov    eax,r8d
   1800018e1:	48 89 ca             	mov    rdx,rcx
   1800018e4:	ee                   	out    dx,al
   1800018e5:	44 89 d0             	mov    eax,r10d
   1800018e8:	4c 89 da             	mov    rdx,r11
   1800018eb:	ee                   	out    dx,al
   1800018ec:	44 89 c0             	mov    eax,r8d
   1800018ef:	4c 89 ca             	mov    rdx,r9
   1800018f2:	ee                   	out    dx,al
   1800018f3:	b8 c7 ff ff ff       	mov    eax,0xffffffc7
   1800018f8:	ba fa 03 00 00       	mov    edx,0x3fa
   1800018fd:	ee                   	out    dx,al
   1800018fe:	ba fc 03 00 00       	mov    edx,0x3fc
   180001903:	b8 0b 00 00 00       	mov    eax,0xb
   180001908:	ee                   	out    dx,al
   180001909:	b8 1e 00 00 00       	mov    eax,0x1e
   18000190e:	ee                   	out    dx,al
   18000190f:	b8 4d 00 00 00       	mov    eax,0x4d
   180001914:	48 89 ca             	mov    rdx,rcx
   180001917:	ee                   	out    dx,al
   180001918:	ec                   	in     al,dx
   180001919:	3c 4d                	cmp    al,0x4d
   18000191b:	74 1b                	je     180001938 <init_com1+0x88>
   18000191d:	48 8b 05 bc 1a 00 00 	mov    rax,QWORD PTR [rip+0x1abc]        # 1800033e0 <.refptr.ST>
   180001924:	45 31 c9             	xor    r9d,r9d
   180001927:	45 31 c0             	xor    r8d,r8d
   18000192a:	31 d2                	xor    edx,edx
   18000192c:	31 c9                	xor    ecx,ecx
   18000192e:	48 8b 00             	mov    rax,QWORD PTR [rax]
   180001931:	48 8b 40 58          	mov    rax,QWORD PTR [rax+0x58]
   180001935:	ff 50 68             	call   QWORD PTR [rax+0x68]
   180001938:	b8 0f 00 00 00       	mov    eax,0xf
   18000193d:	ba fc 03 00 00       	mov    edx,0x3fc
   180001942:	ee                   	out    dx,al
   180001943:	48 83 c4 28          	add    rsp,0x28
   180001947:	c3                   	ret    
   180001948:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   18000194f:	00 

0000000180001950 <write_com1>:
   180001950:	ba f8 03 00 00       	mov    edx,0x3f8
   180001955:	89 c8                	mov    eax,ecx
   180001957:	ee                   	out    dx,al
   180001958:	c3                   	ret    
   180001959:	90                   	nop
   18000195a:	90                   	nop
   18000195b:	90                   	nop
   18000195c:	90                   	nop
   18000195d:	90                   	nop
   18000195e:	90                   	nop
   18000195f:	90                   	nop

0000000180001960 <traslate_map>:
   180001960:	41 55                	push   r13
   180001962:	41 54                	push   r12
   180001964:	55                   	push   rbp
   180001965:	57                   	push   rdi
   180001966:	56                   	push   rsi
   180001967:	53                   	push   rbx
   180001968:	31 f6                	xor    esi,esi
   18000196a:	45 31 d2             	xor    r10d,r10d
   18000196d:	31 db                	xor    ebx,ebx
   18000196f:	45 31 e4             	xor    r12d,r12d
   180001972:	4c 8d 1d 77 19 00 00 	lea    r11,[rip+0x1977]        # 1800032f0 <.rdata>
   180001979:	48 89 d0             	mov    rax,rdx
   18000197c:	31 d2                	xor    edx,edx
   18000197e:	49 f7 f0             	div    r8
   180001981:	8d 78 01             	lea    edi,[rax+0x1]
   180001984:	48 8d 68 ff          	lea    rbp,[rax-0x1]
   180001988:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   18000198f:	00 
   180001990:	48 8b 41 18          	mov    rax,QWORD PTR [rcx+0x18]
   180001994:	4c 8b 49 08          	mov    r9,QWORD PTR [rcx+0x8]
   180001998:	48 c1 e0 0c          	shl    rax,0xc
   18000199c:	83 39 0e             	cmp    DWORD PTR [rcx],0xe
   18000199f:	0f 87 13 01 00 00    	ja     180001ab8 <traslate_map+0x158>
   1800019a5:	8b 11                	mov    edx,DWORD PTR [rcx]
   1800019a7:	49 63 14 93          	movsxd rdx,DWORD PTR [r11+rdx*4]
   1800019ab:	4c 01 da             	add    rdx,r11
   1800019ae:	ff e2                	jmp    rdx
   1800019b0:	4c 01 c8             	add    rax,r9
   1800019b3:	66 49 0f 6e c1       	movq   xmm0,r9
   1800019b8:	66 48 0f 6e d0       	movq   xmm2,rax
   1800019bd:	66 0f 6c c2          	punpcklqdq xmm0,xmm2
   1800019c1:	83 fb 01             	cmp    ebx,0x1
   1800019c4:	0f 84 1e 02 00 00    	je     180001be8 <traslate_map+0x288>
   1800019ca:	44 89 d0             	mov    eax,r10d
   1800019cd:	bb 01 00 00 00       	mov    ebx,0x1
   1800019d2:	29 f0                	sub    eax,esi
   1800019d4:	83 c0 01             	add    eax,0x1
   1800019d7:	48 98                	cdqe   
   1800019d9:	48 8d 04 40          	lea    rax,[rax+rax*2]
   1800019dd:	c7 04 c5 00 80 00 00 	mov    DWORD PTR [rax*8+0x8000],0x1
   1800019e4:	01 00 00 00 
   1800019e8:	0f 11 04 c5 08 80 00 	movups XMMWORD PTR [rax*8+0x8008],xmm0
   1800019ef:	00 
   1800019f0:	41 83 c2 01          	add    r10d,0x1
   1800019f4:	4c 01 c1             	add    rcx,r8
   1800019f7:	44 39 d7             	cmp    edi,r10d
   1800019fa:	75 94                	jne    180001990 <traslate_map+0x30>
   1800019fc:	c7 04 25 00 80 00 00 	mov    DWORD PTR ds:0x8000,0x0
   180001a03:	00 00 00 00 
   180001a07:	48 89 2c 25 08 80 00 	mov    QWORD PTR ds:0x8008,rbp
   180001a0e:	00 
   180001a0f:	4c 89 24 25 10 80 00 	mov    QWORD PTR ds:0x8010,r12
   180001a16:	00 
   180001a17:	5b                   	pop    rbx
   180001a18:	5e                   	pop    rsi
   180001a19:	5f                   	pop    rdi
   180001a1a:	5d                   	pop    rbp
   180001a1b:	41 5c                	pop    r12
   180001a1d:	41 5d                	pop    r13
   180001a1f:	c3                   	ret    
   180001a20:	44 89 d2             	mov    edx,r10d
   180001a23:	4c 01 c8             	add    rax,r9
   180001a26:	66 49 0f 6e c1       	movq   xmm0,r9
   180001a2b:	29 f2                	sub    edx,esi
   180001a2d:	66 48 0f 6e e0       	movq   xmm4,rax
   180001a32:	83 c2 01             	add    edx,0x1
   180001a35:	66 0f 6c c4          	punpcklqdq xmm0,xmm4
   180001a39:	48 63 d2             	movsxd rdx,edx
   180001a3c:	48 8d 14 52          	lea    rdx,[rdx+rdx*2]
   180001a40:	4c 8d 2c d5 00 80 00 	lea    r13,[rdx*8+0x8000]
   180001a47:	00 
   180001a48:	83 fb 0d             	cmp    ebx,0xd
   180001a4b:	0f 84 bf 01 00 00    	je     180001c10 <traslate_map+0x2b0>
   180001a51:	c7 04 d5 00 80 00 00 	mov    DWORD PTR [rdx*8+0x8000],0xd
   180001a58:	0d 00 00 00 
   180001a5c:	bb 0d 00 00 00       	mov    ebx,0xd
   180001a61:	41 0f 11 45 08       	movups XMMWORD PTR [r13+0x8],xmm0
   180001a66:	eb 88                	jmp    1800019f0 <traslate_map+0x90>
   180001a68:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
   180001a6f:	00 
   180001a70:	4c 01 c8             	add    rax,r9
   180001a73:	66 49 0f 6e c1       	movq   xmm0,r9
   180001a78:	66 48 0f 6e c8       	movq   xmm1,rax
   180001a7d:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
   180001a81:	83 fb 04             	cmp    ebx,0x4
   180001a84:	0f 84 5e 01 00 00    	je     180001be8 <traslate_map+0x288>
   180001a8a:	44 89 d0             	mov    eax,r10d
   180001a8d:	bb 04 00 00 00       	mov    ebx,0x4
   180001a92:	29 f0                	sub    eax,esi
   180001a94:	83 c0 01             	add    eax,0x1
   180001a97:	48 98                	cdqe   
   180001a99:	48 8d 04 40          	lea    rax,[rax+rax*2]
   180001a9d:	c7 04 c5 00 80 00 00 	mov    DWORD PTR [rax*8+0x8000],0x4
   180001aa4:	04 00 00 00 
   180001aa8:	0f 11 04 c5 08 80 00 	movups XMMWORD PTR [rax*8+0x8008],xmm0
   180001aaf:	00 
   180001ab0:	e9 3b ff ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001ab5:	0f 1f 00             	nop    DWORD PTR [rax]
   180001ab8:	4c 01 c8             	add    rax,r9
   180001abb:	66 49 0f 6e c1       	movq   xmm0,r9
   180001ac0:	66 48 0f 6e c8       	movq   xmm1,rax
   180001ac5:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
   180001ac9:	83 fb 02             	cmp    ebx,0x2
   180001acc:	0f 84 16 01 00 00    	je     180001be8 <traslate_map+0x288>
   180001ad2:	44 89 d0             	mov    eax,r10d
   180001ad5:	bb 02 00 00 00       	mov    ebx,0x2
   180001ada:	29 f0                	sub    eax,esi
   180001adc:	83 c0 01             	add    eax,0x1
   180001adf:	48 98                	cdqe   
   180001ae1:	48 8d 04 40          	lea    rax,[rax+rax*2]
   180001ae5:	c7 04 c5 00 80 00 00 	mov    DWORD PTR [rax*8+0x8000],0x2
   180001aec:	02 00 00 00 
   180001af0:	0f 11 04 c5 08 80 00 	movups XMMWORD PTR [rax*8+0x8008],xmm0
   180001af7:	00 
   180001af8:	e9 f3 fe ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001afd:	0f 1f 00             	nop    DWORD PTR [rax]
   180001b00:	83 fb 06             	cmp    ebx,0x6
   180001b03:	0f 84 3f 01 00 00    	je     180001c48 <traslate_map+0x2e8>
   180001b09:	44 89 d2             	mov    edx,r10d
   180001b0c:	4c 01 c8             	add    rax,r9
   180001b0f:	66 49 0f 6e c1       	movq   xmm0,r9
   180001b14:	bb 06 00 00 00       	mov    ebx,0x6
   180001b19:	29 f2                	sub    edx,esi
   180001b1b:	66 48 0f 6e d0       	movq   xmm2,rax
   180001b20:	83 c2 01             	add    edx,0x1
   180001b23:	66 0f 6c c2          	punpcklqdq xmm0,xmm2
   180001b27:	48 63 d2             	movsxd rdx,edx
   180001b2a:	48 8d 14 52          	lea    rdx,[rdx+rdx*2]
   180001b2e:	c7 04 d5 00 80 00 00 	mov    DWORD PTR [rdx*8+0x8000],0x6
   180001b35:	06 00 00 00 
   180001b39:	0f 11 04 d5 08 80 00 	movups XMMWORD PTR [rdx*8+0x8008],xmm0
   180001b40:	00 
   180001b41:	e9 aa fe ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001b46:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   180001b4d:	00 00 00 
   180001b50:	4d 8d 24 01          	lea    r12,[r9+rax*1]
   180001b54:	66 49 0f 6e c1       	movq   xmm0,r9
   180001b59:	66 49 0f 6e ec       	movq   xmm5,r12
   180001b5e:	66 0f 6c c5          	punpcklqdq xmm0,xmm5
   180001b62:	83 fb 03             	cmp    ebx,0x3
   180001b65:	0f 84 b5 00 00 00    	je     180001c20 <traslate_map+0x2c0>
   180001b6b:	44 89 d0             	mov    eax,r10d
   180001b6e:	29 f0                	sub    eax,esi
   180001b70:	83 c0 01             	add    eax,0x1
   180001b73:	48 98                	cdqe   
   180001b75:	48 8d 04 40          	lea    rax,[rax+rax*2]
   180001b79:	c7 04 c5 00 80 00 00 	mov    DWORD PTR [rax*8+0x8000],0x3
   180001b80:	03 00 00 00 
   180001b84:	0f 11 04 c5 08 80 00 	movups XMMWORD PTR [rax*8+0x8008],xmm0
   180001b8b:	00 
   180001b8c:	bb 03 00 00 00       	mov    ebx,0x3
   180001b91:	e9 5a fe ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001b96:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   180001b9d:	00 00 00 
   180001ba0:	4c 01 c8             	add    rax,r9
   180001ba3:	66 49 0f 6e c1       	movq   xmm0,r9
   180001ba8:	66 48 0f 6e d8       	movq   xmm3,rax
   180001bad:	66 0f 6c c3          	punpcklqdq xmm0,xmm3
   180001bb1:	83 fb 05             	cmp    ebx,0x5
   180001bb4:	74 32                	je     180001be8 <traslate_map+0x288>
   180001bb6:	44 89 d0             	mov    eax,r10d
   180001bb9:	bb 05 00 00 00       	mov    ebx,0x5
   180001bbe:	29 f0                	sub    eax,esi
   180001bc0:	83 c0 01             	add    eax,0x1
   180001bc3:	48 98                	cdqe   
   180001bc5:	48 8d 04 40          	lea    rax,[rax+rax*2]
   180001bc9:	c7 04 c5 00 80 00 00 	mov    DWORD PTR [rax*8+0x8000],0x5
   180001bd0:	05 00 00 00 
   180001bd4:	0f 11 04 c5 08 80 00 	movups XMMWORD PTR [rax*8+0x8008],xmm0
   180001bdb:	00 
   180001bdc:	e9 0f fe ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001be1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001be8:	83 c6 01             	add    esi,0x1
   180001beb:	44 89 d2             	mov    edx,r10d
   180001bee:	48 83 ed 01          	sub    rbp,0x1
   180001bf2:	29 f2                	sub    edx,esi
   180001bf4:	83 c2 01             	add    edx,0x1
   180001bf7:	48 63 d2             	movsxd rdx,edx
   180001bfa:	48 8d 14 52          	lea    rdx,[rdx+rdx*2]
   180001bfe:	48 89 04 d5 10 80 00 	mov    QWORD PTR [rdx*8+0x8010],rax
   180001c05:	00 
   180001c06:	e9 e5 fd ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001c0b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   180001c10:	49 89 45 10          	mov    QWORD PTR [r13+0x10],rax
   180001c14:	83 c6 01             	add    esi,0x1
   180001c17:	e9 d4 fd ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001c1c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   180001c20:	83 c6 01             	add    esi,0x1
   180001c23:	44 89 d0             	mov    eax,r10d
   180001c26:	48 83 ed 01          	sub    rbp,0x1
   180001c2a:	29 f0                	sub    eax,esi
   180001c2c:	83 c0 01             	add    eax,0x1
   180001c2f:	48 98                	cdqe   
   180001c31:	48 8d 04 40          	lea    rax,[rax+rax*2]
   180001c35:	4c 89 24 c5 10 80 00 	mov    QWORD PTR [rax*8+0x8010],r12
   180001c3c:	00 
   180001c3d:	e9 4a ff ff ff       	jmp    180001b8c <traslate_map+0x22c>
   180001c42:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   180001c48:	83 c6 01             	add    esi,0x1
   180001c4b:	44 89 d2             	mov    edx,r10d
   180001c4e:	4c 01 c8             	add    rax,r9
   180001c51:	48 83 ed 01          	sub    rbp,0x1
   180001c55:	29 f2                	sub    edx,esi
   180001c57:	83 c2 01             	add    edx,0x1
   180001c5a:	48 63 d2             	movsxd rdx,edx
   180001c5d:	48 8d 14 52          	lea    rdx,[rdx+rdx*2]
   180001c61:	48 89 04 d5 10 80 00 	mov    QWORD PTR [rdx*8+0x8010],rax
   180001c68:	00 
   180001c69:	e9 82 fd ff ff       	jmp    1800019f0 <traslate_map+0x90>
   180001c6e:	66 90                	xchg   ax,ax

0000000180001c70 <fetch_memory_map>:
   180001c70:	41 55                	push   r13
   180001c72:	41 54                	push   r12
   180001c74:	55                   	push   rbp
   180001c75:	57                   	push   rdi
   180001c76:	56                   	push   rsi
   180001c77:	53                   	push   rbx
   180001c78:	48 81 ec 28 01 00 00 	sub    rsp,0x128
   180001c7f:	48 8b 1d 5a 17 00 00 	mov    rbx,QWORD PTR [rip+0x175a]        # 1800033e0 <.refptr.ST>
   180001c86:	45 31 c9             	xor    r9d,r9d
   180001c89:	48 8b 03             	mov    rax,QWORD PTR [rbx]
   180001c8c:	48 8b 40 60          	mov    rax,QWORD PTR [rax+0x60]
   180001c90:	48 8d 6c 24 70       	lea    rbp,[rsp+0x70]
   180001c95:	4c 8d 6c 24 68       	lea    r13,[rsp+0x68]
   180001c9a:	49 89 cc             	mov    r12,rcx
   180001c9d:	48 89 d6             	mov    rsi,rdx
   180001ca0:	4c 89 e9             	mov    rcx,r13
   180001ca3:	48 8b 54 24 60       	mov    rdx,QWORD PTR [rsp+0x60]
   180001ca8:	4c 89 c7             	mov    rdi,r8
   180001cab:	49 89 e8             	mov    r8,rbp
   180001cae:	48 c7 44 24 68 08 00 	mov    QWORD PTR [rsp+0x68],0x8
   180001cb5:	00 00 
   180001cb7:	48 c7 44 24 20 00 00 	mov    QWORD PTR [rsp+0x20],0x0
   180001cbe:	00 00 
   180001cc0:	ff 50 38             	call   QWORD PTR [rax+0x38]
   180001cc3:	48 8b 44 24 68       	mov    rax,QWORD PTR [rsp+0x68]
   180001cc8:	4c 8d 44 24 60       	lea    r8,[rsp+0x60]
   180001ccd:	b9 02 00 00 00       	mov    ecx,0x2
   180001cd2:	48 8d 50 50          	lea    rdx,[rax+0x50]
   180001cd6:	48 8b 03             	mov    rax,QWORD PTR [rbx]
   180001cd9:	48 89 54 24 68       	mov    QWORD PTR [rsp+0x68],rdx
   180001cde:	48 8b 40 60          	mov    rax,QWORD PTR [rax+0x60]
   180001ce2:	ff 50 40             	call   QWORD PTR [rax+0x40]
   180001ce5:	48 8b 03             	mov    rax,QWORD PTR [rbx]
   180001ce8:	48 8d 54 24 5c       	lea    rdx,[rsp+0x5c]
   180001ced:	4c 8d 4c 24 78       	lea    r9,[rsp+0x78]
   180001cf2:	49 89 e8             	mov    r8,rbp
   180001cf5:	4c 89 e9             	mov    rcx,r13
   180001cf8:	48 8b 40 60          	mov    rax,QWORD PTR [rax+0x60]
   180001cfc:	48 89 54 24 20       	mov    QWORD PTR [rsp+0x20],rdx
   180001d01:	48 8b 54 24 60       	mov    rdx,QWORD PTR [rsp+0x60]
   180001d06:	ff 50 38             	call   QWORD PTR [rax+0x38]
   180001d09:	48 8b 03             	mov    rax,QWORD PTR [rbx]
   180001d0c:	48 8b 54 24 70       	mov    rdx,QWORD PTR [rsp+0x70]
   180001d11:	4c 89 e1             	mov    rcx,r12
   180001d14:	48 8b 40 60          	mov    rax,QWORD PTR [rax+0x60]
   180001d18:	ff 90 e8 00 00 00    	call   QWORD PTR [rax+0xe8]
   180001d1e:	4c 8b 44 24 78       	mov    r8,QWORD PTR [rsp+0x78]
   180001d23:	48 8b 54 24 68       	mov    rdx,QWORD PTR [rsp+0x68]
   180001d28:	48 8b 4c 24 60       	mov    rcx,QWORD PTR [rsp+0x60]
   180001d2d:	e8 2e fc ff ff       	call   180001960 <traslate_map>
   180001d32:	83 3c 25 18 80 00 00 	cmp    DWORD PTR ds:0x8018,0x1
   180001d39:	01 
   180001d3a:	75 0e                	jne    180001d4a <fetch_memory_map+0xda>
   180001d3c:	48 81 3c 25 28 80 00 	cmp    QWORD PTR ds:0x8028,0x24ffff
   180001d43:	00 ff ff 24 00 
   180001d48:	77 26                	ja     180001d70 <fetch_memory_map+0x100>
   180001d4a:	48 8d 0d df 15 00 00 	lea    rcx,[rip+0x15df]        # 180003330 <.rdata+0x40>
   180001d51:	e8 3a f7 ff ff       	call   180001490 <print_string>
   180001d56:	b8 01 00 00 00       	mov    eax,0x1
   180001d5b:	48 81 c4 28 01 00 00 	add    rsp,0x128
   180001d62:	5b                   	pop    rbx
   180001d63:	5e                   	pop    rsi
   180001d64:	5f                   	pop    rdi
   180001d65:	5d                   	pop    rbp
   180001d66:	41 5c                	pop    r12
   180001d68:	41 5d                	pop    r13
   180001d6a:	c3                   	ret    
   180001d6b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
   180001d70:	66 0f 6f 05 18 16 00 	movdqa xmm0,XMMWORD PTR [rip+0x1618]        # 180003390 <.rdata+0xa0>
   180001d77:	00 
   180001d78:	48 01 f7             	add    rdi,rsi
   180001d7b:	4c 8d 64 24 30       	lea    r12,[rsp+0x30]
   180001d80:	c7 84 24 80 00 00 00 	mov    DWORD PTR [rsp+0x80],0x9
   180001d87:	09 00 00 00 
   180001d8b:	66 48 0f 6e cf       	movq   xmm1,rdi
   180001d90:	4c 89 e1             	mov    rcx,r12
   180001d93:	c7 84 24 a0 00 00 00 	mov    DWORD PTR [rsp+0xa0],0x8
   180001d9a:	08 00 00 00 
   180001d9e:	0f 11 84 24 88 00 00 	movups XMMWORD PTR [rsp+0x88],xmm0
   180001da5:	00 
   180001da6:	66 0f 6f 05 f2 15 00 	movdqa xmm0,XMMWORD PTR [rip+0x15f2]        # 1800033a0 <.rdata+0xb0>
   180001dad:	00 
   180001dae:	66 0f 6f 94 24 80 00 	movdqa xmm2,XMMWORD PTR [rsp+0x80]
   180001db5:	00 00 
   180001db7:	48 8b 84 24 90 00 00 	mov    rax,QWORD PTR [rsp+0x90]
   180001dbe:	00 
   180001dbf:	c7 84 24 c0 00 00 00 	mov    DWORD PTR [rsp+0xc0],0x9
   180001dc6:	09 00 00 00 
   180001dca:	0f 11 84 24 a8 00 00 	movups XMMWORD PTR [rsp+0xa8],xmm0
   180001dd1:	00 
   180001dd2:	66 0f 6f 05 d6 15 00 	movdqa xmm0,XMMWORD PTR [rip+0x15d6]        # 1800033b0 <.rdata+0xc0>
   180001dd9:	00 
   180001dda:	0f 29 54 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm2
   180001ddf:	0f 11 84 24 c8 00 00 	movups XMMWORD PTR [rsp+0xc8],xmm0
   180001de6:	00 
   180001de7:	66 0f 6f 05 d1 15 00 	movdqa xmm0,XMMWORD PTR [rip+0x15d1]        # 1800033c0 <.rdata+0xd0>
   180001dee:	00 
   180001def:	c7 84 24 e0 00 00 00 	mov    DWORD PTR [rsp+0xe0],0x8
   180001df6:	08 00 00 00 
   180001dfa:	0f 11 84 24 e8 00 00 	movups XMMWORD PTR [rsp+0xe8],xmm0
   180001e01:	00 
   180001e02:	66 48 0f 6e c6       	movq   xmm0,rsi
   180001e07:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
   180001e0b:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
   180001e10:	0f 11 84 24 08 01 00 	movups XMMWORD PTR [rsp+0x108],xmm0
   180001e17:	00 
   180001e18:	c7 84 24 00 01 00 00 	mov    DWORD PTR [rsp+0x100],0x7
   180001e1f:	07 00 00 00 
   180001e23:	e8 a8 01 00 00       	call   180001fd0 <addmap>
   180001e28:	48 8b 84 24 b0 00 00 	mov    rax,QWORD PTR [rsp+0xb0]
   180001e2f:	00 
   180001e30:	4c 89 e1             	mov    rcx,r12
   180001e33:	66 0f 6f 9c 24 a0 00 	movdqa xmm3,XMMWORD PTR [rsp+0xa0]
   180001e3a:	00 00 
   180001e3c:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
   180001e41:	0f 29 5c 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm3
   180001e46:	e8 85 01 00 00       	call   180001fd0 <addmap>
   180001e4b:	48 8b 84 24 d0 00 00 	mov    rax,QWORD PTR [rsp+0xd0]
   180001e52:	00 
   180001e53:	4c 89 e1             	mov    rcx,r12
   180001e56:	66 0f 6f a4 24 c0 00 	movdqa xmm4,XMMWORD PTR [rsp+0xc0]
   180001e5d:	00 00 
   180001e5f:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
   180001e64:	0f 29 64 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm4
   180001e69:	e8 62 01 00 00       	call   180001fd0 <addmap>
   180001e6e:	48 8b 84 24 f0 00 00 	mov    rax,QWORD PTR [rsp+0xf0]
   180001e75:	00 
   180001e76:	4c 89 e1             	mov    rcx,r12
   180001e79:	66 0f 6f ac 24 e0 00 	movdqa xmm5,XMMWORD PTR [rsp+0xe0]
   180001e80:	00 00 
   180001e82:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
   180001e87:	0f 29 6c 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm5
   180001e8c:	e8 3f 01 00 00       	call   180001fd0 <addmap>
   180001e91:	48 8b 84 24 10 01 00 	mov    rax,QWORD PTR [rsp+0x110]
   180001e98:	00 
   180001e99:	4c 89 e1             	mov    rcx,r12
   180001e9c:	66 0f 6f 8c 24 00 01 	movdqa xmm1,XMMWORD PTR [rsp+0x100]
   180001ea3:	00 00 
   180001ea5:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
   180001eaa:	0f 29 4c 24 30       	movaps XMMWORD PTR [rsp+0x30],xmm1
   180001eaf:	e8 1c 01 00 00       	call   180001fd0 <addmap>
   180001eb4:	31 c0                	xor    eax,eax
   180001eb6:	48 81 c4 28 01 00 00 	add    rsp,0x128
   180001ebd:	5b                   	pop    rbx
   180001ebe:	5e                   	pop    rsi
   180001ebf:	5f                   	pop    rdi
   180001ec0:	5d                   	pop    rbp
   180001ec1:	41 5c                	pop    r12
   180001ec3:	41 5d                	pop    r13
   180001ec5:	c3                   	ret    
   180001ec6:	90                   	nop
   180001ec7:	90                   	nop
   180001ec8:	90                   	nop
   180001ec9:	90                   	nop
   180001eca:	90                   	nop
   180001ecb:	90                   	nop
   180001ecc:	90                   	nop
   180001ecd:	90                   	nop
   180001ece:	90                   	nop
   180001ecf:	90                   	nop

0000000180001ed0 <splitmap>:
   180001ed0:	45 84 c0             	test   r8b,r8b
   180001ed3:	75 4b                	jne    180001f20 <splitmap+0x50>
   180001ed5:	48 8d 42 02          	lea    rax,[rdx+0x2]
   180001ed9:	48 89 04 25 08 80 00 	mov    QWORD PTR ds:0x8008,rax
   180001ee0:	00 
   180001ee1:	48 39 c1             	cmp    rcx,rax
   180001ee4:	73 33                	jae    180001f19 <splitmap+0x49>
   180001ee6:	48 8d 04 52          	lea    rax,[rdx+rdx*2]
   180001eea:	48 8d 14 49          	lea    rdx,[rcx+rcx*2]
   180001eee:	48 8d 04 c5 00 80 00 	lea    rax,[rax*8+0x8000]
   180001ef5:	00 
   180001ef6:	48 8d 0c d5 d0 7f 00 	lea    rcx,[rdx*8+0x7fd0]
   180001efd:	00 
   180001efe:	66 90                	xchg   ax,ax
   180001f00:	f3 0f 6f 00          	movdqu xmm0,XMMWORD PTR [rax]
   180001f04:	48 8b 50 10          	mov    rdx,QWORD PTR [rax+0x10]
   180001f08:	48 83 e8 18          	sub    rax,0x18
   180001f0c:	0f 11 40 48          	movups XMMWORD PTR [rax+0x48],xmm0
   180001f10:	48 89 50 58          	mov    QWORD PTR [rax+0x58],rdx
   180001f14:	48 39 c1             	cmp    rcx,rax
   180001f17:	75 e7                	jne    180001f00 <splitmap+0x30>
   180001f19:	c3                   	ret    
   180001f1a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
   180001f20:	41 80 f8 01          	cmp    r8b,0x1
   180001f24:	74 5a                	je     180001f80 <splitmap+0xb0>
   180001f26:	41 80 f8 02          	cmp    r8b,0x2
   180001f2a:	75 ed                	jne    180001f19 <splitmap+0x49>
   180001f2c:	48 83 c2 01          	add    rdx,0x1
   180001f30:	48 8d 41 ff          	lea    rax,[rcx-0x1]
   180001f34:	48 89 14 25 08 80 00 	mov    QWORD PTR ds:0x8008,rdx
   180001f3b:	00 
   180001f3c:	48 39 c2             	cmp    rdx,rax
   180001f3f:	76 d8                	jbe    180001f19 <splitmap+0x49>
   180001f41:	48 8d 04 52          	lea    rax,[rdx+rdx*2]
   180001f45:	48 8d 14 49          	lea    rdx,[rcx+rcx*2]
   180001f49:	48 8d 04 c5 00 80 00 	lea    rax,[rax*8+0x8000]
   180001f50:	00 
   180001f51:	4c 8d 04 d5 e8 7f 00 	lea    r8,[rdx*8+0x7fe8]
   180001f58:	00 
   180001f59:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001f60:	48 89 c2             	mov    rdx,rax
   180001f63:	f3 0f 6f 50 e8       	movdqu xmm2,XMMWORD PTR [rax-0x18]
   180001f68:	48 83 e8 18          	sub    rax,0x18
   180001f6c:	0f 11 12             	movups XMMWORD PTR [rdx],xmm2
   180001f6f:	48 8b 48 10          	mov    rcx,QWORD PTR [rax+0x10]
   180001f73:	48 89 4a 10          	mov    QWORD PTR [rdx+0x10],rcx
   180001f77:	4c 39 c0             	cmp    rax,r8
   180001f7a:	75 e4                	jne    180001f60 <splitmap+0x90>
   180001f7c:	c3                   	ret    
   180001f7d:	0f 1f 00             	nop    DWORD PTR [rax]
   180001f80:	48 83 c2 01          	add    rdx,0x1
   180001f84:	48 89 14 25 08 80 00 	mov    QWORD PTR ds:0x8008,rdx
   180001f8b:	00 
   180001f8c:	48 39 d1             	cmp    rcx,rdx
   180001f8f:	73 88                	jae    180001f19 <splitmap+0x49>
   180001f91:	48 8d 04 52          	lea    rax,[rdx+rdx*2]
   180001f95:	48 8d 14 49          	lea    rdx,[rcx+rcx*2]
   180001f99:	48 8d 04 c5 00 80 00 	lea    rax,[rax*8+0x8000]
   180001fa0:	00 
   180001fa1:	4c 8d 04 d5 00 80 00 	lea    r8,[rdx*8+0x8000]
   180001fa8:	00 
   180001fa9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   180001fb0:	48 89 c2             	mov    rdx,rax
   180001fb3:	f3 0f 6f 48 e8       	movdqu xmm1,XMMWORD PTR [rax-0x18]
   180001fb8:	48 83 e8 18          	sub    rax,0x18
   180001fbc:	0f 11 0a             	movups XMMWORD PTR [rdx],xmm1
   180001fbf:	48 8b 48 10          	mov    rcx,QWORD PTR [rax+0x10]
   180001fc3:	48 89 4a 10          	mov    QWORD PTR [rdx+0x10],rcx
   180001fc7:	49 39 c0             	cmp    r8,rax
   180001fca:	75 e4                	jne    180001fb0 <splitmap+0xe0>
   180001fcc:	c3                   	ret    
   180001fcd:	0f 1f 00             	nop    DWORD PTR [rax]

0000000180001fd0 <addmap>:
   180001fd0:	55                   	push   rbp
   180001fd1:	57                   	push   rdi
   180001fd2:	56                   	push   rsi
   180001fd3:	53                   	push   rbx
   180001fd4:	48 83 ec 28          	sub    rsp,0x28
   180001fd8:	48 8b 14 25 08 80 00 	mov    rdx,QWORD PTR ds:0x8008
   180001fdf:	00 
   180001fe0:	48 89 d0             	mov    rax,rdx
   180001fe3:	4c 8b 59 08          	mov    r11,QWORD PTR [rcx+0x8]
   180001fe7:	48 8b 79 10          	mov    rdi,QWORD PTR [rcx+0x10]
   180001feb:	48 89 ce             	mov    rsi,rcx
   180001fee:	48 83 c0 01          	add    rax,0x1
   180001ff2:	0f 84 47 01 00 00    	je     18000213f <addmap+0x16f>
   180001ff8:	41 b9 18 00 00 00    	mov    r9d,0x18
   180001ffe:	41 ba 01 00 00 00    	mov    r10d,0x1
   180002004:	eb 17                	jmp    18000201d <addmap+0x4d>
   180002006:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   18000200d:	00 00 00 
   180002010:	49 83 c2 01          	add    r10,0x1
   180002014:	49 83 c1 18          	add    r9,0x18
   180002018:	4c 39 d0             	cmp    rax,r10
   18000201b:	72 63                	jb     180002080 <addmap+0xb0>
   18000201d:	49 8d 99 00 80 00 00 	lea    rbx,[r9+0x8000]
   180002024:	4d 39 99 08 80 00 00 	cmp    QWORD PTR [r9+0x8008],r11
   18000202b:	72 e3                	jb     180002010 <addmap+0x40>
   18000202d:	0f 84 7d 00 00 00    	je     1800020b0 <addmap+0xe0>
   180002033:	49 8d a9 e8 7f 00 00 	lea    rbp,[r9+0x7fe8]
   18000203a:	49 39 b9 f8 7f 00 00 	cmp    QWORD PTR [r9+0x7ff8],rdi
   180002041:	0f 84 02 01 00 00    	je     180002149 <addmap+0x179>
   180002047:	41 83 b9 e8 7f 00 00 	cmp    DWORD PTR [r9+0x7fe8],0x1
   18000204e:	01 
   18000204f:	0f 84 9b 00 00 00    	je     1800020f0 <addmap+0x120>
   180002055:	41 b8 02 00 00 00    	mov    r8d,0x2
   18000205b:	4c 89 d1             	mov    rcx,r10
   18000205e:	e8 6d fe ff ff       	call   180001ed0 <splitmap>
   180002063:	48 8b 46 10          	mov    rax,QWORD PTR [rsi+0x10]
   180002067:	f3 0f 6f 0e          	movdqu xmm1,XMMWORD PTR [rsi]
   18000206b:	48 89 43 10          	mov    QWORD PTR [rbx+0x10],rax
   18000206f:	0f 11 0b             	movups XMMWORD PTR [rbx],xmm1
   180002072:	31 c0                	xor    eax,eax
   180002074:	48 83 c4 28          	add    rsp,0x28
   180002078:	5b                   	pop    rbx
   180002079:	5e                   	pop    rsi
   18000207a:	5f                   	pop    rdi
   18000207b:	5d                   	pop    rbp
   18000207c:	c3                   	ret    
   18000207d:	0f 1f 00             	nop    DWORD PTR [rax]
   180002080:	48 8d 14 40          	lea    rdx,[rax+rax*2]
   180002084:	48 8d 14 d5 00 80 00 	lea    rdx,[rdx*8+0x8000]
   18000208b:	00 
   18000208c:	f3 0f 6f 06          	movdqu xmm0,XMMWORD PTR [rsi]
   180002090:	48 8b 4e 10          	mov    rcx,QWORD PTR [rsi+0x10]
   180002094:	0f 11 02             	movups XMMWORD PTR [rdx],xmm0
   180002097:	48 89 4a 10          	mov    QWORD PTR [rdx+0x10],rcx
   18000209b:	48 89 04 25 08 80 00 	mov    QWORD PTR ds:0x8008,rax
   1800020a2:	00 
   1800020a3:	48 83 c4 28          	add    rsp,0x28
   1800020a7:	5b                   	pop    rbx
   1800020a8:	5e                   	pop    rsi
   1800020a9:	5f                   	pop    rdi
   1800020aa:	5d                   	pop    rbp
   1800020ab:	c3                   	ret    
   1800020ac:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
   1800020b0:	48 39 7b 10          	cmp    QWORD PTR [rbx+0x10],rdi
   1800020b4:	0f 84 b5 00 00 00    	je     18000216f <addmap+0x19f>
   1800020ba:	41 b8 01 00 00 00    	mov    r8d,0x1
   1800020c0:	4c 89 d1             	mov    rcx,r10
   1800020c3:	e8 08 fe ff ff       	call   180001ed0 <splitmap>
   1800020c8:	48 8b 46 10          	mov    rax,QWORD PTR [rsi+0x10]
   1800020cc:	f3 0f 6f 1e          	movdqu xmm3,XMMWORD PTR [rsi]
   1800020d0:	48 89 43 10          	mov    QWORD PTR [rbx+0x10],rax
   1800020d4:	4b 8d 44 52 03       	lea    rax,[r10+r10*2+0x3]
   1800020d9:	0f 11 1b             	movups XMMWORD PTR [rbx],xmm3
   1800020dc:	48 89 3c c5 08 80 00 	mov    QWORD PTR [rax*8+0x8008],rdi
   1800020e3:	00 
   1800020e4:	eb 8c                	jmp    180002072 <addmap+0xa2>
   1800020e6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
   1800020ed:	00 00 00 
   1800020f0:	45 31 c0             	xor    r8d,r8d
   1800020f3:	4c 89 d1             	mov    rcx,r10
   1800020f6:	e8 d5 fd ff ff       	call   180001ed0 <splitmap>
   1800020fb:	48 8b 46 10          	mov    rax,QWORD PTR [rsi+0x10]
   1800020ff:	4c 89 5d 10          	mov    QWORD PTR [rbp+0x10],r11
   180002103:	f3 0f 6f 16          	movdqu xmm2,XMMWORD PTR [rsi]
   180002107:	48 89 43 10          	mov    QWORD PTR [rbx+0x10],rax
   18000210b:	4b 8d 44 52 03       	lea    rax,[r10+r10*2+0x3]
   180002110:	48 c1 e0 03          	shl    rax,0x3
   180002114:	0f 11 13             	movups XMMWORD PTR [rbx],xmm2
   180002117:	48 8d 90 00 80 00 00 	lea    rdx,[rax+0x8000]
   18000211e:	48 89 b8 08 80 00 00 	mov    QWORD PTR [rax+0x8008],rdi
   180002125:	c7 80 00 80 00 00 01 	mov    DWORD PTR [rax+0x8000],0x1
   18000212c:	00 00 00 
   18000212f:	49 8b 81 38 80 00 00 	mov    rax,QWORD PTR [r9+0x8038]
   180002136:	48 89 42 10          	mov    QWORD PTR [rdx+0x10],rax
   18000213a:	e9 33 ff ff ff       	jmp    180002072 <addmap+0xa2>
   18000213f:	ba 00 80 00 00       	mov    edx,0x8000
   180002144:	e9 43 ff ff ff       	jmp    18000208c <addmap+0xbc>
   180002149:	41 b8 02 00 00 00    	mov    r8d,0x2
   18000214f:	4c 89 d1             	mov    rcx,r10
   180002152:	e8 79 fd ff ff       	call   180001ed0 <splitmap>
   180002157:	f3 0f 6f 26          	movdqu xmm4,XMMWORD PTR [rsi]
   18000215b:	48 8b 46 10          	mov    rax,QWORD PTR [rsi+0x10]
   18000215f:	0f 11 23             	movups XMMWORD PTR [rbx],xmm4
   180002162:	48 89 43 10          	mov    QWORD PTR [rbx+0x10],rax
   180002166:	4c 89 5d 10          	mov    QWORD PTR [rbp+0x10],r11
   18000216a:	e9 03 ff ff ff       	jmp    180002072 <addmap+0xa2>
   18000216f:	f3 0f 6f 2e          	movdqu xmm5,XMMWORD PTR [rsi]
   180002173:	48 8b 46 10          	mov    rax,QWORD PTR [rsi+0x10]
   180002177:	0f 11 2b             	movups XMMWORD PTR [rbx],xmm5
   18000217a:	48 89 43 10          	mov    QWORD PTR [rbx+0x10],rax
   18000217e:	e9 ef fe ff ff       	jmp    180002072 <addmap+0xa2>
   180002183:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
   18000218a:	00 00 00 00 
   18000218e:	66 90                	xchg   ax,ax

0000000180002190 <mapalloc>:
   180002190:	56                   	push   rsi
   180002191:	53                   	push   rbx
   180002192:	48 83 ec 68          	sub    rsp,0x68
   180002196:	48 8b 1c 25 08 80 00 	mov    rbx,QWORD PTR ds:0x8008
   18000219d:	00 
   18000219e:	48 83 c3 01          	add    rbx,0x1
   1800021a2:	74 39                	je     1800021dd <mapalloc+0x4d>
   1800021a4:	48 8b 32             	mov    rsi,QWORD PTR [rdx]
   1800021a7:	b8 18 80 00 00       	mov    eax,0x8018
   1800021ac:	b9 01 00 00 00       	mov    ecx,0x1
   1800021b1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1800021b8:	4c 8b 50 10          	mov    r10,QWORD PTR [rax+0x10]
   1800021bc:	4c 8b 48 08          	mov    r9,QWORD PTR [rax+0x8]
   1800021c0:	4d 89 d3             	mov    r11,r10
   1800021c3:	4d 29 cb             	sub    r11,r9
   1800021c6:	49 39 f3             	cmp    r11,rsi
   1800021c9:	72 05                	jb     1800021d0 <mapalloc+0x40>
   1800021cb:	83 38 01             	cmp    DWORD PTR [rax],0x1
   1800021ce:	74 20                	je     1800021f0 <mapalloc+0x60>
   1800021d0:	48 83 c1 01          	add    rcx,0x1
   1800021d4:	48 83 c0 18          	add    rax,0x18
   1800021d8:	48 39 cb             	cmp    rbx,rcx
   1800021db:	73 db                	jae    1800021b8 <mapalloc+0x28>
   1800021dd:	b8 01 00 00 00       	mov    eax,0x1
   1800021e2:	48 83 c4 68          	add    rsp,0x68
   1800021e6:	5b                   	pop    rbx
   1800021e7:	5e                   	pop    rsi
   1800021e8:	c3                   	ret    
   1800021e9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
   1800021f0:	49 8d 83 00 c0 ff ff 	lea    rax,[r11-0x4000]
   1800021f7:	44 89 44 24 40       	mov    DWORD PTR [rsp+0x40],r8d
   1800021fc:	48 39 c6             	cmp    rsi,rax
   1800021ff:	73 3f                	jae    180002240 <mapalloc+0xb0>
   180002201:	4d 8d 14 31          	lea    r10,[r9+rsi*1]
   180002205:	66 49 0f 6e c1       	movq   xmm0,r9
   18000220a:	66 49 0f 6e ca       	movq   xmm1,r10
   18000220f:	48 8d 4c 24 20       	lea    rcx,[rsp+0x20]
   180002214:	66 0f 6c c1          	punpcklqdq xmm0,xmm1
   180002218:	0f 11 44 24 48       	movups XMMWORD PTR [rsp+0x48],xmm0
   18000221d:	66 0f 6f 54 24 40    	movdqa xmm2,XMMWORD PTR [rsp+0x40]
   180002223:	48 8b 44 24 50       	mov    rax,QWORD PTR [rsp+0x50]
   180002228:	0f 29 54 24 20       	movaps XMMWORD PTR [rsp+0x20],xmm2
   18000222d:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
   180002232:	e8 99 fd ff ff       	call   180001fd0 <addmap>
   180002237:	31 c0                	xor    eax,eax
   180002239:	48 83 c4 68          	add    rsp,0x68
   18000223d:	5b                   	pop    rbx
   18000223e:	5e                   	pop    rsi
   18000223f:	c3                   	ret    
   180002240:	4c 89 1a             	mov    QWORD PTR [rdx],r11
   180002243:	eb c0                	jmp    180002205 <mapalloc+0x75>
   180002245:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
   18000224c:	00 00 00 00 

0000000180002250 <mapfree>:
   180002250:	c3                   	ret    
   180002251:	90                   	nop
   180002252:	90                   	nop
   180002253:	90                   	nop
   180002254:	90                   	nop
   180002255:	90                   	nop
   180002256:	90                   	nop
   180002257:	90                   	nop
   180002258:	90                   	nop
   180002259:	90                   	nop
   18000225a:	90                   	nop
   18000225b:	90                   	nop
   18000225c:	90                   	nop
   18000225d:	90                   	nop
   18000225e:	90                   	nop
   18000225f:	90                   	nop

0000000180002260 <__CTOR_LIST__>:
   180002260:	ff                   	(bad)  
   180002261:	ff                   	(bad)  
   180002262:	ff                   	(bad)  
   180002263:	ff                   	(bad)  
   180002264:	ff                   	(bad)  
   180002265:	ff                   	(bad)  
   180002266:	ff                   	(bad)  
   180002267:	ff 00                	inc    DWORD PTR [rax]
   180002269:	00 00                	add    BYTE PTR [rax],al
   18000226b:	00 00                	add    BYTE PTR [rax],al
   18000226d:	00 00                	add    BYTE PTR [rax],al
	...

0000000180002270 <__DTOR_LIST__>:
   180002270:	ff                   	(bad)  
   180002271:	ff                   	(bad)  
   180002272:	ff                   	(bad)  
   180002273:	ff                   	(bad)  
   180002274:	ff                   	(bad)  
   180002275:	ff                   	(bad)  
   180002276:	ff                   	(bad)  
   180002277:	ff 00                	inc    DWORD PTR [rax]
   180002279:	00 00                	add    BYTE PTR [rax],al
   18000227b:	00 00                	add    BYTE PTR [rax],al
   18000227d:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .rdata:

0000000180003000 <.rdata>:
   180003000:	66 61                	data16 (bad) 
   180003002:	69 6c 65 64 20 74 6f 	imul   ebp,DWORD PTR [rbp+riz*2+0x64],0x206f7420
   180003009:	20 
   18000300a:	61                   	(bad)  
   18000300b:	6c                   	ins    BYTE PTR es:[rdi],dx
   18000300c:	6c                   	ins    BYTE PTR es:[rdi],dx
   18000300d:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   18000300e:	63 61 74             	movsxd esp,DWORD PTR [rcx+0x74]
   180003011:	65 20 6d 65          	and    BYTE PTR gs:[rbp+0x65],ch
   180003015:	6d                   	ins    DWORD PTR es:[rdi],dx
   180003016:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180003017:	72 79                	jb     180003092 <.rdata+0x62>
   180003019:	20 61 74             	and    BYTE PTR [rcx+0x74],ah
   18000301c:	20 00                	and    BYTE PTR [rax],al
   18000301e:	2e 0d 0a 00 00 00    	cs or  eax,0xa
	...

0000000180003030 <.rdata>:
   180003030:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   180003033:	30 6d 41             	xor    BYTE PTR [rbp+0x41],ch
   180003036:	4f 5a                	rex.WRXB pop r10
   180003038:	4f 52                	rex.WRXB push r10
   18000303a:	41 5f                	pop    r15
   18000303c:	4d                   	rex.WRB
   18000303d:	45                   	rex.RB
   18000303e:	4d                   	rex.WRB
   18000303f:	4f 52                	rex.WRXB push r10
   180003041:	59                   	pop    rcx
   180003042:	5f                   	pop    rdi
   180003043:	49                   	rex.WB
   180003044:	4e 56                	rex.WRX push rsi
   180003046:	41                   	rex.B
   180003047:	4c                   	rex.WR
   180003048:	49                   	rex.WB
   180003049:	44 1b 5b 6d          	sbb    r11d,DWORD PTR [rbx+0x6d]
   18000304d:	20 20                	and    BYTE PTR [rax],ah
   18000304f:	20 00                	and    BYTE PTR [rax],al
   180003051:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
   180003054:	00 00                	add    BYTE PTR [rax],al
   180003056:	00 00                	add    BYTE PTR [rax],al
   180003058:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   18000305b:	32 6d 41             	xor    ch,BYTE PTR [rbp+0x41]
   18000305e:	4f 5a                	rex.WRXB pop r10
   180003060:	4f 52                	rex.WRXB push r10
   180003062:	41 5f                	pop    r15
   180003064:	4d                   	rex.WRB
   180003065:	45                   	rex.RB
   180003066:	4d                   	rex.WRB
   180003067:	4f 52                	rex.WRXB push r10
   180003069:	59                   	pop    rcx
   18000306a:	5f                   	pop    rdi
   18000306b:	42                   	rex.X
   18000306c:	4f                   	rex.WRXB
   18000306d:	4f 54                	rex.WRXB push r12
   18000306f:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
   180003072:	20 20                	and    BYTE PTR [rax],ah
   180003074:	20 20                	and    BYTE PTR [rax],ah
   180003076:	20 20                	and    BYTE PTR [rax],ah
	...
   180003080:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   180003083:	36 6d                	ss ins DWORD PTR es:[rdi],dx
   180003085:	41                   	rex.B
   180003086:	4f 5a                	rex.WRXB pop r10
   180003088:	4f 52                	rex.WRXB push r10
   18000308a:	41 5f                	pop    r15
   18000308c:	4d                   	rex.WRB
   18000308d:	45                   	rex.RB
   18000308e:	4d                   	rex.WRB
   18000308f:	4f 52                	rex.WRXB push r10
   180003091:	59                   	pop    rcx
   180003092:	5f                   	pop    rdi
   180003093:	53                   	push   rbx
   180003094:	48                   	rex.W
   180003095:	41 52                	push   r10
   180003097:	45                   	rex.RB
   180003098:	44 1b 5b 6d          	sbb    r11d,DWORD PTR [rbx+0x6d]
   18000309c:	20 20                	and    BYTE PTR [rax],ah
   18000309e:	20 20                	and    BYTE PTR [rax],ah
	...
   1800030a8:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   1800030ab:	36 6d                	ss ins DWORD PTR es:[rdi],dx
   1800030ad:	41                   	rex.B
   1800030ae:	4f 5a                	rex.WRXB pop r10
   1800030b0:	4f 52                	rex.WRXB push r10
   1800030b2:	41 5f                	pop    r15
   1800030b4:	4d                   	rex.WRB
   1800030b5:	45                   	rex.RB
   1800030b6:	4d                   	rex.WRB
   1800030b7:	4f 52                	rex.WRXB push r10
   1800030b9:	59                   	pop    rcx
   1800030ba:	5f                   	pop    rdi
   1800030bb:	44                   	rex.R
   1800030bc:	41 54                	push   r12
   1800030be:	41 1b 5b 6d          	sbb    ebx,DWORD PTR [r11+0x6d]
   1800030c2:	20 20                	and    BYTE PTR [rax],ah
   1800030c4:	20 20                	and    BYTE PTR [rax],ah
   1800030c6:	20 20                	and    BYTE PTR [rax],ah
	...
   1800030d0:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   1800030d3:	36 6d                	ss ins DWORD PTR es:[rdi],dx
   1800030d5:	41                   	rex.B
   1800030d6:	4f 5a                	rex.WRXB pop r10
   1800030d8:	4f 52                	rex.WRXB push r10
   1800030da:	41 5f                	pop    r15
   1800030dc:	4d                   	rex.WRB
   1800030dd:	45                   	rex.RB
   1800030de:	4d                   	rex.WRB
   1800030df:	4f 52                	rex.WRXB push r10
   1800030e1:	59                   	pop    rcx
   1800030e2:	5f                   	pop    rdi
   1800030e3:	43                   	rex.XB
   1800030e4:	4f                   	rex.WRXB
   1800030e5:	44                   	rex.R
   1800030e6:	45 1b 5b 6d          	sbb    r11d,DWORD PTR [r11+0x6d]
   1800030ea:	20 20                	and    BYTE PTR [rax],ah
   1800030ec:	20 20                	and    BYTE PTR [rax],ah
   1800030ee:	20 20                	and    BYTE PTR [rax],ah
	...
   1800030f8:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   1800030fb:	35 6d 41 4f 5a       	xor    eax,0x5a4f416d
   180003100:	4f 52                	rex.WRXB push r10
   180003102:	41 5f                	pop    r15
   180003104:	4d                   	rex.WRB
   180003105:	45                   	rex.RB
   180003106:	4d                   	rex.WRB
   180003107:	4f 52                	rex.WRXB push r10
   180003109:	59                   	pop    rcx
   18000310a:	5f                   	pop    rdi
   18000310b:	4b                   	rex.WXB
   18000310c:	45 52                	rex.RB push r10
   18000310e:	4e                   	rex.WRX
   18000310f:	45                   	rex.RB
   180003110:	4c 1b 5b 6d          	sbb    r11,QWORD PTR [rbx+0x6d]
   180003114:	20 20                	and    BYTE PTR [rax],ah
   180003116:	20 20                	and    BYTE PTR [rax],ah
	...
   180003120:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   180003123:	35 6d 41 4f 5a       	xor    eax,0x5a4f416d
   180003128:	4f 52                	rex.WRXB push r10
   18000312a:	41 5f                	pop    r15
   18000312c:	4d                   	rex.WRB
   18000312d:	45                   	rex.RB
   18000312e:	4d                   	rex.WRB
   18000312f:	4f 52                	rex.WRXB push r10
   180003131:	59                   	pop    rcx
   180003132:	5f                   	pop    rdi
   180003133:	4d                   	rex.WRB
   180003134:	41 50                	push   r8
   180003136:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
   180003139:	20 20                	and    BYTE PTR [rax],ah
   18000313b:	20 20                	and    BYTE PTR [rax],ah
   18000313d:	20 20                	and    BYTE PTR [rax],ah
   18000313f:	20 00                	and    BYTE PTR [rax],al
   180003141:	00 00                	add    BYTE PTR [rax],al
   180003143:	00 00                	add    BYTE PTR [rax],al
   180003145:	00 00                	add    BYTE PTR [rax],al
   180003147:	00 1b                	add    BYTE PTR [rbx],bl
   180003149:	5b                   	pop    rbx
   18000314a:	33 33                	xor    esi,DWORD PTR [rbx]
   18000314c:	6d                   	ins    DWORD PTR es:[rdi],dx
   18000314d:	41                   	rex.B
   18000314e:	4f 5a                	rex.WRXB pop r10
   180003150:	4f 52                	rex.WRXB push r10
   180003152:	41 5f                	pop    r15
   180003154:	4d                   	rex.WRB
   180003155:	45                   	rex.RB
   180003156:	4d                   	rex.WRB
   180003157:	4f 52                	rex.WRXB push r10
   180003159:	59                   	pop    rcx
   18000315a:	5f                   	pop    rdi
   18000315b:	47                   	rex.RXB
   18000315c:	4f 50                	rex.WRXB push r8
   18000315e:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
   180003161:	20 20                	and    BYTE PTR [rax],ah
   180003163:	20 20                	and    BYTE PTR [rax],ah
   180003165:	20 20                	and    BYTE PTR [rax],ah
   180003167:	20 00                	and    BYTE PTR [rax],al
   180003169:	00 00                	add    BYTE PTR [rax],al
   18000316b:	00 00                	add    BYTE PTR [rax],al
   18000316d:	00 00                	add    BYTE PTR [rax],al
   18000316f:	00 1b                	add    BYTE PTR [rbx],bl
   180003171:	5b                   	pop    rbx
   180003172:	33 32                	xor    esi,DWORD PTR [rdx]
   180003174:	6d                   	ins    DWORD PTR es:[rdi],dx
   180003175:	41                   	rex.B
   180003176:	4f 5a                	rex.WRXB pop r10
   180003178:	4f 52                	rex.WRXB push r10
   18000317a:	41 5f                	pop    r15
   18000317c:	4d                   	rex.WRB
   18000317d:	45                   	rex.RB
   18000317e:	4d                   	rex.WRB
   18000317f:	4f 52                	rex.WRXB push r10
   180003181:	59                   	pop    rcx
   180003182:	5f                   	pop    rdi
   180003183:	50                   	push   rax
   180003184:	45 52                	rex.RB push r10
   180003186:	53                   	push   rbx
   180003187:	49 53                	rex.WB push r11
   180003189:	54                   	push   rsp
   18000318a:	45                   	rex.RB
   18000318b:	4e 54                	rex.WRX push rsp
   18000318d:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
	...
   180003198:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   18000319b:	30 6d 41             	xor    BYTE PTR [rbp+0x41],ch
   18000319e:	4f 5a                	rex.WRXB pop r10
   1800031a0:	4f 52                	rex.WRXB push r10
   1800031a2:	41 5f                	pop    r15
   1800031a4:	4d                   	rex.WRB
   1800031a5:	45                   	rex.RB
   1800031a6:	4d                   	rex.WRB
   1800031a7:	4f 52                	rex.WRXB push r10
   1800031a9:	59                   	pop    rcx
   1800031aa:	5f                   	pop    rdi
   1800031ab:	42                   	rex.X
   1800031ac:	41                   	rex.B
   1800031ad:	44 1b 5b 6d          	sbb    r11d,DWORD PTR [rbx+0x6d]
   1800031b1:	20 20                	and    BYTE PTR [rax],ah
   1800031b3:	20 20                	and    BYTE PTR [rax],ah
   1800031b5:	20 20                	and    BYTE PTR [rax],ah
   1800031b7:	20 00                	and    BYTE PTR [rax],al
   1800031b9:	00 00                	add    BYTE PTR [rax],al
   1800031bb:	00 00                	add    BYTE PTR [rax],al
   1800031bd:	00 00                	add    BYTE PTR [rax],al
   1800031bf:	00 1b                	add    BYTE PTR [rbx],bl
   1800031c1:	5b                   	pop    rbx
   1800031c2:	33 33                	xor    esi,DWORD PTR [rbx]
   1800031c4:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800031c5:	41                   	rex.B
   1800031c6:	4f 5a                	rex.WRXB pop r10
   1800031c8:	4f 52                	rex.WRXB push r10
   1800031ca:	41 5f                	pop    r15
   1800031cc:	4d                   	rex.WRB
   1800031cd:	45                   	rex.RB
   1800031ce:	4d                   	rex.WRB
   1800031cf:	4f 52                	rex.WRXB push r10
   1800031d1:	59                   	pop    rcx
   1800031d2:	5f                   	pop    rdi
   1800031d3:	49                   	rex.WB
   1800031d4:	4f 1b 5b 6d          	rex.WRXB sbb r11,QWORD PTR [r11+0x6d]
   1800031d8:	20 20                	and    BYTE PTR [rax],ah
   1800031da:	20 20                	and    BYTE PTR [rax],ah
   1800031dc:	20 20                	and    BYTE PTR [rax],ah
   1800031de:	20 20                	and    BYTE PTR [rax],ah
	...
   1800031e8:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   1800031eb:	33 6d 41             	xor    ebp,DWORD PTR [rbp+0x41]
   1800031ee:	4f 5a                	rex.WRXB pop r10
   1800031f0:	4f 52                	rex.WRXB push r10
   1800031f2:	41 5f                	pop    r15
   1800031f4:	4d                   	rex.WRB
   1800031f5:	45                   	rex.RB
   1800031f6:	4d                   	rex.WRB
   1800031f7:	4f 52                	rex.WRXB push r10
   1800031f9:	59                   	pop    rcx
   1800031fa:	5f                   	pop    rdi
   1800031fb:	4e 56                	rex.WRX push rsi
   1800031fd:	53                   	push   rbx
   1800031fe:	1b 5b 6d             	sbb    ebx,DWORD PTR [rbx+0x6d]
   180003201:	20 20                	and    BYTE PTR [rax],ah
   180003203:	20 20                	and    BYTE PTR [rax],ah
   180003205:	20 20                	and    BYTE PTR [rax],ah
   180003207:	20 00                	and    BYTE PTR [rax],al
   180003209:	00 00                	add    BYTE PTR [rax],al
   18000320b:	00 00                	add    BYTE PTR [rax],al
   18000320d:	00 00                	add    BYTE PTR [rax],al
   18000320f:	00 1b                	add    BYTE PTR [rbx],bl
   180003211:	5b                   	pop    rbx
   180003212:	33 33                	xor    esi,DWORD PTR [rbx]
   180003214:	6d                   	ins    DWORD PTR es:[rdi],dx
   180003215:	41                   	rex.B
   180003216:	4f 5a                	rex.WRXB pop r10
   180003218:	4f 52                	rex.WRXB push r10
   18000321a:	41 5f                	pop    r15
   18000321c:	4d                   	rex.WRB
   18000321d:	45                   	rex.RB
   18000321e:	4d                   	rex.WRB
   18000321f:	4f 52                	rex.WRXB push r10
   180003221:	59                   	pop    rcx
   180003222:	5f                   	pop    rdi
   180003223:	52                   	push   rdx
   180003224:	45 53                	rex.RB push r11
   180003226:	45 52                	rex.RB push r10
   180003228:	56                   	push   rsi
   180003229:	45                   	rex.RB
   18000322a:	44 1b 5b 6d          	sbb    r11d,DWORD PTR [rbx+0x6d]
   18000322e:	20 20                	and    BYTE PTR [rax],ah
	...
   180003238:	1b 5b 33             	sbb    ebx,DWORD PTR [rbx+0x33]
   18000323b:	32 6d 41             	xor    ch,BYTE PTR [rbp+0x41]
   18000323e:	4f 5a                	rex.WRXB pop r10
   180003240:	4f 52                	rex.WRXB push r10
   180003242:	41 5f                	pop    r15
   180003244:	4d                   	rex.WRB
   180003245:	45                   	rex.RB
   180003246:	4d                   	rex.WRB
   180003247:	4f 52                	rex.WRXB push r10
   180003249:	59                   	pop    rcx
   18000324a:	5f                   	pop    rdi
   18000324b:	46 52                	rex.RX push rdx
   18000324d:	45                   	rex.RB
   18000324e:	45 1b 5b 6d          	sbb    r11d,DWORD PTR [r11+0x6d]
   180003252:	20 20                	and    BYTE PTR [rax],ah
   180003254:	20 20                	and    BYTE PTR [rax],ah
   180003256:	20 20                	and    BYTE PTR [rax],ah
   180003258:	00 1b                	add    BYTE PTR [rbx],bl
   18000325a:	5b                   	pop    rbx
   18000325b:	31 3b                	xor    DWORD PTR [rbx],edi
   18000325d:	33 32                	xor    esi,DWORD PTR [rdx]
   18000325f:	6d                   	ins    DWORD PTR es:[rdi],dx
   180003260:	78 00                	js     180003262 <.rdata+0x232>
   180003262:	20 2d 3e 20 00 3a    	and    BYTE PTR [rip+0x3a00203e],ch        # 1ba0052a6 <__IAT_end__+0x39ffd292>
   180003268:	20 73 69             	and    BYTE PTR [rbx+0x69],dh
   18000326b:	7a 65                	jp     1800032d2 <.rdata+0x2a2>
   18000326d:	20 3d 20 00 20 62    	and    BYTE PTR [rip+0x62200020],bh        # 1e2203293 <__IAT_end__+0x621fb27f>
   180003273:	79 74                	jns    1800032e9 <.rdata+0x2b9>
   180003275:	65 73 0a             	gs jae 180003282 <.rdata+0x252>
   180003278:	0d 00 00 00 35       	or     eax,0x35000000
   18000327d:	e3 ff                	jrcxz  18000327e <.rdata+0x24e>
   18000327f:	ff 95 e3 ff ff 41    	call   QWORD PTR [rbp+0x41ffffe3]
   180003285:	e3 ff                	jrcxz  180003286 <.rdata+0x256>
   180003287:	ff 6f e2             	jmp    FWORD PTR [rdi-0x1e]
   18000328a:	ff                   	(bad)  
   18000328b:	ff                   	(bad)  
   18000328c:	7d e3                	jge    180003271 <.rdata+0x241>
   18000328e:	ff                   	(bad)  
   18000328f:	ff 4d e3             	dec    DWORD PTR [rbp-0x1d]
   180003292:	ff                   	(bad)  
   180003293:	ff 59 e3             	call   FWORD PTR [rcx-0x1d]
   180003296:	ff                   	(bad)  
   180003297:	ff 65 e3             	jmp    QWORD PTR [rbp-0x1d]
   18000329a:	ff                   	(bad)  
   18000329b:	ff 71 e3             	push   QWORD PTR [rcx-0x1d]
   18000329e:	ff                   	(bad)  
   18000329f:	ff a1 e3 ff ff ad    	jmp    QWORD PTR [rcx-0x5200001d]
   1800032a5:	e3 ff                	jrcxz  1800032a6 <.rdata+0x276>
   1800032a7:	ff                   	(bad)  
   1800032a8:	b9 e3 ff ff c5       	mov    ecx,0xc5ffffe3
   1800032ad:	e3 ff                	jrcxz  1800032ae <.rdata+0x27e>
   1800032af:	ff 89 e3 ff ff 20    	dec    DWORD PTR [rcx+0x20ffffe3]
   1800032b5:	61                   	(bad)  
   1800032b6:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   1800032b7:	7a 6f                	jp     180003328 <.rdata+0x38>
   1800032b9:	72 61                	jb     18000331c <.rdata+0x2c>
   1800032bb:	20 6d 65             	and    BYTE PTR [rbp+0x65],ch
   1800032be:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800032bf:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   1800032c0:	72 79                	jb     18000333b <.rdata+0x4b>
   1800032c2:	20 6d 61             	and    BYTE PTR [rbp+0x61],ch
   1800032c5:	70 70                	jo     180003337 <.rdata+0x47>
   1800032c7:	69 6e 67 73 20 0a 0d 	imul   ebp,DWORD PTR [rsi+0x67],0xd0a2073
   1800032ce:	00 20                	add    BYTE PTR [rax],ah
   1800032d0:	62                   	(bad)  
   1800032d1:	79 74                	jns    180003347 <.rdata+0x57>
   1800032d3:	65 73 20             	gs jae 1800032f6 <.rdata+0x6>
   1800032d6:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   1800032d7:	66 20 72 61          	data16 and BYTE PTR [rdx+0x61],dh
   1800032db:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800032dc:	20 0a                	and    BYTE PTR [rdx],cl
   1800032de:	0d 00 3a 20 00       	or     eax,0x203a00
   1800032e3:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800032e4:	65 6d                	gs ins DWORD PTR es:[rdi],dx
   1800032e6:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   1800032e7:	72 79                	jb     180003362 <.rdata+0x72>
   1800032e9:	20 00                	and    BYTE PTR [rax],al
   1800032eb:	00 00                	add    BYTE PTR [rax],al
   1800032ed:	00 00                	add    BYTE PTR [rax],al
	...

00000001800032f0 <.rdata>:
   1800032f0:	c8 e7 ff ff          	enter  0xffe7,0xff
   1800032f4:	30 e7                	xor    bh,ah
   1800032f6:	ff                   	(bad)  
   1800032f7:	ff 30                	push   QWORD PTR [rax]
   1800032f9:	e7 ff                	out    0xff,eax
   1800032fb:	ff c0                	inc    eax
   1800032fd:	e6 ff                	out    0xff,al
   1800032ff:	ff c0                	inc    eax
   180003301:	e6 ff                	out    0xff,al
   180003303:	ff c8                	dec    eax
   180003305:	e7 ff                	out    0xff,eax
   180003307:	ff c8                	dec    eax
   180003309:	e7 ff                	out    0xff,eax
   18000330b:	ff c0                	inc    eax
   18000330d:	e6 ff                	out    0xff,al
   18000330f:	ff b0 e8 ff ff c0    	push   QWORD PTR [rax-0x3f000018]
   180003315:	e6 ff                	out    0xff,al
   180003317:	ff 60 e8             	jmp    QWORD PTR [rax-0x18]
   18000331a:	ff                   	(bad)  
   18000331b:	ff 80 e7 ff ff 80    	inc    DWORD PTR [rax-0x7f000019]
   180003321:	e7 ff                	out    0xff,eax
   180003323:	ff c8                	dec    eax
   180003325:	e7 ff                	out    0xff,eax
   180003327:	ff 10                	call   QWORD PTR [rax]
   180003329:	e8 ff ff 00 00       	call   18001332d <__IAT_end__+0xb319>
   18000332e:	00 00                	add    BYTE PTR [rax],al
   180003330:	65 72 72             	gs jb  1800033a5 <.rdata+0xb5>
   180003333:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180003334:	72 20                	jb     180003356 <.rdata+0x66>
   180003336:	61                   	(bad)  
   180003337:	6c                   	ins    BYTE PTR es:[rdi],dx
   180003338:	6c                   	ins    BYTE PTR es:[rdi],dx
   180003339:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   18000333a:	63 61 74             	movsxd esp,DWORD PTR [rcx+0x74]
   18000333d:	69 6e 67 20 61 6f 7a 	imul   ebp,DWORD PTR [rsi+0x67],0x7a6f6120
   180003344:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180003345:	72 61                	jb     1800033a8 <.rdata+0xb8>
   180003347:	2d 6f 73 20 6d       	sub    eax,0x6d20736f
   18000334c:	65 6d                	gs ins DWORD PTR es:[rdi],dx
   18000334e:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   18000334f:	72 79                	jb     1800033ca <.rdata+0xda>
   180003351:	2c 20                	sub    al,0x20
   180003353:	6d                   	ins    DWORD PTR es:[rdi],dx
   180003354:	65 6d                	gs ins DWORD PTR es:[rdi],dx
   180003356:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180003357:	72 79                	jb     1800033d2 <.refptr.BS+0x2>
   180003359:	20 61 74             	and    BYTE PTR [rcx+0x74],ah
   18000335c:	20 6c 6f 63          	and    BYTE PTR [rdi+rbp*2+0x63],ch
   180003360:	61                   	(bad)  
   180003361:	74 69                	je     1800033cc <.rdata+0xdc>
   180003363:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180003364:	6e                   	outs   dx,BYTE PTR ds:[rsi]
   180003365:	20 30                	and    BYTE PTR [rax],dh
   180003367:	20 2d 20 30 78 32    	and    BYTE PTR [rip+0x32783020],ch        # 1b278638d <__IAT_end__+0x3277e379>
   18000336d:	30 30                	xor    BYTE PTR [rax],dh
   18000336f:	30 30                	xor    BYTE PTR [rax],dh
   180003371:	30 20                	xor    BYTE PTR [rax],ah
   180003373:	69 73 20 6e 6f 74 20 	imul   esi,DWORD PTR [rbx+0x20],0x20746f6e
   18000337a:	66 72 65             	data16 jb 1800033e2 <.refptr.ST+0x2>
   18000337d:	65 0a 0d 00 00 00 00 	or     cl,BYTE PTR gs:[rip+0x0]        # 180003384 <.rdata+0x94>
	...
   180003398:	00 40 00             	add    BYTE PTR [rax+0x0],al
   18000339b:	00 00                	add    BYTE PTR [rax],al
   18000339d:	00 00                	add    BYTE PTR [rax],al
   18000339f:	00 00                	add    BYTE PTR [rax],al
   1800033a1:	40 00 00             	rex add BYTE PTR [rax],al
   1800033a4:	00 00                	add    BYTE PTR [rax],al
   1800033a6:	00 00                	add    BYTE PTR [rax],al
   1800033a8:	00 40 03             	add    BYTE PTR [rax+0x3],al
   1800033ab:	00 00                	add    BYTE PTR [rax],al
   1800033ad:	00 00                	add    BYTE PTR [rax],al
   1800033af:	00 00                	add    BYTE PTR [rax],al
   1800033b1:	40 03 00             	rex add eax,DWORD PTR [rax]
   1800033b4:	00 00                	add    BYTE PTR [rax],al
   1800033b6:	00 00                	add    BYTE PTR [rax],al
   1800033b8:	00 40 23             	add    BYTE PTR [rax+0x23],al
   1800033bb:	00 00                	add    BYTE PTR [rax],al
   1800033bd:	00 00                	add    BYTE PTR [rax],al
   1800033bf:	00 00                	add    BYTE PTR [rax],al
   1800033c1:	40 23 00             	rex and eax,DWORD PTR [rax]
   1800033c4:	00 00                	add    BYTE PTR [rax],al
   1800033c6:	00 00                	add    BYTE PTR [rax],al
   1800033c8:	00 00                	add    BYTE PTR [rax],al
   1800033ca:	25 00 00 00 00       	and    eax,0x0
	...

00000001800033d0 <.refptr.BS>:
   1800033d0:	00 60 00             	add    BYTE PTR [rax+0x0],ah
   1800033d3:	80 01 00             	add    BYTE PTR [rcx],0x0
	...

00000001800033e0 <.refptr.ST>:
   1800033e0:	08 60 00             	or     BYTE PTR [rax+0x0],ah
   1800033e3:	80 01 00             	add    BYTE PTR [rcx],0x0
	...

00000001800033f0 <.rdata$zzz>:
   1800033f0:	47                   	rex.RXB
   1800033f1:	43                   	rex.XB
   1800033f2:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   1800033f5:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   1800033f8:	55                   	push   rbp
   1800033f9:	29 20                	sub    DWORD PTR [rax],esp
   1800033fb:	31 31                	xor    DWORD PTR [rcx],esi
   1800033fd:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   180003400:	30 00                	xor    BYTE PTR [rax],al
	...

0000000180003410 <.rdata$zzz>:
   180003410:	47                   	rex.RXB
   180003411:	43                   	rex.XB
   180003412:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   180003415:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   180003418:	55                   	push   rbp
   180003419:	29 20                	sub    DWORD PTR [rax],esp
   18000341b:	31 31                	xor    DWORD PTR [rcx],esi
   18000341d:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   180003420:	30 00                	xor    BYTE PTR [rax],al
	...

0000000180003430 <.rdata$zzz>:
   180003430:	47                   	rex.RXB
   180003431:	43                   	rex.XB
   180003432:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   180003435:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   180003438:	55                   	push   rbp
   180003439:	29 20                	sub    DWORD PTR [rax],esp
   18000343b:	31 31                	xor    DWORD PTR [rcx],esi
   18000343d:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   180003440:	30 00                	xor    BYTE PTR [rax],al
	...

0000000180003450 <.rdata$zzz>:
   180003450:	47                   	rex.RXB
   180003451:	43                   	rex.XB
   180003452:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   180003455:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   180003458:	55                   	push   rbp
   180003459:	29 20                	sub    DWORD PTR [rax],esp
   18000345b:	31 31                	xor    DWORD PTR [rcx],esi
   18000345d:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   180003460:	30 00                	xor    BYTE PTR [rax],al
	...

0000000180003470 <.rdata$zzz>:
   180003470:	47                   	rex.RXB
   180003471:	43                   	rex.XB
   180003472:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   180003475:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   180003478:	55                   	push   rbp
   180003479:	29 20                	sub    DWORD PTR [rax],esp
   18000347b:	31 31                	xor    DWORD PTR [rcx],esi
   18000347d:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   180003480:	30 00                	xor    BYTE PTR [rax],al
	...

0000000180003490 <.rdata$zzz>:
   180003490:	47                   	rex.RXB
   180003491:	43                   	rex.XB
   180003492:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   180003495:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   180003498:	55                   	push   rbp
   180003499:	29 20                	sub    DWORD PTR [rax],esp
   18000349b:	31 31                	xor    DWORD PTR [rcx],esi
   18000349d:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   1800034a0:	30 00                	xor    BYTE PTR [rax],al
	...

00000001800034b0 <.rdata$zzz>:
   1800034b0:	47                   	rex.RXB
   1800034b1:	43                   	rex.XB
   1800034b2:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   1800034b5:	28 47 4e             	sub    BYTE PTR [rdi+0x4e],al
   1800034b8:	55                   	push   rbp
   1800034b9:	29 20                	sub    DWORD PTR [rax],esp
   1800034bb:	31 31                	xor    DWORD PTR [rcx],esi
   1800034bd:	2e 32 2e             	cs xor ch,BYTE PTR [rsi]
   1800034c0:	30 00                	xor    BYTE PTR [rax],al
	...

Disassembly of section .pdata:

0000000180004000 <.pdata>:
   180004000:	00 10                	add    BYTE PTR [rax],dl
   180004002:	00 00                	add    BYTE PTR [rax],al
   180004004:	14 11                	adc    al,0x11
   180004006:	00 00                	add    BYTE PTR [rax],al
   180004008:	00 50 00             	add    BYTE PTR [rax+0x0],dl
	...

000000018000400c <.pdata>:
   18000400c:	20 11                	and    BYTE PTR [rcx],dl
   18000400e:	00 00                	add    BYTE PTR [rax],al
   180004010:	07                   	(bad)  
   180004011:	12 00                	adc    al,BYTE PTR [rax]
   180004013:	00 10                	add    BYTE PTR [rax],dl
   180004015:	50                   	push   rax
   180004016:	00 00                	add    BYTE PTR [rax],al
   180004018:	10 12                	adc    BYTE PTR [rdx],dl
   18000401a:	00 00                	add    BYTE PTR [rax],al
   18000401c:	a3 12 00 00 20 50 00 	movabs ds:0xb000005020000012,eax
   180004023:	00 b0 
   180004025:	12 00                	adc    al,BYTE PTR [rax]
   180004027:	00 9c 13 00 00 2c 50 	add    BYTE PTR [rbx+rdx*1+0x502c0000],bl
   18000402e:	00 00                	add    BYTE PTR [rax],al
   180004030:	a0 13 00 00 88 14 00 	movabs al,ds:0x3c00001488000013
   180004037:	00 3c 
   180004039:	50                   	push   rax
   18000403a:	00 00                	add    BYTE PTR [rax],al
   18000403c:	90                   	nop
   18000403d:	14 00                	adc    al,0x0
   18000403f:	00 ba 14 00 00 50    	add    BYTE PTR [rdx+0x50000014],bh
   180004045:	50                   	push   rax
   180004046:	00 00                	add    BYTE PTR [rax],al
   180004048:	c0 14 00 00          	rcl    BYTE PTR [rax+rax*1],0x0
   18000404c:	89 16                	mov    DWORD PTR [rsi],edx
   18000404e:	00 00                	add    BYTE PTR [rax],al
   180004050:	58                   	pop    rax
   180004051:	50                   	push   rax
   180004052:	00 00                	add    BYTE PTR [rax],al
   180004054:	90                   	nop
   180004055:	16                   	(bad)  
   180004056:	00 00                	add    BYTE PTR [rax],al
   180004058:	b4 17                	mov    ah,0x17
   18000405a:	00 00                	add    BYTE PTR [rax],al
   18000405c:	68 50 00 00        	push   0xffffffffc0000050

0000000180004060 <.pdata>:
   180004060:	c0 17 00             	rcl    BYTE PTR [rdi],0x0
   180004063:	00 08                	add    BYTE PTR [rax],cl
   180004065:	18 00                	sbb    BYTE PTR [rax],al
   180004067:	00 78 50             	add    BYTE PTR [rax+0x50],bh
   18000406a:	00 00                	add    BYTE PTR [rax],al
   18000406c:	10 18                	adc    BYTE PTR [rax],bl
   18000406e:	00 00                	add    BYTE PTR [rax],al
   180004070:	2a 18                	sub    bl,BYTE PTR [rax]
   180004072:	00 00                	add    BYTE PTR [rax],al
   180004074:	80 50 00 00          	adc    BYTE PTR [rax+0x0],0x0
   180004078:	30 18                	xor    BYTE PTR [rax],bl
   18000407a:	00 00                	add    BYTE PTR [rax],al
   18000407c:	34 18                	xor    al,0x18
   18000407e:	00 00                	add    BYTE PTR [rax],al
   180004080:	88 50 00             	mov    BYTE PTR [rax+0x0],dl
   180004083:	00 40 18             	add    BYTE PTR [rax+0x18],al
   180004086:	00 00                	add    BYTE PTR [rax],al
   180004088:	67 18 00             	sbb    BYTE PTR [eax],al
   18000408b:	00 8c 50 00 00 70 18 	add    BYTE PTR [rax+rdx*2+0x18700000],cl
   180004092:	00 00                	add    BYTE PTR [rax],al
   180004094:	83 18 00             	sbb    DWORD PTR [rax],0x0
   180004097:	00 90 50 00 00     	add    BYTE PTR [rax-0x6fffffb0],dl

000000018000409c <.pdata>:
   18000409c:	90                   	nop
   18000409d:	18 00                	sbb    BYTE PTR [rax],al
   18000409f:	00 97 18 00 00 94    	add    BYTE PTR [rdi-0x6bffffe8],dl
   1800040a5:	50                   	push   rax
   1800040a6:	00 00                	add    BYTE PTR [rax],al
   1800040a8:	a0 18 00 00 a5 18 00 	movabs al,ds:0x98000018a5000018
   1800040af:	00 98 
   1800040b1:	50                   	push   rax
   1800040b2:	00 00                	add    BYTE PTR [rax],al
   1800040b4:	b0 18                	mov    al,0x18
   1800040b6:	00 00                	add    BYTE PTR [rax],al
   1800040b8:	48 19 00             	sbb    QWORD PTR [rax],rax
   1800040bb:	00 9c 50 00 00 50 19 	add    BYTE PTR [rax+rdx*2+0x19500000],bl
   1800040c2:	00 00                	add    BYTE PTR [rax],al
   1800040c4:	59                   	pop    rcx
   1800040c5:	19 00                	sbb    DWORD PTR [rax],eax
   1800040c7:	00 a4 50 00 00   	add    BYTE PTR [rax+rdx*2+0x19600000],ah

00000001800040cc <.pdata>:
   1800040cc:	60                   	(bad)  
   1800040cd:	19 00                	sbb    DWORD PTR [rax],eax
   1800040cf:	00 6e 1c             	add    BYTE PTR [rsi+0x1c],ch
   1800040d2:	00 00                	add    BYTE PTR [rax],al
   1800040d4:	a8 50                	test   al,0x50
   1800040d6:	00 00                	add    BYTE PTR [rax],al
   1800040d8:	70 1c                	jo     1800040f6 <.pdata+0x12>
   1800040da:	00 00                	add    BYTE PTR [rax],al
   1800040dc:	c6                   	(bad)  
   1800040dd:	1e                   	(bad)  
   1800040de:	00 00                	add    BYTE PTR [rax],al
   1800040e0:	b8 50 00 00        	mov    eax,0xd0000050

00000001800040e4 <.pdata>:
   1800040e4:	d0 1e                	rcr    BYTE PTR [rsi],1
   1800040e6:	00 00                	add    BYTE PTR [rax],al
   1800040e8:	cd 1f                	int    0x1f
   1800040ea:	00 00                	add    BYTE PTR [rax],al
   1800040ec:	cc                   	int3   
   1800040ed:	50                   	push   rax
   1800040ee:	00 00                	add    BYTE PTR [rax],al
   1800040f0:	d0 1f                	rcr    BYTE PTR [rdi],1
   1800040f2:	00 00                	add    BYTE PTR [rax],al
   1800040f4:	83 21 00             	and    DWORD PTR [rcx],0x0
   1800040f7:	00 d0                	add    al,dl
   1800040f9:	50                   	push   rax
   1800040fa:	00 00                	add    BYTE PTR [rax],al
   1800040fc:	90                   	nop
   1800040fd:	21 00                	and    DWORD PTR [rax],eax
   1800040ff:	00 45 22             	add    BYTE PTR [rbp+0x22],al
   180004102:	00 00                	add    BYTE PTR [rax],al
   180004104:	e0 50                	loopne 180004156 <.pdata+0x72>
   180004106:	00 00                	add    BYTE PTR [rax],al
   180004108:	50                   	push   rax
   180004109:	22 00                	and    al,BYTE PTR [rax]
   18000410b:	00 51 22             	add    BYTE PTR [rcx+0x22],dl
   18000410e:	00 00                	add    BYTE PTR [rax],al
   180004110:	ec                   	in     al,dx
   180004111:	50                   	push   rax
	...

Disassembly of section .xdata:

0000000180005000 <.xdata>:
   180005000:	01 09                	add    DWORD PTR [rcx],ecx
   180005002:	05 00 09 62 05       	add    eax,0x5620900
   180005007:	30 04 60             	xor    BYTE PTR [rax+riz*2],al
   18000500a:	03 70 02             	add    esi,DWORD PTR [rax+0x2]
   18000500d:	c0 00 00             	rol    BYTE PTR [rax],0x0

0000000180005010 <.xdata>:
   180005010:	01 0b                	add    DWORD PTR [rbx],ecx
   180005012:	06                   	(bad)  
   180005013:	00 0b                	add    BYTE PTR [rbx],cl
   180005015:	01 45 00             	add    DWORD PTR [rbp+0x0],eax
   180005018:	04 30                	add    al,0x30
   18000501a:	03 60 02             	add    esp,DWORD PTR [rax+0x2]
   18000501d:	70 01                	jo     180005020 <.xdata+0x10>
   18000501f:	50                   	push   rax
   180005020:	01 09                	add    DWORD PTR [rcx],ecx
   180005022:	04 00                	add    al,0x0
   180005024:	09 01                	or     DWORD PTR [rcx],eax
   180005026:	45 00 02             	add    BYTE PTR [r10],r8b
   180005029:	30 01                	xor    BYTE PTR [rcx],al
   18000502b:	60                   	(bad)  
   18000502c:	01 0b                	add    DWORD PTR [rbx],ecx
   18000502e:	06                   	(bad)  
   18000502f:	00 0b                	add    BYTE PTR [rbx],cl
   180005031:	01 45 00             	add    DWORD PTR [rbp+0x0],eax
   180005034:	04 30                	add    al,0x30
   180005036:	03 60 02             	add    esp,DWORD PTR [rax+0x2]
   180005039:	70 01                	jo     18000503c <.xdata+0x2c>
   18000503b:	50                   	push   rax
   18000503c:	01 0d 07 00 0d 01    	add    DWORD PTR [rip+0x10d0007],ecx        # 1810d5049 <__IAT_end__+0x10cd035>
   180005042:	44 00 06             	add    BYTE PTR [rsi],r8b
   180005045:	30 05 60 04 70 03    	xor    BYTE PTR [rip+0x3700460],al        # 1837054ab <__IAT_end__+0x36fd497>
   18000504b:	50                   	push   rax
   18000504c:	02 c0                	add    al,al
   18000504e:	00 00                	add    BYTE PTR [rax],al
   180005050:	01 05 02 00 05 32    	add    DWORD PTR [rip+0x32050002],eax        # 1b2055058 <__IAT_end__+0x3204d044>
   180005056:	01 30                	add    DWORD PTR [rax],esi
   180005058:	01 08                	add    DWORD PTR [rax],ecx
   18000505a:	05 00 08 42 04       	add    eax,0x4420800
   18000505f:	30 03                	xor    BYTE PTR [rbx],al
   180005061:	60                   	(bad)  
   180005062:	02 70 01             	add    dh,BYTE PTR [rax+0x1]
   180005065:	50                   	push   rax
   180005066:	00 00                	add    BYTE PTR [rax],al
   180005068:	01 0a                	add    DWORD PTR [rdx],ecx
   18000506a:	06                   	(bad)  
   18000506b:	00 0a                	add    BYTE PTR [rdx],cl
   18000506d:	72 06                	jb     180005075 <.xdata+0x65>
   18000506f:	30 05 60 04 70 03    	xor    BYTE PTR [rip+0x3700460],al        # 1837054d5 <__IAT_end__+0x36fd4c1>
   180005075:	50                   	push   rax
   180005076:	02 c0                	add    al,al

0000000180005078 <.xdata>:
   180005078:	01 04 01             	add    DWORD PTR [rcx+rax*1],eax
   18000507b:	00 04 82             	add    BYTE PTR [rdx+rax*4],al
   18000507e:	00 00                	add    BYTE PTR [rax],al
   180005080:	01 04 01             	add    DWORD PTR [rcx+rax*1],eax
   180005083:	00 04 62             	add    BYTE PTR [rdx+riz*2],al
   180005086:	00 00                	add    BYTE PTR [rax],al
   180005088:	01 00                	add    DWORD PTR [rax],eax
   18000508a:	00 00                	add    BYTE PTR [rax],al
   18000508c:	01 00                	add    DWORD PTR [rax],eax
   18000508e:	00 00                	add    BYTE PTR [rax],al
   180005090:	01 00                	add    DWORD PTR [rax],eax
	...

0000000180005094 <.xdata>:
   180005094:	01 00                	add    DWORD PTR [rax],eax
   180005096:	00 00                	add    BYTE PTR [rax],al
   180005098:	01 00                	add    DWORD PTR [rax],eax
   18000509a:	00 00                	add    BYTE PTR [rax],al
   18000509c:	01 04 01             	add    DWORD PTR [rcx+rax*1],eax
   18000509f:	00 04 42             	add    BYTE PTR [rdx+rax*2],al
   1800050a2:	00 00                	add    BYTE PTR [rax],al
   1800050a4:	01 00                	add    DWORD PTR [rax],eax
	...

00000001800050a8 <.xdata>:
   1800050a8:	01 08                	add    DWORD PTR [rax],ecx
   1800050aa:	06                   	(bad)  
   1800050ab:	00 08                	add    BYTE PTR [rax],cl
   1800050ad:	30 07                	xor    BYTE PTR [rdi],al
   1800050af:	60                   	(bad)  
   1800050b0:	06                   	(bad)  
   1800050b1:	70 05                	jo     1800050b8 <.xdata+0x10>
   1800050b3:	50                   	push   rax
   1800050b4:	04 c0                	add    al,0xc0
   1800050b6:	02 d0                	add    dl,al
   1800050b8:	01 0f                	add    DWORD PTR [rdi],ecx
   1800050ba:	08 00                	or     BYTE PTR [rax],al
   1800050bc:	0f 01 25 00 08 30 07 	smsw   WORD PTR [rip+0x7300800]        # 1873058c3 <__IAT_end__+0x72fd8af>
   1800050c3:	60                   	(bad)  
   1800050c4:	06                   	(bad)  
   1800050c5:	70 05                	jo     1800050cc <.xdata>
   1800050c7:	50                   	push   rax
   1800050c8:	04 c0                	add    al,0xc0
   1800050ca:	02 d0                	add    dl,al

00000001800050cc <.xdata>:
   1800050cc:	01 00                	add    DWORD PTR [rax],eax
   1800050ce:	00 00                	add    BYTE PTR [rax],al
   1800050d0:	01 08                	add    DWORD PTR [rax],ecx
   1800050d2:	05 00 08 42 04       	add    eax,0x4420800
   1800050d7:	30 03                	xor    BYTE PTR [rbx],al
   1800050d9:	60                   	(bad)  
   1800050da:	02 70 01             	add    dh,BYTE PTR [rax+0x1]
   1800050dd:	50                   	push   rax
   1800050de:	00 00                	add    BYTE PTR [rax],al
   1800050e0:	01 06                	add    DWORD PTR [rsi],eax
   1800050e2:	03 00                	add    eax,DWORD PTR [rax]
   1800050e4:	06                   	(bad)  
   1800050e5:	c2 02 30             	ret    0x3002
   1800050e8:	01 60 00             	add    DWORD PTR [rax+0x0],esp
   1800050eb:	00 01                	add    BYTE PTR [rcx],al
   1800050ed:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .bss:

0000000180006000 <BS>:
	...

0000000180006008 <ST>:
	...

Disassembly of section .edata:

0000000180007000 <.edata>:
   180007000:	00 00                	add    BYTE PTR [rax],al
   180007002:	00 00                	add    BYTE PTR [rax],al
   180007004:	7d 81                	jge    180006f87 <__bss_end__+0xf77>
   180007006:	c3                   	ret    
   180007007:	61                   	(bad)  
   180007008:	00 00                	add    BYTE PTR [rax],al
   18000700a:	00 00                	add    BYTE PTR [rax],al
   18000700c:	04 71                	add    al,0x71
   18000700e:	00 00                	add    BYTE PTR [rax],al
   180007010:	01 00                	add    DWORD PTR [rax],eax
   180007012:	00 00                	add    BYTE PTR [rax],al
   180007014:	16                   	(bad)  
   180007015:	00 00                	add    BYTE PTR [rax],al
   180007017:	00 16                	add    BYTE PTR [rsi],dl
   180007019:	00 00                	add    BYTE PTR [rax],al
   18000701b:	00 28                	add    BYTE PTR [rax],ch
   18000701d:	70 00                	jo     18000701f <.edata+0x1f>
   18000701f:	00 80 70 00 00 d8    	add    BYTE PTR [rax-0x27ffff90],al
   180007025:	70 00                	jo     180007027 <.edata+0x27>
   180007027:	00 00                	add    BYTE PTR [rax],al
   180007029:	60                   	(bad)  
   18000702a:	00 00                	add    BYTE PTR [rax],al
   18000702c:	08 60 00             	or     BYTE PTR [rax+0x0],ah
   18000702f:	00 d0                	add    al,dl
   180007031:	1f                   	(bad)  
   180007032:	00 00                	add    BYTE PTR [rax],al
   180007034:	70 18                	jo     18000704e <.edata+0x4e>
   180007036:	00 00                	add    BYTE PTR [rax],al
   180007038:	40 18 00             	rex sbb BYTE PTR [rax],al
   18000703b:	00 00                	add    BYTE PTR [rax],al
   18000703d:	10 00                	adc    BYTE PTR [rax],al
   18000703f:	00 70 1c             	add    BYTE PTR [rax+0x1c],dh
   180007042:	00 00                	add    BYTE PTR [rax],al
   180007044:	10 18                	adc    BYTE PTR [rax],bl
   180007046:	00 00                	add    BYTE PTR [rax],al
   180007048:	a0 18 00 00 b0 18 00 	movabs al,ds:0xc0000018b0000018
   18000704f:	00 c0 
   180007051:	17                   	(bad)  
   180007052:	00 00                	add    BYTE PTR [rax],al
   180007054:	90                   	nop
   180007055:	21 00                	and    DWORD PTR [rax],eax
   180007057:	00 50 22             	add    BYTE PTR [rax+0x22],dl
   18000705a:	00 00                	add    BYTE PTR [rax],al
   18000705c:	90                   	nop
   18000705d:	18 00                	sbb    BYTE PTR [rax],al
   18000705f:	00 c0                	add    al,al
   180007061:	14 00                	adc    al,0x0
   180007063:	00 90 16 00 00 a0    	add    BYTE PTR [rax-0x5fffffea],dl
   180007069:	13 00                	adc    eax,DWORD PTR [rax]
   18000706b:	00 90 14 00 00 30    	add    BYTE PTR [rax+0x30000014],dl
   180007071:	18 00                	sbb    BYTE PTR [rax],al
   180007073:	00 d0                	add    al,dl
   180007075:	1e                   	(bad)  
   180007076:	00 00                	add    BYTE PTR [rax],al
   180007078:	60                   	(bad)  
   180007079:	19 00                	sbb    DWORD PTR [rax],eax
   18000707b:	00 50 19             	add    BYTE PTR [rax+0x19],dl
   18000707e:	00 00                	add    BYTE PTR [rax],al
   180007080:	10 71 00             	adc    BYTE PTR [rcx+0x0],dh
   180007083:	00 13                	add    BYTE PTR [rbx],dl
   180007085:	71 00                	jno    180007087 <.edata+0x87>
   180007087:	00 16                	add    BYTE PTR [rsi],dl
   180007089:	71 00                	jno    18000708b <.edata+0x8b>
   18000708b:	00 1d 71 00 00 2c    	add    BYTE PTR [rip+0x2c000071],bl        # 1ac007102 <__IAT_end__+0x2bfff0ee>
   180007091:	71 00                	jno    180007093 <.edata+0x93>
   180007093:	00 3a                	add    BYTE PTR [rdx],bh
   180007095:	71 00                	jno    180007097 <.edata+0x97>
   180007097:	00 43 71             	add    BYTE PTR [rbx+0x71],al
   18000709a:	00 00                	add    BYTE PTR [rax],al
   18000709c:	54                   	push   rsp
   18000709d:	71 00                	jno    18000709f <.edata+0x9f>
   18000709f:	00 66 71             	add    BYTE PTR [rsi+0x71],ah
   1800070a2:	00 00                	add    BYTE PTR [rax],al
   1800070a4:	6a 71                	push   0x71
   1800070a6:	00 00                	add    BYTE PTR [rax],al
   1800070a8:	74 71                	je     18000711b <.edata+0x11b>
   1800070aa:	00 00                	add    BYTE PTR [rax],al
   1800070ac:	7e 71                	jle    18000711f <.edata+0x11f>
   1800070ae:	00 00                	add    BYTE PTR [rax],al
   1800070b0:	87 71 00             	xchg   DWORD PTR [rcx+0x0],esi
   1800070b3:	00 8f 71 00 00 94    	add    BYTE PTR [rdi-0x6bffff8f],cl
   1800070b9:	71 00                	jno    1800070bb <.edata+0xbb>
   1800070bb:	00 a8 71 00 00 b2    	add    BYTE PTR [rax-0x4dffff8f],ch
   1800070c1:	71 00                	jno    1800070c3 <.edata+0xc3>
   1800070c3:	00 bc 71 00 00 c9 71 	add    BYTE PTR [rcx+rsi*2+0x71c90000],bh
   1800070ca:	00 00                	add    BYTE PTR [rax],al
   1800070cc:	db 71 00             	(bad)  [rcx+0x0]
   1800070cf:	00 e4                	add    ah,ah
   1800070d1:	71 00                	jno    1800070d3 <.edata+0xd3>
   1800070d3:	00 f1                	add    cl,dh
   1800070d5:	71 00                	jno    1800070d7 <.edata+0xd7>
   1800070d7:	00 00                	add    BYTE PTR [rax],al
   1800070d9:	00 01                	add    BYTE PTR [rcx],al
   1800070db:	00 02                	add    BYTE PTR [rdx],al
   1800070dd:	00 03                	add    BYTE PTR [rbx],al
   1800070df:	00 04 00             	add    BYTE PTR [rax+rax*1],al
   1800070e2:	05 00 06 00 07       	add    eax,0x7000600
   1800070e7:	00 08                	add    BYTE PTR [rax],cl
   1800070e9:	00 09                	add    BYTE PTR [rcx],cl
   1800070eb:	00 0a                	add    BYTE PTR [rdx],cl
   1800070ed:	00 0b                	add    BYTE PTR [rbx],cl
   1800070ef:	00 0c 00             	add    BYTE PTR [rax+rax*1],cl
   1800070f2:	0d 00 0e 00 0f       	or     eax,0xf000e00
   1800070f7:	00 10                	add    BYTE PTR [rax],dl
   1800070f9:	00 11                	add    BYTE PTR [rcx],dl
   1800070fb:	00 12                	add    BYTE PTR [rdx],dl
   1800070fd:	00 13                	add    BYTE PTR [rbx],dl
   1800070ff:	00 14 00             	add    BYTE PTR [rax+rax*1],dl
   180007102:	15 00 42 4f 4f       	adc    eax,0x4f4f4200
   180007107:	54                   	push   rsp
   180007108:	58                   	pop    rax
   180007109:	36 34 2e             	ss xor al,0x2e
   18000710c:	45                   	rex.RB
   18000710d:	46                   	rex.RX
   18000710e:	49 00 42 53          	rex.WB add BYTE PTR [r10+0x53],al
   180007112:	00 53 54             	add    BYTE PTR [rbx+0x54],dl
   180007115:	00 61 64             	add    BYTE PTR [rcx+0x64],ah
   180007118:	64 6d                	fs ins DWORD PTR es:[rdi],dx
   18000711a:	61                   	(bad)  
   18000711b:	70 00                	jo     18000711d <.edata+0x11d>
   18000711d:	64 72 61             	fs jb  180007181 <.edata+0x181>
   180007120:	77 5f                	ja     180007181 <.edata+0x181>
   180007122:	70 69                	jo     18000718d <.edata+0x18d>
   180007124:	78 65                	js     18000718b <.edata+0x18b>
   180007126:	6c                   	ins    BYTE PTR es:[rdi],dx
   180007127:	5f                   	pop    rdi
   180007128:	70 6f                	jo     180007199 <.edata+0x199>
   18000712a:	73 00                	jae    18000712c <.edata+0x12c>
   18000712c:	64 72 61             	fs jb  180007190 <.edata+0x190>
   18000712f:	77 5f                	ja     180007190 <.edata+0x190>
   180007131:	70 69                	jo     18000719c <.edata+0x19c>
   180007133:	78 65                	js     18000719a <.edata+0x19a>
   180007135:	6c                   	ins    BYTE PTR es:[rdi],dx
   180007136:	5f                   	pop    rdi
   180007137:	78 79                	js     1800071b2 <.edata+0x1b2>
   180007139:	00 65 66             	add    BYTE PTR [rbp+0x66],ah
   18000713c:	69 5f 6d 61 69 6e 00 	imul   ebx,DWORD PTR [rdi+0x6d],0x6e6961
   180007143:	66 65 74 63          	data16 gs je 1800071aa <.edata+0x1aa>
   180007147:	68 5f 6d 65 6d       	push   0x6d656d5f
   18000714c:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   18000714d:	72 79                	jb     1800071c8 <.edata+0x1c8>
   18000714f:	5f                   	pop    rdi
   180007150:	6d                   	ins    DWORD PTR es:[rdi],dx
   180007151:	61                   	(bad)  
   180007152:	70 00                	jo     180007154 <.edata+0x154>
   180007154:	67 65 74 5f          	addr32 gs je 1800071b7 <.edata+0x1b7>
   180007158:	67 72 61             	addr32 jb 1800071bc <.edata+0x1bc>
   18000715b:	70 68                	jo     1800071c5 <.edata+0x1c5>
   18000715d:	69 63 73 5f 6d 6f 64 	imul   esp,DWORD PTR [rbx+0x73],0x646f6d5f
   180007164:	65 00 69 6e          	add    BYTE PTR gs:[rcx+0x6e],ch
   180007168:	62                   	(bad)  
   180007169:	00 69 6e             	add    BYTE PTR [rcx+0x6e],ch
   18000716c:	69 74 5f 63 6f 6d 31 	imul   esi,DWORD PTR [rdi+rbx*2+0x63],0x316d6f
   180007173:	00 
   180007174:	6c                   	ins    BYTE PTR es:[rdi],dx
   180007175:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180007176:	63 61 74             	movsxd esp,DWORD PTR [rcx+0x74]
   180007179:	65 47                	gs rex.RXB
   18000717b:	4f 50                	rex.WRXB push r8
   18000717d:	00 6d 61             	add    BYTE PTR [rbp+0x61],ch
   180007180:	70 61                	jo     1800071e3 <.edata+0x1e3>
   180007182:	6c                   	ins    BYTE PTR es:[rdi],dx
   180007183:	6c                   	ins    BYTE PTR es:[rdi],dx
   180007184:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   180007185:	63 00                	movsxd eax,DWORD PTR [rax]
   180007187:	6d                   	ins    DWORD PTR es:[rdi],dx
   180007188:	61                   	(bad)  
   180007189:	70 66                	jo     1800071f1 <.edata+0x1f1>
   18000718b:	72 65                	jb     1800071f2 <.edata+0x1f2>
   18000718d:	65 00 6f 75          	add    BYTE PTR gs:[rdi+0x75],ch
   180007191:	74 62                	je     1800071f5 <.edata+0x1f5>
   180007193:	00 70 72             	add    BYTE PTR [rax+0x72],dh
   180007196:	69 6e 74 5f 61 6f 7a 	imul   ebp,DWORD PTR [rsi+0x74],0x7a6f615f
   18000719d:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   18000719e:	72 61                	jb     180007201 <__bss_end__+0x11f1>
   1800071a0:	5f                   	pop    rdi
   1800071a1:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800071a2:	65 6d                	gs ins DWORD PTR es:[rdi],dx
   1800071a4:	6f                   	outs   dx,DWORD PTR ds:[rsi]
   1800071a5:	72 79                	jb     180007220 <__bss_end__+0x1210>
   1800071a7:	00 70 72             	add    BYTE PTR [rax+0x72],dh
   1800071aa:	69 6e 74 5f 6d 61 70 	imul   ebp,DWORD PTR [rsi+0x74],0x70616d5f
   1800071b1:	00 70 72             	add    BYTE PTR [rax+0x72],dh
   1800071b4:	69 6e 74 5f 6e 75 6d 	imul   ebp,DWORD PTR [rsi+0x74],0x6d756e5f
   1800071bb:	00 70 72             	add    BYTE PTR [rax+0x72],dh
   1800071be:	69 6e 74 5f 73 74 72 	imul   ebp,DWORD PTR [rsi+0x74],0x7274735f
   1800071c5:	69 6e 67 00 73 65 74 	imul   ebp,DWORD PTR [rsi+0x67],0x74657300
   1800071cc:	5f                   	pop    rdi
   1800071cd:	67 72 61             	addr32 jb 180007231 <__bss_end__+0x1221>
   1800071d0:	70 68                	jo     18000723a <__bss_end__+0x122a>
   1800071d2:	69 63 73 5f 6d 6f 64 	imul   esp,DWORD PTR [rbx+0x73],0x646f6d5f
   1800071d9:	65 00 73 70          	add    BYTE PTR gs:[rbx+0x70],dh
   1800071dd:	6c                   	ins    BYTE PTR es:[rdi],dx
   1800071de:	69 74 6d 61 70 00 74 	imul   esi,DWORD PTR [rbp+rbp*2+0x61],0x72740070
   1800071e5:	72 
   1800071e6:	61                   	(bad)  
   1800071e7:	73 6c                	jae    180007255 <__bss_end__+0x1245>
   1800071e9:	61                   	(bad)  
   1800071ea:	74 65                	je     180007251 <__bss_end__+0x1241>
   1800071ec:	5f                   	pop    rdi
   1800071ed:	6d                   	ins    DWORD PTR es:[rdi],dx
   1800071ee:	61                   	(bad)  
   1800071ef:	70 00                	jo     1800071f1 <.edata+0x1f1>
   1800071f1:	77 72                	ja     180007265 <__bss_end__+0x1255>
   1800071f3:	69 74 65 5f 63 6f 6d 	imul   esi,DWORD PTR [rbp+riz*2+0x5f],0x316d6f63
   1800071fa:	31 
	...

Disassembly of section .idata:

0000000180008000 <__IAT_end__-0x14>:
	...

Disassembly of section .reloc:

0000000180009000 <.reloc>:
   180009000:	00 30                	add    BYTE PTR [rax],dh
   180009002:	00 00                	add    BYTE PTR [rax],al
   180009004:	0c 00                	or     al,0x0
   180009006:	00 00                	add    BYTE PTR [rax],al
   180009008:	d0                   	.byte 0xd0
   180009009:	a3                   	.byte 0xa3
   18000900a:	e0 a3                	loopne 180008faf <__IAT_end__+0xf9b>
