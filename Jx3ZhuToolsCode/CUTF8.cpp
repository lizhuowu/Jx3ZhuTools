#include "stdafx.h"
#include "CUTF8.h"


CCUTF8::CCUTF8(void)
{
}


CCUTF8::~CCUTF8(void)
{
}

void CCUTF8::UTF8_to_UNICODE2( wchar_t *pOut,char *pText)
{
	char *uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return;
}
CString CCUTF8::UTF8_to_UNICODE(const char *utf8_string, int length)
{
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8_string, length, NULL, 0);   
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, utf8_string, length, wszString, wcsLen);
	wszString[wcsLen] = '\0';
	CString unicodeText(wszString); 
	delete[] wszString;
	return unicodeText;
}

WCHAR* CCUTF8::UTF_8ToUnicode(char *ustart)  //把UTF-8转换成Unicode
{
	char char_one;
	char char_two;
	char char_three;
	int Hchar;
	int Lchar;
	static char uchar[2];
	WCHAR *unicode;
	CString string_one;
	CString string_two;
	CString string_three;
	CString combiString;
	char_one = *ustart;
	char_two = *(ustart+1);
	char_three = *(ustart+2);
	string_one.Format("%x",char_one);
	string_two.Format("%x",char_two);
	string_three.Format("%x",char_three);
	string_three = string_three.Right(2);
	string_two = string_two.Right(2);
	string_one = string_one.Right(2);
	string_three = HexToBin(string_three.Left(1))+HexToBin(string_three.Right(1));
	string_two = HexToBin(string_two.Left(1))+HexToBin(string_two.Right(1));
	string_one = HexToBin(string_one.Left(1))+HexToBin(string_one.Right(1));
	combiString = string_one +string_two +string_three;
	combiString = combiString.Right(20);
	combiString.Delete(4,2);
	combiString.Delete(10,2);
	Hchar = BinToInt(combiString.Left(8));
	Lchar = BinToInt(combiString.Right(8));
	uchar[1] = (char)Hchar;
	uchar[0] = (char)Lchar;
	unicode = (WCHAR *)uchar;
	return unicode;
}
char * CCUTF8::UnicodeToGB2312(unsigned short uData)  //把Unicode 转换成 GB2312
{
	char *buffer ;
	buffer = new char[sizeof(WCHAR)];
	WideCharToMultiByte(CP_ACP,NULL,(LPCWCH)&uData,1,buffer,sizeof(WCHAR),NULL,NULL);
	return buffer;
}
CString CCUTF8::HexToBin(CString string)//将16进制数转换成2进制
{
	if( string == "0") return "0000";
	if( string == "1") return "0001";
	if( string == "2") return "0010";
	if( string == "3") return "0011";
	if( string == "4") return "0100";
	if( string == "5") return "0101";
	if( string == "6") return "0110";
	if( string == "7") return "0111";
	if( string == "8") return "1000";
	if( string == "9") return "1001";
	if( string == "a") return "1010";
	if( string == "b") return "1011";
	if( string == "c") return "1100";
	if( string == "d") return "1101";
	if( string == "e") return "1110";
	if( string == "f") return "1111";
	return "";
}


CString CCUTF8::BinToHex(CString BinString)//将2进制数转换成16进制
{
	if( BinString == "0000") return "0";
	if( BinString == "0001") return "1";
	if( BinString == "0010") return "2";
	if( BinString == "0011") return "3";
	if( BinString == "0100") return "4";
	if( BinString == "0101") return "5";
	if( BinString == "0110") return "6";
	if( BinString == "0111") return "7";
	if( BinString == "1000") return "8";
	if( BinString == "1001") return "9";
	if( BinString == "1010") return "a";
	if( BinString == "1011") return "b";
	if( BinString == "1100") return "c";
	if( BinString == "1101") return "d";
	if( BinString == "1110") return "e";
	if( BinString == "1111") return "f";
	return "";
}

int CCUTF8::BinToInt(CString string)//2进制字符数据转换成10进制整型
{
	int len =0;
	int tempInt = 0;
	int strInt = 0;
	for(int i =0 ;i < string.GetLength() ;i ++)
	{
		tempInt = 1;
		strInt = (int)string.GetAt(i)-48;
		for(int k =0 ;k < 7-i ; k++)
		{
			tempInt = 2*tempInt;
		}
		len += tempInt*strInt;
	}
	return len;
}