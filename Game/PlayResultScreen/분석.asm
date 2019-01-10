loc_CBDB:
		les	bx, dword_11E6E
		mov	al, es:[bx+11h];//difficulty

loc_CBE3:
		;pesudo code
		mov	m_difficulty, al  ;m_difficulty = al
		mov	ax, list_x		  ;ax = list_x 
		add	ax, 0A0h          ;ax = ax + 0x0A0
		push	ax			  ;push ax to stack
		mov	ax, list_y 		  ;ax = list_y
		add	ax, 18h	          ;ax = ax + 0x18
		push	ax	          ;push ax to stack
		push	10h 	      ;push 0x10 to stack
		push	ds            ;push ds to stack
		mov	al, m_difficulty  ;al = m_difficulty
		mov	ah, 0	          ;ah = 0
		shl	ax, 3	          ;shift ax left 3 bits
		add	ax, offset grEASY ;difficulty :: ax = ax + (memory address of grEasy) ???
		push	ax			  ;push ax to stack
		push	word_116E4    ;push word_116E4 to stack
		call	graph_gaiji_puts ;call function graph_gaiji_puts
		
		mov	ax, list_x        ;ax = list_x
		add	ax, 80h           ;ax = ax + 0x80
		push	ax	          ;push ax to stack
		mov	ax, list_y        ;ax = list_y
		add	ax, 30h	          ;ax = ax + 0x30 
		push	ax            ;push ax to stack
		mov	ax, word ptr dword_11E6E ;ax = pointer (mem Addr)
		add	ax, 32	; ' ', Seems to be word is 32bit long?
		push	word ptr dword_11E6E+2 ;highest ptr of memAddr and push
		push	ax	; push the ax
		call	sub_C67F	;call sub_C67F??
		
		mov	ax, list_x		;ax = list_x
		add	ax, 0E0h ; '・	 ax = ax + 0x0E0h
		push	ax			;push ax to stack
		mov	ax, list_y		;ax = list_y
		add	ax, 48h	; 'H'	 ax = ax + 0x48
		push	ax			;push ax into stack
		les	bx, dword_11E6E	;Load Pointer using ES??? 
							;https://stackoverflow.com/questions/20434360/assembly-commands-lea-lds-les
							; =>
							;bx = dword_11E6E content
							;ds = dword_11E6E's memory address
							;es = dword_11E6E content
		mov	al, es:[bx+1Bh] ;miss - Maybe related to protected Memory? (Check article below)
							;https://pdos.csail.mit.edu/6.828/2005/readings/i386/s05_01.htm
		mov	ah, 0			;ah = 0
		push	ax			;push ax to stack
		call	sub_C5E7	;call function sub_C5E7
		
		
		mov	ax, list_x		;ax = list_x
		add	ax, 0E0h ; '・
		push	ax			;
		mov	ax, list_y
		add	ax, 60h
		push	ax
		les	bx, dword_11E6E
		mov	al, es:[bx+1Ch];bomb
		mov	ah, 0
		push	ax
		call	sub_C5E7
		
		
		mov	ax, list_x
		add	ax, 110h
		push	ax
		mov	ax, list_y
		add	ax, 48h	; 'H'
		push	ax
		push	word_116E4;times
		push	ds
		push	offset aI
		call	sub_E914
		
		
		mov	ax, list_x
		add	ax, 110h
		push	ax
		mov	ax, list_y
		add	ax, 60h
		push	ax
		push	word_116E4;times
		push	ds
		push	offset aI_0
		call	sub_E914
		
		
		mov	byte_1517C, 1
		les	bx, dword_11E6E
		if([bx+13h]!=6)//;is extra stage?
		{
			if([bx+1Ah]>=0xFE);1ah:END Prameter
				[bx+2Ch]=46000;

			mov	ax, list_x
			add	ax, 0B0h ; 'ｰ'
			push	ax
			mov	ax, list_y
			add	ax, 78h	
			push	ax
			push	46000
		}
		else
		{
			if([bx+1Ah]==0xFD)
				[bx+2Ch]=12800;

			mov	ax, list_x
			add	ax, 0B0h 
			push	ax
			mov	ax, list_y
			add	ax, 78h	
			push	ax
			push	12800
		}
		les	bx, dword_11E6E
		push	word ptr es:[bx+2Ch]
		call	print_similar_double
		
		
		mov	byte_1517C, 0
		mov	ax, list_x
		add	ax, 0B0h ; 'ｰ'
		push	ax
		mov	ax, list_y
		add	ax, 90h	; '・
		push	ax
		les	bx, dword_11E6E
		push	word ptr es:[bx+36h];悪霊退治率
		push	word ptr es:[bx+38h]
		call	print_similar_double
		
		
		mov	ax, list_x
		add	ax, 0B0h ; 'ｰ'
		push	ax
		mov	ax, list_y
		add	ax, 0A8h ; 'ｨ'
		push	ax
		les	bx, dword_11E6E
		push	word ptr es:[bx+2Eh]
		push	word ptr es:[bx+30h]
		call	print_similar_double
		
		
		mov	ax, list_x
		add	ax, 0B0h ; 'ｰ'
		push	ax
		mov	ax, list_y
		add	ax, 0C0h
		push	ax
		les	bx, dword_11E6E
		push	word ptr es:[bx+32h];得点アイテム最高点率
		push	word ptr es:[bx+34h]
		call	print_similar_double
		
		
		call	sub_C8AE
		mov	byte_116EA, 1
		mov	ax, list_x
		add	ax, 0B0h ; 'ｰ'
		push	ax
		mov	ax, list_y
		add	ax, 0F0h ; '・;"処理落ち率"
		push	ax
		les	bx, dword_11E6E
		
		eax=[bx+40h]
		ebx=10;
		edx=0;
		div	ebx
		push	ax
		
		mov	bx, word ptr dword_11E6E
		mov	eax, es:[bx+3Ch]
		ebx=10;
		edx=0;
		div	ebx
		push	ax
		call	print_similar_double
		
		
		mov	byte_116EA, 0
		m_ability/=12
		m_ability+=dword_15182

		
		if([bx+4Bh]>=10){
			m_ability+=500000
		}
		else{
		m_ability+= [bx+4Ah]*5000
		m_ability+= [bx+4Bh]*5000
		}

