#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct plaka{
	char harf_kod[4];
	int sayi_kod;
};
struct sehir{
	int adet;
	struct plaka *plakakodlar;//alt diziyi tutan adres(*plakakodlar)
}sehirler[82];//ana dizi

void plaka_ekleme(){
	int plaka_kod;
	char harf_kod[4];
	int sayi_kod;
	int j,flag=1;
	static int x,y;
	static int i;
	sehirler[plaka_kod].adet=0;
		
	printf("Plakayi giriniz:");
	scanf("%d%s%d",&plaka_kod,harf_kod,&sayi_kod);
	
	struct plaka *p_plaka_kod;
	
	if(sehirler[plaka_kod].plakakodlar==NULL){
		p_plaka_kod=(struct plaka*)calloc(1,sizeof(struct plaka));
		sehirler[plaka_kod].plakakodlar=p_plaka_kod;// plaka_kod icin bir dizi oluþtu.
		
		if((strlen(harf_kod)<4&& strlen(harf_kod)>=2) && (9<sayi_kod && sayi_kod<10000) && plaka_kod>=0 && plaka_kod<82 ){
			for(i=0;i<1;i++){
			strcpy(sehirler[plaka_kod].plakakodlar[i].harf_kod,harf_kod);
			sehirler[plaka_kod].plakakodlar[i].sayi_kod=sayi_kod;	
			}
			sehirler[plaka_kod].adet++;
			printf("Kayit islemi gerceklesti.\n");
			printf("if teki sehir plaka adedi:%d",sehirler[plaka_kod].adet);
			}
		else
			printf("Girilen plaka gecerli degil.\n");
	}
		
	else{
		p_plaka_kod=(struct plaka*)realloc(p_plaka_kod,1*sizeof(struct plaka));
		for(y=1;y<81;y++){
			for(x=0;x<sehirler[y].adet;x++){
			if( (strcmp(sehirler[y].plakakodlar[x].harf_kod,harf_kod) == 0 )&&(sehirler[y].plakakodlar[x].sayi_kod==sayi_kod)){
				flag=0;
				break;
			}	
			}}
		if(flag==0){
			printf("Girilen plaka daha once kaydedilmistir.\n");
		}
		else{
				if((strlen(harf_kod)<4&& strlen(harf_kod)>=2) && (9<sayi_kod && sayi_kod<10000) && plaka_kod>=0 && plaka_kod<82){	
					for(;i<sehirler[plaka_kod].adet+1;i++){
						strcpy(sehirler[plaka_kod].plakakodlar[i].harf_kod,harf_kod);
						sehirler[plaka_kod].plakakodlar[i].sayi_kod=sayi_kod;
						}
						sehirler[plaka_kod].adet++;
						printf("Kayit islemi gerceklesti.\n");
						printf("else teki sehir plaka adedi:%d",sehirler[plaka_kod].adet);
					}
				else
					printf("Girilen plaka gecerli degil.\n");					
			}				
	}
}

void sehre_gore_listele(){
	FILE *d1;
	int plaka;
	int i;
	char cevap;
	
	printf("Hangi sehrin plakalarini listelemek istiyorsunuz:");
	scanf("%d",&plaka);
	if(plaka==0){
		printf("Toplam %d tane plaka kaydedilmistir.\n\n",sehirler[0].adet);
	}
	else{
		printf("%d Nolu Sehre Ait Plakalar\n",plaka);
		for(i=0;i<sehirler[plaka].adet;i++){
		printf("%d) %d %s %d\n\n",i+1,plaka,sehirler[plaka].plakakodlar[i].harf_kod,sehirler[plaka].plakakodlar[i].sayi_kod);
		}
	}
	char a[20]="plakalar_";//taným
	char b[4]="";//ýnt to strýng ýcýn bos strýng
	 itoa(plaka,b,10);//dondurme ýstemý
	 strcat(a,b);//býrlestýrm
	 strcat(a,".txt");//býrlestýrme
	printf("Bilgileri dosyaya yazdirmak istiyor musunuz?(E/H):\n");
	getchar();
	cevap=getchar();
	d1=fopen(a,"w");//elde edýlen strýng ýcýn dosya olusturma :)
	if(cevap=='E'||cevap=='e'){	
		if(d1==NULL){
			printf("Dosya yazdirma icin acilamadi");
		}
		else{
			for(i=0;i<sehirler[plaka].adet;i++){
			fprintf(d1,"%d%s%d\n",plaka,sehirler[plaka].plakakodlar[i].harf_kod,sehirler[plaka].plakakodlar[i].sayi_kod);
			}
			fclose(d1);
		}	
	}		
}

