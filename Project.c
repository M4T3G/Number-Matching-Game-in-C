#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100
#define MAX_USERS 20

struct kullanici {
    char isim[50];
    int skor;
};

void kullaniciEkle(struct kullanici kullanicilar[], int *sayac, const char *isim) {
	int i;
    if (*sayac >= MAX_USERS) {
        printf("Maksimum kullanici sayisina ulasildi.\n");
        return;
    }

    for (i = 0; i < *sayac; i++) {
        if (strcmp(kullanicilar[i].isim, isim) == 0) {
            printf("Kullanici '%s' zaten var.\n", isim);
            return;
        }
    }

    strcpy(kullanicilar[*sayac].isim, isim);
    kullanicilar[*sayac].skor = 0;
    (*sayac)++;

    printf("Kullanici '%s' eklendi.\n", isim);
}


void skorArtir(struct kullanici kullanicilar[], int sayac, const char *isim, int *puan,int r,int N,int sure,int undo,int *oyun) {
	int i,skor=0;
    for (i = 0; i < sayac; i++) {
        if (strcmp(kullanicilar[i].isim, isim) == 0) {
            skor=*puan;
        }
    }
    for ( i = 0; i < sayac; i++) {
        if (strcmp(kullanicilar[i].isim, isim) == 0) {
        	*puan=(*puan)+100*N*r*(*oyun)-(sure/10)-(10*undo);
            kullanicilar[i].skor = *puan;
            printf("Kullanici '%s' puanini %d artirdi.", isim, *puan);
            return;
        }
    }
    for (i = 0; i < sayac; i++) {
        if (strcmp(kullanicilar[i].isim, isim) == 0) {
            skor+=*puan;
			*puan=skor;
        }        
    }
    
    printf("Kullanici '%s' bulunamadý.\n", isim);
}

void sonucYaz(struct kullanici kullanicilar[], int sayac) {
	int i;
    printf("Kullanicilar:\n");
    for ( i = 0; i < sayac; i++) {
        printf("Kullanici: %s, Puan: %d\n", kullanicilar[i].isim, kullanicilar[i].skor);
    }
}

void readFromFile(int matris[][MAX], char *fileName){
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matris[i][j]=temp; 
    }  
  	fclose(data); 
   // Buraya kadar olan bolumde dosyadan okuma yapiliyor. Kodu degistirmeyiniz.
}

int kontrol(int array[], int N, int sayi1, int sayi2) {
    int i;
    for (i = 0; i < N * 2; i += 2) {
        if (array[i] == sayi1 && array[i + 1] == sayi2) {
            return 1; // Sayý daha önce kullanýldý
        }
    }
    return 0; // Sayý daha önce kullanýlmadý
}
void sahaYazdir(int saha[][MAX], int N){
    int i,j;
    for (i = 0; i < N; i++) {
        printf("\n");
        for (j = 0; j < N; j++) {
            printf("  %d   ", saha[i][j]);
        }
    }
}

void duseyHamle(int saha[][MAX],int N,int x1,int y1,int x2){
	int i,j;
	if(x1<x2){
		for(i=x1;i<=x2;i++){
			saha[i][y1]=saha[x1][y1];
		}
	}
	if(x2<x1){
		for(i=x1;i>=x2;i--){
			saha[i][y1]=saha[x1][y1];
		}
	}		
}

void yatayHamle(int saha[][MAX],int N,int x1,int y1,int y2){
	int i,j;
	if(y1<y2){
		for(i=y1;i<=y2;i++){
			saha[x1][i]=saha[x1][y1];
		}
	}
	if(y1>y2){
		for(i=y1;i>=y2;i--){
			saha[x1][i]=saha[x1][y1];
		}		
	}	
}

