#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define maxSize 50

typedef struct SINHVIEN{
	wchar_t MSSV[8];
	wchar_t hoVaTen[maxSize];
	wchar_t khoa[maxSize];
	wchar_t khoaTuyen[5];
	wchar_t ngaySinh[11];
	wchar_t hinhAnhCaNhan[maxSize];
	wchar_t moTa[maxSize];
	wchar_t soThich1[maxSize];
	wchar_t soThich2[maxSize];
} SV;

wchar_t* getPart(FILE* file, wchar_t* str);
void getSinhVien(FILE* file, SINHVIEN &x);
void fileCopy(FILE* fin, FILE* fout);

wchar_t* getPart(FILE* file, wchar_t* str, int &ch){
	int leng = 0;
	ch = 0;
	do{
		ch = fgetwc(file);
		if (ch == ',' || ch == '\n' || ch == EOF) break;
		str[leng] = ch;
		leng++;
	} while (1);
	str[leng] = L'\0';
	return str;
}

void getSinhVien(FILE* file, SINHVIEN &x, int ch){
	
	getPart(file, x.MSSV,ch);
	getPart(file, x.hoVaTen,ch);
	getPart(file, x.khoa,ch);
	getPart(file, x.khoaTuyen,ch);
	getPart(file, x.ngaySinh,ch);
	getPart(file, x.hinhAnhCaNhan,ch);
	getPart(file, x.moTa,ch);
	if (ch == '\n'){
		x.soThich1[0] = '\0';
		x.soThich2[0] = '\0';
		return;
	}
		getPart(file, x.soThich1,ch);
		if (ch == '\n'){
			x.soThich2[0] = '\0';
			return;
		}
		getPart(file, x.soThich2,ch);
}

void fileCopy(FILE* fin, FILE* fout){
	int ch;
	do{
		ch = fgetc(fin);
		fputc(ch, fout);
	} while (ch != EOF);
}

//HAM MAIN
void wmain(){
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	SINHVIEN A[2];
	FILE* fin, *fout;
	_wfopen_s(&fin, L"danhsach.csv", L"rt,ccs=UTF-8");
	if (!fin){
		wprintf(L"Không thể đọc file!\n");
	}
	else{
		fseek(fin, 3, SEEK_SET);
		for (int i = 0; i < 2; i++){
			int ch = 0;
			getSinhVien(fin, A[i],ch);
			//dat ten cho file
			wchar_t ten[13];
			wcscpy_s(ten, A[i].MSSV);
			wcscat_s(ten, L".html\0");
			_wfopen_s(&fout, ten, L"wt,ccs=UTF-8");
			fwprintf(fout, L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\r\n<title>HCMUS - %s</title>\r\n</head>\r\n<body>\r\n<div class=\"Layout_container\">\r\n<!-- Begin Layout Banner Region -->\r\n<div class=\"Layout_Banner\" >\r\n<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\r\n<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\r\n</div>\r\n<!-- End Layout Banner Region -->\r\n<!-- Begin Layout MainContents Region -->\r\n<div class=\"Layout_MainContents\">\r\n<!-- Begin Below Banner Region -->\r\n<div class=\"Personal_Main_Information\">\r\n<!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\r\n<div class=\"Personal_Location\">\r\n<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\r\n<span class=\"Personal_FullName\">%s - %s</span>\r\n<div class=\"Personal_Department\">%s</div>\r\n<br />\r\n<div class=\"Personal_Phone\">\r\nEmail: %s@student.hcmus.edu.vn\r\n</div>\r\n<br />\r\n<br /> \r\n</div>\r\n<!-- End Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\r\n<div class=\"Personal_HinhcanhanKhung\">\r\n<img src=\"Images/%s\" class=\"Personal_Hinhcanhan\" />\r\n</div>\r\n</div>\r\n<!-- End Below Banner Region -->\r\n<!-- Begin MainContents Region -->\r\n<div class=\"MainContain\">\r\n\r\n<!-- Begin Top Region -->\r\n<div class=\"MainContain_Top\">\r\n\r\n<div class=\"InfoGroup\">Thông tin cá nhân</div>\r\n<div>\r\n<ul class=\"TextInList\">\r\n<li>Họ và tên: %s</li>\r\n<li>MSSV: %s</li>\r\n<li>Sinh viên khoa %s</li>\r\n<li>Ngày sinh: %s</li>\r\n<li>Email: %s@student.hcmus.edu.vn</li>\r\n</ul>\r\n</div>\r\n<div class=\"InfoGroup\">Sở thích</div>\r\n<div>\r\n<ul class=\"TextInList\">\r\n<li>%s</li>\r\n<li>%s</li>\r\n</ul>\r\n</div>\r\n<div class=\"InfoGroup\">Mô tả</div>\r\n<div class=\"Description\">\r\n%s.\r\n</div>\r\n\r\n</div>\r\n</div>\r\n</div>\r\n\r\n<!-- Begin Layout Footer -->\r\n<div class=\"Layout_Footer\">\r\n<div class=\"divCopyright\">\r\n<br />\r\n<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\r\n<br />\r\n@2018</br>\r\nĐồ án giữ kỳ</br>\r\nKỹ thuật lập trình</br>\r\nTH2012/03</br>\r\n1712874 - Nguyễn Chánh Anh Tuấn</br>\r\n</div>\r\n</div>\r\n<!-- End Layout Footer -->\r\n</div>\r\n</body>\r\n</html>", A[i].hoVaTen, A[i].hoVaTen, A[i].MSSV, A[i].khoa, A[i].MSSV, A[i].hinhAnhCaNhan, A[i].hoVaTen, A[i].MSSV, A[i].khoa, A[i].ngaySinh, A[i].MSSV, A[i].soThich1, A[i].soThich2, A[i].moTa);
		}
		wprintf(L"%ls", A[0].hinhAnhCaNhan);
		fclose(fin);
		fclose(fout);
	}
}