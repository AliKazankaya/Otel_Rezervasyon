#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ODA_SAYISI 100


typedef struct{
	
	char *musteriAdi;
	char *musteriSoyadi;
	
	
}musteriBilgileri;

typedef struct{
	
	int gun;
	int ay;
	int yil;
	
	
}tarihBilgileri;


typedef struct{
	
	int kisiSayisi;
	int odaNumarasi; // 1-100 arasýnda
	int odaDurumu; // doluysa 1 ,bossa 0
	double fiyatBilgisi;
	musteriBilgileri musteri;
	tarihBilgileri girisTarihi;
	tarihBilgileri cikisTarihi;


}odaBilgileri;

typedef enum{

	musteri=0,personel=1
		
}yetkiSeviyeleri;

int gunFarkiHesapla(tarihBilgileri girisTarihi,tarihBilgileri cikisTarihi){
	
	if(girisTarihi.gun>girisTarihi.gun){
		
		cikisTarihi.ay-=1;
		cikisTarihi.gun+=30;
		
	}
	
	if(girisTarihi.ay>girisTarihi.ay){
		
		cikisTarihi.yil-=1;
		cikisTarihi.ay+=12;
		
	}
	
	tarihBilgileri tarihFarki;
	
	tarihFarki.gun=cikisTarihi.gun-girisTarihi.gun;
	tarihFarki.ay=cikisTarihi.ay-girisTarihi.ay;
	tarihFarki.yil=cikisTarihi.yil-girisTarihi.yil;
	
	int gunFarki=tarihFarki.yil*365+tarihFarki.ay*30+tarihFarki.gun;
	return gunFarki;
}



 double fiyatHesapla(odaBilgileri *odalar,int odaNumarasi){
 	
 	int gunFarki=gunFarkiHesapla(odalar[odaNumarasi-1].girisTarihi,odalar[odaNumarasi-1].cikisTarihi);
 	printf("Kalacaginiz gun sayisi : %d\n",gunFarki);
 
 	return gunFarki*150*odalar[odaNumarasi-1].kisiSayisi;
 	
 	
 		
 }
 
 
 void rezervasyonTemizle(odaBilgileri *odalar, int odaNumarasi)
{
	odalar[odaNumarasi-1].odaDurumu=0;
	free(odalar[odaNumarasi-1].musteri.musteriAdi);
	free(odalar[odaNumarasi-1].musteri.musteriSoyadi);
	printf(" %d numarali odanin iptal-cikis islemi basariyla yapilmistir.",odaNumarasi);
	
	
}



