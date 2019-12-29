#include<stdio.h>
#include<stdlib.h>
typedef struct esir{
	int num;
	struct esir *sonraki;
	struct esir *onceki;
}esir;

esir *bas = NULL,*son=NULL;

int esir_sayisi=5;
int vezir=7;

ekle(int n){
	esir *yeni=malloc(sizeof(esir));
	yeni->num=n;
	yeni->sonraki=NULL;
	if(bas==NULL){
		bas=yeni;
		son=yeni;
		yeni->onceki=NULL;	
	} 
	else{
		yeni->onceki=son;
		son->sonraki=yeni;
		son=yeni;
	}
}

goster(){
	if(bas==NULL) printf("Liste bos\n");
	else{
		esir *temp = bas;
		while(temp != NULL){
			printf(" %d -> ",temp->num);
			temp = temp->sonraki;
		}
		printf("\n\n");
	}
}

oldur(){
	int kalan=esir_sayisi;
	esir *d=bas,*prev=NULL,*prev2=NULL;
	while(kalan>1){//Tek bir esir kalana kadar döngü devam edecek.
		int i;
		for(i=1;i<=vezir;i++){//Vezirin söylediği sayı kadar sayacak.
			prev2=prev;//Silme işlemi için silinenden öncekini tutmamız gerekir.
			prev=d;
			d=d->sonraki;
			
			if(prev->sonraki==NULL){//Eğer son sayıya geldiyse
				d=bas;//saymaya bastan devam edecek.
			} 
		}
		printf(" %d numarali esir oldu...\n",prev->num);
		
		//Ölen esirin bağlı listeden çıkarılması
		if(prev->sonraki!=NULL)//Eğer esir arada ise
			prev2->sonraki=prev->sonraki;
		else if(prev->sonraki==NULL){//Esir sonda ise 
			prev2->sonraki=NULL;
		}
		else//Esir başta ise
			prev=prev->sonraki;
		kalan--;
	}
	printf("\n");
	printf(" Yasayan = %d numarali esir",d->num);
}

int main(){
	int i;
	for(i=1;i<=esir_sayisi;i++){
		ekle(i);
	}
	goster();
	oldur();

return 0;
}