loc_CDF3:
		mov	ax, m_difficulty
		mov	bx, ax
		cmp	bx, 4
		ja	loc_CEAF
		add	bx, bx
		//;jmp	cs:off_D165[bx]
		switch case(bx)
		
loc_CE08:;case 0
		m_ability-=50000
		[bp+var_4]=800000
		jmp	loc_CEAF

loc_CE1C:;case 1
		[bp+var_4]=1000000;var_4=totalScore
		jmp	loc_CEAF

loc_CE27:;case 2
		m_ability*=5
		m_ability/=4
		m_ability+=150000
		[bp+var_4]=1200000
		jmp	short loc_CEAF

loc_CE55:;case 3
		m_ability*=3
		m_ability/=2
		m_ability+300000
		[bp+var_4]=1400000
		jmp	short loc_CEAF

loc_CE83:;case 4
		m_ability*=3
		m_ability/=2
		m_ability+250000
		[bp+var_4]=2000000
		
		
loc_CEAF:;default
		les	bx, dword_11E6E
		ax=[bx+0Dh]
		ax--;
		bx=ax;
		cmp	bx, 5
		ja	short loc_CF0A
		add	bx, bx
		jmp	cs:off_D159[bx]

loc_CEC8:;case 0
		m_ability+=50000
		[bp+var_4]+=100000
		jmp	short loc_CF0A

loc_CEDB:;case 1
		m_ability+=25000
		[bp+var_4]+=50000
		jmp	short loc_CF0A

loc_CEEE:;case 3
		[bp+var_4]-=25000
		jmp	short loc_CF0A

loc_CEF8:;case 4
		[bp+var_4]-=50000
		jmp	short loc_CF0A

loc_CF02:;case 5
		[bp+var_4]-=75000

loc_CF0A:;case 2;default
		if([bx+0Eh]==0){
			m_ability+=50000
			[bp+var_4]+=100000
		}
		else if([bx+0Eh]==1){
			m_ability+=30000
			[bp+var_4]+=50000
		}
		else if([bx+0Eh]==2){
			m_ability+=20000
			[bp+var_4]+=25000
		}
		
		if([bx+16h]==0){
			m_ability-=200000
			[bp+var_4]-=100000
		}

		if([bx+1Bh]>=10){
			m_ability-=300000
		}
		else{
			m_ability-=[bx+1Bh]*30000
		}
		
		if([bx+1Ch]>=15){
			m_ability-= 225000
		}
		else{
			m_ability-=[bx+1Ch]*15000
		}
		
		if([bx+1Ah]<0xFD){
		m_ability*=7
		m_ability/=8
		}

		if(m_ability<0){
			m_ability=0;
		}
		else{
			if(m_ability> [bp+var_4])
				m_ability=[bp+var_4]
		}
		mov	byte_15187, 0
		mov	byte_151A5, 0
		;mov	eax, es:[bx+40h]
		;shr	eax, 1
		if(([bx+40h]>>1)>[bx+3Ch])
		jbe	loc_D120
		
		mov	ax, list_x
		add	ax, 0B0h ; 'ｰ'
		push	ax
		mov	ax, list_y
		add	ax, 110h
		push	ax
		pushd	[m_ability]
		call	sub_C835
		
		mov	ax, list_x
		add	ax, 110h
		push	ax
		mov	ax, list_y
		add	ax, 110h
		push	ax
		push	word_116E4
		push	ds
		push	offset aU_
		call	sub_E914
		
		push	ds
		push	offset a_ude_txt ; "_ude.txt"
		call	file_ropen
		
		loc_D120:
		if(dword_1517E>=1500000)
		{
			printf(x=110h,"？？？？？？点")
			printf(x=128h,"処理落ちによる判定不可")
			;goto loc_D0E1;
		}
		if(dword_1517E==0)
		{
			si=25;
		}
		else if(dword_1517E<1050000)
		{
			bx=dword_1517E/50000;
			si=24-bx;
		}
		else if(dword_1517E<1200000)
		{
			si=3;
		}
		else if (dword_1517E<1350000)
		{
			si=2;
		}
		else
		{
			si=1;
		}
			
		char udeTxtFile[] = "_UDE.TXT";
		
		int fileIdx = CGame::s_pCurGame->m_kaiki1Dat.GetChildFileIndex(udeTxtFile);
		CGame::s_pCurGame->m_kaiki1Dat.Childfseek(fileIdx, si * 30, SEEK_SET);
		CGame::s_pCurGame->m_kaiki1Dat.Childfread(ability_cmt, 1, 30, fileIdx);
		call	sub_CA02
		CGame::s_pCurGame->m_kaiki1Dat.Childfseek(fileIdx, si * 30+780, SEEK_SET);
		CGame::s_pCurGame->m_kaiki1Dat.Childfread(ability_cmt_2, 1, 30, fileIdx);
		
	