void tum_plaka_listele(){
	int i,j,sayac=0;
	FILE *d4;
	char cevap2;
	printf("Kayitli Tum Plakalar\n");
	for(j=1;j<81;j++){
		for(i=0;i<sehirler[j].adet;i++){
		printf("%d %s %d\n\n",j,sehirler[j].plakakodlar[i].harf_kod,sehirler[j].plakakodlar[i].sayi_kod);
		sayac++;
		}
	}
	sehirler[0].adet=sayac;
	
	printf("Bilgileri dosyaya yazdirmak istiyor musunuz?(E/H):\n");
	getchar();
	cevap2=getchar();

	if(cevap2=='E'||cevap2=='e'){	
		if((d4=fopen("plakalar.txt","w"))==NULL){
			printf("Dosya yazdirma icin acilamadi");
		}
		else{
			for(j=1;j<81;j++){
			for(i=0;i<sehirler[j].adet;i++){
			fprintf(d4,"%d%s%d\n\n",j,sehirler[j].plakakodlar[i].harf_kod,sehirler[j].plakakodlar[i].sayi_kod);
			}
		}
		fclose(d4);	
		}		
	}
}

void plaka_bilgileri_dosya_okuma(){
	//ikili dosya okuma
	static int i;
	int j;
	FILE *d3;
  	if((d3=fopen("hedef.bin","rb"))==NULL)
		printf("Dosya acilamadi(okuma)\n");
	else{
		
		for(j=1;j<82;j++){
			fread(&sehirler[j].adet,sizeof(int),1,d3);
			//if(j==0)
			//	continue;
		sehirler[j].plakakodlar=(struct plaka *)malloc(sehirler[j].adet*sizeof(struct plaka));	
		for(i=0;i<sehirler[j].adet;i++){
			fread(&sehirler[j].plakakodlar[i],sizeof(struct plaka),1,d3);
		}}
	fclose(d3);
	}
}

void plaka_bilgileri_dosya_yazma(){
	//ikili dosya yazma
	static int i;
	int j;
	FILE *d2;
	
	if((d2=fopen("hedef.bin","wb"))==NULL)
		printf("Dosya acilamadi(yazma)\n");
	else{
		for(j=1;j<82;j++){
			fwrite(&sehirler[j].adet,sizeof(int),1,d2);
		//	if(j==0)
		//		continue;
		for(i=0;i<sehirler[j].adet;i++){
			fwrite(&sehirler[j].plakakodlar[i],sizeof(struct plaka),1,d2);
		
		}}
		fclose(d2);
	}
	
}

void plaka_gecerliligi(){

	
}

int main(){
	int n;
	FILE *p;
	p=fopen("hedef.bin","rb");
	if(!p){
		
	}
	else{
	
		plaka_bilgileri_dosya_okuma();
	}
	printf("\t\t\t\t\tPLAKA KAYIT PROGRAMI\n");
	do{
		printf("\nYapacaginiz Islemi Seciniz:\n");
		printf("--Yeni plaka girisi icin (1)'e \n"
		"--Tum plakalari listelenmesi icin (2)'ye \n"
		"--Sehir plaka kodu girerek sadece sehirdeki plakalari listelemek icin (3)'e\n"
		"--Programi kapatmak icin (0)'a basiniz.\n");
		scanf("%d",&n);
		
		if(n==1){
			plaka_ekleme();		
		}
		
		else if(n==2){
			tum_plaka_listele();
		}
		else if(n==3){
			sehre_gore_listele();
		}
		else if(n==0){
			plaka_bilgileri_dosya_yazma();
		}
		else{
			printf("Secilen islem gecersiz!");
		}
		
	}while(n!=0);
}
