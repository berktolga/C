//Alt�n Kesit Arama Algortimas�
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

#define altin_oran 0.618

float f(float katsayilar[],int polinom_derece,float x){
	int i,derece_yedek=polinom_derece;
	float toplam=0;
	for(i=0;i<polinom_derece;i++){
		toplam+=katsayilar[i]*pow(x,derece_yedek);
		derece_yedek--;	
	}
	return toplam;
}

int main(){
	FILE *p;
	float *katsayilar;
		
	int i,polinom_derecesi;
	float epsilon;
	float a,b;
	float x1,x2,t1,t2;
	
	p=fopen("girdi.txt","r");
	if(p==NULL){
		printf("Dosya acilamadi");
		exit(0);
	}
	else{
		fscanf(p,"%d\n",&polinom_derecesi);
		
		katsayilar=(float*)malloc(polinom_derecesi*sizeof(float));
		
		for(i=0;i<polinom_derecesi;i++){
			fscanf(p,"%f\n",&katsayilar[i]);
		}
	
		fscanf(p,"%f\n",&epsilon);
		
		fscanf(p,"%f\n",&a);
		fscanf(p,"%f\n",&b);
		
	fclose(p);
	}
	
	for(i=0;i<polinom_derecesi;i++){
		katsayilar[i]*=(-1);
		/*
	    do while d�ng�s� i�erisindeki ko�ullar�n �al��abilmesi i�in,
		katsay�lar (-1) ile �arp�larak minimizasyondan maksimizisazyona �evrildi.
		*/
	}

	p=fopen("cikti.txt","w");
	if(p==NULL){
		printf("Dosya acilamadi");
		exit(0);
	}

	fprintf(p,"%4.3f  %4.3f\n",a,b);
	
	do{
		x1=b-(altin_oran*(b-a));
		x2=a+(altin_oran*(b-a));
		
		//x1 ve x2, f fonksiyonuna g�nderilerek fonksiyon de�erleri hesaplan�yor.
		t1=f(katsayilar,polinom_derecesi,x1);
		t2=f(katsayilar,polinom_derecesi,x2);
		//t1 ve t2, f'ten d�nen x1 ve x2'nin fonksiyon de�erlerini tutuyor.
		
		if(t1 < t2){
			a=x1;//t1 t2'den k���kse yeni aral���n a de�eri x1 olacak, b ayn� kalacak.
			x1=x2;//yeni x3 de�eri �nceki x2 de�erine e�it olacak.
			x2=a+(altin_oran*(b-a));//x4 de�eri yeniden hesaplanacak.
		}
		else{
			b=x2;//t1 t2'den b�y�k veya e�itse yeni aral���n b de�eri x2 olacak, a ayn� kalacak.
			x2=x1;//yeni x4 de�eri �nceki x1 de�erine e�it olacak.
			x1=b-(altin_oran*(b-a));//x3 de�eri yeniden hesaplanacak.
		}
		
		fprintf(p,"%4.3f  %4.3f\n",a,b);

	}while((b - a) > epsilon );
	
	fclose(p);	
	
	return 0;
}
