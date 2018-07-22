; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_E41D	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		word_116E2=20h	; ' '
		word_116E4=0Dh
		word_116E6=0Dh
		word_116E8=10h
		mov	PaletteTone, 0
		call	far ptr	palette_show
		call	grcg_setcolor pascal, (GC_RMW shl 16) + 1
		mov	dx, 0A6h ; 'ｦ'
		mov	al, 0
		out	dx, al
		pushd	0
		push	4F018Fh
		call	grcg_byteboxfill_x
		mov	dx, 7Ch
		mov	al, GC_OFF
		out	dx, al
		call	sub_D21D
		push	3700h
		call	sub_E39F
		call	grcg_setcolor pascal, (GC_RMW shl 16) + 1
		pushd	0
		push	4F018Fh
		call	grcg_byteboxfill_x
		mov	dx, 0A6h ; 'ｦ'
		mov	al, 1
		out	dx, al
		pushd	0
		push	4F018Fh
		call	grcg_byteboxfill_x
		mov	dx, 7Ch
		mov	al, GC_OFF
		out	dx, al
		call	snd_load pascal, ds, offset aStaff, SND_LOAD_SONG
		kajacall	KAJA_SONG_PLAY
		push	0
		push	ds
		push	offset aStf00_cdg ; "stf00.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	1
		push	ds
		push	offset aStf01_cdg ; "stf01.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	2
		push	ds
		push	offset aStf02_cdg ; "stf02.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	3
		push	ds
		push	offset aStf03_cdg ; "stf03.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	4
		push	ds
		push	offset aStf04_cdg ; "stf04.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	5
		push	ds
		push	offset aStf05_cdg ; "stf05.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	6
		push	ds
		push	offset aStf06_cdg ; "stf06.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	7
		push	ds
		push	offset aStf07_cdg ; "stf07.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	8
		push	ds
		push	offset aStf08_cdg ; "stf08.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	9
		push	ds
		push	offset aStf09_cdg ; "stf09.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		push	10
		push	ds
		push	offset aStf10_cdg ; "stf10.cdg"
		call	LoadCD2CDGAllSpriteFromDat
		
		push	ds
		push	offset aStf01_bft ; "stf01.bft"
		call	super_entry_bfnt
		push	ds
		push	offset aStf00_bft ; "stf00.bft"
		call	super_entry_bfnt
		for(si=0;si<8;si++)
		{
			push	si
			call	super_convert_tiny
		}	
		mov	Palettes+2, 30h	; '0'
		call	sub_D387
		si=0;
		mov	word_151E2, 0

loc_E565:
		cmp	si, 64h	; 'd'
		jg	short loc_E573
		mov	PaletteTone, si
		call	far ptr	palette_show

loc_E573:
		call	sub_E349
		inc	si
		if(word_151E0>=30)
		{
			call	sub_D49D
			for(si=0; si<32; si++)
			{
			call	sub_D8F5
			call	sub_E349
			inc	si
			}
		}

		

loc_E594:
		call	sub_D931
		si=ax;
		call	sub_E349
		if(si==0)
			goto loc_E594
		if(word_151E0< 30h)	; '0'
			goto loc_E594
			
		si= si
		di= di

loc_E5AB:
		call	sub_D931
		if(si> 80h)
		{
			push	0210 00F0h ;x=528, y=240
			push	0001 004Ch;Mystic square ;for 76frame
			call	sub_DE74 ;ax counter?
			if(ax!=0)
				si=0;
		}
		push	01D0 00C0h  ;x=464, y=192
		pushd	0000 004Ch ;????? ;for 76frame
		call	sub_DCFC
		di=ax
		call	sub_E349 ;di counter?
		si++			;si count;after this, Yin-Yang bullet curves to left	
		if(di==0)		;if((di!=0)==0)
			goto loc_E5AB
		
		di=0

