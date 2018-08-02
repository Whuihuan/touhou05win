
typedef struct strPARTICLE{
	//0
	//4
	//unsigned char flag;		//
	//unsigned char age;		//
	//unsigned short curX;	//8
	//unsigned short curY;	//10
	//unsigned short lastR;	//12
	//unsigned short curR;	//14
	//unsigned short vel;		
	
	unsigned char angle;	//18
	unsigned char img;		//19
}PARTICLE;

sub_D387	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	si, 50E4h
		mov	[bp+var_2], 55F8h
		mov	[bp+var_4], 5618h
		push	0140 00C8h
		push	0180 0140h
		call	sub_D31F
		mov	word_151DE, 0
		di=0
		jmp	short loc_D41B
; ---------------------------------------------------------------------------

loc_D3B3:
		
		[si+ 0]=rand()%word_151CE<<4-word_151CE<<3
		[si+ 4]=rand()%word_151D0<<4-word_151D0<<3
		[si+12]=0
		[si+14]=10
		[si+18]=rand()%256
		[si+19]=0
		
		vector2_at([si+18],[si+14],0,0,[si+ 8])
		di++
		si+=20

loc_D41B:
		cmp	di, 64
		jl	short loc_D3B3
		
		[si+ 0]=0xFFFFC190;dword
		[si+ 8], 0
		[si+10], 0
		[si+19], 0
		word_151DA=0
		word_151DC=0
		di=0
		jmp	short loc_D451
; ---------------------------------------------------------------------------

loc_D445:
		bx=[bp+var_2];64th(zero-base) particle
		[bx]=0xC190;word
		di++
		[bp+var_2]+=4

loc_D451:
		cmp	di, 8
		jl	short loc_D445
		
		di=0;
		jmp	short loc_D494
; ---------------------------------------------------------------------------

loc_D45A:
		
		bx=[bp+var_4]
		[bx]=rand()%word_151CE<<4-word_151CE<<3
		bx=[bp+var_4]
		[bx+ 2]=rand()%word_151D0<<4-word_151D0<<3
		di++
		[bp+var_4]+=4

loc_D494:
		cmp	di, 48	; '0'
		jl	short loc_D45A
		
		pop	di
		pop	si
		leave
		retn
sub_D387	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D49D	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 50E4h
		di=0
		jmp	short loc_D4ED
; ---------------------------------------------------------------------------

loc_D4A9:
		[si+18]=iatan2((-1)*[si],(-1)*[si+4])%256
		
		[si+14]=ihypot((word)[si+4],(word)[si])/32
		[si+16]=0
		call	vector2_at([si+18]%256,[si+14],(dword)0,&[si+8])
		di++
		si+=20

loc_D4ED:
		cmp	di, 64
		jl	short loc_D4A9
		(dword)[si]=0
		(dword)[si+4]=0
		(byte)[si+19]=1
		pop	di
		pop	si
		pop	bp
		retn
sub_D49D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D509	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 50E4h
		ax=0
		jmp	short loc_D51F
; ---------------------------------------------------------------------------

loc_D514:
		mov	dword ptr [si],	0FFFFC190h
		ax++
		si+=20

loc_D51F:
		cmp	ax, 64
		jl	short loc_D514
		(byte)[si+19]=16
		mov	word_151DE, 1
		pop	si
		pop	bp
		retn
sub_D509	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D531	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 50E4h
		di=0
		jmp	loc_D5C9
; ---------------------------------------------------------------------------

loc_D53E:
		mov	ax, [si+4]
		neg	ax
		push	ax
		mov	ax, [si]
		neg	ax
		push	ax
		call	iatan2
		[si+12h]=ax%256
		push	word ptr [si]
		push	word ptr [si+4]
		call	ihypot
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+0Eh], ax
		mov	word ptr [si+0Ch], 0
		call	IRand
		and	al, 7Fh
		[si+12h]=ax%256
		call	IRand
		mov	bx, 40h
		cwd
		idiv	bx
		add	dx, 5Ch
		mov	[si+0Eh], dx
		push	50D2h
		push	word_156E4
		push	word_156E8
		push	0C0h
		ax=[si+12h]%256
		call	vector2_at
		lea	ax, [si+8]
		push	ax
		pushd	0
		push	word ptr [si+0Eh]
		ax=[si+12h]%256
		push	ax
		call	vector2_at
		movsx	eax, word_151D2
		mov	[si], eax
		movsx	eax, word_151D4
		mov	[si+4],	eax
		inc	di
		si+=20

loc_D5C9:
		cmp	di, 40h
		jl	loc_D53E
		mov	dword ptr [si],	0FFFFC190h
		mov	word_151DE, 1
		pop	di
		pop	si
		pop	bp
		retn