void yeniMusteriEkeleme(odaBilgileri *odalar){
int sorgulanacakOda;
char musteriAdi[20];
char musteriSoyadi[20];
char ch;
printf("Lutfen kayit olmak istediginiz odayi giriniz.");
scanf("%d",&sorgulanacakOda);

if(odalar[sorgulanacakOda-1].odaDurumu!=0){
	

  printf("Malesef kayit yaptirmak istediginiz oda %d %d %d tarihine kadar doludur.",odalar[sorgulanacakOda-1].cikisTarihi.gun,odalar[sorgulanacakOda-1].cikisTarihi.ay,odalar[sorgulanacakOda-1].cikisTarihi.yil);
}

odalar[sorgulanacakOda-1].odaNumarasi=sorgulanacakOda;
printf("Lutfen ad ve soyad bilgilerinizi sirasiyla giriniz.");
scanf("%s%s",&musteriAdi,&musteriSoyadi);

odalar[sorgulanacakOda-1].musteri.musteriAdi=(char*)malloc(sizeof(char)*strlen(musteriAdi)+1);
odalar[sorgulanacakOda-1].musteri.musteriSoyadi=(char*)malloc(sizeof(char)*strlen(musteriSoyadi)+1);
strcpy(odalar[sorgulanacakOda-1].musteri.musteriAdi,musteriAdi);
strcpy(odalar[sorgulanacakOda-1].musteri.musteriSoyadi,musteriSoyadi);

printf("Lutfen kac kisi kalacaginizi giriniz.");
fflush(stdin);
scanf("%d",&odalar[sorgulanacakOda-1].kisiSayisi);
fflush(stdin);
printf("Lutfen giris tarihi bilgisini (gun:ay:yil) seklinde giriniz..");
scanf("%d:%d:%d",&odalar[sorgulanacakOda-1].girisTarihi.gun,&odalar[sorgulanacakOda-1].girisTarihi.ay,&odalar[sorgulanacakOda-1].girisTarihi.yil);
printf("Lutfen cikis tarihi bilgisini (gun:ay:yil)seklinde giriniz.");
fflush(stdin);
scanf("%d:%d:%d",&odalar[sorgulanacakOda-1].cikisTarihi.gun,&odalar[sorgulanacakOda-1].cikisTarihi.ay,&odalar[sorgulanacakOda-1].cikisTarihi.yil);
odalar[sorgulanacakOda-1].fiyatBilgisi=fiyatHesapla(odalar,sorgulanacakOda);
printf("Odemeniz gereken tutar %.2lf\n",odalar[sorgulanacakOda-1].fiyatBilgisi);
printf("Onayliyor musunuz ? E or H ");
fflush(stdin);
ch=getchar();

if(ch=='H'){
	rezervasyonTemizle(odalar,sorgulanacakOda);
	return;
}

odalar[sorgulanacakOda-1].odaDurumu=1; //odamýz doldu.

}
void doluOdaBilgileriYazdirma(odaBilgileri *odalar){
	
	int i;
	
	for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu!=0){
			printf("----------------------------------\n");
			printf("Oda numarasi: %d\n",odalar[i].odaNumarasi);
			printf("Musteri adi-soyadi : %s %s\n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
			printf("Kac kisi var ? %d\n",odalar[i].kisiSayisi);
			printf("Fiyat : %.2lf\n",odalar[i].fiyatBilgisi);
			printf("Giris Tarihi : %d-%d-%d\n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
			printf("Cikis Tarihi : %d-%d-%d\n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);
			
			
		
		}
		
			
	}
}

void odaBilgisiSorgulama(odaBilgileri *odalar, int odaNumarasi){
	
	if(odalar[odaNumarasi-1].odaDurumu!=0){
		
		printf("%d numarali oda %d %d %d tarihine kadar doludur.\n",odaNumarasi,odalar[odaNumarasi-1].cikisTarihi.gun,odalar[odaNumarasi-1].cikisTarihi.ay,odalar[odaNumarasi-1].cikisTarihi.yil);
	}
	else{
		printf("%d numarali  oda bostur...",odaNumarasi);
		
	}
}

void fiyatBilgisiYazdirma(){
	
	int kisiSayisi;
	double toplamTutar=0.0;
	tarihBilgileri girisTarihi,cikisTarihi;
	
	printf("Lutfen kac kisi olacaginizi giriniz.");
	scanf("%d",&kisiSayisi);
	
	printf("Lutfen giris tarihini gun:ay:yil seklinde giriniz.\n");
	scanf("%d:%d:%d",&girisTarihi.gun,&girisTarihi.ay,&girisTarihi.yil);
	printf("Lutfen cikis tarihinizi gun:ay:yil seklinde giriniz\n");
	scanf("%d:%d:%d",&cikisTarihi.gun,&cikisTarihi.ay,&cikisTarihi.yil);
	
	toplamTutar=gunFarkiHesapla(girisTarihi,cikisTarihi)*kisiSayisi*150;
	printf("%.2lf\n",toplamTutar);
}
void yedekAlma(odaBilgileri *odalar){
	
	int i;
	FILE *otelKayitlari=fopen("OtelKayitlari.txt","a");
	if(otelKayitlari==NULL){
		printf("Bir hata olustu.");
		exit(1);
	}
	else{
		for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu!=0){
			
			fprintf(otelKayitlari,"--------------------------------------------------\n");
			fprintf(otelKayitlari,"Oda Numarasi %d\n",odalar[i].odaNumarasi);
			fprintf(otelKayitlari,"Musterinin adi-soyadi: %s %s\n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
			fprintf(otelKayitlari,"Kisi sayisi %d\n",odalar[i].kisiSayisi);
			fprintf(otelKayitlari,"Toplam Tutar %.2lf\n",odalar[i].fiyatBilgisi);
			fprintf(otelKayitlari,"Giris Tarihi %d:%d:%d\n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
			fprintf(otelKayitlari,"Cikis Tarihi %d:%d:%d\n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);

				
		}
	}
	
}

fclose(otelKayitlari);

}



int main()
{
 	
 
 odaBilgileri *odaDizisi;
 char ch;
 int belirlenensifre=123456,kullanicininGirdigiSifre,odaNumarasi;
 yetkiSeviyeleri kullaniciYetkisi;
 odaDizisi=(odaBilgileri*)calloc(ODA_SAYISI,sizeof(odaBilgileri)); //dinamik bir þekilde ve baslangýcta her odaya 0 atamak icin.
 
 printf("\t\t\t Otel rezervasyon sistemine hosgeldiniz...\n");
 printf("Lutfen burada calisiyorsaniz sifrenizi giriniz.\n");
 scanf("%d",&kullanicininGirdigiSifre);
 
 if(belirlenensifre==kullanicininGirdigiSifre){
 	kullaniciYetkisi=personel;
 	
 	
 }
 
 else{
 
 kullaniciYetkisi=musteri;
}


do{
	
	printf("1.Yeni musteri girisi yapmak istiyorsaniz 'E'\n2.Oda bilgisini sorgulamak istiyorsaniz 'S'\n3.Dolu oda bilgilerini goruntulemek istiyorsaniz 'G'\n");
	printf("4.Fiyat sorgusu yapmak istiyorsaniz 'F'\n5.Musteri cikisi yapmak isityorsaniz 'C'\n6.Sistemden cikmak istiyorsaniz 'Q' tuslayiniz. :");
	fflush(stdin);
    ch=getchar();
    switch (ch){
    	case 'E':
    		if(kullaniciYetkisi==personel){
    			yeniMusteriEkeleme(odaDizisi);
			}
			else{
				printf("Bu alan sadece calisanlar tarafindan kullanilabilir...");
			}
    		break;
    	case 'S':
    		printf("Lutfen sorgulanacak odanin numarasini giriniz.");
    		scanf("%d",&odaNumarasi);
    		odaBilgisiSorgulama(odaDizisi,odaNumarasi);
    		break;
        case 'G':
        	if(kullaniciYetkisi==personel){
        		doluOdaBilgileriYazdirma(odaDizisi);
			}
        	break;
        case 'F':
        	fiyatBilgisiYazdirma();
        	break;
		case 'C':
				if(kullaniciYetkisi==personel){
        		printf("Cikis yapmak istediginiz odanin numarasini giriniz.");
        		scanf("%d",&odaNumarasi);
			     rezervasyonTemizle(odaDizisi,odaNumarasi);
			 }
			 else{
			 	printf("Bu alan sadece calisanlar tarafindan goruntulenebilir.");
			 }
			break;
		case 'Q':
			yedekAlma(odaDizisi);
		    break;	
	    default:
	    	break;
	
}
	
	
	
}while(ch!='Q');
 
}


 	
 	
 	
 	

  
  
  
  