loc_E5E1:
		call	sub_D931
		push	01D000C8h  ;x=464, y=200
		push	0002005Ch;STAFF for 84 frame
		call		
		di= ax
		call	sub_E349
		if(di==0)
			goto loc_E5E1
		si=0
		di=0

loc_E600:
		call	sub_D931
		if(si> 100h)
		{
			push	01D000E0h
			push	00040078h;ZUN(?????)
			call	sub_DE74
			if(ax!=0)
				si=0;
		}
		push	01D000B0h
		push	00030078h;Programing Graphics and Music
		call	sub_DCFC
		di=ax
		call	sub_E349
		si++				;si count;after this, Yin-Yang bullet brust
		if(di==0)
			goto loc_E600
		call	sub_D531

loc_E63A:
		call	sub_DAD7
		si=ax
		call	sub_E349
		if(si==0)
			goto loc_E63A
		di=0

loc_E648:
		call	sub_DAD7
		push	00B000C8h
		push	000500ACh;Special Tanks	
		call	sub_DCFC
		di=ax
		call	sub_E349
		if(di==0)
			goto loc_E648

loc_E663:
		call	sub_DAD7
		push	00B000C8h
		push	000600BCh;Atoka
		call	sub_DCFC
		mov	di, ax
		call	sub_E349
		or	di, di
		jz	short loc_E663

loc_E67E:
		call	sub_DAD7
		push	00B000C8h
		push	000700CCh;??????
		call	sub_DCFC
		mov	di, ax
		call	sub_E349
		or	di, di
		jz	short loc_E67E

loc_E699:
		call	sub_DAD7
		push	00B000C8h
		push	000800DCh;PMD??-KAJA
		call	sub_DCFC
		mov	di, ax
		call	sub_E349
		or	di, di
		jz	short loc_E699

loc_E6B4:
		call	sub_DAD7
		push	00B000C8h
		push	000900ECh;And You..
		call	sub_DCFC
		mov	di, ax
		call	sub_E349
		or	di, di
		jz	short loc_E6B4
		xor	si, si
		mov	[bp+var_2], 0
		mov	[bp+var_4], 0

loc_E6DB:
		call	sub_F202
		if(si== 100h||si == 101h);if(si==128)
		{
l			call	sub_CA9B
			}
		else if(si== 140h||si == 141h)
		{
			call	sub_D16F
		}
		else if(si== 15Eh)
		{
			push	0
			call	sub_E39F
		}


loc_E70D:
		call	sub_DAD7
		push	00B00170h
		push	000A0F9Ch;1998(c)ZuN c55 version
		call	sub_DCFC
		inc	si
		cmp	si, 190h
		jl	loc_E7BB
		test	byte ptr word_key_input_+1, 10h
		jnz	short loc_E757
		test	byte ptr word_key_input_, 10h
		jnz	short loc_E757
		cmp	[bp+var_4], 0
		jnz	short loc_E781
		test	byte ptr word_key_input_, 20h
		jnz	short loc_E74A
		test	byte ptr word_key_input_+1, 20h
		jz	short loc_E75C

loc_E74A:
		cmp	[bp+var_2], 0
		jnz	short loc_E757
		mov	[bp+var_4], 1
		jmp	short loc_E75C
; ---------------------------------------------------------------------------

loc_E757:
		call	sub_E349
		jmp	short loc_E7C1
; ---------------------------------------------------------------------------

loc_E75C:
		test	byte ptr word_key_input_, 2
		jz	short loc_E76E
		cmp	[bp+var_2], 0
		jnz	short loc_E76E
		mov	[bp+var_4], 1

loc_E76E:
		test	byte ptr word_key_input_, 1
		jz	short loc_E781
		cmp	[bp+var_2], 3700h
		jnz	short loc_E781
		mov	[bp+var_4], 2

