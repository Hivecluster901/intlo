#include <conio.h>
#include <fstream>

namespace chili
{
	void print( const char* s )
	{
		for( ; *s != 0; s++ )
		{
			_putch( *s );
		}
	}

	void printGraph(char** names, int* values, int count)
	{
		print("\n");
		print("\n");
		print("        Beautiful Chart Bitches!");
		print("\n");
		print("        ------------------------");
		print("\n");
		print("\n");
		for (int i = 0; i < count; i++)
		{
			print(names[i]);
			print("|");
			for (int j = 0; j < values[i]; j++)
			{
				print("=");
			}
			print("\n");
		}
		print("\n");
		print("\n");
	}

	void read( char* buf,int maxSize )
	{
		const char* const pEnd = buf + maxSize;
		for( char c = _getch(); c != 13 && (buf + 1 < pEnd); c = _getch(),buf++ )
		{
			_putch( c );
			*buf = c;
		}
		*buf = 0;
	}

	void readMenuOption(char* buf)
	{
		read(buf, 2);
	}
	void readName(char* buf, int maxSize)
	{
		char* const pEnd = buf + maxSize;
		for (char c = _getch(); c != 13 && (buf + 1 < pEnd); c = _getch(), buf++)
		{
			_putch(c);
			*buf = c;
		}
		while (buf + 1 < pEnd )
		{
			*buf = 32;
			buf++;
		}
		*(pEnd - 1) = 0;
	}

	int str2int( const char* s )
	{
		// scan to start point
		const char* p = s;
		for( ; *p >= '0' && *p <= '9'; p++ );
		p--;

		int val = 0;
		int place = 1;
		// convert place values and accumulate
		for( ; p >= s; p-- )
		{
			val += (*p - '0') * place;
			place *= 10;
		}

		return val;
	}

	int fib( int n )
	{
		if( n < 2 )
		{
			return n;
		}
		return fib( n - 1 ) + fib( n - 2 );
	}

	void strrev( char* pl )
	{
		// scan to start point
		char* pr = pl;
		for( ; *pr != 0; pr++ );
		pr--;

		for( ; pl < pr; pl++,pr-- )
		{
			const char temp = *pl;
			*pl = *pr;
			*pr = temp;
		}
	}

	void int2str( int val,char* buf,int size )
	{
		char* const pStart = buf;
		char* const pEnd = buf + size;
		for( ; val > 0 && (buf + 1 < pEnd); val /= 10,buf++ )
		{
			*buf = '0' + val % 10;
		}
		*buf = 0;
		strrev( pStart );
	}
}

void Menu(char** names, int* values, int count)
{
	chili::print("(l)oad (s)ave (a)dd (q)uit (p)rint?");
	char answer[60];
	char answerName[10];
	chili::readMenuOption(answer);
	chili::print("\n");

	switch (*answer)
	{
	case 'l':
	{
		chili::print("Enter File Name :");
		chili::read(answer, 60);
		std::ifstream in(answer, std::ios::binary);
		in.read(reinterpret_cast<char*> (count), sizeof(int));
		for (int i = 0; i < count; i++)
		{
			in.read(*(names + i), 1); // 10bytes(one name occupies 10 bytes including spaces.)
			in.read(reinterpret_cast<char*>(values + i), sizeof(int));
		}
		Menu(names, values, count);
	}
		break;
	case 's':
	{
		chili::print("Enter File Name :");
		chili::read(answer, 60);
		std::ofstream out(answer, std::ios::binary);
		out.write(reinterpret_cast<char*>(&count), sizeof(int));
		for (int i = 0; i < count; i++)
		{
			char* name = names[i];
			out.write(name, sizeof(10)); // 10bytes(one name occupies 10 bytes including spaces.)
			out.write(reinterpret_cast<char*>(values + i), sizeof(int));
		}
		chili::print("\n");
		Menu(names, values, count);
	}
		break;
	case 'a':
		chili::print("Enter Name :");
		chili::readName(answerName, 10);
		names[count] = answerName;
		chili::print("\nEnter Value :");
		chili::read(answer, 60);
		values[count] = chili::str2int(answer);
		count++;
		chili::print("\n");
		Menu(names, values, count);
		break;
	case 'q':
		break;
	case 'p':
		chili::printGraph(names, values, count);
		Menu(names, values, count);
		break;
	default:
		chili::print("Please select a valid option.\n");
		Menu(names, values, count);
	}
	
}

int main()
{
	char* names[40];
	int values[40];
	int count = 0;
	Menu(names, values, count);
	while( !_kbhit() );
	return 0;
}