//;[bx+1Ah]:End prameter
sub_CA02	
		if([bx+1Ah]==0xFF||[bx+1Ah]==0xFD); no continue
		{
			if([bx+11h]==0)//;difficulty
				ax=4;//目標：  ノーマルに挑戦しよう
			else if([bx+27h]<=7)//
				ax=1;//目標：  もっと稼ごう      
			else if([bx+1Bh]>=6)//;miss count
				ax=7;//目標：  ミスを減らそう
			else if([bx+0Ch]>=15)//;total used bomb?
				ax=8;//目標：  ボムを節約しよう
			else
				ax=0;//目標：  全一目指そう（笑）  
		}		
		else if([bx+1Ah]==0xFE); continue used
		{
				ax=2;//目標：１コインクリアをしよう
		}
		else; not cleared
		{
				ax=[bx+1Ch];//bomb count
				dx=[bx+1Bh];//miss count
				dx+=dx;
				if(ax<=dx)
					ax=5;//目標：　ボムを使って生きよう
				else
				{
					if([bx+13h]>=4||[bx+32h]<=350)//stage and high get score?
						ax=6;//目標：  得点アイテムを取ろう
					else
						ax=3;//目標：  クリアをしよう     
						
				}
				
		}

off_D159	dw offset loc_CEC8
		dw offset loc_CEDB
		dw offset loc_CF0A
		dw offset loc_CEEE
		dw offset loc_CEF8
		dw offset loc_CF02

off_D165	dw offset loc_CE08
		dw offset loc_CE1C
		dw offset loc_CE27
		dw offset loc_CE55
		dw offset loc_CE83

		
print_similar_double
sub_C729	proc near

var_6		= dword	ptr -6
var_2		= word ptr -2
arg_0		= word ptr  4;value?
arg_2		= word ptr  6;Total able? 
arg_4		= word ptr  8;y?
arg_6		= word ptr  0Ah;x?
;percent => arg0/arg_2?
		si=[bp+arg_6]
		di=[bp+arg_4]
		if([bp+arg_2]!= 0)
		{
			[bp+var_6]=1000000
		}
		else
		{
			[bp+var_6]=0
		}

		if([bp+arg_2]!=[bp+arg_0])
		{
			if([bp+arg_2]!=0)
			{
				ebx=[bp+arg_2]
				eax=[bp+var_6]
				edx=0
				div	ebx
				mov	[bp+var_6], eax
			}
			else{
				[bp+var_6]=0
			}
			[bp+var_6]*=[bp+arg_0]
		}
		
		if(byte_116EA==0)
		{
			eax=dword_1517E
			eax+=[bp+var_6]
		}
		else
		{
			eax=dword_1517E
			eax=+[bp+var_6]
		}
		dword_1517E=eax
		
		if(byte_1517C!=0)
		{
			eax=[bp+var_6]
			//;shr	eax, 2
			eax>>2
			dword_15182=eax
		}
		
		eax=[bp+var_6]
		ebx, 10000
		edx=0
		div	ebx
		[bp+var_2]=ax
		;push	si
		;push	di
		;push	ax
		;call	sub_C5E7
		
		ebx=10000
		eax=[bp+var_6]
		edx=0
		div	ebx
		[bp+var_6]=edx
		eax=[bp+var_6]
		ebx=100 ; 'd'
		edx=0
		div	ebx
		[bp+var_2]=ax
		byte_11713=1
		lea	ax, [si+30h]
		push	ax
		push	di
		push	[bp+var_2]
		call	sub_C5E7
		
		mov	byte_11713, 0
		lea	ax, [si+30h]
		push	ax
		push	di
		push	word_116E4
		push	ds
		push	offset aBd
		call	sub_E914
		
		lea	ax, [si+60h]
		push	ax
		push	di
		push	word_116E4
		push	ds
		push	offset aBu
		call	sub_E914
		pop	di
		pop	si
		leave
		retn	8
sub_C729	endp