int yolKontrol(int saha[][MAX],int N,int x1,int y1,int x2,int y2){
	int i,j;
	if(x1==x2){
		if(y1<y2){
			for(i=y1+1;i<y2;i++){
				if((saha[x1][i]!=0)&&(saha[x1][i]!=saha[x1][y1])){
					return 0;
				}
			}
		}
		if(y2<y1){
			for(i=y1-1;i>y2;i--){
				if((saha[x1][i]!=0)&&(saha[x1][i]!=saha[x1][y1])){
					return 0;
				}
			}
		}		
	}
	if(y1==y2){
		if(x1<x2){
			for(i=x1+1;i<x2;i++){
				if((saha[i][y1]!=0)&&(saha[i][y1]!=saha[x1][y1])){
					return 0;
				}
			}
		}
		if (x2 < x1) {
    		for (i=x1-1;i>x2;i--) {
 	      		if ((saha[i][y1]!=0) && (saha[i][y1]!=saha[x1][y1])) {
 	            return 0;
 	       		}
   			}	
		}
	}		
	return 1;
}

void geriAl(int saha[][MAX],int yedek[][MAX],int N){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			saha[i][j]=yedek[i][j];
		}
	}
}

int doluluk(int saha[][MAX],int N){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
		if(saha[i][j]==0){
			return 0;
		}	
		}
	}
	return 1;
}

void rastgele(int saha[][MAX],int N) {
    srand(time(NULL));
    char devam;
    int i, j, a, b, k ;
    int kullanilan_sayilar[MAX * 2] = {0};
    do{
    for(i=0;i<2*N;i++){
    	kullanilan_sayilar[i]=0;
	}
    k=0;   
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            saha[i][j] = 0;
        }
    }
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < 2; j++) {
            do {
                a = rand() % N;
                b = rand() % N;
            } while (kontrol(kullanilan_sayilar, k / 2, a, b) == 1);            
            kullanilan_sayilar[k] = a;
            kullanilan_sayilar[k + 1] = b;
            k += 2;
        }
    }    
    k = 0;
    for (i = 0; i < N; i++) {
        saha[kullanilan_sayilar[k]][kullanilan_sayilar[k + 1]] = i + 1;
        saha[kullanilan_sayilar[k + 2]][kullanilan_sayilar[k + 3]] = i + 1;
        k += 4;
    }
    printf("\nOyun alani:\n");
    sahaYazdir(saha,N);
    printf("\nOynanabilir matris degilse y harfine basarak yeni bir matris olusturunuz.\n");
    scanf(" %c",&devam);
	}
	while(devam=='y');
}

void dosya(int saha[][MAX],int N){
    int i,j,k; 
    char fileName[20];	
  	printf("Dosya Adini Giriniz\n");
  	scanf("%s",fileName);
	/* buradan itibaren menü vb kodlarý olmalidir. dosya okumak için asagidaki kod verilmistir */
	
	readFromFile(saha, fileName);
 	   printf("\nOyun alani:\n");
		sahaYazdir(saha,N);	
}

void hareket(int saha[][MAX],int yedek[][MAX],int N,int *undo){
	int x1,x2,y1,y2,i,j;
	char geri;
	do{
		do{
			printf("\nSadece dusey ya da yatay hareket edebilirsiniz.\n");
			printf("Girdigini 2 koordinat arasinda 0'dan baska sayi olmamalidir.Aksi halde tekrar koordinat girmeniz istenecektir.\n");
		do{
			printf("\nEger baslangic noktasini bos yani 0 secerseniz degerler yeniden istenecektir.\n");
			printf("Hamleye baslangic koordinatlari seciniz.\n");
			printf("x=");
			scanf("%d",&x1);
			printf("y=");
			scanf("%d",&y1);
			}while(saha[x1][y1]==0);						
			do{
				printf("Gitmek istediginiz yerde basladiginiz yerdekinden baska sayi varsa degerleri tekrar girmelisiniz.\n");
				printf("Gitmek istediginiz noktanin koordinatlari giriniz.\n");
				printf("x=");
				scanf("%d",&x2);
				printf("y=");
				scanf("%d",&y2);			
			}while((saha[x2][y2]!=saha[x1][y1])&&(saha[x2][y2]!=0));
			for(i=0;i<N;i++){
				for(j=0;j<N;j++){
					yedek[i][j]=saha[i][j];
				}
			}			
		}while(yolKontrol(saha,N,x1,y1,x2,y2)==0);		
			if(y1==y2){
				duseyHamle(saha,N,x1,y1,x2);
			}
			if(x1==x2){
				yatayHamle(saha,N,x1,y1,y2);
			}								
		sahaYazdir(saha,N);
		printf("\nGeri almak icin u harfine basiniz.\n");
		scanf(" %c",&geri);
		if(geri=='u'){
			geriAl(saha,yedek,N);
			(*undo)++;
		}
		sahaYazdir(saha,N);
	}while(doluluk(saha,N)==0);
	printf("\nTebrikler.Oyunu bitirdiniz.\n");		
}

