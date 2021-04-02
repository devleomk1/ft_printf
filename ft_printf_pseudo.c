/*
									서식지정자 별로 분리
								/-	c(char)		-\
ft_printf()	->	parse_symbol()	--	s(string)	--	print
								\-	others		-/
									|- d & i
									|- p (pointer)
									|- u (unsinged int 10base)
									|- x (lowcase int 16base)
									|- X (uppercase int 16base)
*/

/*
ft_printf.c
print_char.c
print_string.c
print_number.c
*/

/*
앞	중간	끝
___값___
000
*/

/*
구조체
int		minus	T/F
int		zero	T/F
int		width
int		precision
int		num_base
int		num_sign
char	type
*/
/*---------- prototype cal : num에서 전부 동일하게 연산------------*/
				int	len = 0;
				char tmp_num[21];
				//char c;
				if (num == 0)
					tmp_num[len++] = '0';
				else
				{
					while (num != 0)
					{
						tmp_num[len++] = DIGITS[num % info->num_base];
						num = num / info->num_base;
					}
				}
				if (info->precision < len)
					info->precision = len;
				info->width -= info->precision;
				if (info->minus == DISABLE && info->zero == DISABLE)
					while ((info->width)-- > 0)
						*str++ = ' ';
				/* -- number sign -- */
				if (info->num_sign == -1)
					*str++ = '-';
				/*-------- 수정 HERE! --------- */
				/*
				if (info->zero == DISABLE)
						while ((info->width)-- > 0)
							*str++ = '0';
				*/
				/* GAP PRINT */
				if (info->minus == DISABLE)
				{
					if (info->zero == ENABLE)
						while ((info->width)-- > 0)
								*str++ = '0';
					else if (info->zero == DISABLE)
						while ((info->width)-- > 0)
								*str++ = ' ';
				}
				while (len < (info->precision)--)
					*str++ = '0';

				/*-------- NUM 출력 --------*/
				while (len-- > 0)
					*str++ = tmp_num[len];
				while ((info->width)-- > 0)		//minus 일때 뒤쪽 width 남은거 출력
					*str++ = ' ';
				printed += write(1, temp, str - temp);