sub_D531	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D5E1	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	si, 50E4h
		mov	[bp+var_4], 55F8h
		mov	di, 5618h
		mov	[bp+var_2], 0
		jmp	loc_D6FF
; ---------------------------------------------------------------------------

loc_D5FA:
		cmp	dword ptr [si],	0FFFFC190h
		jz	loc_D6F9
		mov	ax, [si+8]
		sub	ax, word_151DA
		cwde
		add	[si], eax
		mov	ax, [si+0Ah]
		sub	ax, word_151DC
		cwde
		add	[si+4],	eax
		cmp	word_151DE, 0
		jnz	loc_D6AB
		mov	ax, word_151CE
		neg	ax
		shl	ax, 3
		add	ax, 0FFC0h
		cwde
		cmp	eax, [si]
		jl	short loc_D649
		mov	ax, word_151CE
		shl	ax, 4
		add	ax, 80h
		cwde
		add	[si], eax
		jmp	short loc_D667
; ---------------------------------------------------------------------------

loc_D649:
		mov	ax, word_151CE
		shl	ax, 3
		add	ax, 40h
		cwde
		cmp	eax, [si]
		jg	short loc_D667
		mov	ax, word_151CE
		shl	ax, 4
		add	ax, 80h
		cwde
		sub	[si], eax

loc_D667:
		mov	ax, word_151D0
		neg	ax
		shl	ax, 3
		add	ax, 0FFC0h
		cwde
		cmp	eax, [si+4]
		jl	short loc_D68B
		mov	ax, word_151D0
		shl	ax, 4
		add	ax, 80h
		cwde
		add	[si+4],	eax
		jmp	short loc_D6AB
; ---------------------------------------------------------------------------

loc_D68B:
		mov	ax, word_151D0
		shl	ax, 3
		add	ax, 40h
		cwde
		cmp	eax, [si+4]
		jg	short loc_D6AB
		mov	ax, word_151D0
		shl	ax, 4
		add	ax, 80h
		cwde
		sub	[si+4],	eax

loc_D6AB:
		cmp	word_151DE, 0
		jz	short loc_D6F9
		mov	ax, word_151DE
		sub	[si+0Eh], ax
		cmp	word ptr [si+0Eh], 0
		jnz	short loc_D6C7
		mov	dword ptr [si],	0FFFFC190h
		jmp	short loc_D6F9
; ---------------------------------------------------------------------------

loc_D6C7:
		cmp	word ptr [si+0Eh], 23h ; '#'
		jle	short loc_D6D4
		mov	word ptr [si+0Ch], 0
		jmp	short loc_D6E4
; ---------------------------------------------------------------------------

loc_D6D4:
		mov	ax, [si+0Eh]
		mov	bx, 7
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_D6E4
		inc	word ptr [si+0Ch]

loc_D6E4:
		lea	ax, [si+8]
		push	ax
		pushd	0
		push	word ptr [si+0Eh]
		ax=[si+12h]%256
		push	ax
		call	vector2_at

loc_D6F9:
		inc	[bp+var_2]
		si+=20

loc_D6FF:
		cmp	[bp+var_2], 40h
		jl	loc_D5FA
		mov	[bp+var_2], 0
		jmp	short loc_D72C
; ---------------------------------------------------------------------------

loc_D70E:
		mov	bx, [bp+var_4]
		cmp	word ptr [bx], 0C190h
		jz	short loc_D725
		mov	bx, [bp+var_4]
		mov	ax, word_151DA
		sub	[bx], ax
		mov	ax, word_151DC
		sub	[bx+2],	ax

loc_D725:
		inc	[bp+var_2]
		add	[bp+var_4], 4

loc_D72C:
		cmp	[bp+var_2], 8
		jl	short loc_D70E
		mov	[bp+var_2], 0
		jmp	loc_D7F8
; ---------------------------------------------------------------------------

loc_D73A:
		mov	ax, [bp+var_2]
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_D751
		mov	ax, word_151DA
		sub	[di], ax
		mov	ax, word_151DC
		jmp	short loc_D763
; ---------------------------------------------------------------------------

loc_D751:
		mov	ax, word_151DA
		cwd
		sub	ax, dx
		sar	ax, 1
		sub	[di], ax
		mov	ax, word_151DC
		cwd
		sub	ax, dx
		sar	ax, 1

loc_D763:
		sub	[di+2],	ax
		cmp	word_151DA, 0
		jnz	short loc_D7A5
		mov	ax, word_151CE
		neg	ax
		shl	ax, 3
		cmp	ax, [di]
		jge	short loc_D783
		mov	ax, word_151CE
		shl	ax, 3
		cmp	ax, [di]
		jg	short loc_D7CA

