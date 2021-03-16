#include <unistd.h>
#include <stdarg.h>

#define max_value(a, b) ((a < b) ? b : a)
#define ft_isdigit(c) (((c) >= '0' && (c) <= '9') ? 1 : 0)
#define digit "0123456789abcdefg"

int		ft_strlen(char *fmt)
{
	int		count;

	count = 0;
	while (*fmt++ != '\0')
		count++;
	return (count);
}

char	*ft_strchr(char *fmt, int c)
{
	while (*fmt != c)
	{
		if (!*fmt)
			return (0);
		fmt++;
	}
	return (fmt);
}

int		read_integer(char **fmt) // width, prec를 int로 변경하여 변수에 전달.
{
	int		result;

	result = **fmt - '0';
	*fmt = ++(*fmt);
	while (ft_isdigit(**fmt))
	{
		result = result * 10 + (**fmt - '0');
		*fmt = ++(*fmt);
	}
	return (result);
}

int		outstring(char *fmt, int len) // len 기준으로 문장을 출력
{
	write(1, fmt, len);
	return (len);
}

int		print_width_prec(int pad, int len) // 갯수만큼 패딩을 출력
{
	int count;

	count = 0;
	if (len > 0)
		while (count++ < len)
			write(1, &pad, 1);
	return (len);
}

int		process(char **fmt, va_list arg)
{
	int					done; // 반환값
	int					width; // 넓이
	int					prec; // 정밀도
	int					pad; // 패딩 공백 또는 공백
	int					base; // 진법
	int					is_negative; // 음수 체크
	long long int		temp_num; //음수를 위한 변수
	unsigned long long	num; // 숫자를 담기 위한 변수
	char				*word; // 출력 할 단이
	int					len; // 출력값 길이

	done = 0;
	pad = ' ';
	width = -1;
	prec = -1;
	*fmt = ++(*fmt); // % 다음 포인트로 이동
	if (ft_isdigit(**fmt)) // width 파싱
		width = read_integer(fmt);
	if (**fmt == '.') // prec 파싱
	{
		*fmt = ++(*fmt); // . 다음 포인트로 이동
		if (ft_isdigit(**fmt))
			prec = read_integer(fmt);
		else
			prec = -2; // .만 있고 숫자가 주어지지 않는 경우 (prec여부를 따른 확인하는 flag를 두지 않기 위함)
	}
	if (**fmt == 's')
	{
		word = va_arg(arg, char *);
		if (word == NULL)
			word = "(null)";
		len = ft_strlen(word);
		if (prec >= 0 && prec < len) // 정밀도가 str보다 작으면 정밀도 기준으로 출력 되기 때문
			len = prec;
		else if (prec == -2) // .만 있으면 출력하지 않기 위해서
			len = 0;
		width = max_value(0, width - len); //0보다 작으면 0 으로 초기화 시켜 출력하지 않음
		done += print_width_prec(pad, width);
		done += outstring(word, len);
	}
	else
	{
		if (**fmt == 'd')
		{
			temp_num = va_arg(arg, int);
			is_negative = temp_num < 0 ? 1 : 0;
			num = is_negative ? (-temp_num) : temp_num;
			base = 10;
		}
		else
		{
			num = va_arg(arg, unsigned int);
			is_negative = 0;
			base = 16;
		}
		if (num == 0)
		{
			if (prec == -2 || prec == 0)
			{
				word = "";
				len = 0;
			}
			else
			{
				word = "0";
				len = 1;
			}
		}
		else
		{
			word = (char [21]){}; //자동 초기화 0으로 - compound literal
			len = 20; //정상 출력에서 최대 숫자의 자릿수 20 이므로
			while (num != 0)
			{
				word[len--]= digit[num % base];
				num = num / base;
			}
			word = &word[len + 1]; // 한자리 앞으로 이동되어 있어서 첫번째 위치로
			len = 20 - len;
		}
		if (is_negative) // 음수면 부호 - 때문에 width 감소
			width--;
		prec = max_value(0, prec - len); //0보다 작으면 0 으로 초기화 시켜 출력하지 않음
		width = max_value(0, width - (len + prec)); //0보다 작으면 0 으로 초기화 시켜 출력하지 않음
		done += print_width_prec(pad, width);
		if (is_negative) //음수인 경우 - 출력
			done += outstring("-", 1);
		pad = '0'; //정밀도는 숫자 0이 붙기 때문에 변경
		done += print_width_prec(pad, prec);
		done += outstring(word, len);
	}
	*fmt = ++(*fmt); // 서식지정자 뒤로포인트 이동
	return (done);
}

int		ft_printf(const char *fmt, ...)
{
	va_list		arg;
	int			done;
	char		*start;
	char		*target;

	va_start(arg, fmt);
	start = (char *)fmt;
	done = 0;
	while ((target = ft_strchr(start, '%'))) // %기준으로 파싱 후 바로 출력
	{
		done += outstring(start, target - start);
		done += process(&target, arg);
		start = target;
	}
	done += outstring(start, ft_strlen(start)); // %이 없으면 전체문장 %이 있으면 그 이후 마지막 부분 출력
	va_end(arg);
	return (done);
}

#include <stdio.h>

int main()
{
	printf("%10.8d", -42);

	ft_printf("%10.8d", -42);
}
