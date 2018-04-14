#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#define maxSize 30

typedef struct SINHVIEN{
	wchar_t MSSV[8];
	wchar_t hoVaTen[maxSize];
	wchar_t khoa[maxSize];
	wchar_t khoaTuyen[5];
	wchar_t ngaySinh[11];
	wchar_t hinhAnhCaNhan[maxSize];
} SV;

wchar_t* getPart(FILE* file, wchar_t* str){
	int ch, leng = 0;
	do{
		ch = fgetwc(file);
		if (ch == ',' || ch == '\n' || ch == EOF) break;
		str[leng] = ch;
		leng++;
	} while (1);
	str[leng] = L'\0';
	return str;
}

void getSinhVien(FILE* file, SINHVIEN &x){
	getPart(file, x.MSSV);
	getPart(file, x.hoVaTen);
	getPart(file, x.khoa);
	getPart(file, x.khoaTuyen);
	getPart(file, x.ngaySinh);
	getPart(file, x.hinhAnhCaNhan);
}

void wmain(){
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	SINHVIEN a;
	FILE* fin, *fout;
	_wfopen_s(&fin, L"1712882.csv", L"rt,ccs=UTF-8");
	if (!fin){
		wprintf(L"Không thể đọc file!\n");
	}
	else{
		fseek(fin, 3, SEEK_SET);
		getSinhVien(fin, a);
		fclose(fin);
		_wfopen_s(&fout, a.MSSV, L"wt,ccs=UTF-8");
		fwprintf(fout, L"%ls", &a.MSSV);
		fclose(fout);
	}
}