loc_E781:
		if([bp+var_4]!= 1)
			goto loc_E79A
		
		[bp+var_2]+= 140h
		if([bp+var_2]<=3700h
			goto loc_E7B5
		[bp+var_2]= 3700h
		jmp	short loc_E7B0
; ---------------------------------------------------------------------------

loc_E79A:
		cmp	[bp+var_4], 2
		jnz	short loc_E7BB
		sub	[bp+var_2], 140h
		cmp	[bp+var_2], 0
		jge	short loc_E7B5
		[bp+var_2]= 0

loc_E7B0:
		mov	[bp+var_4], 0

loc_E7B5:
		push	[bp+var_2]
		call	sub_E3CA

loc_E7BB:
		call	sub_E349
		jmp	loc_E6DB
; ---------------------------------------------------------------------------

loc_E7C1:
		kajacall	KAJA_SONG_FADE, 4
		mov	si, 64h	; 'd'

loc_E7CC:
		mov	PaletteTone, si
		call	far ptr	palette_show
		call	sub_DAD7
		call	sub_E349
		dec	si
		or	si, si
		jg	short loc_E7CC
		call	sub_F3EE
		call	super_free
		pushd	0
		push	27F018Fh
		call	grc_setclip
		pop	di
		pop	si
		leave
		retn
sub_E41D	endp
; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D49D	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 50E4h
		xor	di, di
		jmp	short loc_D4ED
; ---------------------------------------------------------------------------

loc_D4A9:
		mov	ax, [si+4]
		neg	ax
		push	ax
		mov	ax, [si]
		neg	ax
		push	ax
		call	iatan2
		mov	[si+12h], al
		push	word ptr [si]
		push	word ptr [si+4]
		call	ihypot
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+0Eh], ax
		mov	word ptr [si+10h], 0
		lea	ax, [si+8]
		push	ax
		pushd	0
		push	word ptr [si+0Eh]
		mov	al, [si+12h]
		mov	ah, 0
		push	ax
		call	vector2_at
		inc	di
		add	si, 14h

loc_D4ED:
		cmp	di, 40h
		jl	short loc_D4A9
		mov	dword ptr [si],	0
		mov	dword ptr [si+4], 0
		mov	byte ptr [si+13h], 1
		pop	di
		pop	si
		pop	bp
		retn
sub_D49D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_D8F5	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 50E4h
		xor	cx, cx
		jmp	short loc_D91D
; ---------------------------------------------------------------------------

loc_D900:
		inc	word ptr [si+10h]
		mov	ax, [si+10h]
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_D919
		cmp	word ptr [si+0Ch], 5
		jge	short loc_D919
		inc	word ptr [si+0Ch]

loc_D919:
		inc	cx
		add	si, 14h

loc_D91D:
		cmp	cx, 40h
		jl	short loc_D900
		cmp	byte ptr [si+13h], 10h
		jnb	short loc_D92E
		mov	al, byte_1183A
		add	[si+13h], al

loc_D92E:
		pop	si
		pop	bp
		retn
sub_D8F5	endp

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_E349	proc near
		push	bp
		mov	bp, sp
		call	sub_D5E1
		call	sub_DFEC
		push	1
		call	frame_delay
		mov	dx, 0A6h ; 'ｦ'
		mov	al, byte_1183A
		out	dx, al
		mov	al, 1
		sub	al, byte_1183A
		mov	byte_1183A, al
		mov	dx, 0A4h
		out	dx, al
		cmp	byte_11846, 0
		jz	short loc_E37E
		call	text_clear
		mov	byte_11846, 0

loc_E37E:
		inc	word_151E2
		call	sub_F23C
		mov	word_151E0, ax
		cmp	word_151E0, 0
		jge	short loc_E39D
		mov	ax, word_151E2
		mov	bx, 16h
		cwd
		idiv	bx
		mov	word_151E0, ax

loc_E39D:
		pop	bp
		retn
sub_E349	endp
; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame



