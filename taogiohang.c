#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct{
	char tensp[30];
	int gia;
	int soluong;
}
sp_st;

typedef struct{
	char tenkhachhang[30];
	char diachi[50];
	int sosanpham;
	sp_st dssp[30];
}
 giohang_st;

void taoGioHang(giohang_st *a){
	printf("Nhap ten khach hang: ");
	gets(a->tenkhachhang);
	fflush(stdin);
	printf("Nhap dia chi: ");
	gets(a->diachi);
	fflush(stdin);
	a->sosanpham = 0;
	printf("\n");
}

void chonHang(giohang_st *a){
	a->sosanpham++;
	printf("Nhap ten san pham: ");
	gets(a->dssp[a->sosanpham-1].tensp);
	fflush(stdin);
	printf("Nhap so luong: ");
	scanf("%d", &a->dssp[a->sosanpham-1].soluong);
	fflush(stdin);
	printf("Nhap gia: ");
	scanf("%d", &a->dssp[a->sosanpham-1].gia);
	fflush(stdin);
	printf("\n");
}

void sapXepGioHang(giohang_st *a){
	sp_st temp;
	int i;
	for(i = 0; i < a->sosanpham-1; i++){
		if(a->dssp[i].tensp[0] > a->dssp[i+1].tensp[0]){
			temp = a->dssp[i];
			a->dssp[i] = a->dssp[i+1];
			a->dssp[i+1] = temp;
		}
	}
}

void hienThiGioHang(giohang_st a){
	printf("----------------------THONG TIN GIO HANG----------------------\n");
	printf("| Ten Khach hang : %-41s |\n", a.tenkhachhang);
	printf("| Dia chi: %-49s |\n", a.diachi);
	printf("| So san pham: %-46d|\n", a.sosanpham);
	printf("|------------------------------------------------------------|\n");
	printf("| %-5s %-30s %-10s %-10s |\n", "STT", "Ten san pham", "Gia", "So luong");
	int i;
	for(i = 0; i < a.sosanpham; i++){
		printf("| %-5d %-30s %-10d %-10d |\n", i+1, a.dssp[i].tensp, a.dssp[i].gia, a.dssp[i].soluong);
	}
	printf("|____________________________________________________________|\n\n");
}

void loaiBoMotMatHang(giohang_st *a){
	int num, i;
	do{
		printf("Can loai bo san pham thu may: ");
		scanf("%d", &num);
		fflush(stdin);
		if(num <= 0 || num > a->sosanpham){
			printf("Ban phai nhap thu tu dung voi danh sach!");
		}
	}while(num <= 0 || num > a->sosanpham);
	for( i = num-1; i < a->sosanpham-1; i++ ){
		a->dssp[i] = a->dssp[i+1];
	}
	a->sosanpham--;
}

void ghiFileNhiPhan(giohang_st a, FILE *p){
	p = fopen("cart.dat", "wb");
	fwrite(&a.tenkhachhang, sizeof(giohang_st), 1, p);
	fwrite(&a.diachi, sizeof(giohang_st), 1, p);
	fwrite(&a.sosanpham, sizeof(giohang_st), 1, p);
	int i;
	for(i = 0; i < a.sosanpham; i++){
		fwrite(&a.dssp[i], sizeof(giohang_st), 1, p);
	}
	fclose(p);
}

void docFileNhiPhan(giohang_st *a, FILE *p){
	p = fopen("cart.dat", "rb");
	fread(&a->tenkhachhang, sizeof(giohang_st), 1, p);
	fread(&a->diachi, sizeof(giohang_st), 1, p);
	fread(&a->sosanpham, sizeof(giohang_st), 1, p);
	int i;
	for(i = 0; i < a->sosanpham; i++){
		fread(&a->dssp[i], sizeof(giohang_st), 1, p);
	}
	fclose(p);
}

int main(){
	giohang_st giocuatoi;
	FILE *p;
	int chon;
	do{
		printf("-------------MENU-------------\n1. Tao gio hang\n2. Chon hang\n3. Xem chi tiet gio hang\n4. Loai bo mot mon hang\n5. Ghi toan bo noi dung gio hang vao tep nhi phan cart.dat\n6. Lay du lieu khach hang cu\n7. Thoat\n\n");
		do{
			printf("Lua chon cua ban la: ");
			scanf("%d", &chon);
			printf("\n");
			fflush(stdin);
			if(chon <= 0 || chon > 7){
				printf("Vui long nhap dung so thu tu trong menu!\n");
			}
		}while(chon <= 0 || chon > 7);
		system("cls");
		switch(chon){
			case 1:{
				taoGioHang(&giocuatoi);
				break;
			}
			case 2:{
				chonHang(&giocuatoi);
				break;
			}
			case 3:{
				if(giocuatoi.sosanpham > 0){	
					sapXepGioHang(&giocuatoi);
				}
				hienThiGioHang(giocuatoi);
				break;
			}
			case 4:{
				loaiBoMotMatHang(&giocuatoi);
				break;
			}
			case 5:{
				ghiFileNhiPhan(giocuatoi, p);
				break;
			}
			case 6:{
				docFileNhiPhan(&giocuatoi, p);
				hienThiGioHang(giocuatoi);
				break;
			}
			case 7:{
				break;
			}
			default:{
				if(chon != 7){
					printf("Vui long nhap dung so thu tu trong menu!\n");
				}
				break;
			}
		}
	}while(chon != 7);
	return 0;
}