loc_D783:
		call	IRand
		cwd
		idiv	word_151CE
		shl	dx, 4
		mov	ax, word_151CE
		shl	ax, 3
		sub	dx, ax
		mov	[di], dx
		mov	ax, word_151D0
		shl	ax, 3
		mov	[di+2],	ax
		jmp	short loc_D7CA
; ---------------------------------------------------------------------------

loc_D7A5:
		mov	ax, word_151CE
		neg	ax
		shl	ax, 3
		cmp	ax, [di]
		jl	short loc_D7B6
		mov	ax, word_151CE
		jmp	short loc_D7C5
; ---------------------------------------------------------------------------

loc_D7B6:
		mov	ax, word_151CE
		shl	ax, 3
		cmp	ax, [di]
		jg	short loc_D7CA
		mov	ax, word_151CE
		neg	ax

loc_D7C5:
		shl	ax, 3
		mov	[di], ax

loc_D7CA:
		mov	ax, word_151D0
		neg	ax
		shl	ax, 3
		cmp	ax, [di+2]
		jl	short loc_D7DC
		mov	ax, word_151D0
		jmp	short loc_D7EC
; ---------------------------------------------------------------------------

loc_D7DC:
		mov	ax, word_151D0
		shl	ax, 3
		cmp	ax, [di+2]
		jg	short loc_D7F2
		mov	ax, word_151D0
		neg	ax

loc_D7EC:
		shl	ax, 3
		mov	[di+2],	ax

loc_D7F2:
		inc	[bp+var_2]
		add	di, 4

loc_D7F8:
		cmp	[bp+var_2], 30h	; '0'
		jl	loc_D73A
		mov	si, 55E4h
		cmp	dword ptr [si],	0FFFFC190h
		jz	short loc_D83F
		mov	ax, [si+8]
		sub	ax, word_151DA
		cwde
		add	[si], eax
		mov	ax, [si+0Ah]
		sub	ax, word_151DC
		cwde
		add	[si+4],	eax
		cmp	byte ptr [si+13h], 10h
		jb	short loc_D83F
		cmp	byte_1183A, 0
		jz	short loc_D83F
		call	sub_D853
		cmp	word ptr [si+0Ah], 0B4h	; 'ｴ'
		jge	short loc_D83F
		inc	word ptr [si+0Ah]

loc_D83F:
		mov	ax, word_151E2
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_D84F
		call	sub_D8B6

loc_D84F:
		pop	di
		pop	si
		leave
		retn
sub_D5E1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D853	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_1183C
		inc	word_1183C
		imul	ax, 14h
		add	ax, 50E4h
		mov	si, ax
		mov	word ptr [si+0Ch], 0
		call	IRand
		and	al, 7Fh
		[si+12h]=ax%256
		mov	word ptr [si+0Eh], 30h ; '0'
		push	50D2h
		push	word_156E4
		push	word_156E8
		push	0C0h
		ax=[si+12h]%256
		push	ax
		call	vector2_at
		movsx	eax, word_151D2
		mov	[si], eax
		movsx	eax, word_151D4
		mov	[si+4],	eax
		cmp	word_1183C, 40h
		jl	short loc_D8B3
		mov	word_1183C, 0

loc_D8B3:
		pop	si
		pop	bp
		retn
sub_D853	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D8B6	proc near
		push	bp
		mov	bp, sp
		mov	dx, 6
		jmp	short loc_D8E3
; ---------------------------------------------------------------------------

loc_D8BE:
		mov	bx, dx
		shl	bx, 2
		mov	ax, [bx+55F8h]
		mov	bx, dx
		shl	bx, 2
		mov	[bx+55FCh], ax
		mov	bx, dx
		shl	bx, 2
		mov	ax, [bx+55FAh]
		mov	bx, dx
		shl	bx, 2
		mov	[bx+55FEh], ax
		dec	dx

loc_D8E3:
		or	dx, dx
		jge	short loc_D8BE
		mov	ax, word_156E4
		mov	word_156F8, ax
		mov	ax, word_156E8
		mov	word_156FA, ax
		pop	bp
		retn
sub_D8B6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D8F5	proc near;praticle staff relate
		push	bp
		mov	bp, sp
		push	si
		mov	si, 50E4h
		cx=0
		
		jmp	short loc_D91D
; ---------------------------------------------------------------------------

loc_D900:
		(word)[si+10h]++
		if([si+10h]%8==0 && (word)[si+0Ch]<5)
			[si+0Ch]++
			
		cx++
		si=+20

loc_D91D:
		cmp	cx, 64
		jl	short loc_D900
		
		if((byte)[si+13h]>16)
			[si+13h]+=byte_1183A%256

		pop	si
		pop	bp
		retn
sub_D8F5	endp