sub_DCFC	proc near

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		enter	4, 0
		push	si
		push	di
		mov	di, [bp+arg_4]
		mov	ax, [bp+arg_2]
		shl	ax, 4
		add	ax, 29FEh
		mov	si, ax
		mov	ax, [si+2]
		cwd
		sub	ax, dx
		sar	ax, 1
		sub	[bp+arg_6], ax
		mov	ax, [si+4]
		cwd
		sub	ax, dx
		sar	ax, 1
		sub	di, ax
		cmp	word_11848, 1
		jg	loc_DDBC
		mov	ax, [si+2]
		mov	bx, 10h
		cwd
		idiv	bx
		add	ax, 7
		mov	word_151C4, ax
		mov	word_151C6, 0
		inc	word_11848
		push	[bp+arg_6]
		push	di
		push	[bp+arg_2]
		call	sub_EA6E
		mov	[bp+var_2], 0
		jmp	short loc_DDB1
; ---------------------------------------------------------------------------

loc_DD5A:
		mov	[bp+var_4], 0
		jmp	short loc_DDA2
; ---------------------------------------------------------------------------

loc_DD61:
		mov	ax, [bp+arg_6]
		mov	bx, 8
		cwd
		idiv	bx
		push	ax
		mov	ax, [bp+var_4]
		cwd
		idiv	bx
		pop	dx
		add	dx, ax
		cmp	dx, 50h	; 'P'
		jge	short loc_DD9E
		mov	ax, [bp+arg_6]
		cwd
		idiv	bx
		push	ax
		mov	ax, [bp+var_4]
		cwd
		idiv	bx
		pop	dx
		add	dx, ax
		push	dx
		mov	ax, di
		mov	bx, 10h
		cwd
		idiv	bx
		push	ax
		push	ds
		push	offset unk_1184C
		push	TX_BLACK + TX_REVERSE
		call	text_putsa

loc_DD9E:
		add	[bp+var_4], 10h

loc_DDA2:
		mov	ax, [si+2]
		cmp	ax, [bp+var_4]
		jge	short loc_DD61
		add	[bp+var_2], 10h
		add	di, 10h

loc_DDB1:
		mov	ax, [si+4]
		cmp	ax, [bp+var_2]
		jge	short loc_DD5A
		jmp	loc_DE6C
; ---------------------------------------------------------------------------

loc_DDBC:
		cmp	word_11848, 3
		jg	short loc_DE01
		inc	word_151C6
		mov	ax, word_151C6
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_DDD8
		dec	word_151C4

loc_DDD8:
		push	[bp+arg_6]
		push	di
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word_151C4
		push	1
		call	sub_DBE6
		cmp	al, 1
		jnz	short loc_DE6C
		inc	word_11848
		mov	word_151C4, 0
		mov	word_151C6, 0
		jmp	short loc_DE6C
; ---------------------------------------------------------------------------

loc_DE01:
		mov	ax, word_151E0
		cmp	ax, [bp+arg_0]
		jl	short loc_DE6C
		cmp	[bp+arg_0], 0F9Ch
		jz	short loc_DE6C
		cmp	word_11848, 4
		jnz	short loc_DE49
		inc	word_151C6
		mov	ax, word_151C6
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_DE2C
		inc	word_151C4

loc_DE2C:
		push	[bp+arg_6]
		push	di
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word_151C4
		push	0FFFFh
		call	sub_DBE6
		cmp	al, 2
		jnz	short loc_DE6C
		inc	word_11848
		jmp	short loc_DE6C
; ---------------------------------------------------------------------------

loc_DE49:
		push	[bp+arg_6]
		push	di
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	80FFFFh
		call	sub_DBE6
		mov	word_11848, 0
		mov	byte_11846, 1
		mov	ax, 1
		jmp	short loc_DE6E
; ---------------------------------------------------------------------------

loc_DE6C:
		xor	ax, ax

loc_DE6E:
		pop	di
		pop	si
		leave
		retn	8
sub_DCFC	endp