int main() {
    clock_t baslangic, bitis;
    struct kullanici kullanicilar[MAX_USERS];
    int sure,oyun=0;
    int secenek,i,j,k,saha[MAX][MAX]={{0}},yedek[MAX][MAX]={{0}},N,undo=0,puan=0,kullanicisayisi = 0,r/*rastgele*/;
    char isim[MAX];
    do{
    	undo=0;
    	puan=0;
    	printf("\nBu oyunda oto mod yoktur.\n");
    	printf("Kullanici ismi giriniz.\n");
    	scanf("%s", isim);
    	kullaniciEkle(kullanicilar, &kullanicisayisi, isim);
    	printf("\nPuanlandirma soyledir:\nCozdugunuz matris buyuklugu*r*Oynadiginizoyunsayisi*100-(sure/10)-(10*gerialmasayisi)\n");//100*N*r-(sure/10)-(10*undo);
    	printf("r sayisi dosyadan acma icin 2,rastgele matris icin 4'tur.\n");
    	printf("\nAsagidaki seceneklerden birini seciniz.\n");
    	printf("0-Cikis\n");
    	printf("1-Rastgele Matris Olustur\n");
    	printf("2-Dosyadan Matris Olustur\n");
    	printf("3-Kullanici Skorlarini Goster\n");
    	scanf("%d", &secenek);	   
 	   while ((secenek<0)||(secenek>3)) {
   		    printf("Gecerli bir sayi giriniz.\n");
    	    scanf("%d", &secenek);
    	}       	                        	
	    switch (secenek) {
 	       case 0:
	            printf("\nHoscakalin");
	            break;
	        case 1:
 	        	printf("\n1-Rastgele Matris Olustur\n");
 	        	baslangic = clock();
 	        	r=4;
 	        	oyun++;
 	        	do {
 	        		printf("\nMatris boyutunu giriniz.\n");
 	        		printf("Degerleriniz 0 ile 99 arasinda olmalidir.\n");
 	        		scanf("%d", &N);
 	        		} while (N > 99);
  	            rastgele(saha,N);
  	            hareket(saha,yedek,N,&undo);
  	            printf("Undo sayiniz=%d",undo);
  	            bitis = clock();
  	            sure = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
  	            printf("\nGecen sure: %.2d saniye\n", sure);
  	            skorArtir(kullanicilar,kullanicisayisi,isim,&puan,r,N,sure,undo,&oyun);
  	            sonucYaz(kullanicilar, kullanicisayisi);
  	          	break;
	   	    case 2:
            	printf("\n2-Dosyadan Matris Olustur\n");
            	baslangic = clock();
            	r=2;
 	        	do {
 	        		printf("\nMatris boyutunu giriniz.\n");
 	        		printf("Degerleriniz 0 ile 99 arasinda olmalidir.\n");
 	        		scanf("%d", &N);
 	        		} while (N > 99);
  					  for (i = 0; i < N; i++) {
				        for (j = 0; j < N; j++) {
 				           saha[i][j] = 0;
				        }
				    } 	        		
            		dosya(saha,N);
            		hareket(saha,yedek,N,&undo);
            		printf("Undo sayiniz=%d",undo);
            		bitis = clock();
            		sure = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
            		printf("\nGecen sure: %.2d saniye\n", sure);
            		skorArtir(kullanicilar,kullanicisayisi,isim,&puan,r,N,sure,undo,&oyun);
            		sonucYaz(kullanicilar, kullanicisayisi);
            		oyun++;
            		break;   
			case 3:
				printf("\n3-Kullanici Skorlarini Goster\n");
				sonucYaz(kullanicilar, kullanicisayisi);
				break;	
		}
	}
	while (secenek!=0);    
    return 0;
}
