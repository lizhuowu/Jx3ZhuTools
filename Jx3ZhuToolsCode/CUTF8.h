#pragma once
class CCUTF8
{
public:
	CCUTF8(void);
	~CCUTF8(void);
	void CCUTF8::UTF8_to_UNICODE2( wchar_t *pOut,char *pText);
	CString CCUTF8::UTF8_to_UNICODE(const char *utf8_string, int length);
	WCHAR* UTF_8ToUnicode(char *ustart);  //把UTF-8转换成Unicode
	char * UnicodeToGB2312(unsigned short uData);  //把Unicode 转换成 GB2312

	CString HexToBin(CString string);//将16进制数转换成2进制;
	CString BinToHex(CString BinString);//将2进制数转换成16进制;
	int BinToInt(CString string);//2进制字符数据转换成10进制整型
};


