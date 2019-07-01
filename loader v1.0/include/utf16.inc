
; UTF-16

macro du [arg]
{
			local current,char
			if arg eqtype ''
					virtual at 0
						db	arg
						count	=	$
					end virtual
					current	=	0
					while	current <	count
							virtual	at	0
									db	arg
									load  char  byte from  current
									wide=char										
									virtual at 0
											file 'utf16':char*2,2
											load  char word from 0
									end virtual
									current	=	current+1
											if char <>	0
													wide	=		char
													if current < count
															load  char byte from current
															wide=(wide+char)*2
															virtual at 0
																file 'utf16':wide,2
																load  wide  word  from 0
															end virtual
															
													else
															wide	=		0
													end if
													current	=	current	+	1
											end if
							end virtual
							dw  wide
					end while
			else
					dw  arg
			end if
}

struc du [args]
 { 
 		common label . word
   	du args
   	.size=$-.
 }								
			
		