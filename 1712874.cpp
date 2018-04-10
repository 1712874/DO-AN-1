#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#define maxSize 30

typedef struct SINHVIEN{
	wchar_t MSSV[8];
	wchar_t hoVaTen[maxSize];
	wchar_t khoa[maxSize];
	int khoaTuyen;
	wchar_t ngaySinh[11];
	wchar_t hinhAnhCaNhan[maxSize];
} SV;

wchar_t* getPart(FILE* file, wchar_t* str){
	int ch, leng = 0;
	do{
		ch = fgetc(file);
		if (ch == ',' || ch == '\n' || ch == EOF) break;
		str[leng] = ch;
		leng++;
	} while (1);
	str[leng] = '\0';
	return str;
}

void wmain(){
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	SINHVIEN a;
	FILE* fin, *fout;
	fopen_s(&fin, "1712874.csv", "rt");
	if (!fin){
		wprintf(L"Không thể đọc file!\n");
	}
	else{
		getPart(fin, a.MSSV);
		wprintf(L"MSSV: %ls", a.MSSV);
		fclose(fin);
		fopen_s(&fout, "fileout.csv", "wt");
		fwprintf(fout, a.MSSV);
		fclose(fout);
	}

}